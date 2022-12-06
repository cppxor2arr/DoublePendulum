cmake_minimum_required(VERSION 3.20)
project(DoublePendulum VERSION 0.1.0 LANGUAGES CXX)

add_executable(DoublePendulum
    src/main.cpp
    src/double_pendulum.cpp
    src/double_pendulum_renderer.cpp
    src/input_handler.cpp
    src/vector2_operations.cpp)

target_compile_features(DoublePendulum PRIVATE cxx_std_17)
set_target_properties(DoublePendulum PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(DoublePendulum PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)

target_include_directories(DoublePendulum PRIVATE include)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(DoublePendulum PRIVATE sfml-graphics)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET DoublePendulum POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:DoublePendulum> $<TARGET_FILE_DIR:DoublePendulum> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS DoublePendulum)
