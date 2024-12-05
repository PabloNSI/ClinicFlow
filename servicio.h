// servicio.h
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "medico.h"

class Servicio {
private:
    std::string nombreServicio;
    std::vector<Medico*> medicos;

public:
    Servicio(std::string _nombreServicio) : nombreServicio(_nombreServicio) {}

    void agregarMedico(Medico* medico) {
    // Agregar medico a la lista
    medicos.push_back(medico);
    std::cout << "Medico " << medico->getNombre() << " agregado al servicio " << nombreServicio << std::endl;

    // Guardar medico-servicio en el archivo
    std::ofstream archivo("medicos_por_servicio.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << "Servicio: " << nombreServicio << "\n";
        archivo << "Medico: " << medico->getNombre() << "\n";
        archivo << "ID: " << medico->getID() << "\n";
        archivo << "\n"; // Separador entre registros
        archivo.close();
    } else {
        std::cerr << "Error al guardar la relación medico-servicio.\n";
    }
}
    void listarMedicosPorServicio() {
        std::cout << "Medicos en el servicio " << nombreServicio << ":\n";
        for (auto medico : medicos) {
            std::cout << "- " << medico->getNombre() << " (Especialidad: " << medico->getEspecialidad() << ")\n";
        }
    }
    void buscarMedicosPorEspecialidad(const std::string& especialidad) {
        std::cout << "Medicos en " << nombreServicio << " con especialidad " << especialidad << ":\n";
        for (auto medico : medicos) {
            if (medico->getEspecialidad() == especialidad) {
                std::cout << "- " << medico->getNombre() << "\n";
            }
        }
    }
    std::string getNombreServicio() const {
        return nombreServicio;
    }
};
