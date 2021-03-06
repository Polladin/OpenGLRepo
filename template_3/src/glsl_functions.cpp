
#include "glsl_functions.h"

#include "SOIL.h"

#include <iostream>


static const bool IS_SHADER = true;
static const bool IS_PROGRAM = false;


std::string GLSLHelper::read_shader( const std::string & filename )
{
  std::ifstream ifs( filename.c_str() );
  std::string res;

  if ( !ifs )
  {
    throw std::string( "Failed to open shader source file" );
  }

  // get length
  ifs.seekg( 0, std::ifstream::end );
  long len{ ifs.tellg() };
  ifs.seekg( 0, std::ifstream::beg );

  if ( len <= 0 )
  {
    throw std::string( "Failed to read file with shader source" );
  }

  // allocate memory for shader
  res.resize( static_cast<unsigned long>( len ) + 1 );

  // read text
  ifs.read( &res[ 0 ], len );

  return res;
}


void check_compile_log( GLuint shader, bool is_shader )
{
  GLint success = 0;

  is_shader ? glGetShaderiv( shader, GL_COMPILE_STATUS, &success )
            : glGetProgramiv( shader, GL_LINK_STATUS, &success );

  if ( success == GL_FALSE )
  {
    GLint maxLength = 0;

    is_shader ? glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength )
              : glGetProgramiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog( maxLength );

    is_shader ? glGetShaderInfoLog( shader, maxLength, &maxLength, &errorLog[ 0 ] )
              : glGetProgramInfoLog( shader, maxLength, &maxLength, &errorLog[ 0 ] );

    std::cout << "ERROR " << ( is_shader ? "SHADER" : "PROGRAM" ) <<  " COMPILE : " << errorLog.data() << std::endl;
  }
}


GLuint GLSLHelper::compile_shader( GLenum shaderType, std::string shaderBody )
{
  GLuint shader = glCreateShader( shaderType );

  const char * src = &shaderBody[ 0 ];

  glShaderSource( shader, 1, &src, nullptr );
  glCompileShader( shader );

  check_compile_log( shader, IS_SHADER );

  return shader;
}


GLuint GLSLHelper::compile_program( const t_shader_descr & shadersDescription )
{
  GLuint program = glCreateProgram();
  std::vector< GLuint > compiledShader;

  compiledShader.reserve( shadersDescription.size() );

  for ( const auto & shaderDescr : shadersDescription )
  {
    // compile_shader( GLenum shaderType, std::string shaderBody )
    compiledShader.push_back( compile_shader( shaderDescr.first, shaderDescr.second ) );
    glAttachShader( program, compiledShader.back() );
  }

  glLinkProgram( program );

  check_compile_log( program, IS_PROGRAM );

  for ( auto & shader : compiledShader )
  {
    glDeleteShader( shader );
  }

  return program;
}


GLuint GLSLHelper::load_texture( std::string texturePath )
{
  GLuint texture;

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture ); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
  
  // Set the texture wrapping parameters
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
  
  // Set texture filtering parameters
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // Load image, create texture and generate mipmaps
  int width, height;
  unsigned char* image = SOIL_load_image( ( std::string( TEXTURE_FOLDER ) + texturePath ).c_str(), &width, &height, 0, SOIL_LOAD_RGB );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
  glGenerateMipmap( GL_TEXTURE_2D );

  SOIL_free_image_data( image );
  glBindTexture( GL_TEXTURE_2D, 0 ); // Unbind texture when done, so we won't accidentily mess up our texture.

  return texture;
}
