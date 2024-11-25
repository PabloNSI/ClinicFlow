#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "citaMedica.h"
#include "paciente.h"
#include "medico.h"

class Reporte {
public:
    void listarPacientesPorRangoFechas(
        const std::vector<CitaMedica*>& citas, 
        const std::string& fechaInicio, 
        const std::string& fechaFin) {
        std::cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
        for (const auto& cita : citas) {
            if (cita->getFecha() >= fechaInicio && cita->getFecha() <= fechaFin) {
                std::cout << "Paciente: " << cita->getPaciente()->getNombre() << " - Fecha: " 
                << cita->getFecha() << "\n";
            }
        }
    }

    void listarCitasPendientes(const std::vector<CitaMedica*>& citas, const std::string& criterio) {
        std::cout << "Citas pendientes por " << (criterio == "medico" ? "medico" : "especialidad") << ":\n";
        for (const auto& cita : citas) {
            if (criterio == "medico") {
                std::cout << "Medico: " << cita->getMedico()->getNombre() 
                << " - Paciente: " << cita->getPaciente()->getNombre() << " - Fecha: " 
                << cita->getFecha() << "\n";
            } else if (criterio == "especialidad") {
                std::cout << "Especialidad: " << cita->getMedico()->getEspecialidad() 
                << " - Paciente: " << cita->getPaciente()->getNombre() << " - Fecha: " 
                << cita->getFecha() << "\n";
            }
        }
    }

    void reportePacientesCronicos(const std::vector<Paciente*>& pacientes) {
        std::cout << "Pacientes con enfermedades cronicas:\n";
        for (const auto& paciente : pacientes) {
            if (tieneEnfermedadCronica(paciente)) {
                std::cout << "Paciente: " << paciente->getNombre() << " - ID: " 
                << paciente->getID() << "\n";
            }
        }
    }

private:
    bool tieneEnfermedadCronica(Paciente* paciente) {
        return true;
    }
};
