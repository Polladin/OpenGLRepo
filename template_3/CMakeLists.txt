include(sources.cmake)

cmake_minimum_required(VERSION 2.8)

project(Template_3)

#################### Definitions #################################

set (CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# Add predefined variables for:
#   - Shaders
#   - Textures
add_definitions(-DSRC_WITH_SHADERS="${PROJECT_SOURCE_DIR}/src/shaders/")
add_definitions(-DTEXTURE_FOLDER="${PROJECT_SOURCE_DIR}/textures/")


################### Import libs #####################################
# Import GLFW
set (GLFW_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/glfw3.lib)

# Import SOIL lib
set (SOIL_libs ${PROJECT_SOURCE_DIR}/import/libs/win64/lib/SOIL.lib)

# Imported lib
set(OPENGL_LIBRARIES opengl32)

set(IMPORTED_LIBS  ${GLFW_libs} ${OPENGL_LIBRARIES} ${SOIL_libs})

################## Include #############################################
set (Imported_include ${PROJECT_SOURCE_DIR}/import/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

################### Template 3 ##########################################

add_executable(template_3 ${OPENGL_ENGINE_SRC} ${OPENGL_ENGINE_HEADER} ${SHADERS_SRC} )
set_target_properties(template_3 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(template_3 PUBLIC ${Imported_include} )
                                            
target_link_libraries(template_3 ${IMPORTED_LIBS})
                                