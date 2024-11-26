#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#pragma once

class CitaMedica;

class Paciente {
private:
    std::string nombre;
    std::string ID;
    std::string fechaIngreso;
    std::vector<CitaMedica*> citas;

public:
    Paciente(std::string _nombre, std::string _ID, std::string _fechaIngreso)
        : nombre(_nombre), ID(_ID), fechaIngreso(_fechaIngreso) {}

    void registrarPaciente() {
        std::ofstream archivo("pacientes.txt", std::ios::app); 
        if (archivo.is_open()) {
            archivo << "Nombre: " << nombre << "\n";
            archivo << "ID: " << ID << "\n";
            archivo << "Fecha de ingreso: " << fechaIngreso << "\n\n";
        } else {
            std::cerr << "Error al abrir el archivo para registrar el paciente.\n";
        }

        archivo.close();
    }

    void eliminarPaciente() {
        std::cout << "Paciente " << nombre << " eliminado." << std::endl;
    }

    void modificarPaciente(std::string nuevoNombre, std::string nuevaID) {
        nombre = nuevoNombre;
        ID = nuevaID;
        std::cout << "Paciente modificado a " << nombre << " con ID " << ID << std::endl;
    }

    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }

    std::string getNombre() const { return nombre; }
    std::string getID() const { return ID; }
    std::string getFechaIngreso() const { return fechaIngreso; }
};
