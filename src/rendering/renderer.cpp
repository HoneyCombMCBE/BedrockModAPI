#include "bedrock/rendering/renderer.h"
#include <d2d1.h>
#include <vector>

namespace Bedrock {
namespace Rendering {

// Vertex structure for primitives
struct Vertex {
    float x, y, z;
    float r, g, b, a;
};

// Simple vertex shader
static const char* g_vertexShaderSrc = R"(
struct VS_INPUT {
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT {
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT main(VS_INPUT input) {
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0f);
    output.color = input.color;
    return output;
}
)";

// Simple pixel shader
static const char* g_pixelShaderSrc = R"(
struct PS_INPUT {
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float4 main(PS_INPUT input) : SV_Target {
    return input.color;
}
)";

Renderer& Renderer::getInstance() {
    static Renderer instance;
    return instance;
}

bool Renderer::initialize(ID3D11Device* device, ID3D11DeviceContext* context) {
    if (initialized_) return true;
    if (!device || !context) return false;
    
    device_ = device;
    context_ = context;
    
    // Get screen size from back buffer
    ID3D11Texture2D* backBuffer = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    
    // Get swap chain from device
    // TODO: Get swap chain properly
    
    if (!createResources()) {
        shutdown();
        return false;
    }
    
    initialized_ = true;
    return true;
}

void Renderer::shutdown() {
    if (!initialized_) return;
    
    releaseResources();
    
    device_ = nullptr;
    context_ = nullptr;
    initialized_ = false;
}

bool Renderer::createResources() {
    HRESULT hr;
    
    // Create DirectWrite factory
    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&writeFactory_)
    );
    if (FAILED(hr)) return false;
    
    // Create text format
    hr = writeFactory_->CreateTextFormat(
        L"Arial",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        16.0f,
        L"en-us",
        &textFormat_
    );
    if (FAILED(hr)) return false;
    
    // Create D2D factory
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory_);
    if (FAILED(hr)) return false;
    
    // Create vertex buffer
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = sizeof(Vertex) * 10000; // Max 10000 vertices
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    
    hr = device_->CreateBuffer(&bufferDesc, nullptr, &vertexBuffer_);
    if (FAILED(hr)) return false;
    
    // Create blend state for transparency
    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
    hr = device_->CreateBlendState(&blendDesc, &blendState_);
    if (FAILED(hr)) return false;
    
    // TODO: Compile and create shaders
    // TODO: Create input layout
    
    return true;
}

void Renderer::releaseResources() {
    if (writeFactory_) writeFactory_->Release();
    if (textFormat_) textFormat_->Release();
    if (d2dFactory_) d2dFactory_->Release();
    if (d2dRenderTarget_) d2dRenderTarget_->Release();
    if (vertexBuffer_) vertexBuffer_->Release();
    if (vertexShader_) vertexShader_->Release();
    if (pixelShader_) pixelShader_->Release();
    if (inputLayout_) inputLayout_->Release();
    if (blendState_) blendState_->Release();
    if (renderTarget_) renderTarget_->Release();
    
    writeFactory_ = nullptr;
    textFormat_ = nullptr;
    d2dFactory_ = nullptr;
    d2dRenderTarget_ = nullptr;
    vertexBuffer_ = nullptr;
    vertexShader_ = nullptr;
    pixelShader_ = nullptr;
    inputLayout_ = nullptr;
    blendState_ = nullptr;
    renderTarget_ = nullptr;
}

void Renderer::beginFrame() {
    if (!initialized_) return;
    
    // Set blend state
    float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    context_->OMSetBlendState(blendState_, blendFactor, 0xffffffff);
}

void Renderer::endFrame() {
    if (!initialized_) return;
    
    // Restore default blend state
    context_->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void Renderer::drawText(const std::string& text, float x, float y, const Color& color, float scale) {
    if (!initialized_ || !d2dRenderTarget_) return;
    
    // Convert string to wstring
    std::wstring wtext(text.begin(), text.end());
    
    // Create brush
    ID2D1SolidColorBrush* brush = nullptr;
    d2dRenderTarget_->CreateSolidColorBrush(
        D2D1::ColorF(color.r, color.g, color.b, color.a),
        &brush
    );
    
    if (!brush) return;
    
    // Draw text
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 1000, y + 100);
    d2dRenderTarget_->DrawText(
        wtext.c_str(),
        wtext.length(),
        textFormat_,
        layoutRect,
        brush
    );
    
    brush->Release();
}

void Renderer::drawRect(float x, float y, float width, float height, const Color& color, bool filled) {
    if (!initialized_) return;
    
    // Convert screen coordinates to NDC
    float left = (x / screenSize_.x) * 2.0f - 1.0f;
    float top = 1.0f - (y / screenSize_.y) * 2.0f;
    float right = ((x + width) / screenSize_.x) * 2.0f - 1.0f;
    float bottom = 1.0f - ((y + height) / screenSize_.y) * 2.0f;
    
    std::vector<Vertex> vertices;
    
    if (filled) {
        // Two triangles for filled rect
        vertices = {
            { left, top, 0.0f, color.r, color.g, color.b, color.a },
            { right, top, 0.0f, color.r, color.g, color.b, color.a },
            { left, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { right, top, 0.0f, color.r, color.g, color.b, color.a },
            { right, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { left, bottom, 0.0f, color.r, color.g, color.b, color.a }
        };
    } else {
        // Four lines for outline
        vertices = {
            { left, top, 0.0f, color.r, color.g, color.b, color.a },
            { right, top, 0.0f, color.r, color.g, color.b, color.a },
            { right, top, 0.0f, color.r, color.g, color.b, color.a },
            { right, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { right, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { left, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { left, bottom, 0.0f, color.r, color.g, color.b, color.a },
            { left, top, 0.0f, color.r, color.g, color.b, color.a }
        };
    }
    
    // Update vertex buffer
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = context_->Map(vertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (SUCCEEDED(hr)) {
        memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(Vertex));
        context_->Unmap(vertexBuffer_, 0);
        
        // Draw
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
        context_->IASetPrimitiveTopology(filled ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST : D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        context_->Draw(vertices.size(), 0);
    }
}

void Renderer::drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness) {
    if (!initialized_) return;
    
    // Convert to NDC
    float startX = (x1 / screenSize_.x) * 2.0f - 1.0f;
    float startY = 1.0f - (y1 / screenSize_.y) * 2.0f;
    float endX = (x2 / screenSize_.x) * 2.0f - 1.0f;
    float endY = 1.0f - (y2 / screenSize_.y) * 2.0f;
    
    std::vector<Vertex> vertices = {
        { startX, startY, 0.0f, color.r, color.g, color.b, color.a },
        { endX, endY, 0.0f, color.r, color.g, color.b, color.a }
    };
    
    // Update vertex buffer
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = context_->Map(vertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (SUCCEEDED(hr)) {
        memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(Vertex));
        context_->Unmap(vertexBuffer_, 0);
        
        // Draw
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
        context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        context_->Draw(vertices.size(), 0);
    }
}

void Renderer::drawCircle(float x, float y, float radius, const Color& color, bool filled, int segments) {
    if (!initialized_) return;
    
    std::vector<Vertex> vertices;
    
    // Convert center to NDC
    float centerX = (x / screenSize_.x) * 2.0f - 1.0f;
    float centerY = 1.0f - (y / screenSize_.y) * 2.0f;
    float radiusX = radius / screenSize_.x * 2.0f;
    float radiusY = radius / screenSize_.y * 2.0f;
    
    if (filled) {
        // Triangle fan
        vertices.push_back({ centerX, centerY, 0.0f, color.r, color.g, color.b, color.a });
        
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 3.14159f * 2.0f;
            float px = centerX + cos(angle) * radiusX;
            float py = centerY + sin(angle) * radiusY;
            vertices.push_back({ px, py, 0.0f, color.r, color.g, color.b, color.a });
        }
    } else {
        // Line loop
        for (int i = 0; i < segments; i++) {
            float angle1 = (float)i / segments * 3.14159f * 2.0f;
            float angle2 = (float)(i + 1) / segments * 3.14159f * 2.0f;
            
            float px1 = centerX + cos(angle1) * radiusX;
            float py1 = centerY + sin(angle1) * radiusY;
            float px2 = centerX + cos(angle2) * radiusX;
            float py2 = centerY + sin(angle2) * radiusY;
            
            vertices.push_back({ px1, py1, 0.0f, color.r, color.g, color.b, color.a });
            vertices.push_back({ px2, py2, 0.0f, color.r, color.g, color.b, color.a });
        }
    }
    
    // Update vertex buffer and draw
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = context_->Map(vertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (SUCCEEDED(hr)) {
        memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(Vertex));
        context_->Unmap(vertexBuffer_, 0);
        
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
        context_->IASetPrimitiveTopology(filled ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST : D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        context_->Draw(vertices.size(), 0);
    }
}

} // namespace Rendering
} // namespace Bedrock
