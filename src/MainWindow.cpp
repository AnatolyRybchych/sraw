#include "MainWindow.hpp"
#include "App.hpp"

LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    case WM_SHOWWINDOW:{
        if(!lParam)
            break;
    }
    case WM_ERASEBKGND:{

    } return 1;
    case WM_KILLFOCUS:{
        Hide();
    }return 0;
    }
    if(currState != nullptr){
        return currState->WndProc(hWnd, msg, wParam, lParam);
    }
    else{
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


MainWindow::MainWindow(HINSTANCE hInstance, App &app)
    :Window(hInstance, L"WNDCLASS_MAINWINDOW", L"", 0, 0, 100, 100, WS_POPUP|WS_SYSMENU, nullptr, WS_EX_TOOLWINDOW | WS_EX_TOPMOST), app(app){
    dc = GetDC(GetHWnd());

    PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,  
		PFD_TYPE_RGBA,      
		32,                  
		0, 0, 0, 0, 0, 0,
		0,0,0,0, 0, 0, 0,
		24,                  
		8,                  
		0,                    
		PFD_MAIN_PLANE,
		0,0, 0, 0
	};
    SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd), &pfd);
    glRc = wglCreateContext(dc);
	wglMakeCurrent(dc, glRc);

    if(glewInit()) throw std::runtime_error("cannot load glew");
}

void MainWindow::ClearCurrentState() noexcept{
    windowStates.erase(std::find(windowStates.begin(), windowStates.end(), currState));
    currState = nullptr;
}

MainWindow::~MainWindow(){

}

void MainWindow::Show(){
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    HMONITOR monitor = MonitorFromPoint(cursorPos, MONITOR_DEFAULTTONEAREST);
    SetCurrState(monitor);

    ShowWindow(GetHWnd(), SW_SHOW);
    UpdateWindow(GetHWnd());
    SetFocus(GetHWnd());
}

void MainWindow::SetCurrState(HMONITOR monitor){
    for(auto state:windowStates){
        if(state->GetMonitor() == monitor){
            currState = state;
            return;
        }
    }

    currState = std::shared_ptr<MainWindowState>(new MainWindowState(*this, monitor, app));
    windowStates.push_back(currState);
}

void MainWindow::MakeCurrent() const noexcept{
    wglMakeCurrent(dc, glRc);
}
void MainWindow::SwapBuffers() const noexcept{
    ::SwapBuffers(dc);
}

void MainWindow::Hide() const noexcept{
    ShowWindow(GetHWnd(), SW_HIDE);
}
