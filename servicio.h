#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#pragma once

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
};