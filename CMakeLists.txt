cmake_minimum_required(VERSION 3.10.0)

project(CMake)

set(lista_archivos
main.cpp
citaMedica.h
gestorArchivos.h
medico.h
paciente.h
reporte.h
servicio.h
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-pendantic -Wall -Wextra -std=gnu++17")
set(CMAKE_CXX_FLAGS_RELEASE "-03 -std=gnu++17")

add_executable(prueba ${lista_archivos})

install(TARGETS prueba RUNTIME DESTINATION binaries)
