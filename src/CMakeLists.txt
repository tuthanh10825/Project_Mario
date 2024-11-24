# CMakeList.txt : CMake project for Project_Mario, include source and define
# project specific logic here.
#
#adding all file in the src directories. 
file(GLOB_RECURSE SOURCES ENDF6_SRC 
	{PROJECT_SOURCE_DIR}/src/*.cpp
	{PROJECT_SOURCE_DIR/src/*.h
)
# Add source to this project's executable.
add_executable (game "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET game PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(game PRIVATE sfml-graphics)
