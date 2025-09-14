# CMakeList.txt : CMake project for SDL_Game_2D, include source and define
# project specific logic here.
#

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(glm REQUIRED)

# Add source to this project's executable.
add_executable (SDL_Game_2D "SDL_Game_2D.cpp" "SDL_Game_2D.hpp"   "gameObject.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL_Game_2D PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SDL_Game_2D PRIVATE SDL3::SDL3 SDL3_image::SDL3_image glm::glm)

# TODO: Add tests and install targets if needed.
