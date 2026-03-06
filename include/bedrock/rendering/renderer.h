#pragma once

#include "../api.h"
#include <d3d11.h>
#include <dwrite.h>
#include <memory>
#include <string>

namespace Bedrock {
namespace Rendering {

// DirectX renderer for drawing text and primitives
class BEDROCK_API Renderer {
public:
    static Renderer& getInstance();
    
    // Initialize renderer with D3D11 device
    bool initialize(ID3D11Device* device, ID3D11DeviceContext* context);
    void shutdown();
    
    // Frame management
    void beginFrame();
    void endFrame();
    
    // Text rendering
    void drawText(const std::string& text, float x, float y, const Color& color, float scale = 1.0f);
    
    // Primitive rendering
    void drawRect(float x, float y, float width, float height, const Color& color, bool filled = true);
    void drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness = 1.0f);
    void drawCircle(float x, float y, float radius, const Color& color, bool filled = true, int segments = 32);
    
    // Screen info
    Vec2<float> getScreenSize() const { return screenSize_; }
    
private:
    Renderer() = default;
    ~Renderer() = default;
    
    bool createResources();
    void releaseResources();
    
    // DirectX resources
    ID3D11Device* device_ = nullptr;
    ID3D11DeviceContext* context_ = nullptr;
    ID3D11RenderTargetView* renderTarget_ = nullptr;
    
    // DirectWrite resources
    IDWriteFactory* writeFactory_ = nullptr;
    IDWriteTextFormat* textFormat_ = nullptr;
    ID2D1Factory* d2dFactory_ = nullptr;
    ID2D1RenderTarget* d2dRenderTarget_ = nullptr;
    
    // Vertex buffer for primitives
    ID3D11Buffer* vertexBuffer_ = nullptr;
    ID3D11VertexShader* vertexShader_ = nullptr;
    ID3D11PixelShader* pixelShader_ = nullptr;
    ID3D11InputLayout* inputLayout_ = nullptr;
    ID3D11BlendState* blendState_ = nullptr;
    
    Vec2<float> screenSize_;
    bool initialized_ = false;
};

} // namespace Rendering
} // namespace Bedrock
