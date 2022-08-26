#pragma once


namespace Lia
{
    
    class Window
    {
    public:
    
        struct Settings
        {
            std::string Name;
            glm::ivec2 Resolution;
        };
    
        Window(const Settings& settings);
        ~Window();
    
    
        Window(Window&) = delete;
        Window& operator=(Window&) = delete;
    
        glm::vec2 GetDimensions() const { return mSettings.Resolution;}
    
        GLFWwindow* GetGLFWWindow() const { return mWindow; }
        bool IsActive() const { return !glfwWindowShouldClose(mWindow); }
    
    
    
    
    
        void UpdateInput();
    
    
        static void Init();
        static void DeInit();
    private:
        GLFWwindow* mWindow;
        Settings mSettings{};
        
        
    };
    
    
    void errorcallglfw(int ecode, const char* str);
}
