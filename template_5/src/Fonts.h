#pragma once

#include <map>
#include <array>

#include "glsl_functions.h"


class Fonts
{
    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character 
    {
        GLuint              TextureID;  // ID handle of the glyph texture
        std::array<int, 2>  Size;       // Size of glyph
        std::array<int, 2>  Bearing;    // Offset from baseline to left/top of glyph
        GLuint              Advance;    // Horizontal offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;

public:

    Fonts();

    void RenderText( std::string text, GLfloat x, GLfloat y, GLfloat scale, std::array<float, 3> color );

private:

    GLuint program;

    GLuint VAO, VBO;
};