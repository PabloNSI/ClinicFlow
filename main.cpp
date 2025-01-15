#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>

#include "citaMedica.h"
#include "gestorArchivos.h"
#include "paciente.h"
#include "medico.h"
#include "reporte.h"

Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, int id) {
    for (Paciente* paciente : pacientes) {
        if (paciente->getID() == id) {
            return paciente;
        }
    }
    return nullptr;
}

Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, int id) {
    for (Medico* medico : medicos) {
        if (medico->getID() == id) {
            return medico;
        }
    }
    return nullptr;
}

int main() {
    std::vector<Paciente*> pacientes;
    std::vector<Medico*> medicos;
    std::vector<CitaMedica*> citas;
    int opcion;
    GestorArchivos gestor;

    gestor.recuperarDatosPacientes(pacientes);
    gestor.recuperarDatosMedicos(medicos);
    gestor.recuperarDatosCitas(citas, pacientes, medicos);

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Agregar, ver o editar paciente\n";
        std::cout << "2. Agregar, ver o editar medico\n";
        std::cout << "3. Agregar, ver o editar citas medicas\n";
        std::cout << "4. Pacientes atendidos entre fechas determinadas\n";
        std::cout << "5. Citas pendientes por medico\n";
        std::cout << "6. Registro de historial clinico\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
                            // Agregar, ver o editar paciente
            case 1: {
                int subopcion;
                do {
                    std::cout << "\n--- MENU PACIENTES ---\n";
                    std::cout << "1. Ver pacientes\n";
                    std::cout << "2. Editar paciente\n";
                    std::cout << "3. Eliminar paciente\n";
                    std::cout << "4. Registrar paciente\n";
                    std::cout << "0. Volver al menu principal\n";
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;
                    std::cin.ignore(); // Limpiar el buffer de entrada

                    switch(subopcion) {
                                        // Ver pacientes
                        case 1: {
                            int opcion;
                            std::string fechaIngreso, nombre;
                            do {
                                std::cout << "\n--- MENU VER PACIENTES ---\n";
                                std::cout << "1. Ver lista completa de pacientes\n";
                                std::cout << "2. Buscar pacientes por fecha de ingreso\n";
                                std::cout << "3. Buscar pacientes por ID\n";
                                std::cout << "4. Buscar pacientes por nombre\n";
                                std::cout << "0. Salir\n";
                                std::cout << "Ingrese una opcion: ";
                                std::cin >> opcion;
                                std::cin.ignore();

                                switch(opcion) {
                                    // Ver lista completa de pacientes
                                    case 1:{
                                        std::cout << "\n--- Lista de Pacientes ---\n\n";
                                        if (pacientes.empty()) {
                                            std::cout << "No hay pacientes registrados.\n";
                                        }else {
                                            for (const auto& paciente : pacientes) {
                                                paciente->mostrarPaciente();
                                            }
                                        }break;
                                    }
                                    // Ver pacientes por fecha de ingreso
                                    case 2:{
                                        Paciente::verPacientePorFecha(pacientes, fechaIngreso);
                                        break;
                                    }
                                    // Ver pacientes por ID
                                    case 3:{
                                        Paciente::verPacientePorID(pacientes);
                                        break;
                                    }
                                    // Ver pacientes por nombre
                                    case 4:{
                                        Paciente::verPacientePorNombre(pacientes);
                                        break;
                                    }

                                    case 0:
                                        std::cout << "Volviendo al menu de pacientes...\n";
                                        break;

                                    default:
                                        std::cout << "Opcion no valida. Intente de nuevo.\n";
                                }

                            } while (opcion != 0);

                            break;
                        }
                                        // Editar pacientes
                        case 2: {
                            for (Paciente* paciente : pacientes) {
                                paciente->editarPaciente(pacientes);
                                break;
                            }
                            break;
                        }
                                        // Eliminar pacientes
                        case 3: {
                            Paciente::eliminarPaciente(pacientes);
                            break;
                        }
                                        // Registrar paciente   
                        case 4: {
                            Paciente* nuevoPaciente = new Paciente();
                            nuevoPaciente->registrarPaciente();
                            pacientes.push_back(nuevoPaciente);
                            break;
                        }
                        case 0:
                            std::cout << "Volviendo al menu principal...\n";
                            break;
                        default:
                            std::cout << "Opcion no valida. Intenta de nuevo.\n";
                            break;
                    }
                } while (subopcion != 0);
                break;
            }
                            // Agregar, ver o editar medico
            case 2: {
                int subopcion;
                do {
                    std::cout << "\n--- MENU MEDICOS ---\n";
                    std::cout << "1. Ver medicos\n";
                    std::cout << "2. Editar medico\n";
                    std::cout << "3. Eliminar medico\n";
                    std::cout << "4. Registrar medico\n";
                    std::cout << "0. Volver al menu principal\n";
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;
                    std::cin.ignore();

                    switch(subopcion) {
                                    // ver medicos
                        case 1: {
                            int opcion;
                            std::string servicio, nombre;
                            do {
                                std::cout << "\n--- MENU VER MEDICOS ---\n";
                                std::cout << "1. Ver lista completa de medicos\n";
                                std::cout << "2. Buscar medico por servicio\n";
                                std::cout << "3. Buscar medico por ID\n";
                                std::cout << "4. Buscar medico por nombre\n";
                                std::cout << "5. Buscar medico por disponibilidad\n";
                                std::cout << "0. Salir\n";
                                std::cout << "Ingrese una opcion: ";
                                std::cin >> opcion;
                                std::cin.ignore();

                                switch(opcion) {
                                    // ver lista completa de medicos
                                    case 1:{
                                        std::cout << "\n--- Lista de Medicos ---\n\n";
                                        if (medicos.empty()) {
                                            std::cout << "No hay medicos en el sistema.\n";
                                        } else {
                                            for (const auto& medico : medicos) {
                                                medico->mostrarMedico();
                                            }
                                        }
                                        break;
                                    }
                                    // ver medicos por servicio
                                    case 2:{
                                        Medico::verMedicoPorServicio(medicos);
                                        break;
                                    }
                                    // ver medicos por ID
                                    case 3:{
                                        Medico::verMedicoPorID(medicos);
                                        break;
                                    }
                                    // ver medicos por nombre
                                    case 4:{
                                        Medico::verMedicoPorNombre(medicos);
                                        break;
                                    }
                                    // ver medicos por disponibilidad
                                    case 5:{
                                        Medico::verMedicoPorDisponibilidad(medicos);
                                        break;
                                    }

                                    case 0:
                                        std::cout << "Volviendo al menu de medicos...\n";
                                        break;

                                    default:
                                        std::cout << "Opcion no valida. Intente de nuevo.\n";
                                }

                            } while (opcion != 0);

                            break;
                        }
                                    // Editar medicos
                        case 2: {
                            for (Medico* medico : medicos) {
                                medico->modificarMedico(medicos);
                                break;
                            }
                            break; 
                        }
                                    // Eliminar medico
                        case 3: {
                            Medico::eliminarMedico(medicos);
                            break;
                        }
                                    // Registrar medico
                        case 4: {
                            Medico nuevoMedico;
                            nuevoMedico.registrarMedico();
                            medicos.push_back(new Medico(nuevoMedico));
                            break;
                        }
                        
                        case 0:
                            std::cout << "Volviendo al menu principal...\n";
                            break;
                        default:
                            std::cout << "Opcion no valida. Intente de nuevo.\n";
                    }
                } while (subopcion != 0);
                break;
            }
                            // Agregar, ver o editar citas medicas
            case 3:{
                int subopcion;
                do {
                    std::cout << "\n--- MENU CITAS MEDICAS ---\n";
                    std::cout << "1. Ver citas\n";
                    std::cout << "2. Editar cita\n";
                    std::cout << "3. Eliminar cita\n";
                    std::cout << "4. Registrar cita\n";
                    std::cout << "0. Volver al menu principal\n";
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;
                    std::cin.ignore();

                    switch(subopcion) {
                                    // ver cita
                        case 1: {
                            std::cout << "\n--- Lista de Citas ---\n\n";
                            if (citas.empty()) {
                                std::cout << "No hay citas registradas.\n";
                            } else {
                                for (const auto& cita : citas) {
                                    cita->mostrarCita();
                                }
                            }
                            break;
                        }
                                    // Editar cita
                        case 2: {
                            CitaMedica::modificarCita(pacientes, medicos, citas);
                            break;
                        }
                                    // Eliminar cita
                        case 3: {
                            CitaMedica::eliminarCita(citas);
                            break;
                        }
                                    // Registrar cita
                        case 4: {
                            CitaMedica cita("", 0, nullptr, nullptr);
                            cita.registrarCita(pacientes, medicos, citas);
                            break;
                        }                      
                        case 0:
                            std::cout << "Volviendo al menu principal...\n";
                            break;
                        default:
                            std::cout << "Opcion no valida. Intente de nuevo.\n";
                    }
                } while (subopcion != 0);
                break;
            }
                            // Pacientes atendidos entre fechas determinadas
            case 4: {
                std::string fechaInicio, fechaFin;
                std::cout << "Fecha inicio (yyyy-mm-dd): ";
                std::getline(std::cin, fechaInicio);
                std::cout << "Fecha fin (yyyy-mm-dd): ";
                std::getline(std::cin, fechaFin);
                Reporte reporte;
                reporte.listarPacientesPorRangoFechas(citas, fechaInicio, fechaFin);
                break;
            }
                            // Citas pendientes por medico
            case 5: {
                int medicoID;
                std::cout << "ID del medico: ";
                std::cin >> medicoID;
                Reporte reporte;
                reporte.listarCitasPendientes(citas, "medico");
                break;
            }
                            // Registro de historial clinico
            case 6:{
                break;
            }
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intenta de nuevo.\n";
                break;
         }
    } while (opcion != 0);

        // Guardar datos de pacientes, medicos y citas en sus archivos
    gestor.guardarDatosPacientes(pacientes);
    gestor.guardarDatosMedicos(medicos);
    gestor.guardarDatosCitas(citas);

    // Liberar memoria
    for (Paciente* p : pacientes) {
        delete p;
    }
    for (Medico* m : medicos) {
    delete m;
    }
    for (CitaMedica* c : citas) {
        delete c;
    }

    return 0;
}
