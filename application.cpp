#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>
#include <array>
#include <vector>
#include <span>
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
        std::println("Could not load glad!!!");
        return -1;
    }

    // 1. Setting up hardcode shader as a string (this would be loaded as a file)
    std::string vertex_shader_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

    std::string frag_shader_src = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    // 2. loading, compiling, and linking those two shader sources
    uint32_t vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    auto vert_c_str = vertex_shader_src.c_str();
    glShaderSource(vertex_shader, 1, &vert_c_str, nullptr);
    glCompileShader(vertex_shader);

    // 3. Setting up the logs for when shader errors out for vertex shader
    int success;
    std::array<char, 512> info_log;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log.data());
        std::println("ERROR: Cannot load vertex shader!!!");
    }

    // 4. Setting up the logs for when shader errors out for fragment shader
    uint32_t fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    auto frag_c_str = frag_shader_src.c_str();
    glShaderSource(fragment_shader, 1, &frag_c_str, nullptr);
    glCompileShader(fragment_shader);

    // compiling the shader sources here
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, info_log.size(), nullptr, info_log.data());
        // std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::println("ERROR: Cannot load fragment shader!!!");
    }

    // opengl requires you create a program and link the shaders you compiled then linking them
    uint32_t shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // 7. Get status if attaching and linking the shaders were successful then delete them after they are loaded as not needed
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, info_log.size(), nullptr, info_log.data());
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // 5. load your vertices
    // opengl requires that you have your vertex buffer created with an ID
    // then a vertex array to handle vertices
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    std::span<float> vertices_span(vertices.begin(), vertices.end());
    uint32_t size_bytes = vertices_span.size_bytes();

    // 
    uint32_t vbo_id;
    uint32_t vao_id;
    glGenBuffers(1, &vbo_id);
    glGenVertexArrays(1, &vao_id);

    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, size_bytes, vertices_span.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.5f, 1.0f, 1.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shader_program);
        glBindVertexArray(vao_id); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
