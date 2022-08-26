#include "Window.h"



namespace Lia
{

    Window::Window(const Settings& settings) 
        :mSettings(settings)
    {

            
        glfwSetErrorCallback(errorcallglfw);
    
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        
        mWindow = glfwCreateWindow(
            mSettings.Resolution.x, mSettings.Resolution.y,
            mSettings.Name.c_str(), nullptr, nullptr);
        
    
        glfwSetWindowUserPointer(mWindow, this);
    
    
    }
    
    
    
    
    Window::~Window() 
    {
        glfwDestroyWindow(mWindow);
    }
    
    
    void Window::UpdateInput() 
    {
        glfwPollEvents();    
    }
    
    void Window::Init()
    {
        if (!glfwInit())
        {
            LOG_CRITICAL("[GLFW]: INITIALIZATON FAILED, EXITING APPLICATION");
            exit(-1);
        };
    }
    
    void Window::DeInit()
    {
        glfwTerminate();
    }
    
    
    
    
    void errorcallglfw(int ecode, const char* str)
    {
        LOG_ERROR("[GLFW][CODE:{}]: {}", ecode, str);
    }
}
