cmake_minimum_required(VERSION 3.20)

# set the project name
project(OrionEngine)

include(FetchContent)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

FetchContent_Declare(
	glfw-stable
	GIT_REPOSITORY https://github.com/TripleCometAndy/glfw-stable
	GIT_TAG b43c122dd194d74996d76c574a46d4bc23d6c7b0
)

FetchContent_MakeAvailable(glfw-stable)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG efec5db081e3aad807d0731e172ac597f6a39447
)

FetchContent_MakeAvailable(glm)

add_library(OrionEngineLib)

target_include_directories(OrionEngineLib PUBLIC
    include
    src
)

target_link_libraries(OrionEngineLib glfw glm)

add_subdirectory(src)

# Don't pull tests in to whoever uses our library
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_executable(OrionEngine)

    target_include_directories(OrionEngine PUBLIC
        include
        src
    )

    target_sources(OrionEngine PRIVATE
        src/main.cpp
    )

    target_link_libraries(OrionEngine OrionEngineLib)

    enable_testing()
    add_subdirectory(test)
endif()