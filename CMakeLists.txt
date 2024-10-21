cmake_minimum_required(VERSION 3.15)
project(Starter C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)

add_executable(${PROJECT_NAME} Application.cpp)

# Copy to compile_commands.json for .clangd
add_custom_target(
    copy-compile-commands ALL
    DEPENDS
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    DEPENDS
    # Unlike "proper" targets like executables and libraries, 
    # custom command / target pairs will not set up source
    # file dependencies, so we need to list file explicitly here
    generate-compile-commands
    ${CMAKE_BINARY_DIR}/compile_commands.json
)

# Generate the compilation commands. Necessary so cmake knows where it came
# from and if for some reason you delete it.
add_custom_target(generate-compile-commands
    DEPENDS
        ${CMAKE_BINARY_DIR}/compile_commands.json
)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -B${CMAKE_BINARY_DIR} -S${CMAKE_SOURCE_DIR}
)

# This is used because if we do not have this users systems may give them a linked error with oldnames.lib
# Usage - used to suppress that lld-link error and use the defaulted linked .library
if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "/Z1" "/NOD")
# else()
#     target_compile_options(${PROJECT_NAME} PUBLIC "-fsanitize=address")
endif(MSVC)

# Libraries linking
find_package(glfw3 REQUIRED)
find_package(imguidocking REQUIRED)

target_link_libraries(${PROJECT_NAME}
    glfw
    imguidocking::imguidocking
)
