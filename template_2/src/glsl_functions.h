#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS 1

#include "GL/gl3w.h""

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include <GLFW/glfw3.h>

class GLSLHelper
{
public:

  using t_shader_descr = std::vector< std::pair< GLenum, std::string > >;

public :

  static std::string read_shader( const std::string & filename );

  static GLuint compile_shader( GLenum shaderType, std::string shaderBody );

  static GLuint compile_program( const t_shader_descr & shadersDescription );
};



