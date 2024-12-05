#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class CitaMedica;

class Paciente {
private:
    std::string nombre;
    std::string ID;
    std::string fechaIngreso;
    std::vector<CitaMedica*> citas;

public:
    // Constructor
    Paciente(std::string _nombre, std::string _ID, std::string _fechaIngreso)
        : nombre(_nombre), ID(_ID), fechaIngreso(_fechaIngreso) {}

    void registrarPaciente() {
        std::ofstream archivo("pacientes.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "Nombre: " << nombre << "\n";
            archivo << "ID: " << ID << "\n";
            archivo << "Fecha de ingreso: " << fechaIngreso << "\n\n";
            archivo.close();
        } else {
            std::cerr << "Error al abrir el archivo para registrar el paciente.\n";
        }
    }
    void eliminarPaciente() {
        std::cout << "Paciente " << nombre << " eliminado.\n";
    }
    void modificarPaciente(const std::string& nuevoNombre, const std::string& nuevaID) {
        nombre = nuevoNombre;
        ID = nuevaID;
        std::cout << "Paciente modificado a " << nombre << " con ID " << ID << "\n";
    }
    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }
    // Metodos de consulta
    std::string getNombre() const { return nombre; }
    std::string getID() const { return ID; }
    std::string getFechaIngreso() const { return fechaIngreso; }
    // Metodo estatico para obtener el numero de campos requeridos
    static int camposRequeridos() { return 3; } // Nombre, ID, Fecha de ingreso
    // Metodo para comparar IDs ignorando mayus y espacios
    bool compararID(const std::string& otroID) const {
        std::string id1 = ID, id2 = otroID;
        // Eliminar espacios y convertir a minus
        id1.erase(0, id1.find_first_not_of(' '));
        id1.erase(id1.find_last_not_of(' ') + 1);
        id2.erase(0, id2.find_first_not_of(' '));
        id2.erase(id2.find_last_not_of(' ') + 1);

        std::transform(id1.begin(), id1.end(), id1.begin(), ::tolower);
        std::transform(id2.begin(), id2.end(), id2.begin(), ::tolower);

        return id1 == id2;
    }
};
