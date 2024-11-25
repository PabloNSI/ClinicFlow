#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#pragma once


class Medico {
private:
    std::string nombre;
    std::string ID;
    std::string especialidad;
    bool disponibilidad;
    std::vector<CitaMedica*> citas;

public:
    Medico(std::string _nombre, std::string _ID, std::string _especialidad, bool _disponibilidad)
        : nombre(_nombre), ID(_ID), especialidad(_especialidad), disponibilidad(_disponibilidad) {}

    void registrarMedico() {
        std::cout << "Medico " << nombre << " registrado." << std::endl;
    }

    void modificarMedico(std::string nuevoNombre, std::string nuevaEspecialidad) {
        nombre = nuevoNombre;
        especialidad = nuevaEspecialidad;
        std::cout << "Medico modificado a " << nombre << " con especialidad " << especialidad << std::endl;
    }

    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }

    std::string getNombre() { return nombre; }
    std::string getEspecialidad() { return especialidad; }
};