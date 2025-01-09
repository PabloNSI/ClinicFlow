#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "paciente.h"
#include "medico.h"
#include "servicio.h"

Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, int id);
Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, int id);

class GestorArchivos {
public:
// Función para guardar los datos de los pacientes
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
            pacientes.push_back(new Paciente(nombre, ID, fechaIngreso));
        }
    }

    archivo.close();
}
    // Función para guardar los datos de los medicos
void guardarDatosMedicos(const std::vector<Medico*>& medicos) {
    std::ofstream archivo("medicos.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo medicos.txt para escribir." << std::endl;
        return;
    }

    for (Medico* medico : medicos) {
        archivo << "Dr. " << medico->getNombre() << "\n";
            // Como el dato tipo int omite los ceros a la izq, se usa setw y setfill para mostrarlos
            archivo << std::setw(4) << std::setfill('0') << "ID: " << medico->getID() << "\n";
             archivo << "Especialidad: " << medico->getEspecialidad() << "\n";
             archivo << "Disponibilidad: " << medico->getDisponibilidad()<< "\n";
             archivo << "\n";
    }

    archivo.close();
}
    // Función para recuperar los datos de los medicos
void recuperarDatosMedicos(std::vector<Medico*>& medicos) {
        std::ifstream archivo("medicos.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
            return;
        }

        std::string linea, nombre, especialidad;
        int ID;
        while (std::getline(archivo, linea)){
            if (linea.find("Dr. ") != std::string::npos) {
                nombre = linea.substr(4);
            } else if (linea.find("ID: ") != std::string::npos) {
                ID = std::stoi(linea.substr(4));
            } else if (linea.find("Especialidad: ") != std::string::npos){
               especialidad = linea.substr(14);
            } else if (linea.find("Disponibilidad: ") != std::string::npos) {
                std::string valor_disponibilidad = linea.substr(16);
                int disponibilidad_int = std::stoi(valor_disponibilidad);
                bool disponibilidad = (disponibilidad_int != 0);
                medicos.push_back(new Medico(nombre, ID, especialidad, disponibilidad));
            }

        }

        archivo.close();
    }
    // Función para guardar los datos de las citas
void guardarDatosCitas(const std::vector<CitaMedica*>& citas) {
    std::ofstream archivo("citas.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo citas.txt para escribir.\n";
        return;
    }

    for (const CitaMedica* cita : citas) {
        archivo << "Fecha: " << cita->getFecha() << "\n";
        archivo << "Paciente: " << cita->getPaciente()->getNombre() 
                << " (ID: " << cita->getPaciente()->getID() << ")\n";
        archivo << "Medico: " << cita->getMedico()->getNombre() 
                << " (ID: " << cita->getMedico()->getID() << ")\n";
        archivo << "Urgencia: " << cita->getUrgencia() << "\n";
        archivo << "--------------------------------------\n";
    }

    archivo.close();
}

    // Funcion para recuperar los datos de las citas
void recuperarDatosCitas(std::vector<CitaMedica*>& citas, 
                        const std::vector<Paciente*>& pacientes, 
                        const std::vector<Medico*>& medicos) {
    std::ifstream archivo("citas.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo citas.txt para leer.\n";
        return;
    }

    std::string linea, fecha;
    int idPaciente, idMedico, urgencia;

    while (std::getline(archivo, linea)) {
        if (linea.find("Fecha: ") == 0) {
            // Leer la fecha
            fecha = linea.substr(7);
            // Leer el paciente
            std::getline(archivo, linea);
            idPaciente = std::stoi(linea.substr(linea.find("ID: ") + 4, linea.find(")") - linea.find("ID: ") - 4));
            // Leer el médico
            std::getline(archivo, linea);
            idMedico = std::stoi(linea.substr(linea.find("ID: ") + 4, linea.find(")") - linea.find("ID: ") - 4));
            // Leer la urgencia
            std::getline(archivo, linea);
            urgencia = std::stoi(linea.substr(10));

            // Buscar al paciente y al médico por sus ID
            Paciente* paciente = buscarPacientePorID(pacientes, idPaciente);
            Medico* medico = buscarMedicoPorID(medicos, idMedico);

            if (paciente != nullptr && medico != nullptr) {
                // Crear la cita y agregarla al vector
                citas.push_back(new CitaMedica(fecha, urgencia, paciente, medico));
            } else {
                std::cerr << "Error: No se encontró el paciente o médico para la cita con fecha " << fecha << ".\n";
            }
        }
    }

    archivo.close();
}
    // Función para guardar los datos de los servicios
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
    // Función para recuperar los datos de los servicios
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
