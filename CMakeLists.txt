cmake_minimum_required(VERSION 3.10.0)
project(AB_UNIT20 VERSION 0.1.0 LANGUAGES CXX)

set(lista_archivos
main.cpp
citaMedica.h
gestorArchivos.h
medico.h
paciente.h
reporte.h
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-pedantic -Wall -Wextra -std=gnu++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=gnu++17")

add_executable(AB_UNIT20 main.cpp)

install(TARGETS AB_UNIT20 RUNTIME DESTINATION binaries)

set(CMAKE_BUILD_TYPE Release)