#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class CitaMedica;

class Medico {
private:
    std::string nombre;
    int ID;
    std::string especialidad;
    bool disponibilidad;
    std::vector<CitaMedica*> citas;

public:
    // Constructor
    Medico(std::string& nombre, int ID, const std::string& especialidad, bool disponibilidad)
        : nombre(nombre), ID(ID), especialidad(especialidad), disponibilidad(disponibilidad) {}

    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setID(const int& ID) { this->ID = ID; }
    void setEspecialidad(const std::string& especialidad){ this->especialidad = especialidad; }
    void setDisponibilidad(const bool& disponibilidad){ this->disponibilidad = disponibilidad; }

    void mostrarMedico() const {
        std::cout << "Nombre: " << nombre << ", ID: " << ID << ", Especialidad: " << especialidad 
        << ", Disponibilidad: " << disponibilidad <<std::endl;
    }

    void registrarMedico() {
        std::cout << "Medico registrado correctamente: " << nombre << " (ID: " << ID << ")" << std::endl;
    }

void modificarMedico() {
    std::cout << "Ingrese el nuevo nombre del medico: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nombre);
    std::cout << "Ingrese el nuevo ID del medico (1234): ";
    while (!(std::cin >> ID)) {
        std::cout << "ID invalido. Intenta de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Ingrese la nueva especialidad del medico: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, especialidad);
    std::cout << "Esta disponible el medico? (1 = Si / 0 = No): ";
    while (!(std::cin >> disponibilidad)) {
        std::cout << "Entrada invalida. Intenta de nuevo (1 = Si / 0 = No): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Medico modificado correctamente.\n";
}

        static void eliminarMedico(std::vector<Medico*>& medicos, int& idMedico) {
        auto it = std::remove_if(medicos.begin(), medicos.end(), [&idMedico](Medico* m) {
            return m->getID() == idMedico;
        });

        if (it != medicos.end()) {
            delete *it;
            medicos.erase(it);
        }
    }
    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }
    // Metodos de consulta (getters)
    std::string getNombre() const { return nombre; }
    std::string getEspecialidad() const { return especialidad; }
    int getID() const { return ID; }
    bool getDisponibilidad() const { return disponibilidad; }
    // Metodo estatico para obtener el número de campos requeridos
    static int camposRequeridos() { return 4; } // Nombre, ID, Especialidad, Disponibilidad

};

