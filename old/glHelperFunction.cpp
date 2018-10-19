/*
 * glHelperFunction.cpp
 *
 *  Created on: Nov 1, 2016
 *      Author: alex
 */

#include <iostream>

#include "glHelperFunction.hpp"


// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "color = ourColor;\n"
    "}\n\0";


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


GLFWwindow* GlHelperFunction::create_glfw_window(GLuint width, GLuint height)
{
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::terminate();
    }

    return window;
}

// initialize static variables
GLint  GlHelperFunction::success;
GLchar GlHelperFunction::infoLog[512];


GLFWwindow* GlHelperFunction::init_gl_window(GLuint width, GLuint height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = GlHelperFunction::create_glfw_window(width, height);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        std::terminate();
    }

    int fbsWidth, fbsHeight;
    glfwGetFramebufferSize(window, &fbsWidth, &fbsHeight);

    glViewport(0, 0, fbsWidth, fbsHeight);

    return window;
}


GLuint GlHelperFunction::create_vertex_shader()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compile time errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertexShader;
}


GLuint GlHelperFunction::create_fragment_shader()
{
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragmentShader;
}


GLuint GlHelperFunction::link_shaders(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}


GLuint GlHelperFunction::get_shader_program()
{
    // Build and compile our shader program
    GLuint vertexShader = GlHelperFunction::create_vertex_shader();

    // Fragment shader
    GLuint fragmentShader = GlHelperFunction::create_fragment_shader();

    // Link shaders
    GLuint shaderProgram = GlHelperFunction::link_shaders(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


GLuint GlHelperFunction::get_vertex_array(  t_vertext_arr & vertextArr
                                          , t_idx_arr & idxArr
                                          , std::vector<GLuint> & buffs )
{
    GLuint VAO;
    buffs.clear();
    buffs.resize(2);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(buffs.size(), buffs.data());

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, buffs[0]);
        glBufferData(GL_ARRAY_BUFFER, vertextArr.size() * sizeof(vertextArr[0]), vertextArr.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffs[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxArr.size() * sizeof(idxArr[0]), idxArr.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    return VAO;
}






