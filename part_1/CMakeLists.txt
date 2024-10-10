add_executable(part1 main.cpp)

target_include_directories(part1 PRIVATE ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
target_link_directories(part1 PRIVATE ${GLFW3_LIBRARIES_DIR} ${GLEW_LIBRARIES_DIR})

# target_link_libraries(first opengl32.lib glfw3.lib glew32s.lib)
target_link_libraries(part1 opengl32.lib glfw3.dll glew32.dll)