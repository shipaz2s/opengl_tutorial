add_executable(part4 main.cpp
	${CMAKE_SOURCE_DIR}/include/shader.hpp
	${CMAKE_SOURCE_DIR}/src/shader.cpp
	${CMAKE_SOURCE_DIR}/include/camera_ext.hpp
	${CMAKE_SOURCE_DIR}/include/window.hpp
	${CMAKE_SOURCE_DIR}/src/window.cpp)

target_include_directories(part4 PRIVATE ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_directories(part4 PRIVATE ${GLFW3_LIBRARIES_DIR} ${GLEW_LIBRARIES_DIR} ${GLM_LIBRARIES_DIR})

target_link_libraries(part4 opengl32.lib glfw3.dll glew32.dll)