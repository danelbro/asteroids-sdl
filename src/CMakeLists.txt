add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
  AIComponent.hpp AIComponent.cpp
  Asteroid.hpp Asteroid.cpp
  AsteroidsApp.hpp AsteroidsApp.cpp
  asteroids.cpp
  Bullet.hpp Bullet.cpp
  Colors.hpp
  Enemy.hpp Enemy.cpp
  Engine.hpp Engine.cpp
  flags.hpp flags.cpp
  GameOver.hpp GameOver.cpp
  Gun.hpp Gun.cpp
  Hyperdrive.hpp Hyperdrive.cpp
  MainLevel.hpp MainLevel.cpp
  PhysicsManager.hpp PhysicsManager.cpp
  Player.hpp Player.cpp
  ScoreManager.hpp ScoreManager.cpp
  Ship.hpp Ship.cpp
  TitleScreen.hpp TitleScreen.cpp)
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
