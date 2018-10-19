
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "opengl_wrapper.h"


class CallBackOpenGLProcess
{
public:

  GLuint VAO;
  GLuint program;

  CallBackOpenGLProcess( GLuint i_program )
    : program { i_program }
  {
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    glPointSize( 20.0f );
  }

  ~CallBackOpenGLProcess()
  {
    glDeleteVertexArrays( 1, &VAO );
  }

  // Render function
  void callback()
  {
    float factor1 = (std::sin( glfwGetTime() ) + 1 ) / 2.0;
    float factor2 = (std::cos( glfwGetTime() ) + 1 ) / 2.0;
    float factor3 = (std::sin( glfwGetTime() * 0.5)) / 2.0;

    glClearColor( factor1, factor2, factor3, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( program );
    glDrawArrays( GL_POINTS, 0, 1 );
  }
};


int main()
{
  std::cout << "Remote OpenGL starting .." << std::endl;

  OpenGLWrapper openGLEngine;
  CallBackOpenGLProcess renderObject ( openGLEngine.get_program() );

  // Main Loop
  openGLEngine.process( [ &renderObject ](){ renderObject.callback(); } );
}