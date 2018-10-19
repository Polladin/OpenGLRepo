/*
 * main.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: alex
 */

#include <iostream>
#include <iomanip>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "glHelperFunction.hpp"
#include "primitives.hpp"

#include <cmath>

// Window dimensions
const GLuint  WIDTH  = 800
            , HEIGHT = 600;


/*
 * Add the primitive Car 1
 *
 */

std::unique_ptr<t_primitive> add_primitive_car_1()
{
    std::unique_ptr<t_primitive> carScene (new t_primitive());

    add_to_primitives(*carScene, PRIM_CAR_WHEEL, -0.6, -0.32);
    add_to_primitives(*carScene, PRIM_CAR_WHEEL,  0.4, -0.32);
    add_to_primitives(*carScene, PRIM_CAR_BACK,  -0.8, 0.4);
    add_to_primitives(*carScene, PRIM_CAR_FRONT, 0.32, 0.2);

    scale_primitives(*carScene, 0.5);
    move_primitives(*carScene, 0.3, 0.4);

    return carScene;
}






/*
 * The main function
 *
 */
int main()
{
    GLFWwindow* window = GlHelperFunction::init_gl_window(WIDTH, HEIGHT);

    GLuint shaderProgram = GlHelperFunction::get_shader_program();


    // test something
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


    // get unique ptr to the primitive
    auto carScene = add_primitive_car_1();

    // create vertex array object
    std::vector<GLuint> buffs;
    GLuint VAO = GlHelperFunction::get_vertex_array(carScene->first, carScene->second, buffs);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // main cycle
    while(!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.)
        // and call corresponding response functions
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // blink colors
        GLfloat timeValue = glfwGetTime();
        GLfloat redValue = (std::sin(timeValue) / 2) + 0.5;
        GLfloat greenValue = (std::sin(timeValue) / 4) + 0.5;
        GLfloat blueValue = (std::sin(timeValue) / 8) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        //
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, carScene->second.size(), GL_UNSIGNED_INT, 0);

        //
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }


    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(buffs.size(), buffs.data());

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}


