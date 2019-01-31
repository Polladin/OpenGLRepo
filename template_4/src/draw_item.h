#pragma once

#include <vector>
#include <array>

#include "glsl_functions.h"

static const std::array<float, 4> DEFAULT_COLOR{ 1.0f, 0.8f, 1.0f, 1.0f };


class DrawItem
{
public:

    enum class DrawType
    {
        UNKNOWN
        , LINE
        , LINE_LOOP
        , TRIANGLE
    };

public:

    void draw( GLuint program, GLuint VBO, GLint colorUniLocation ) const;

private:

    static GLenum convert_draw_type( DrawType type );

public:

    DrawType type { DrawType::UNKNOWN };

    std::array<float, 4> color = DEFAULT_COLOR;
    std::vector<float> dots;
};


class DrawRect : public DrawItem
{
public:
    DrawRect( std::pair<float, float> topLeft, std::pair<float, float> botRight );

};