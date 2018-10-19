/*
 * glHelperFunction.hpp
 *
 *  Created on: Nov 1, 2016
 *      Author: alex
 */

#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "primitives.hpp"

class GlHelperFunction
{
public:

    static GLFWwindow* init_gl_window(GLuint width, GLuint height);

    static GLFWwindow* create_glfw_window(GLuint width, GLuint height);

    static GLuint create_vertex_shader();

    static GLuint create_fragment_shader();

    static GLuint link_shaders(GLuint vertexShader, GLuint fragmentShader);

    static GLuint get_shader_program();

    static GLuint get_vertex_array(   t_vertext_arr & vertextArr
                                    , t_idx_arr & idxArr
                                    , std::vector<GLuint> & buffs );

public:

    static GLint  success;
    static GLchar infoLog[512];
};
