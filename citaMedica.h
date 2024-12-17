#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include "paciente.h"
#include "medico.h"

Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, int id);

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
        std::ofstream archivo("citas.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "Fecha: " << fecha << "\n";
            archivo << "Urgencia: " << urgencia << "\n";
            archivo << "Paciente: " << paciente->getNombre() << " (ID: " << paciente->getID() << ")\n";
            archivo << "Médico: " << medico->getNombre() << " (ID: " << medico->getID() << ")\n";
            archivo << "----------------------\n";
            archivo.close();
        } else {
            std::cerr << "Error al abrir el archivo de citas.\n";
        }
    }
    // Métodos para obtener los datos si es necesario
    std::string getFecha() const { return fecha; }
    int getUrgencia() const { return urgencia; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
};

Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, int pacienteID);
Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, const std::string& medicoID);

// Menú para registrar la cita
void registrarCita(std::vector<Paciente*>& pacientes, std::vector<Medico*>& medicos, std::vector<CitaMedica*>& citas) {
    std::string fecha;
    int urgencia;
    int pacienteID;
    std::string  medicoID;
    // Solicitar fecha
    std::cout << "Fecha de la cita: ";
    std::getline(std::cin >> std::ws, fecha);
    // Solicitar urgencia
    std::cout << "Urgencia (1-5): ";
    while (!(std::cin >> urgencia) || urgencia < 1 || urgencia > 5) {
        std::cout << "Por favor, ingrese un valor válido para la urgencia (1-5): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el buffer
    // Solicitar ID del paciente y médico
    std::cout << "ID del paciente: ";
    std::cin >>  pacienteID;
    std::cout << "ID del médico: ";
    std::getline(std::cin >> std::ws, medicoID);
    // Buscar paciente y médico por ID
    Paciente* paciente = buscarPacientePorID(pacientes, pacienteID);
    Medico* medico = buscarMedicoPorID(medicos, medicoID);
    // Validar y asignar cita
    if (paciente && medico) {
        // Crear nueva cita
        CitaMedica* nuevaCita = new CitaMedica(fecha, urgencia, paciente, medico);
        // Asignar la cita
        nuevaCita->asignarCita();
        citas.push_back(nuevaCita);  
        // Añadir la cita al paciente y al médico
        paciente->añadirCita(nuevaCita);
        medico->añadirCita(nuevaCita);
        std::cout << "Cita asignada correctamente.\n";
    } else {
        std::cout << "Paciente o médico no encontrado. \n";
    }
}
