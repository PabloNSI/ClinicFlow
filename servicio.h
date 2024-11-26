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
        medicos.push_back(medico);
        std::cout << "Medico " << medico->getNombre() << " agregado al servicio " << nombreServicio << std::endl;
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
