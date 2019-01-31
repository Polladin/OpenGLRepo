
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "opengl_wrapper.h"

const float PI_2 = 6.28318530718f;

std::vector< float > generateCircle( std::size_t seed )
{
  std::vector< float > res;

  auto add_zero = [ &res ]()
  {
    for ( int i = 0; i < 3; ++i )
      res.push_back( 0.0f );
  };

  for ( std::size_t i = 0; i < seed; ++i )
  {
    // Add zero
    add_zero();

    // first point
    res.push_back( std::sin( i * PI_2 / seed ) ); // X
    res.push_back( std::cos( i * PI_2 / seed ) ); // Y
    res.push_back( 0.0f ); // Z

    // next step point
    res.push_back( std::sin( i * PI_2 / seed + PI_2 / seed ) ); // X
    res.push_back( std::cos( i * PI_2 / seed + PI_2 / seed ) ); // Y
    res.push_back( 0.0f ); // Z
  }

  return res;
}

const std::size_t CIRCLE_SEED = 20;

class CallBackOpenGLProcess
{
public:

  GLuint VAO;
  GLuint VBO;
  GLuint program;
  GLuint texture;

  CallBackOpenGLProcess( GLuint i_program )
    : program { i_program }
  {
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    // set active VAO
    glBindVertexArray( VAO );

    // generate data set with circle
    auto data = generateCircle( CIRCLE_SEED );

    // copy data to VBO
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, data.size() *  sizeof(data[0]), data.data(), GL_STATIC_DRAW );

    // initiate 0 layout
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
    glEnableVertexAttribArray( 0 );

    // load texture
    texture = GLSLHelper::load_texture("tex2.jpg");
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Draw w/o filling
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }

  ~CallBackOpenGLProcess()
  {
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
  }

  // Render function
  void callback()
  {
    glClearColor( 0.1, 0.1, 0.1, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( program );

    glDrawArrays( GL_TRIANGLES, 0, CIRCLE_SEED * 3 );
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