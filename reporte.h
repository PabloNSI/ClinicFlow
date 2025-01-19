#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>  // Para obtener la fecha actual
#include "citaMedica.h"
#include "paciente.h"
#include "medico.h"

class Reporte {
public:
    // Función para listar las citas pendientes por medico o servicio
    void listarCitasPendientes(const std::vector<CitaMedica*>& citas, const std::string& criterio) {
        std::cout << "Citas pendientes por " << (criterio == "medico" ? "medico" : "servicio") << ":\n";
        for (const auto& cita : citas) {
            if (criterio == "medico") {
                std::cout << "Medico: " << cita->getMedico()->getNombre() 
                << " - Paciente: " << cita->getPaciente()->getNombre() << " - Fecha: " 
                << cita->getFecha() << "\n";
            } else if (criterio == "servicio") {
                std::cout << "Servicio: " << cita->getMedico()->getServicio() 
                << " - Paciente: " << cita->getPaciente()->getNombre() << " - Fecha: " 
                << cita->getFecha() << "\n";
            }
        }
    }

    // Función para generar el reporte de pacientes crónicos
    void reportePacientesCronicos(const std::vector<Paciente*>& pacientes) {
        std::cout << "Pacientes con enfermedades cronicas:\n";
        for (const auto& paciente : pacientes) {
            if (tieneEnfermedadCronica(paciente)) {
                std::cout << "Paciente: " << paciente->getNombre() << " - ID: " 
                << paciente->getID() << "\n";
            }
        }
    }

    // Función auxiliar para comparar si una fecha es pasada
    bool esCitaPasada(const std::string& fechaCita, int year, int month, int day) {
        int citaYear = std::stoi(fechaCita.substr(6, 4));
        int citaMonth = std::stoi(fechaCita.substr(3, 2));
        int citaDay = std::stoi(fechaCita.substr(0, 2));

        return citaYear < year || (citaYear == year && citaMonth < month) || 
            (citaYear == year && citaMonth == month && citaDay < day);
    }

    // Función para ver el historial de un paciente
    void verHistorialClinico(std::vector<CitaMedica*>& citas) {
        // Obtener la fecha actual
        std::time_t t = std::time(0);  
        std::tm* now = std::localtime(&t);
        int year = now->tm_year + 1900;
        int month = now->tm_mon + 1;
        int day = now->tm_mday;

        std::cout << "\nHistorial Clinico:\n";

        // Solicitar ID del paciente
        std::cout << "Ingrese el ID del paciente para ver su historial clinico (0 para todos): ";
        int idPaciente;
        std::cin >> idPaciente;

        // Ordenar citas por fecha
        for (size_t i = 0; i < citas.size(); ++i) {
            for (size_t j = 0; j < citas.size() - i - 1; ++j) {
                int dia1 = std::stoi(citas[j]->getFecha().substr(0, 2));
                int mes1 = std::stoi(citas[j]->getFecha().substr(3, 2));
                int año1 = std::stoi(citas[j]->getFecha().substr(6, 4));

                int dia2 = std::stoi(citas[j + 1]->getFecha().substr(0, 2));
                int mes2 = std::stoi(citas[j + 1]->getFecha().substr(3, 2));
                int año2 = std::stoi(citas[j + 1]->getFecha().substr(6, 4));

                if (año1 < año2 || (año1 == año2 && mes1 < mes2) || (año1 == año2 && mes1 == mes2 && dia1 < dia2)) {
                    CitaMedica* temp = citas[j];
                    citas[j] = citas[j + 1];
                    citas[j + 1] = temp;
                }
            }
        }

        // Mostrar historial solo de citas pasadas para el paciente indicado
        bool encontrado = false;
        for (const auto& cita : citas) {
            std::string fechaCita = cita->getFecha();

            if (esCitaPasada(fechaCita, year, month, day)) {
                int idCitaPaciente = cita->getPaciente()->getID();
                if (idPaciente == 0 || idPaciente == idCitaPaciente) {
                    encontrado = true;
                    std::cout << "El paciente " << cita->getPaciente()->getNombre()
                            << ", con ID " << idCitaPaciente
                            << " acudio al servicio " << cita->getMedico()->getServicio()
                            << " con el doctor " << cita->getMedico()->getNombre()
                            << " el dia " << cita->getFecha() << " por enfermedad.\n";
                }
            }
        }

        if (!encontrado) {
            if (idPaciente == 0) {
                std::cout << "No hay citas pasadas registradas.\n";
            } else {
                std::cout << "No se encontraron citas pasadas para el paciente con ID " << idPaciente << ".\n";
            }
        }
    }

    // Función para modificar enfermedad crónica y guardar en un archivo
    void modificarEnfermedadCronica(const std::vector<Paciente*>& pacientes) {
        std::string nombrePaciente;
        bool encontrado = false;
        char reintentar;

        do {
            std::cout << "Ingrese el nombre del paciente: ";
            std::cin.ignore();
            std::getline(std::cin, nombrePaciente);

            for (const auto& paciente : pacientes) {
                if (paciente->getNombre() == nombrePaciente) {
                    encontrado = true;
                    bool enfermedadCronica;
                    std::cout << "Paciente encontrado: " << paciente->getNombre() << "\n";
                    std::cout << "Modificar si tiene enfermedad cronica (1 para Si, 0 para No): ";
                    std::cin >> enfermedadCronica;

                    guardarEnArchivo(paciente->getNombre(), enfermedadCronica);
                    std::cout << "Informacion actualizada y guardada correctamente.\n";
                    break;
                }
            }

            if (!encontrado) {
                std::cout << "Paciente no encontrado. Desea intentar de nuevo? (S/N): ";
                std::cin >> reintentar;
                reintentar = tolower(reintentar);
            } else {
                reintentar = 'n';
            }
        } while (reintentar == 's');

        if (!encontrado) {
            std::cout << "Operacion cancelada. No se encontro el paciente.\n";
        }
    }

private:
    bool tieneEnfermedadCronica(Paciente*) {
            return true;
        }
    
    void guardarEnArchivo(const std::string& nombrePaciente, bool enfermedadCronica) {
        std::ofstream archivo("pacientes_cronicos.txt", std::ios::app);

        if (archivo.is_open()) {
            archivo << "Nombre: " << nombrePaciente << "\n";
            archivo << "Enfermedad cronica: " << (enfermedadCronica ? "Si" : "No") << "\n";
            archivo << "--------------------------\n";
            archivo.close();
        } else {
            std::cerr << "No se pudo abrir el archivo para guardar la informacion.\n";
        }
    }
};
