/*
 * primitives.hpp
 *
 *  Created on: Nov 1, 2016
 *      Author: alex
 */

#pragma once

#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using t_vertext_arr = std::vector<GLfloat>;
using t_idx_arr     = std::vector<GLuint>;
using t_primitive   = std::pair<t_vertext_arr, t_idx_arr>;


const t_primitive PRIM_CAR_WHEEL =
{
    {
        0.0f,  0.0f,  0.0f,
        0.2f,  0.0f,  0.0f,
        0.2f, -0.2f,  0.0f,
        0.0f, -0.2f,  0.0f
    },
    {
       0, 1, 2,
       0, 2, 3
    }
};


const t_primitive PRIM_CAR_BACK =
{
    {
        0.0f,  0.0f,  0.0f,
        1.1f,  0.0f,  0.0f,
        1.1f, -0.7f,  0.0f,
        0.0f, -0.7f,  0.0f
    },
    {
        0, 1, 2,
        0, 2, 3
    }
};


const t_primitive PRIM_CAR_FRONT =
{
        {   // first part
            0.0f,  0.0f,  0.0f,
            0.38f,  0.0f,  0.0f,
            0.38f, -0.5f,  0.0f,
            0.0f,  -0.5f,  0.0f,

            // second part
            0.0f,  0.3f,  0.0f,
            0.0f,  0.0f,  0.0f,
            0.38f, 0.0f,  0.0f,

            // third part
            0.38f,  0.0f,  0.0f,
            0.38f, -0.5f,  0.0f,
            0.48f, -0.5f,  0.0f
        },
        {   // first part
            0, 1, 2,
            0, 2, 3,

            // second part
            4, 5, 6,

            // third part
            7, 8, 9
        }
};


void add_to_primitives(         t_primitive & scene
                        , const t_primitive & objToAdd
                        , GLfloat xOffset, GLfloat yOffset);

void scale_primitives(t_primitive & scene, GLfloat scale);

void move_primitives(t_primitive & scene, GLfloat xOffset, GLfloat yOffset);






