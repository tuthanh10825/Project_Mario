# CMakeList.txt : CMake project for Project_Mario, include source and define
# project specific logic here.
#
#adding all file in the src directories. 
# Add the executable
add_executable(game main.cpp "MovableBlock.h" "MovableBlock.cpp" "Hub.h" "Hub.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET game PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(game PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(TARGET game POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	${CMAKE_SOURCE_DIR}/assets 	${CMAKE_SOURCE_DIR}/map
	${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(game PRIVATE nlohmann_json::nlohmann_json)

target_sources(game PUBLIC "Enemy.h" "Enemy.cpp" "Pickup.h" "Pickup.cpp" "Projectitle.h" "Projectitle.cpp") 
target_sources(game PUBLIC "Animation.h" "Animation.cpp" "Utility.h" "Utility.cpp") 
target_sources(game PUBLIC "Application.cpp" "Application.h") 
target_sources(game PUBLIC "ID.h")
target_sources(game PUBLIC "MenuState.cpp" "MenuState.h")
target_sources(game PUBLIC "ResourceHolder.h")
target_sources(game PUBLIC "Character.h" "Character.cpp")  
target_sources(game PUBLIC "State.cpp" "State.h" "StateStack.cpp" "StateStack.h")
target_sources(game PUBLIC "GameState.h" "GameState.cpp" "SceneNode.h" "SceneNode.cpp" )
target_sources(game PUBLIC "Entity.h" "Entity.cpp")
target_sources(game PUBLIC "SpriteNode.h" "SpriteNode.cpp")
target_sources(game PUBLIC "World.h" "World.cpp")
target_sources(game PUBLIC "Command.h" "CommandQueue.h" "CommandQueue.cpp")
target_sources(game PUBLIC "Player.h" "Player.cpp")
target_sources(game PUBLIC "Block.h" "Block.cpp")
target_sources(game PUBLIC "PauseState.h" "PauseState.cpp" "LevelSelectState.h" "LevelSelectState.cpp" "Hub.h" "Hub.cpp")
