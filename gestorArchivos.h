#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "paciente.h"
#include "medico.h"
#include "servicio.h"

class GestorArchivos {
public:
    void guardarDatosPacientes(const std::vector<Paciente*>& pacientes) {
        std::ofstream archivo("pacientes.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los pacientes." << std::endl;
            return;
        }

        for (Paciente* paciente : pacientes) {
            archivo << "Nombre: " << paciente->getNombre() << "\n";
            archivo << "ID: " << paciente->getID() << "\n";
            archivo << "Fecha de ingreso: " << paciente->getFechaIngreso() << "\n\n";
        }

        archivo.close();
    }

    // Función para recuperar los datos de los pacientes
void recuperarDatosPacientes(std::vector<Paciente*>& pacientes) {
    std::ifstream archivo("pacientes.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para leer los pacientes." << std::endl;
        return;
    }

    std::string linea, nombre, fechaIngreso;
    int ID;  // Ahora ID es un int
    while (std::getline(archivo, linea)) {
        if (linea.find("Nombre: ") != std::string::npos) {
            nombre = linea.substr(8);
        } else if (linea.find("ID: ") != std::string::npos) {
            ID = std::stoi(linea.substr(4));  // Convertir el string a int
        } else if (linea.find("Fecha de ingreso: ") != std::string::npos) {
            fechaIngreso = linea.substr(18);
            pacientes.push_back(new Paciente(nombre, ID, fechaIngreso));  // ID es int
        }
    }

    archivo.close();
}

void guardarDatosMedicos( std::vector<Medico*>& medicos) {
    std::ofstream archivo("medicos.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo medicos.txt para escribir." << std::endl;
        return;
    }

    for ( auto& medico : medicos) {
        archivo << medico->getNombre() << ","
                << medico->getID() << ","
                << medico->getEspecialidad() << ","
                << (medico->getDisponibilidad() ? "1" : "0") << "\n";
    }

    archivo.close();
}


    void recuperarDatosMedicos(std::vector<Medico*>& medicos) {
        std::ifstream archivo("medicos.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
            return;
        }

        std::string nombre, ID, especialidad;
        while (std::getline(archivo, nombre, ',') && 
               std::getline(archivo, ID, ',') && 
               std::getline(archivo, especialidad)) {
            medicos.push_back(new Medico(nombre, ID, especialidad, true));
        }

        archivo.close();
    }

    void guardarDatosServicios(const std::vector<Servicio*>& servicios) {
        std::ofstream archivo("servicios.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
            return;
        }

        for (auto servicio : servicios) {
            archivo << servicio->getNombreServicio() << "\n";
        }

        archivo.close();
    }

    void recuperarDatosServicios(std::vector<Servicio*>& servicios) {
        std::ifstream archivo("servicios.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
            return;
        }

        std::string nombreServicio;
        while (std::getline(archivo, nombreServicio)) {
            servicios.push_back(new Servicio(nombreServicio));
        }

        archivo.close();
    }
};
