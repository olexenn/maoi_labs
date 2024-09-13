#ifndef Gui_h
#define Gui_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>

enum LabState {
    LAB_1,
    LAB_2,
    LAB_3,
    LAB_4,
    LAB_5,
    LAB_6,
    LAB_7
};

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
    
    LabState m_labState = LAB_1;
    
    void ui_init();
    void draw();
    
    void drawLabSwitcher();
};

#endif
