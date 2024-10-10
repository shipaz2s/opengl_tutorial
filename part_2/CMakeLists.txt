add_executable(part2 main.cpp
	${CMAKE_SOURCE_DIR}/include/shader.hpp
	${CMAKE_SOURCE_DIR}/src/shader.cpp)

target_include_directories(part2 PRIVATE ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_directories(part2 PRIVATE ${GLFW3_LIBRARIES_DIR} ${GLEW_LIBRARIES_DIR})

target_link_libraries(part2 opengl32.lib glfw3.dll glew32.dll)