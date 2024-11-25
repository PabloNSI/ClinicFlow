#pragma once
#include <iostream>
#include <string>

class Paciente;
class Medico;

class CitaMedica {
private:
    std::string fecha;
    int urgencia;
    Paciente* paciente;
    Medico* medico;
public:
    CitaMedica(std::string _fecha, int _urgencia, Paciente* _paciente, Medico* _medico)
        : fecha(_fecha), urgencia(_urgencia), paciente(_paciente), medico(_medico) {}

    void asignarCita() {
        std::cout << "Cita asignada para el paciente en la fecha " << fecha << std::endl;
    }

    void cancelarCita() {
        std::cout << "Cita cancelada para el paciente." << std::endl;
    }

    void modificarCita(std::string nuevaFecha, int nuevaUrgencia) {
        fecha = nuevaFecha;
        urgencia = nuevaUrgencia;
        std::cout << "Cita modificada a la fecha " << fecha << " con urgencia " << urgencia << std::endl;
    }

    std::string getFecha() { return fecha; }
    int getUrgencia() { return urgencia; }

    Paciente* getPaciente() { return paciente; }

    Medico* getMedico() { return medico; }

};
