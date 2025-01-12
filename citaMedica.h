#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "paciente.h"
#include "medico.h"

class CitaMedica {
private:
    std::string fecha;
    int urgencia;
    Paciente* paciente;
    Medico* medico;

public:
    CitaMedica(std::string _fecha, int _urgencia, Paciente* _paciente, Medico* _medico)
        : fecha(_fecha), urgencia(_urgencia), paciente(_paciente), medico(_medico) {}

    std::string getFecha() const { return fecha; }
    Paciente* getPaciente() const { return paciente; }
    Medico* getMedico() const { return medico; }
    int getUrgencia() const { return urgencia; }

    // Función para  guardar una cita en citas.txt -> registrarCita()
    void asignarCita() {
        std::ofstream archivo("citas.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "Fecha: " << fecha << "\n"
                    << "Paciente: " << paciente->getNombre() << " (ID: " << paciente->getID() << ")\n"
                    << "Medico: " << medico->getNombre() << " (ID: " << medico->getID() << ")\n"
                    << "Urgencia: " << urgencia << "\n--------------------------------------\n";
            archivo.close();
        } else {
            std::cerr << "Error al abrir el archivo de citas.\n";
        }
    }
    
    // Buscar paciente por ID
    static Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, int id) {
        for (Paciente* paciente : pacientes) {
            if (paciente->getID() == id) {
                return paciente;
            }
        }
        return nullptr;
    }
    
    // Buscar médico por ID
    static Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, int id) {
        for (Medico* medico : medicos) {
            if (medico->getID() == id) {
                return medico;
            }
        }
        return nullptr;
    }
    
    // Validar fecha en formato DD-MM-AAAA
    static bool esFechaValida(const std::string& fecha) {
        if (fecha.size() != 10 || fecha[2] != '-' || fecha[5] != '-') return false;

        int dia = std::stoi(fecha.substr(0, 2));
        int mes = std::stoi(fecha.substr(3, 2));
        int year = std::stoi(fecha.substr(6, 4));

        if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || year < 2000 || year > 2999) return false;
        if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
        if (mes == 2 && dia > 28) return false;

        return true;
    }
    
    // Ver citas
    void mostrarCita() const {
        std::cout << "Servicio: " << medico->getServicio() << "\n"
                  << "Fecha: " << fecha << "\n"
                  << "Paciente: " << paciente->getNombre()
                  << " (ID: " << paciente->getID() << ")" << "\n"
                  << "Medico: Dr. " << medico->getNombre()
                  << "(ID: " << medico->getID() << ")\n"
                  << "Urgencia: " << urgencia << "\n"
                  << "-----------" << "\n";
    }
    
    // Registrar una cita
    static void registrarCita(std::vector<Paciente*>& pacientes, std::vector<Medico*>& medicos, std::vector<CitaMedica*>& citas) {
        std::string fecha;
        int urgencia, pacienteID, medicoID;

        while (true) {
            std::cout << "Fecha de la cita (DD-MM-AAAA): ";
            std::getline(std::cin, fecha);
            if (esFechaValida(fecha)) {
                break;
            } else {
                std::cout << "Fecha invalida. Intenta de nuevo.\n";
            }
        }
        while (true) {
            std::cout << "Urgencia (1-5): ";
            std::cin >> urgencia;
            if (urgencia >= 1 && urgencia <= 5) {
                break;
            } else {
                std::cout << "Urgencia invalida. Intenta de nuevo (1-5).\n";
            }
        }
        std::cin.ignore();
        std::cout << "Pacientes disponibles:\n";
        for (Paciente* p : pacientes) {
            std::cout << "ID: " << p->getID() << ", Nombre: " << p->getNombre() << "\n";
        }
        std::cout << "Medicos disponibles:\n";
        for (Medico* m : medicos) {
            std::cout << "ID: " << m->getID() << ", Nombre: " << m->getNombre() << "\n";
        }
        while (true) {
            std::cout << "ID del paciente: ";
            std::cin >> pacienteID;
            std::cout << "ID del medico: ";
            std::cin >> medicoID;
            std::cin.ignore();
            Paciente* paciente = buscarPacientePorID(pacientes, pacienteID);
            Medico* medico = buscarMedicoPorID(medicos, medicoID);

            if (paciente && medico) {
                // Crear la cita
                CitaMedica* nuevaCita = new CitaMedica(fecha, urgencia, paciente, medico);
                nuevaCita->asignarCita();
                citas.push_back(nuevaCita);
                std::cout << "Cita asignada correctamente.\n";
                break;
            } else {
                std::cout << "Paciente o medico no encontrado. Intenta de nuevo.\n";
            }
        }
    }
    
    // Modificar una cita
    static void modificarCita(std::vector<Paciente*>& pacientes, std::vector<Medico*>& medicos, std::vector<CitaMedica*>& citas) {
        std::string fecha;
        int pacienteID, medicoID;

        // Solicitar y validar la fecha
        std::cout << "Ingrese la fecha de la cita a modificar (DD-MM-AAAA): ";
        while (true) {
            std::cin >> fecha;
            std::cin.ignore();
            if (esFechaValida(fecha)) {
                break;
            } else {
                std::cout << "Fecha invalida. Intenta de nuevo (DD-MM-AAAA): ";
            }
        }

        // Buscar la cita con la fecha ingresada
        auto it = std::find_if(citas.begin(), citas.end(), [&fecha](CitaMedica* c) {
            return c->getFecha() == fecha;
        });

        if (it != citas.end()) {
            CitaMedica* cita = *it;

            // Solicitar y validar ID del paciente
            std::cout << "ID del paciente: ";
            Paciente* paciente = nullptr;
            while (true) {
                std::cin >> pacienteID;
                std::cin.ignore();
                paciente = buscarPacientePorID(pacientes, pacienteID);
                if (paciente) {
                    break;  // El paciente existe, continuar
                } else {
                    std::cout << "Paciente no encontrado. Intenta de nuevo: ";
                }
            }
            std::cout << "Cita encontrada: \n";
            std::cout << "Servicio: " << cita->getMedico()->getServicio() << "\n"
                    << "Fecha: " << cita->getFecha() << "\n"
                    << "Paciente: " << cita->getPaciente()->getNombre()
                    << " (ID: " << cita->getPaciente()->getID() << ")\n"
                    << "Medico: Dr. " << cita->getMedico()->getNombre()
                    << " (ID: " << cita->getMedico()->getID() << ")\n"
                    << "Urgencia: " << cita->getUrgencia() << "\n";
            // Solicitar y validar la nueva fecha
            std::cout << "Ingrese la nueva fecha (DD-MM-AAAA): ";
            while (true) {
                std::getline(std::cin, cita->fecha);
                if (esFechaValida(cita->fecha)) {
                    break;
                } else {
                    std::cout << "Fecha invalida. Intenta de nuevo (DD-MM-AAAA): ";
                }
            }

            // Solicitar y validar nuevo ID de paciente
            std::cout << "Ingrese el ID del paciente para asignar a la nueva cita: ";
            while (true) {
                std::cin >> pacienteID;
                std::cin.ignore();
                paciente = buscarPacientePorID(pacientes, pacienteID);
                if (paciente) {
                    break;  // El paciente existe, continuar
                } else {
                    std::cout << "Paciente no encontrado. Intenta de nuevo: ";
                }
            }

            // Solicitar y validar ID de médico
            std::cout << "Ingrese el ID del medico para asignar a la nueva cita: ";
            Medico* medico = nullptr;
            while (true) {
                std::cin >> medicoID;
                std::cin.ignore();
                medico = buscarMedicoPorID(medicos, medicoID);
                if (medico) {
                    break;  // El médico existe, continuar
                } else {
                    std::cout << "Medico no encontrado. Intenta de nuevo: ";
                }
            }

            // Solicitar y validar nivel de urgencia
            std::cout << "Ingrese el nuevo nivel de urgencia (1-5): ";
            while (true) {
                std::cin >> cita->urgencia;
                std::cin.ignore();
                if (cita->urgencia >= 1 && cita->urgencia <= 5) {
                    break;  // Nivel de urgencia válido, continuar
                } else {
                    std::cout << "Nivel de urgencia invalido. Intenta de nuevo (1-5): ";
                }
            }

            std::cout << "Cita modificada correctamente.\n";
        } else {
            std::cout << "Cita no encontrada.\n";
        }
    }
    
    // Eliminar una cita
    static void eliminarCita(std::vector<CitaMedica*>& citas) {
        std::string fecha;
        int pacienteID;

        while (true) {
            std::cout << "Ingrese la fecha de la cita a eliminar (DD-MM-AAAA): ";
            std::getline(std::cin, fecha);
            std::vector<CitaMedica*> citasEnFecha;

            for (CitaMedica* cita : citas) {
                if (cita->getFecha() == fecha) {
                    citasEnFecha.push_back(cita);
                }
            }
            if (!citasEnFecha.empty()) {
                std::cout << "Citas encontradas en la fecha " << fecha << ":\n";
                for (CitaMedica* cita : citasEnFecha) {
                    cita->mostrarCita();
                }

                while (true) {
                    std::cout << "Ingrese el ID del paciente para eliminar la cita correspondiente: ";
                    std::cin >> pacienteID;
                    std::cin.ignore();

                    CitaMedica* citaSeleccionada = nullptr;
                    for (CitaMedica* cita : citasEnFecha) {
                        if (cita->getPaciente()->getID() == pacienteID) {
                            citaSeleccionada = cita;
                            break;
                        }
                    }

                    if (citaSeleccionada) {
                        int confirmar;
                        std::cout << "Estas seguro de eliminar la cita? (1 para confirmar, 0 para cancelar): ";
                        while (!(std::cin >> confirmar) || (confirmar != 1 && confirmar != 0)) {
                            std::cout << "Entrada invalida. Intente de nuevo (1 para confirmar, 0 para cancelar): ";
                            std::cin.clear();
                            std::cin.ignore();
                        }
                        std::cin.ignore();

                        if (confirmar == 1) {
                            // Eliminar la cita del vector
                            auto it = std::remove_if(citas.begin(), citas.end(), [&citaSeleccionada](CitaMedica* cita) {
                                return cita->getFecha() == citaSeleccionada->getFecha() &&
                                    cita->getPaciente()->getID() == citaSeleccionada->getPaciente()->getID();
                            });

                            if (it != citas.end()) {
                                delete *it;
                                citas.erase(it);
                                std::cout << "Cita eliminada correctamente.\n";
                            } else {
                                std::cout << "No se encontro la cita en el sistema.\n";
                            }
                        } else {
                            std::cout << "Eliminacion cancelada.\n";
                        }
                        return;
                    } else {
                        std::cout << "No se encontro una cita para ese paciente en esa fecha. Intenta de nuevo.\n";
                    }
                }
            } else {
                std::cout << "No se encontraron citas para esa fecha. Intenta de nuevo.\n";
            }
        }
    }

};
