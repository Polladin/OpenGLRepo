
file(GLOB COMMON_HEADER   		src/*.h)
file(GLOB COMMON_SRC      		src/*.cpp)

file(GLOB OPENGL_FILE      		src/opengl_files/*.c)

#
file(GLOB_RECURSE SHADERS_SRC	src/shaders/*.glsl)


# Sources
set(OPENGL_ENGINE_SRC 
					${COMMON_SRC} 
					${OPENGL_FILE}
)
         
# Common OpenGL functions		 
set(OPENGL_ENGINE_HEADER 
					${COMMON_HEADER} 
)
           

# Create folders in Visual Studio
source_group("src\\opengl_files"      		    FILES ${OPENGL_FILE})

source_group("header"               			FILES ${COMMON_HEADER})          
source_group("src"               				FILES ${COMMON_SRC})        

source_group("shaders" 							FILES ${SHADERS_SRC} )
                   