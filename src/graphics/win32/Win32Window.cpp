#include "graphics/win32/Win32Window.h"

std::unordered_map<HWND, std::queue<prism::Event>> eventMap;
// holds state of keys and mouse buttons, incrementing if != 0 for each time pollWindow is called
    // resets to 0 if key or mouse button released
    // sets to 0 if key or mouse button is pressed
    // possible with vector that keeps track of currently pressed ONLY, for optimization
std::unordered_map<HWND, std::unordered_map<prism::KeyId, int>> keyStateMap;
std::unordered_map<HWND, std::set<prism::KeyId>> heldKeysSet;
std::unordered_map<HWND, std::unordered_map<prism::MouseButton, int>> mouseButtonStateMap;
std::unordered_map<HWND, std::set<prism::MouseButton>> heldMouseButtonsSet;
long debugCounter = 0;
std::unordered_map<HWND, int> debugCounterMap;

float mouseEventPreviousX;
float mouseEventPreviousY;

prism::KeyId getKeyFromCode(WPARAM keyCode) {
    prism::KeyId key;

    switch (keyCode) {
        case 0x30: key = prism::KeyId::NUM0; break;
        case 0x31: key = prism::KeyId::NUM1; break;
        case 0x32: key = prism::KeyId::NUM2; break;
        case 0x33: key = prism::KeyId::NUM3; break;
        case 0x34: key = prism::KeyId::NUM4; break;
        case 0x35: key = prism::KeyId::NUM5; break;
        case 0x36: key = prism::KeyId::NUM6; break;
        case 0x37: key = prism::KeyId::NUM7; break;
        case 0x38: key = prism::KeyId::NUM8; break;
        case 0x39: key = prism::KeyId::NUM9; break;
        case 0x41: key = prism::KeyId::A; break;
        case 0x42: key = prism::KeyId::B; break;
        case 0x43: key = prism::KeyId::C; break;
        case 0x44: key = prism::KeyId::D; break;
        case 0x45: key = prism::KeyId::E; break;
        case 0x46: key = prism::KeyId::F; break;
        case 0x47: key = prism::KeyId::G; break;
        case 0x48: key = prism::KeyId::H; break;
        case 0x49: key = prism::KeyId::I; break;
        case 0x4a: key = prism::KeyId::J; break;
        case 0x4b: key = prism::KeyId::K; break;
        case 0x4c: key = prism::KeyId::L; break;
        case 0x4d: key = prism::KeyId::M; break;
        case 0x4e: key = prism::KeyId::N; break;
        case 0x4f: key = prism::KeyId::O; break;
        case 0x50: key = prism::KeyId::P; break;
        case 0x51: key = prism::KeyId::Q; break;
        case 0x52: key = prism::KeyId::R; break;
        case 0x53: key = prism::KeyId::S; break;
        case 0x54: key = prism::KeyId::T; break;
        case 0x55: key = prism::KeyId::U; break;
        case 0x56: key = prism::KeyId::V; break;
        case 0x57: key = prism::KeyId::W; break;
        case 0x58: key = prism::KeyId::X; break;
        case 0x59: key = prism::KeyId::Y; break;
        case 0x5a: key = prism::KeyId::Z; break;
        case VK_BACK: key = prism::KeyId::BACKSPACE; break;
        case VK_RETURN: key = prism::KeyId::RETURN; break;
        case VK_TAB: key = prism::KeyId::TAB; break;
        case VK_SPACE: key = prism::KeyId::SPACE; break;
        case VK_CAPITAL: key = prism::KeyId::CAPS; break;
        case VK_ESCAPE: key = prism::KeyId::ESC; break;
        case VK_SHIFT: key = prism::KeyId::L_SHIFT; break;
        case VK_LSHIFT: key = prism::KeyId::L_SHIFT; break;
        case VK_RSHIFT: key = prism::KeyId::R_SHIFT; break;
        case VK_CONTROL: key = prism::KeyId::L_CTRL; break;
        case VK_LCONTROL: key = prism::KeyId::L_CTRL; break;
        case VK_RCONTROL: key = prism::KeyId::R_CTRL; break;
        case VK_MENU: key = prism::KeyId::L_ALT; break;
        case VK_LMENU: key = prism::KeyId::L_ALT; break;
        case VK_RMENU: key = prism::KeyId::R_ALT; break;
        case VK_INSERT: key = prism::KeyId::INS; break;
        case VK_DELETE: key = prism::KeyId::DEL; break;
        case VK_PRIOR: key = prism::KeyId::PG_UP; break;
        case VK_NEXT: key = prism::KeyId::PG_DN; break;
        case VK_END: key = prism::KeyId::END; break;
        case VK_HELP: key = prism::KeyId::HELP; break;
        case VK_HOME: key = prism::KeyId::HOME; break;
        case VK_DECIMAL: key = prism::KeyId::NP_DECIMAL; break;
        case VK_MULTIPLY: key = prism::KeyId::NP_MULT; break;
        case VK_DIVIDE: key = prism::KeyId::NP_DIV; break;
        case VK_ADD: key = prism::KeyId::NP_PLUS; break;
        case VK_SUBTRACT: key = prism::KeyId::NP_MINUS; break;
        case VK_OEM_1: key = prism::KeyId::SEMICOLON; break;
        case VK_OEM_2: key = prism::KeyId::SLASH; break;
        case VK_OEM_3: key = prism::KeyId::GRAVE; break;
        case VK_OEM_4: key = prism::KeyId::L_SQ_BRACK; break;
        case VK_OEM_5: key = prism::KeyId::BACKSLASH; break;
        case VK_OEM_6: key = prism::KeyId::R_SQ_BRACK; break;
        case VK_OEM_7: key = prism::KeyId::QUOTE; break;
        case VK_OEM_COMMA: key = prism::KeyId::COMMA; break;
        case VK_OEM_PERIOD: key = prism::KeyId::PERIOD; break;
        case VK_OEM_MINUS: key = prism::KeyId::MINUS; break;
        case VK_OEM_PLUS: key = prism::KeyId::EQ; break;
        case VK_VOLUME_UP: key = prism::KeyId::VOL_UP; break;
        case VK_VOLUME_DOWN: key = prism::KeyId::VOL_DN; break;
        case VK_VOLUME_MUTE: key = prism::KeyId::MUTE; break;
        case VK_NUMPAD0: key = prism::KeyId::NP0; break;
        case VK_NUMPAD1: key = prism::KeyId::NP1; break;
        case VK_NUMPAD2: key = prism::KeyId::NP2; break;
        case VK_NUMPAD3: key = prism::KeyId::NP3; break;
        case VK_NUMPAD4: key = prism::KeyId::NP4; break;
        case VK_NUMPAD5: key = prism::KeyId::NP5; break;
        case VK_NUMPAD6: key = prism::KeyId::NP6; break;
        case VK_NUMPAD7: key = prism::KeyId::NP7; break;
        case VK_NUMPAD8: key = prism::KeyId::NP8; break;
        case VK_NUMPAD9: key = prism::KeyId::NP9; break;
        case VK_F1: key = prism::KeyId::F1; break;
        case VK_F2: key = prism::KeyId::F2; break;
        case VK_F3: key = prism::KeyId::F3; break;
        case VK_F4: key = prism::KeyId::F4; break;
        case VK_F5: key = prism::KeyId::F5; break;
        case VK_F6: key = prism::KeyId::F6; break;
        case VK_F7: key = prism::KeyId::F7; break;
        case VK_F8: key = prism::KeyId::F8; break;
        case VK_F9: key = prism::KeyId::F9; break;
        case VK_F10: key = prism::KeyId::F10; break;
        case VK_F11: key = prism::KeyId::F11; break;
        case VK_F12: key = prism::KeyId::F12; break;
        case VK_F13: key = prism::KeyId::F13; break;
        case VK_F14: key = prism::KeyId::F14; break;
        case VK_F15: key = prism::KeyId::F15; break;
        case VK_F16: key = prism::KeyId::F16; break;
        case VK_F17: key = prism::KeyId::F17; break;
        case VK_F18: key = prism::KeyId::F18; break;
        case VK_F19: key = prism::KeyId::F19; break;
        case VK_F20: key = prism::KeyId::F20; break;
        case VK_F21: key = prism::KeyId::F21; break;
        case VK_F22: key = prism::KeyId::F22; break;
        case VK_F23: key = prism::KeyId::F23; break;
        case VK_F24: key = prism::KeyId::F24; break;
        case VK_LEFT: key = prism::KeyId::ARR_L; break;
        case VK_RIGHT: key = prism::KeyId::ARR_R; break;
        case VK_DOWN: key = prism::KeyId::ARR_DN; break;
        case VK_UP: key = prism::KeyId::ARR_UP; break;
        default: key = prism::KeyId::UNKNWN;
    }
    return key;
}


/**
 * windows event callback function
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    
    static std::set<WPARAM> currentlyPressed{};

    // mouse location and other info from lParam, wParam, will only be used if applicable
    short mouseX = (short)LOWORD(lParam);
    short mouseY = (short)HIWORD(lParam);
    float wheelDelta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam));

    switch (uMsg) {
        case WM_SETFOCUS:
            // got focus
            eventMap[hwnd].push(prism::FocusEvent(prism::EventState::ON));
            break;
        case WM_KILLFOCUS:
            // lost focus
            eventMap[hwnd].push(prism::FocusEvent(prism::EventState::OFF));
            // reset key holds and add corresponding keyup messages
            keyStateMap[hwnd].clear();
            for (prism::KeyId keyId : heldKeysSet[hwnd]) {
                eventMap[hwnd].push(prism::KeyEvent(keyId, prism::EventState::UP));
            }
            heldKeysSet[hwnd].clear();
            // reset mouse holds and add corresponding mousebuttonup messages
            mouseButtonStateMap[hwnd].clear();
            POINT mousePoint;
            if (GetCursorPos(&mousePoint)) {
                for (prism::MouseButton mb : heldMouseButtonsSet[hwnd]) {
                    eventMap[hwnd].push(prism::MouseButtonEvent(mb, prism::EventState::UP, static_cast<short>(mousePoint.x), static_cast<short>(mousePoint.y)));
                }
            }
            heldMouseButtonsSet[hwnd].clear();
            break;
        case WM_CLOSE: 
            eventMap[hwnd].push(prism::ExitEvent());
            break;
        // keyboard events
        case WM_KEYDOWN:
        {
            prism::KeyId keyId = getKeyFromCode(wParam);
            if (!heldKeysSet[hwnd].contains(keyId)) {
                eventMap[hwnd].push(prism::KeyEvent(keyId, prism::EventState::DOWN));
                keyStateMap[hwnd][keyId] = 0;
                currentlyPressed.emplace(wParam);
                heldKeysSet[hwnd].emplace(keyId);
            }
            break;
        }
        case WM_KEYUP:
        {
            prism::KeyId keyId = getKeyFromCode(wParam);
            eventMap[hwnd].push(prism::KeyEvent(keyId, prism::EventState::UP));
            keyStateMap[hwnd][keyId] = 0;
            currentlyPressed.erase(wParam);
            heldKeysSet[hwnd].erase(keyId);
            break;
        }
        // mouse button events:
        case WM_LBUTTONDOWN:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::LEFT, prism::EventState::DOWN, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].emplace(prism::MouseButton::LEFT);
            mouseButtonStateMap[hwnd][prism::MouseButton::LEFT] = 0;
            break;
        case WM_LBUTTONUP:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::LEFT, prism::EventState::UP, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].erase(prism::MouseButton::LEFT);
            mouseButtonStateMap[hwnd][prism::MouseButton::LEFT] = 0;
            break;
        case WM_RBUTTONDOWN:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::RIGHT, prism::EventState::DOWN, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].emplace(prism::MouseButton::RIGHT);
            mouseButtonStateMap[hwnd][prism::MouseButton::RIGHT] = 0;
            break;
        case WM_RBUTTONUP:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::RIGHT, prism::EventState::UP, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].erase(prism::MouseButton::RIGHT);
            mouseButtonStateMap[hwnd][prism::MouseButton::RIGHT] = 0;
            break;
        case WM_MBUTTONDOWN:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MIDDLE, prism::EventState::DOWN, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].emplace(prism::MouseButton::MIDDLE);
            mouseButtonStateMap[hwnd][prism::MouseButton::MIDDLE] = 0;
            break;
        case WM_MBUTTONUP:
            eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MIDDLE, prism::EventState::UP, mouseX, mouseY));
            heldMouseButtonsSet[hwnd].erase(prism::MouseButton::MIDDLE);
            mouseButtonStateMap[hwnd][prism::MouseButton::MIDDLE] = 0;
            break;
        case WM_XBUTTONDOWN:
            if (wParam & MK_XBUTTON1) {
                eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MB4, prism::EventState::DOWN, mouseX, mouseY));
                heldMouseButtonsSet[hwnd].emplace(prism::MouseButton::MB4);
                mouseButtonStateMap[hwnd][prism::MouseButton::MB4] = 0;
            } else if (wParam & MK_XBUTTON2) {
                eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MB5, prism::EventState::DOWN, mouseX, mouseY));
                heldMouseButtonsSet[hwnd].emplace(prism::MouseButton::MB5);
                mouseButtonStateMap[hwnd][prism::MouseButton::MB5] = 0;
            }
            break;
        case WM_XBUTTONUP:
            if ((wParam >> 16) & XBUTTON1) {
                eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MB4, prism::EventState::UP, mouseX, mouseY));
                heldMouseButtonsSet[hwnd].erase(prism::MouseButton::MB4);
                mouseButtonStateMap[hwnd][prism::MouseButton::MB4] = 0;
            } else if ((wParam >> 16) & XBUTTON2) {
                eventMap[hwnd].push(prism::MouseButtonEvent(prism::MouseButton::MB5, prism::EventState::UP, mouseX, mouseY));
                heldMouseButtonsSet[hwnd].erase(prism::MouseButton::MB5);
                mouseButtonStateMap[hwnd][prism::MouseButton::MB5] = 0;
            }
            break;
        case WM_MOUSEWHEEL:
            eventMap[hwnd].push(prism::MouseScrollEvent(wheelDelta, mouseX, mouseY));
            break;
        case WM_INPUT: 
        // https://learn.microsoft.com/en-us/windows/win32/dxtecharts/taking-advantage-of-high-dpi-mouse-movement
        {
            UINT dwSize = sizeof(RAWINPUT);
            static BYTE lpb[sizeof(RAWINPUT)];

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

            RAWINPUT* raw = (RAWINPUT*)lpb;

            if (raw->header.dwType == RIM_TYPEMOUSE) 
            {
                int xPosRelative = raw->data.mouse.lLastX;
                int yPosRelative = raw->data.mouse.lLastY;

                eventMap[hwnd].push(prism::MouseMoveEvent(xPosRelative, yPosRelative, xPosRelative, yPosRelative));
            } 
            break;
        }
        default:
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
    }

    return result;
}

namespace prism {

Win32Window::Win32Window(std::string windowName, std::uint32_t width, std::uint32_t height)
    : Window(width, height),
    instance(),
    window(),
    hdc(),
    wc(),
    fullscreen(false) // for now, default is not fullscreen
{
    if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)) {
        if (GetLastError() == ERROR_ACCESS_DENIED) {
            Logger::warn("Win32Window::Win32Window", "Process DPI awareness already set, expected if more than 1 window created...");
        } else {
            Logger::error("Win32Window::Win32Window", "could not set process DPI awareness.");
            throw Exception("Win32Window: could not set process DPI awareness.");
        }
    }

    HINSTANCE hInstance = GetModuleHandle(NULL);
    instance = {hInstance, [this](HINSTANCE hInstance) {
            if(!UnregisterClass(wc.lpszClassName, hInstance)) {
                if (GetLastError() == ERROR_CLASS_HAS_WINDOWS) {
                    Logger::warn("Win32Window::hInstanceDestructor", "Unable to unregister window class, due to existing windows.");
                } else {
                    Logger::error("Win32Window::hInstanceDestructor", "Unable to unregister window class.");
                }
            } else {
                Logger::info("Win32Window::hInstanceDestructor", "Successfully unregistered window class.");
            }
            hInstance = NULL;
        }};

    // define default prism window class
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = "PrismDefaultWin32WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // no background needed
    wc.lpszMenuName = NULL; // no menu

    // register window class
    if (!RegisterClassA(&wc)) {
        if (GetLastError() == ERROR_CLASS_ALREADY_EXISTS) {
            Logger::warn("Win32Window::Win32Window", "class wc already exists, expected if more than 1 window created...");
        } else {
            Logger::error("Win32Window::Win32Window", "could not register class wc.");
            throw Exception("Win32Window: could not register class.");
        }
    } else {
        Logger::info("Win32Window::Win32Window", "successfully registered class wc.");
    }

    // attempt fullscreen if specified:
    DWORD dwExStyle, dwStyle;
    if (fullscreen) {
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = width;
        dmScreenSettings.dmPelsHeight = height;
        dmScreenSettings.dmBitsPerPel = 24; // number of bits to use for colour bit depth
        dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            if (MessageBox(NULL, "Could not use fullscreen. Use Windowed Mode Instead?", "Fullscreen Error", MB_YESNO|MB_ICONEXCLAMATION) == IDYES) {
                // use windowed mode
                fullscreen = false;
            } else {
                // exit program
                MessageBox(NULL, "Exiting...", "ERROR", MB_OK|MB_ICONSTOP);
                throw Exception("Win32Window: Could not enter fullscreen mode.");
            }
        }
    }
    if (fullscreen) {
        // still fullscreen?
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
        showWindowCursor(false);
    } else {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }

    // adjust window to set size
    RECT windowRect;
    windowRect.left = static_cast<long>(0);
    windowRect.right = static_cast<long>(width);
    windowRect.top = static_cast<long>(0);
    windowRect.bottom = static_cast<long>(height);
    if (!AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle)) {
        Logger::error("Win32Window::Win32Window", "could not adjust window rect");
        throw Exception("Win32Window: could not adjust window rect.");
    } else {
        Logger::info("Win32Window::Win32Window", "successfully set window size.");
    }

    // create window first, resize with dpi and scale after
    window = {CreateWindowExA(dwExStyle,
                                wc.lpszClassName,
                                windowName.c_str(),
                                dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                0, 0,                   // position of window
                                windowRect.right - windowRect.left,             // window width
                                windowRect.bottom - windowRect.top,             // window height
                                NULL,                                           // no parent window
                                NULL,                                           // no menu
                                wc.hInstance,
                                NULL                                            // don't pass anything to WM_CREATE
    ), [this](HWND hwnd) {
        if(!DestroyWindow(hwnd)) {
            Logger::error("Win32Window::HwndDestructor", "Unable to destroy window.");
        } else {
            Logger::info("Win32Window::HwndDestructor", "Successfully destroyed window.");
        }
    }};
    if (!window) {
        Logger::error("Win32Window::Win32Window", "could not create window");
        DWORD err = GetLastError();
        throw Exception("Win32Window: could not create window.");
    } else {
        Logger::info("Win32Window::Win32Window", "Successfully created window.");
    }

    // resize window with dpi and scale
    const int scWidth = GetSystemMetrics(SM_CXSCREEN);
    const int scHeight = GetSystemMetrics(SM_CYSCREEN);
    const std::uint32_t scale = getScreenScale();

    windowRect = {0};
    windowRect.left = static_cast<long>(0);
    windowRect.right = static_cast<long>(width * scale);
    windowRect.top = static_cast<long>(0);
    windowRect.bottom = static_cast<long>(height * scale);
    if (!AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle)) {
        Logger::error("Win32Window::Win32Window", "could not adjust window rect");
        throw Exception("Win32Window: could not adjust window rect.");
    } else {
        Logger::info("Win32Window::Win32Window", "successfully set window size.");
    }

    // check that the window size is scaled properly for dpi
    if (!SetWindowPos(
        window,
        window,
        windowRect.left + (scWidth / 2) - ((width * scale) / 2),
        windowRect.top + (scHeight / 2) - ((height * scale) / 2),
        windowRect.right - windowRect.left,
        windowRect.bottom  - windowRect.top,
        SWP_NOZORDER | SWP_NOACTIVATE
    )) {
        Logger::error("Win32Window::Win32Window", "incorrectly scaled window for DPI.");
        throw Exception("Win32Window: incorrectly scaled window for DPI.");
    } else {
        Logger::info("Win32Window::Win32Window", "successfully scaled window for DPI.");
    }

    hdc = {GetDC(window), [this](HDC dc) {
            if(!ReleaseDC(window, dc)) {
                Logger::error("Win32Window::HdcDestructor", "Unable to release DC.");
            } else {
                Logger::info("Win32Window::HdcDestructor", "Successfully released DC.");
            }
        }};
    if (!hdc) {
        Logger::error("Win32Window::Win32Window", "Unable to get DC.");
        throw Exception("Win32Window: Unable to get DC.");
    } else {
        Logger::info("Win32Window::Win32Window", "successfully got DC.");
    }

    // done, can show window
    ShowWindow(window, SW_SHOW);
    SetForegroundWindow(window);
    SetFocus(window);
    UpdateWindow(window);

    // everything good, register mouse for higher def mouse data
    // https://learn.microsoft.com/en-us/windows/win32/dxtecharts/taking-advantage-of-high-dpi-mouse-movement

#   ifndef HID_USAGE_PAGE_GENERIC
#       define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#   endif
#   ifndef HID_USAGE_GENERIC_MOUSE
#       define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#   endif

    RAWINPUTDEVICE rid[1];
    rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    rid[0].dwFlags = RIDEV_INPUTSINK;   
    rid[0].hwndTarget = window;
    RegisterRawInputDevices(rid, 1, sizeof(rid[0]));

}

void Win32Window::setCursorStyle() {

}

void Win32Window::showWindowCursor(bool shouldShow) {
    ShowCursor(shouldShow);
}

std::optional<Event> Win32Window::pollWindow() {
    //grabPrismFocus();
    MSG msg;
    while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) != 0) {
        // retrieve all windows messages
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    std::optional<Event> event;
    if (eventMap.find(window) != eventMap.end()) {
        if (!eventMap[window].empty()) {
            event = eventMap[window].front();
            eventMap[window].pop();
        }
    }

    // iterate to count number of ticks a key/mouse button is pressed
    for (prism::KeyId keyId : heldKeysSet[window]) {
        keyStateMap[window][keyId] += 1;
    }
    for (prism::MouseButton mb : heldMouseButtonsSet[window]) {
        mouseButtonStateMap[window][mb] += 1;
    }

    // interception of events (like focus events) before returning
    if (event.has_value() && event.value().getEventType() == EventType::FOCUS) {
        switch(event.value().getFocusEvent().value().state) {
        case EventState::ON:
            grabPrismFocus();
            hasPrismFocus = true;
            break;
        case EventState::OFF:
            hasPrismFocus = false;
            break;
        default:
            break;
        }
    }

    // TODO: allow user to register listeners and other functions to the window, which can be processed/called here
    // TODO: onWindowChangedSize function, needs to modify renderer renderpipeline etc

    return event;
}

HDC Win32Window::getDeviceContext() const {
    return hdc;
}

std::uint32_t Win32Window::getDpi() const {
    // based on HWND (window) DPI_AWARENESS:
    // DPI_AWARENESS_UNAWARE -> return 96
    // DPI_AWARENESS_SYSTEM_AWARE -> return system DPI
    // DPI_AWARENESS_PER_MONITOR_AWARE -> return DPI of monitor that has the window
    return GetDpiForWindow(window);
}

std::uint32_t Win32Window::getScreenScale() const {
    // default 100% scaling is 96dpi
    return static_cast<std::uint32_t>(std::ceil(static_cast<float>(getDpi() / 96.0f)));
}

Win32Window::~Win32Window() {
    if (fullscreen) {
        ChangeDisplaySettings(NULL, 0);
        showWindowCursor(true);
    }
}

}