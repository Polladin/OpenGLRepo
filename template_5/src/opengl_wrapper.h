#pragma once

#include <memory>


#include "glsl_functions.h"


using t_opengl_window = std::unique_ptr< GLFWwindow, decltype( &glfwDestroyWindow ) >;


class OpenGLWrapper
{
public:

  // Create window and default shader program
  OpenGLWrapper(  int width = 800 
                , int height = 600 
                , const char * name = "Remote OpenGL"
                , const std::string vertexShader = "/simple.vs.glsl"
                , const std::string fragmentShader = "/simple.fs.glsl" );

  // Main Loop
  void process( std::function<void( void )> callbackFunction );

  //------------------- Getters --------------------------
  GLuint get_program() { return program; }
  //----------------- END Getters ------------------------

  // Destructor
  ~OpenGLWrapper()
  { 
    glfwTerminate();
  }

private:

  // Return compiled shader program 
  GLuint compile_shader_program( const std::string & vertexShader, const std::string & fragmentShader );

  // Create a window
  void create_window( int width = 400, int height = 200, const char * name = "Remote OpenGL" );

private:
  
  // Default OpenGL window
  t_opengl_window window;

  // Default shader program
  GLuint program;

};