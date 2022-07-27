#pragma once
#include "../DrawingTool.hpp"
#include "../GlWrappers/Texture.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include <memory>

class EraserTool: public DrawingTool{
private:
    static constexpr float scaleIncrement = 0.1; 
    static constexpr float scaleMin = 0.004; 
    static constexpr float scaleMax = 1.0; 

    GLuint bg;
    std::unique_ptr<Texture> buffer;
    std::unique_ptr<Framebuffer> frameBuffer;
    
    GLuint prog;
    GLuint VBO;

    GLint vertex_pPos;
    GLint posPos;
    GLint viewportPos;
    GLint scalePos;
    GLint bgPos;

    bool isMouseDown = false;

    float scale = 0.02;

    int prevX;
    int prevY;

    void Erse(int x, int y) const noexcept;
    void ClearBuffer() const noexcept;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept override;
    virtual void OnDrawCommit() noexcept override;
    virtual void OnResize(int cx, int cy) noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
public:
    EraserTool(int cx, int cy, CommitHandler &commitHandler, GLuint bg) noexcept;

    ~EraserTool() noexcept;
};