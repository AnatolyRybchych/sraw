#include "BlockDiagramTool.hpp"
#include "../DrawDiagramBgProgram.hpp"

class InOutBlockDiagramTool: public BlockDiagramTool{
private:
    DrawDiagramBgProgram bgDrawingProgram;
protected:
    virtual void DrawBg() const noexcept override;
    virtual void DrawTxt() const noexcept override;
public:
    InOutBlockDiagramTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, BlockDiagramSetting &settings);

    virtual int GetTextWidth() const noexcept override;
};