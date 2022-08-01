#include "Coords.hpp"

Coords::Coords(int viewportCx, int viewportCy) noexcept{
    this->viewportCx = viewportCx;
    this->viewportCy = viewportCy;
}

float Coords::GetXGl() const noexcept{
    return 2.0 * winX / (double)viewportCx  + 1.0;
}

float Coords::GetYGl() const noexcept{
    return 1.0 - 2.0 * winY / (double)viewportCy;
}

int Coords::GetXWindows() const noexcept{
    return winX;
}

int Coords::GetYWindows() const noexcept{
    return winY;
}

float Coords::GetXGlPixels() const noexcept{
    return winX;
}

float Coords::GetYGlPixels() const noexcept{
    return viewportCy - winY;
}

void Coords::SetXGl(float x) noexcept{
    winX = (x * 0.5 + 0.5) * viewportCx;
}

void Coords::SetYGl(float y) noexcept{
    winY = (1.0 - y * 0.5) * viewportCy;
}

void Coords::SetXWindows(int x) noexcept{
    winX = x;
}

void Coords::SetYWindows(int y) noexcept{
    winY = y;
}

void Coords::SetXGlPixels(float x) noexcept{
    winX = x;
}

void Coords::SetYGlPixels(float y) noexcept{
    winY = viewportCy - y;
}

void Coords::SetViewport(int cx, int cy) noexcept{
    viewportCx = cx;
    viewportCy = cy;
}
