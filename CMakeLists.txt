cmake_minimum_required(VERSION 3.20)
project(CasinoSimulator LANGUAGES CXX)

# C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ostrzeżenia kompilatora
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

# Znajdź SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found")
endif()

# Znajdź OpenGL
find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

# Znajdź GLEW
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found")
endif()

# Automatycznie znajdź pliki CPP w src i podfolderach
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Dodaj plik wykonywalny
add_executable(CasinoSimulator ${SOURCES})

# Dołącz nagłówki z katalogu include
target_include_directories(CasinoSimulator
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
)

# Podlinkuj SDL2 i OpenGL
target_link_libraries(CasinoSimulator
    PRIVATE
        SDL2::SDL2
        OpenGL::GL
        GLEW::GLEW
)

# Debug: wyświetl znalezione ścieżki
message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

