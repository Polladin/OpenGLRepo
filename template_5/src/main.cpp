
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "opengl_wrapper.h"
#include "Fonts.h"


class CallBackOpenGLProcess
{
public:

  GLuint VAO;
  GLuint program;
  Fonts fonts;


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
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( program );

    glBindVertexArray( VAO );
    glDrawArrays( GL_POINTS, 0, 1 );
    glBindVertexArray( 0 );

    int maxNum = 20;

    for (int i = 0; i < maxNum; ++i )
        fonts.RenderText( std::to_string(i), -1.0f, 1.0f - 2.0f * i * ( 1.0f / maxNum ), 0.001f, { 1.0f, 0.8f, 0.2f } );
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