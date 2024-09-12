#include <glad/glad.h>
#include <imgui_internal.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES/gl2.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include "ui/Gui.h"

#include <iostream>

static void glfwErrorCallback(int error, const char *description)
{
    exit(1);
}

static std::string getExecutablePath()
{
#ifdef __APPLE__
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::string resultPath = path;
        return resultPath.substr(0, resultPath.find("maoi_labs"));
    }
    else {
        std::cout << "ERROR: Can't find executable" << std::endl;
        exit(1);
    }
#endif
}

Gui::Gui()
{
    float highDPIScaleFactor = 1.1;
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        exit(1);
    
    const char *glsl_version = "#version 150";
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    m_window = glfwCreateWindow(1280, 720, "MAOI LABS DUDNICK", NULL, NULL);
    if (m_window == NULL) exit(1);
    glfwSetWindowSizeLimits(m_window, 1080, 720, 2560, 1600);
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1); // vsync
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    
    ImGui::StyleColorsClassic();
    
    ImGuiStyle& style = ImGui::GetStyle();
    ImFontConfig cfg;
    cfg.OversampleH = cfg.OversampleV = 3;
    
    std::string fontFileName = getExecutablePath() + "/fonts/Montserrat-Regular.ttf";
    m_mainFont = io.Fonts->AddFontFromFileTTF(fontFileName.c_str(), 13.0f, &cfg);
    m_headerFont = io.Fonts->AddFontFromFileTTF(fontFileName.c_str(), 20.0f, &cfg);
    
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Gui::ui_init()
{}

void Gui::run()
{
    ImVec4 clearColor = ImVec4(0.392f, 0.584f, 0.929f, 1.00f);
    
    while(!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Test");
        ImGui::PushFont(m_headerFont);
        ImGui::Text("Hello");
        ImGui::PopFont();
        
        ImGui::End();
        
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }
}
