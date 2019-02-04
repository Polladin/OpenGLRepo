include(sources.cmake)

cmake_minimum_required(VERSION 2.8)

project(Template_5)

#################### Definitions #################################

set (CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# Add predefined variables for:
#   - Shaders
#   - Textures
add_definitions(-DSRC_WITH_SHADERS="${PROJECT_SOURCE_DIR}/src/shaders")
add_definitions(-DTEXTURE_FOLDER="${PROJECT_SOURCE_DIR}/textures")
add_definitions(-DFONTS_FOLDER="${PROJECT_SOURCE_DIR}/fonts")


################### Import libs #####################################
# Import GLFW
set (GLFW_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/glfw3.lib)
set(FreeTypesLibs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/freetype.lib
                  ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/libpng16.lib
                  ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/bz2.lib
                  ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/zlib.lib
#                  ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/glew32s.lib 
   )

# Imported lib
set(OPENGL_LIBRARIES opengl32)

set(IMPORTED_LIBS  ${GLFW_libs} ${OPENGL_LIBRARIES} ${FreeTypesLibs})

################## Include #############################################
set (Imported_include ${PROJECT_SOURCE_DIR}/import/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

################### Template 5 ##########################################

add_executable(template_5 ${OPENGL_ENGINE_SRC} ${OPENGL_ENGINE_HEADER} ${SHADERS_SRC} )
set_target_properties(template_5 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(template_5 PUBLIC ${Imported_include} )
                                            
target_link_libraries(template_5 ${IMPORTED_LIBS})
                                