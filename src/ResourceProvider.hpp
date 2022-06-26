#pragma once
#include <memory>
#include <string>
#include <glad/glad.h>

class ResourceProvider{
private:
    static std::unique_ptr<ResourceProvider> provider;
    ResourceProvider() noexcept;
public:
    static const ResourceProvider &GetProvider() noexcept;

    GLuint GetMouseHighlightIcon() const noexcept;
    GLuint GetBrushIcon() const noexcept;
    std::string GetMenuBgFragment() const noexcept;
    std::string GetMenuBgVertex() const noexcept;
    std::string GetDrawImageVertex() const noexcept;
    std::string GetDrawImageFragment() const noexcept;
    std::string GetMenuItemFragment() const noexcept;
    std::string GetMenuItemVertex() const noexcept;
};
