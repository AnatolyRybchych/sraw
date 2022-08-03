#include "LineTool.hpp"

void LineTool::DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept{
    GetBrush().DrawLine(mouseDownCoord.GetXWindows(), mouseDownCoord.GetYWindows(), mouseUpCoord.GetXWindows(), mouseUpCoord.GetYWindows());
}

LineTool::LineTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:PrimitiveTool(cx, cy, bg, state, brush){

}