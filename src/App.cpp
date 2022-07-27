#include "App.hpp"
#include "DrawImage.hpp"
#include "Tools/MouseHighlight.hpp"
#include <iostream>
#include "UnicodeWindows.hpp"
#include "paths.hpp"
#include "GlWrappers/RenderText.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

App::App(HINSTANCE hInstance){
    this->hInstance = hInstance;
}

int App::Run(){
    window = new MainWindow(hInstance, *this);
    GlobalWindowInput::Init(*this);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    DrawImage::Init();
    MouseHighlight::Init();
    RenderText::InitDefaultRenderer(FileArial);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return msg.wParam;
}

void App::QuitApp() noexcept{
    if(MessageBoxW(window->GetHWnd(), L"Exit?", L"", MB_OKCANCEL) == IDOK)
        PostQuitMessage(0);
    else HideWindow();
}

void App::HideWindow() noexcept{
    window->Hide();
}

void App::HideWindowAndResoreState() noexcept{
    HideWindow();
    window->ClearCurrentState();
}

void App::HideWindowSaveStateToFile() noexcept{
    HideWindow();
}

void App::HideWindowCopyStateToClipboard() noexcept{
    HideWindow();
}

bool App::OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept{
    static bool control = false;
    static bool win = false;

    if(args->vkCode == VK_ESCAPE){
        window->Hide();
        return true;
    }

    if(message == KeyboardMessages::KeyDown || message == KeyboardMessages::SysKeyDown){
        if(args->vkCode == VK_LCONTROL) control = true;
        else if(args->vkCode == VK_LWIN) win = true;
    }
    else if(message == KeyboardMessages::KeyUp || message == KeyboardMessages::SysKeyUp){
        if(args->vkCode == VK_LCONTROL) control = false;
        else if(args->vkCode == VK_LWIN) win = false;
    }

    if(control && win && (args->vkCode == VK_LCONTROL || args->vkCode == VK_LWIN)){
        if(IsWindowVisible(window->GetHWnd()))window ->Hide();
        else
            window->Show();
        win = false;
            control = false;
    }

    return true;
}
