// needs: pixelformatdescriptor
// ChoosePixelFormat(dc, pfd)
// SetPixelFormat(dc, pixelformat, pfd)
// gl create context command (wglCreateContext)
// gl make current command
// init openGL
    // gl commands (glClearColor, glClearDepth, glEnable(GL_DEPTH_TEST), glViewPort etc...)

#include "graphics/win32/Win32OpenglWindow.h"

#define DONT_MAKE_GL_EXTERN
#include "graphics/opengl/opengl.h"

#include "graphics/opengl/openglRenderer.h"

// function pointers that need to be resolved
typedef HGLRC WINAPI wglCreateContextAttribsARBFunc(HDC, HGLRC, const int *);
typedef BOOL WINAPI wglChoosePixelFormatARBFunc(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
typedef BOOL WINAPI wglSwapIntervalEXTFunc(int);
typedef GLubyte * WINAPI glGetStringiFunc(GLenum, GLuint);

wglCreateContextAttribsARBFunc *wglCreateContextAttribsARB;
wglChoosePixelFormatARBFunc *wglChoosePixelFormatARB;
wglSwapIntervalEXTFunc *wglSwapIntervalEXT;
glGetStringiFunc *glGetStringi;

#define RESOLVE_FUNCTION(_, NAME, ...) resolveGlFunction(NAME, #NAME);

namespace {
// only want these functions to be accessible from here

using AutoHGLRC = prism::AutoResource<HGLRC>;

template<class T>
void resolveGlFunction(T &func, const std::string &name) {
    const auto funcAddress = wglGetProcAddress(name.c_str());
    if (funcAddress == NULL) {
        prism::Logger::error("Win32OpenglWindow::resolveWglFunctions", "could not resolve gl function" + name);
        throw prism::Exception("Win32OpenglWindow: could not resolve gl function.");
    }
    if(funcAddress == 0 ||
        (funcAddress == (void*)0x1) || (funcAddress == (void*)0x2) || (funcAddress == (void*)0x3) ||
        (funcAddress == (void*)-1) )
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        void *p = (void *)GetProcAddress(module, name.c_str());
        func = reinterpret_cast<T>(p);
    } else {
        func = reinterpret_cast<T>(funcAddress);
    }
}

bool initOpenGlExtensions(HINSTANCE instance) {
    // dummy windowclass:
    WNDCLASSA dummyWc = {0};
    dummyWc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    dummyWc.lpfnWndProc = (WNDPROC) DefWindowProcA;
    dummyWc.hInstance = instance;
    dummyWc.lpszClassName = "PrismDummyWin32OpenGLWindowClass";
    // register dummy window class:
    if (!RegisterClassA(&dummyWc)) {
        if (GetLastError() == ERROR_CLASS_ALREADY_EXISTS) {
            prism::Logger::warn("Win32OpenglWindow::Win32OpenglWindow", "dummy wc already exists, expected if more than 1 window created...");
        } else {
            prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "could not register dummy wc.");
            throw prism::Exception("Win32OpenglWindow: could not register dummy window class.");
        }
    } else {
        prism::Logger::info("Win32OpenglWindow::Win32OpenglWindow", "successfully registered dummy wc.");
    }
    // create dummy window:
    prism::Win32OpenglWindow::AutoHwnd dummyHwnd = {CreateWindowExA(0,
                                dummyWc.lpszClassName,
                                "dummy window title",
                                0,
                                0, 0,                                           // position of window
                                0,                                              // window width
                                0,                                              // window height
                                NULL,                                           // no parent window
                                NULL,                                           // no menu
                                dummyWc.hInstance,
                                NULL                                            // don't pass anything to WM_CREATE
        ), [&dummyHwnd](HWND dummyHwnd) {
            if(!DestroyWindow(dummyHwnd)) {
                prism::Logger::error("Win32OpenglWindow::HwndDestructor", "Unable to destroy dummy window.");
            } else {
                prism::Logger::info("Win32OpenglWindow::HwndDestructor", "Successfully destroyed dummy window.");
            }
        }
    };
    if (!dummyHwnd) {
        prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "could not create dummy window");
        DWORD err = GetLastError();
        throw prism::Exception("Win32OpenglWindow: could not create dummy window.");
    } else {
        prism::Logger::info("Win32OpenglWindow::Win32OpenglWindow", "Successfully created dummy window.");
    }
    // create dummy dc:
    prism::Win32OpenglWindow::AutoHdc dummyHdc = {GetDC(dummyHwnd), [&dummyHwnd](HDC hdc) {
        if(!ReleaseDC(dummyHwnd, hdc)) {
            prism::Logger::error("Win32OpenglWindow::HdcDestructor", "Unable to release dummy DC.");
        } else {
            prism::Logger::info("Win32OpenglWindow::HdcDestructor", "Successfully released dummy DC.");
        }
    }};
    if (!dummyHdc) {
        prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Unable to get dummy DC.");
        throw prism::Exception("Win32OpenglWindow: Unable to get dummy DC.");
    } else {
        prism::Logger::info("Win32OpenglWindow::Win32OpenglWindow", "successfully got dummy DC.");
    }
    // pixel format:
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    // choose pixel format:
    int chosenPixelFormat = ChoosePixelFormat(dummyHdc, &pfd); 
    if (!chosenPixelFormat) {
        prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Unable to choose pixel format.");
        throw prism::Exception("Win32OpenglWindow: Unable to choose pixel format.");
    }
    if (!SetPixelFormat(dummyHdc, chosenPixelFormat, &pfd)) {
        prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Unable to set pixel format.");
        throw prism::Exception("Win32OpenglWindow: Unable to set pixel format.");
    }
    // gl context:
    AutoHGLRC dummyGlContext = {wglCreateContext(dummyHdc), 
        [&dummyGlContext](HGLRC hglrc) {
            if (!wglDeleteContext(hglrc)) {
                prism::Logger::error("Win32OpenglWindow::HGLRCDestructor", "Unable to destroy dummy gl context.");
            } else {
                prism::Logger::info("Win32OpenglWindow::HGLRCDestructor", "Successfully destroyed dummy gl context.");
            }
        }
    };
    // set current gl context:
    if (!wglMakeCurrent(dummyHdc, dummyGlContext)) {
        prism::Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Unable to set current gl context.");
        throw prism::Exception("Win32OpenglWindow: Unable to set current gl context.");
    }
    // resolve needed wgl functions for actual use
    resolveGlFunction(wglCreateContextAttribsARB, "wglCreateContextAttribsARB");
    resolveGlFunction(wglChoosePixelFormatARB, "wglChoosePixelFormatARB");
    resolveGlFunction(wglSwapIntervalEXT, "wglSwapIntervalEXT");
    resolveGlFunction(glGetStringi, "glGetStringi");

    // done
    wglMakeCurrent(dummyHdc, 0);

    return true;
}

void resolveAllOpenGlFunctions() {
    // depending on number of windows, this gets called more than once, so we can skip once all have already been resolved
    if (prismResolvedGLFunctions) return;
    LOOP_GL_DECL_FUNC(RESOLVE_FUNCTION);
    prismResolvedGLFunctions = true;
}

}

namespace prism {

Win32OpenglWindow::Win32OpenglWindow(std::string windowName, std::uint32_t width, std::uint32_t height) 
    : Win32Window(windowName, width, height)
{
    //https://stackoverflow.com/questions/45518843/initializing-opengl-without-libraries
    

    // resolve opengl extensions first with dummy window:
    if (!initOpenGlExtensions(instance)) {
        Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Failed to resolve required wgl functions");
        throw Exception("Win32OpenglWindow: Failed to resolve required wgl functions");
    }
    // can init openGL for real now:
    if (!initActualOpenGL(hdc)) {
        Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Failed to initialize opengl");
        throw Exception("Win32OpenglWindow: Failed to initialize opengl");
    }
    // gl sanity check
    GLint majVer = -1;
    GLint minVer = -1;
    glGetIntegerv(GL_MAJOR_VERSION, &majVer); 
    glGetIntegerv(GL_MINOR_VERSION, &minVer);
    if (majVer != PRISM_OPENGL_MAJOR_VERSION || minVer != PRISM_OPENGL_MINOR_VERSION) {
        Logger::error("Win32OpenglWindow::Win32OpenglWindow", "Sanity check failed, unexpected openGL version...");
    }   

    // resolve the rest of the opengl functions required by the engine
    resolveAllOpenGlFunctions();
    
    // set window renderer to openGL
    renderer = std::make_unique<OpenGLRenderer>(width, height);
}

void Win32OpenglWindow::removeContext() {
    if (!wglMakeCurrent(hdc, 0)) {
        prism::Logger::error("Win32OpenglWindow::removeContext", "Unable to set current gl context to null");
        throw prism::Exception("Win32OpenglWindow: Unable to set current gl context to null.");
    }
}

void Win32OpenglWindow::setContext() {
    // set context again (when this window needs to render in another thread that the one that created the window)
    if (!wglMakeCurrent(hdc, glContext)) {
        Logger::error("Win32OpenglWindow::setContext", "Failed to set current render context");
        throw Exception("Win32OpenglWindow: Failed to set current render context");
    }
}

bool Win32OpenglWindow::initActualOpenGL(HDC actualDc) {
    
    // assumes that initOpenGlExtensions successfully resolved wglChoosePixelFormatARB

// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
#   define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#   define WGL_ACCELERATION_ARB                      0x2003
#   define WGL_SUPPORT_OPENGL_ARB                    0x2010
#   define WGL_DOUBLE_BUFFER_ARB                     0x2011
#   define WGL_PIXEL_TYPE_ARB                        0x2013
#   define WGL_COLOR_BITS_ARB                        0x2014
#   define WGL_DEPTH_BITS_ARB                        0x2022
#   define WGL_STENCIL_BITS_ARB                      0x2023

#   define WGL_FULL_ACCELERATION_ARB                 0x2027
#   define WGL_TYPE_RGBA_ARB                         0x202B

    int pixelFormatAttributes[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    int pixel_format;
    UINT num_formats;
    wglChoosePixelFormatARB(actualDc, pixelFormatAttributes, 0, 1, &pixel_format, &num_formats);
    if (!num_formats) {
        prism::Logger::error("Win32OpenglWindow::initActualOpenGL", "Failed to choose the window's pixel format");
        throw prism::Exception("Win32OpenglWindow: Failed to choose the window's pixel format");
    }

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(actualDc, pixel_format, sizeof(pfd), &pfd);
    if (!SetPixelFormat(actualDc, pixel_format, &pfd)) {
        prism::Logger::error("Win32OpenglWindow::initActualOpenGL", "Failed to set the window's pixel format");
        throw prism::Exception("Win32OpenglWindow: Failed to set the window's pixel format");
    }

// https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
#   define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#   define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#   define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#   define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

    // using OpenGl 4.5
    int openGLAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, PRISM_OPENGL_MAJOR_VERSION,
        WGL_CONTEXT_MINOR_VERSION_ARB, PRISM_OPENGL_MINOR_VERSION,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    glContext = wglCreateContextAttribsARB(actualDc, 0, openGLAttributes);
    if (!glContext) {
        prism::Logger::error("Win32OpenglWindow::initActualOpenGL", "Failed to create OpenGL context");
        throw prism::Exception("Win32OpenglWindow: Failed to create OpenGL context");
    }

    if (!wglMakeCurrent(actualDc, glContext)) {
        prism::Logger::error("Win32OpenglWindow::initActualOpenGL", "Failed to set OpenGL context");
        throw prism::Exception("Win32OpenglWindow: Failed to set OpenGL context");
    }

    return true;
}

}