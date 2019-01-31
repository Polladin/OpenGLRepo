
#include <string>
#include <chrono>
#include <thread>

#include "opengl_wrapper.h"


static void framebuffer_callback( GLFWwindow * window, int width, int height )
{
  glViewport( 0, 0, width, height );
}

static void process_input( GLFWwindow * window )
{
  if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS
    || glfwGetKey( window, GLFW_KEY_ENTER ) == GLFW_PRESS
    || glfwGetKey( window, GLFW_KEY_KP_ENTER ) == GLFW_PRESS )
  {
    glfwSetWindowShouldClose( window, true );
  }
}


//----------------------------- OpenGLWrapper -------------------------------

OpenGLWrapper::OpenGLWrapper( int width, int height, const char * name, const std::string vertexShader, const std::string fragmentShader )
  : window( nullptr, glfwDestroyWindow )
{
  // Init GLFW lib
  if ( glfwInit() == GLFW_FALSE )
  {
    throw std::string( "Failed to init GLFW" );
  }

  // Set Core version of OpenGL
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  // Create Window 
  create_window( width, height, name );

  // Init GL3W lib
  if ( gl3wInit() == -1 )
  {
    throw std::string( "Failed to init GL3W" );
  }

  // Coplile program
  program = compile_shader_program( vertexShader, fragmentShader );


  //glfwSetKeyCallback( window.get(), glfw_onKey );
}


GLuint OpenGLWrapper::compile_shader_program(const std::string & vertexShader, const std::string & fragmentShader)
{
  GLSLHelper::t_shader_descr shaderDescrs = 
  {  { GL_VERTEX_SHADER, GLSLHelper::read_shader( std::string( SRC_WITH_SHADERS ) + vertexShader ) }
   , { GL_FRAGMENT_SHADER, GLSLHelper::read_shader( std::string( SRC_WITH_SHADERS ) + fragmentShader ) } };

  return GLSLHelper::compile_program( shaderDescrs );
}


void OpenGLWrapper::process( std::function<void(void)> callbackFunction )
{
  while ( !glfwWindowShouldClose( window.get() ) )
  {
    process_input( window.get() );

    callbackFunction();

    glfwSwapBuffers( window.get() );
    glfwPollEvents();

    std::this_thread::sleep_for( std::chrono::microseconds( 16667 ) );
  }

}

void OpenGLWrapper::create_window( int width, int height, const char * name)
{
  window.reset( glfwCreateWindow( width, height, name, nullptr, nullptr ) );
  if ( !window )
  {
    throw std::string( "Failed to create window" );
  }

  glfwMakeContextCurrent( window.get() );
  glfwSetFramebufferSizeCallback( window.get(), framebuffer_callback );
}
