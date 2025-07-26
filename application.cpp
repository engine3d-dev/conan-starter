#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;


int main(){
    if(!glfwInit()){
        fmt::print("glfwInit could not be initialized!\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    int width = 800;
    int height = 600;
    std::string title = "Hello Window";
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Required to setup glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        
        glClearColor(0.5f, 1.0f, 1.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
    }
    return 0;
}
