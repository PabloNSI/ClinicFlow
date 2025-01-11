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
    int ID;
    std::string fechaIngreso;
    std::vector<CitaMedica*> citas;
   
    // Método para validar la fecha
    bool esFechaValida(const std::string& fecha) const {
        if (fecha.size() != 10) return false;

        if (fecha[2] != '-' || fecha[5] != '-') return false;

        int dia = std::stoi(fecha.substr(0, 2));
        int mes = std::stoi(fecha.substr(3, 2));
        int year = std::stoi(fecha.substr(6, 4));

        if (dia < 1 || dia > 31) return false;
        if (mes < 1 || mes > 12) return false;
        if (year < 2000 || year > 2999) return false;

        if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
        if (mes == 2 && dia > 28) return false;

        return true;
    }

public:
    // Constructor por defecto
    Paciente()
    : nombre(""), ID(0), fechaIngreso(""){}
    // Constructor
    Paciente(const std::string& nombre, int ID, const std::string& fechaIngreso) 
        : nombre(nombre), ID(ID), fechaIngreso(fechaIngreso) {}

    // Getters
    std::string getNombre() const { return nombre; }
     int getID() const { return ID; }
    std::string getFechaIngreso() const { return fechaIngreso; }

    // Setters
    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setID(const int& ID) { this->ID = ID; }
    void setFechaIngreso(const std::string& fechaIngreso) {
        if (esFechaValida(fechaIngreso)) {
            this->fechaIngreso = fechaIngreso;
        } else {
            std::cout << "Error: La fecha debe tener el formato dd-MM-AAAA." << std::endl;
        }
    }

        // Método para mostrar los datos del paciente
    void mostrarPaciente() const {
        std::cout << "Nombre: " << nombre << ", ID: " << ID << "\n"
        << "Fecha de ingreso: " << fechaIngreso << "\n"
        << "----------------------------" << "\n";
    }
        
        // Método para editar el paciente
    void editarPaciente(std::vector<Paciente*>& pacientes) {
        int idPaciente;
        std::cout << "Ingrese el ID del paciente a editar: ";
        while (!(std::cin >> idPaciente)) {
            std::cout << "Entrada invalida. Intente de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        auto it = std::find_if(pacientes.begin(), pacientes.end(),
            [&idPaciente](Paciente* p) { return p->getID() == idPaciente; });
        if (it != pacientes.end()) {
            Paciente* paciente = *it;
            std::cout << "Paciente encontrado: " << paciente->nombre << ", ID: " << paciente->ID << ", Fecha de ingreso: " << paciente->fechaIngreso << std::endl;
            std::cout << "Ingrese el nuevo nombre del paciente: ";
            std::getline(std::cin, paciente->nombre);
            std::cout << "Ingrese el nuevo ID del paciente (4 digitos): ";
            while (!(std::cin >> paciente->ID)) {
                std::cout << "ID invalido. Intente de nuevo: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore();
            std::string nuevaFecha;
            bool fechaValida = false;
            while (!fechaValida) {
                std::cout << "Ingrese la nueva fecha de ingreso (dd-MM-AAAA): ";
                std::getline(std::cin, nuevaFecha);
                if (esFechaValida(nuevaFecha)) {
                    fechaValida = true;
                    paciente->setFechaIngreso(nuevaFecha); // Establecer la nueva fecha
                } else {
                    std::cout << "Error: La fecha debe tener el formato dd-MM-AAAA." << std::endl;
                }
            }
            std::cout << "Paciente editado correctamente." << std::endl;
        } else {
            std::cout << "Paciente no encontrado.\n";
        }
    }

        // Método estático para eliminar un paciente
    static void eliminarPaciente(std::vector<Paciente*>& pacientes) {
        int idPaciente;
        std::cout << "Ingrese el ID del paciente a eliminar: ";
        while (!(std::cin >> idPaciente)) {
            std::cout << "Entrada invalida. Intente de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        std::cout << "Estas seguro de eliminar al paciente con ID " << idPaciente 
                << "? (1 para confirmar, 0 para cancelar): ";
        int confirmar;
        while (!(std::cin >> confirmar) || (confirmar != 1 && confirmar != 0)) {
            std::cout << "Entrada invalida. Intente de nuevo (1 para confirmar, 0 para cancelar): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        if (confirmar == 1) {
            auto it = std::remove_if(pacientes.begin(), pacientes.end(), [&idPaciente](Paciente* p) {
                return p->getID() == idPaciente;
            });

            if (it != pacientes.end()) {
                delete *it;
                pacientes.erase(it); // Eliminar del vector
                std::cout << "Paciente eliminado correctamente.\n";
            } else {
                std::cout << "Paciente no encontrado.\n";
            }
        } else {
            std::cout << "Eliminacion cancelada.\n";
        }
    }

        // Método para registrar el paciente
    void registrarPaciente() {
        std::cout << "Nombre y apellidos del paciente: ";
        std::getline(std::cin, nombre);
        std::cout << "ID del paciente (1234): ";
        while (!(std::cin >> ID)) {
            std::cout << "ID invalido. Intenta de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        bool fechaValida = false;
            while (!fechaValida) {
                std::cout << "Fecha de ingreso (dd-MM-AAAA): ";
                std::getline(std::cin, fechaIngreso);
                if (esFechaValida(fechaIngreso)) {
                    fechaValida = true;
                } else {
                    std::cout << "Error: La fecha debe tener el formato dd-MM-AAAA." << std::endl;
                }
            }
        std::cout << "Paciente registrado correctamente: " << nombre 
                << " (ID: " << ID << ")" << std::endl;
    }
    
};