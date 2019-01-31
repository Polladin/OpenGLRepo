

#include "draw_item.h"

/*************************************************************************
*                   Draw Item
**************************************************************************/


void DrawItem::draw( GLuint program, GLuint VBO, GLint colorUniLocation ) const
{
    glUseProgram( program );

    glUniform4fv( colorUniLocation, 1, color.data() );

    // copy data to VBO
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, dots.size() * sizeof( dots[ 0 ] ), dots.data(), GL_DYNAMIC_DRAW );

    // draw
    glDrawArrays( convert_draw_type( type ), 0, dots.size() / 3 );
}

GLenum DrawItem::convert_draw_type( DrawType type )
{
    switch ( type )
    {
    case DrawType::LINE:
        return GL_LINES;
    case DrawType::LINE_LOOP:
        return GL_LINE_LOOP;
    case DrawType::TRIANGLE:
        return GL_TRIANGLES;
    }

    throw std::string("Unknown type for draw object");
}

DrawRect::DrawRect( std::pair<float, float> topLeft, std::pair<float, float> botRight )
{
    type = DrawType::TRIANGLE;

    // Top Left
    dots.push_back( topLeft.first );
    dots.push_back( topLeft.second );
    dots.push_back( 0.0f );

    // Top Right
    dots.push_back( botRight.first );
    dots.push_back( topLeft.second );
    dots.push_back( 0.0f );

    // Bot Right
    dots.push_back( botRight.first );
    dots.push_back( botRight.second );
    dots.push_back( 0.0f );

    // Bot Right
    dots.push_back( botRight.first );
    dots.push_back( botRight.second );
    dots.push_back( 0.0f );

    // Bot Left
    dots.push_back( topLeft.first );
    dots.push_back( botRight.second );
    dots.push_back( 0.0f );

    // Top Left
    dots.push_back( topLeft.first );
    dots.push_back( topLeft.second );
    dots.push_back( 0.0f );
}
