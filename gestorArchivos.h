#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "paciente.h"

class GestorArchivos {
public:
    void guardarDatosPacientes(const std::vector<Paciente*>& pacientes) {
        std::ofstream archivo("pacientes.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
            return;
        }

        for (auto paciente : pacientes) {
            archivo << paciente->getNombre() << "," << paciente->getID() << "\n";
        }

        archivo.close();
    }

    void recuperarDatosPacientes(std::vector<Paciente*>& pacientes) {
        std::ifstream archivo("pacientes.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
            return;
        }

        std::string nombre, ID;
        while (std::getline(archivo, nombre, ',') && std::getline(archivo, ID)) {
            pacientes.push_back(new Paciente(nombre, ID, ""));
        }

        archivo.close();
    }
};
