add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
  "../include/AIComponent.hpp" "AIComponent.cpp"
  "../include/Asteroid.hpp" "Asteroid.cpp"
  "../include/AsteroidsApp.hpp" "AsteroidsApp.cpp"
  "asteroids.cpp"
  "../include/Bullet.hpp" "Bullet.cpp"
  "../include/Colors.hpp"
  "../include/Enemy.hpp" "Enemy.cpp"
  "../include/Engine.hpp" "Engine.cpp"
  "../include/flags.hpp" "flags.cpp"
  "../include/GameOver.hpp" "GameOver.cpp"
  "../include/Gun.hpp" "Gun.cpp"
  "../include/Hyperdrive.hpp" "Hyperdrive.cpp"
  "../include/MainLevel.hpp" "MainLevel.cpp"
  "../include/PhysicsManager.hpp" "PhysicsManager.cpp"
  "../include/Player.hpp" "Player.cpp"
  "../include/ScoreManager.hpp" "ScoreManager.cpp"
  "../include/Ship.hpp" "Ship.cpp"
  "../include/TitleScreen.hpp" "TitleScreen.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "../include")
target_link_libraries(${PROJECT_NAME} PRIVATE asteroids_extern)
target_link_libraries(${PROJECT_NAME} PRIVATE utilityKnife)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
target_link_options(${PROJECT_NAME} PRIVATE $<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:-mwindows>)

set(is_CC "$<CXX_COMPILER_ID:Clang,AppleClang,GNU>")
set(is_MS "$<CXX_COMPILER_ID:MSVC>")
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<OR:${is_CC}>:-Wall>
	$<$<OR:${is_CC}>:-Wextra>
	$<$<OR:${is_CC}>:-Wsign-conversion>
	$<$<OR:${is_CC}>:-pedantic>
	$<$<OR:${is_CC}>:-std=c++20>
	$<$<OR:${is_CC}>:-Weffc++>
	$<${is_MS}:/W4>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/data/)
