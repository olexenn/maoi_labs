#ifndef Gui_h
#define Gui_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>

class Gui
{
public:
    Gui();
    ~Gui();
    void run();
    
private:
    GLFWwindow *m_window;
    ImGuiStyle m_style;
    ImVec2 m_windowSize;
    ImVec2 m_cursorPos;
    
    ImFont *m_mainFont;
    ImFont *m_headerFont;
    
    void ui_init();
    void draw();
};

#endif
