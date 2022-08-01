#include "ConditionBlockDiagramTool.hpp"
#include "../ResourceProvider.hpp"

void ConditionBlockDiagramTool::DrawBg() const noexcept{
    bgDrawingProgram.Draw(
        GetCurrMPosX(), 
        GetCurrMPosY(), 
        GetTextWidth(),
        GetSettings().GetFontSize(),
        GetSettings().GetPalet().GetRed(),
        GetSettings().GetPalet().GetGreen(),
        GetSettings().GetPalet().GetBlue()
    );
}

void ConditionBlockDiagramTool::DrawTxt() const noexcept{
    RenderText::GetDefaultRenderer()->Render(
        GetText().c_str(), 
        0, 
        GetSettings().GetFontSize(), 
        GetCurrMPosX() - GetTextWidth() / 2, GetCurrMPosY() - GetSettings().GetFontSize() / 2, 
        GetSettings().GetPalet().GetRed(),
        GetSettings().GetPalet().GetGreen(),
        GetSettings().GetPalet().GetBlue(),
        false);
}

ConditionBlockDiagramTool::ConditionBlockDiagramTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, BlockDiagramSetting &settings):
BlockDiagramTool(cx, cy, commitHandler, bg, settings), bgDrawingProgram(ResourceProvider::GetProvider().GetDrawConditionDiagramBgProgram()){

}

int ConditionBlockDiagramTool::GetTextWidth() const noexcept{
    return RenderText::GetDefaultRenderer()->GetTextWidth(GetText().c_str(), 0, GetSettings().GetFontSize());;
}