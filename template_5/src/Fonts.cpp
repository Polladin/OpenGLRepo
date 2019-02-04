
#include <string>
#include <iostream>

#include "Fonts.h"

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H


static const std::string FONT_VERTEX_SHARDER = "/font.vs.glsl";
static const std::string FONT_FRAGMENT_SHARDER = "/font.fs.glsl";

static const int WIDTH = 800;
static const int HEIGHT = 600;


Fonts::Fonts()
{
    // Set OpenGL options
    //glEnable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    GLSLHelper::t_shader_descr shaderDescrs =
    { { GL_VERTEX_SHADER, GLSLHelper::read_shader( std::string( SRC_WITH_SHADERS ) + FONT_VERTEX_SHARDER ) }
    ,{ GL_FRAGMENT_SHADER, GLSLHelper::read_shader( std::string( SRC_WITH_SHADERS ) + FONT_FRAGMENT_SHARDER ) } };

    program = GLSLHelper::compile_program( shaderDescrs );

    glUseProgram( program );

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if ( FT_Init_FreeType( &ft ) )
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    FT_Face face;
    if ( FT_New_Face( ft, FONTS_FOLDER"/arial.ttf", 0, &face ) )
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes( face, 0, 64 );

    // Disable byte-alignment restriction
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Load first 128 characters of ASCII set
    for ( GLubyte c = 0; c < 128; c++ )
    {
        // Load character glyph 
        if ( FT_Load_Char( face, c, FT_LOAD_RENDER ) )
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures( 1, &texture );
        glBindTexture( GL_TEXTURE_2D, texture );
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        // Now store character for later use
        Character character = {
            texture,
            { face->glyph->bitmap.width, face->glyph->bitmap.rows },
            { face->glyph->bitmap_left, face->glyph->bitmap_top },
            face->glyph->advance.x
        };
        Characters.insert( std::pair<GLchar, Character>( c, character ) );
    }

    glBindTexture( GL_TEXTURE_2D, 0 );
    // Destroy FreeType once we're finished
    FT_Done_Face( face );
    FT_Done_FreeType( ft );


    // Configure VAO/VBO for texture quads
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    // Bind buffers
    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );

    // Configure data flow
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 6 * 4, NULL, GL_DYNAMIC_DRAW );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 );

    // Unbind buffers
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

void Fonts::RenderText( std::string text, GLfloat x, GLfloat y, GLfloat scale, std::array<float, 3> color )
{
    // Activate corresponding render state	
    glUseProgram( program );

    glUniform3f( glGetUniformLocation( program, "textColor" ), color[0], color[1], color[2] );
    glActiveTexture( GL_TEXTURE0 );

    glBindVertexArray( VAO );

    // Iterate through all characters
    std::string::const_iterator c;
    for ( c = text.begin(); c != text.end(); c++ )
    {
        Character ch = Characters[ *c ];

        GLfloat xpos = x + ch.Bearing[0] * scale;
        GLfloat ypos = y - ( ch.Size[1] - ch.Bearing[1] ) * scale;
        //GLfloat ypos = y;

        GLfloat w = ch.Size[0] * scale;
        GLfloat h = ch.Size[1] * scale;
        // Update VBO for each character
        GLfloat vertices[ 6 ][ 4 ] = {
            { xpos,     ypos - h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos - h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos - h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture( GL_TEXTURE_2D, ch.TextureID );
        // Update content of VBO memory
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( vertices ), vertices ); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        // Render quad
        glDrawArrays( GL_TRIANGLES, 0, 6 );
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += ( ch.Advance >> 6 ) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray( 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glUseProgram( 0 );
}

