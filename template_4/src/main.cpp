
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "opengl_wrapper.h"

#include "draw_item.h"


std::vector<std::shared_ptr<DrawItem>> drawItems;

//DrawRect rect( { -0.5f, 0.5f }, { 0.5f, -0.5f } );

// Array 10x10
std::vector<std::vector<int>> pictureArr =
{
     { 0,0,0,0,0,0,0,0,0,0 }
    ,{ 0,1,1,1,1,0,0,0,1,0 }
    ,{ 0,1,0,0,0,0,0,0,1,0 }
    ,{ 0,1,0,0,0,0,0,0,1,0 }
    ,{ 0,1,1,1,1,0,0,0,1,0 }
    ,{ 0,0,0,0,1,0,0,0,1,0 }
    ,{ 0,0,0,0,1,0,0,0,1,0 }
    ,{ 0,0,0,0,1,0,0,0,1,0 }
    ,{ 0,1,1,1,1,0,0,0,1,0 }
    ,{ 0,0,0,0,0,0,0,0,0,0 }
};


std::vector<std::shared_ptr<DrawItem>> get_picture(const std::vector<std::vector<int>> & pic)
{
    std::vector<std::shared_ptr<DrawItem>> res;

    float width = 0.2f;

    for ( int i = 0; i < pic.size(); ++i )
    {
        for ( int j = 0; j < pic[ i ].size(); ++j )
        {
            if ( pic[ i ][ j ] == 0 )
                continue;

            res.emplace_back( std::make_shared<DrawRect>(  std::make_pair(-1.0f + j * width, 1.0f - i * width)
                                                         , std::make_pair( -1.0f + (j + 1)* width, 1.0f - (i + 1) * width ) ) );
        }
    }

    return res;
}


class CallBackOpenGLProcess
{
public:

    GLuint VAO;
    GLuint VBO;
    GLuint program;
    GLuint colorUniLocation;

    CallBackOpenGLProcess( GLuint i_program )
        : program { i_program }
    {
        drawItems = get_picture( pictureArr );

        glGenVertexArrays( 1, &VAO );
        glGenBuffers( 1, &VBO );

        // set active VAO
        glBindVertexArray( VAO );

        // Initialize VBO
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW );

        // initiate 0 layout
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
        glEnableVertexAttribArray( 0 );

        // color location in shader
        colorUniLocation = glGetUniformLocation( program, "color_in" );

        //Draw w/o filling
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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

        for ( const auto & el : drawItems )
            el->draw( program, VBO, colorUniLocation );
    }

};


/********************************************
*               MAIN
*********************************************/
int main()
{
  std::cout << "Remote OpenGL starting .." << std::endl;

  OpenGLWrapper openGLEngine;
  CallBackOpenGLProcess renderObject ( openGLEngine.get_program() );

  // Main Loop
  openGLEngine.process( [ &renderObject ](){ renderObject.callback(); } );
}