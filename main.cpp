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

int leerEntero(const std::string& mensaje) {
    int numero;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> numero) {
            return numero;
        } else {
            std::cout << "Entrada invalida. Por favor, ingrese un numero: " << std::endl;
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore();
        }
    }
}

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
    Reporte reporte;

    gestor.recuperarDatosPacientes(pacientes);
    gestor.recuperarDatosMedicos(medicos);
    gestor.recuperarDatosCitas(citas, pacientes, medicos);

    do {
        opcion = leerEntero(
            "\n--- MENU ---\n"
            "1. Agregar, ver o editar paciente\n"
            "2. Agregar, ver o editar medico\n"
            "3. Agregar, ver o editar citas medicas\n"
            "4. Registro de historial clinico\n"
            "5. Registrar enfermedad cronica\n"
            "0. Salir\n"
            "Seleccione una opcion: ");

        switch(opcion) {
                            // Agregar, ver o editar paciente
            case 1: {
                int subopcion;
                do {
                    subopcion = leerEntero(
                        "\n--- MENU PACIENTES ---\n"
                        "1. Ver pacientes\n"
                        "2. Editar paciente\n"
                        "3. Eliminar paciente\n"
                        "4. Registrar paciente\n"
                        "0. Volver al menu principal\n"
                        "Seleccione una opcion: ");

                    switch(subopcion) {
                                        // Ver pacientes
                        case 1: {
                            int subopcion2;
                            std::string fechaIngreso, nombre;
                            do {
                                subopcion2 = leerEntero(
                                "\n--- MENU VER PACIENTES ---\n"
                                "1. Ver lista completa de pacientes\n"
                                "2. Buscar pacientes por fecha de ingreso\n"
                                "3. Buscar pacientes por ID\n"
                                "4. Buscar pacientes por nombre\n"
                                "5. Ver pacientes atendidos entre fechas determinadas\n"
                                "0. Salir\n"
                                "Ingrese una opcion: ");

                                switch(subopcion2) {
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
                                    // Ver pacientes atendidos entre fechas determinadas
                                    case 5: {
                                        CitaMedica::buscarCitasEnIntervalo(citas);
                                        break;
                                    }

                                    case 0:
                                        std::cout << "Volviendo al menu de pacientes...\n";
                                        break;

                                    default:
                                        std::cout << "Opcion no valida. Intente de nuevo.\n";
                                }

                            } while (subopcion2 != 0);

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
                    subopcion = leerEntero(
                        "\n--- MENU MEDICOS ---\n"
                        "1. Ver medicos\n"
                        "2. Editar medico\n"
                        "3. Eliminar medico\n"
                        "4. Registrar medico\n"
                        "0. Volver al menu principal\n"
                        "Seleccione una opcion: ");

                    switch(subopcion) {
                                    // ver medicos
                        case 1: {
                            int subopcion2;
                            std::string servicio, nombre;
                            do {
                                subopcion2 = leerEntero(
                                "\n--- MENU VER MEDICOS ---\n"
                                "1. Ver lista completa de medicos\n"
                                "2. Buscar medico por servicio\n"
                                "3. Buscar medico por ID\n"
                                "4. Buscar medico por nombre\n"
                                "5. Buscar medico por disponibilidad\n"
                                "0. Salir\n"
                                "Ingrese una opcion: ");

                                switch(subopcion2) {
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

                            } while (subopcion2 != 0);

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
            case 3: {
                int subopcion;
                do {
                    subopcion = leerEntero(
                        "\n--- MENU CITAS MEDICAS ---\n"
                        "1. Ver citas\n"
                        "2. Editar cita\n"
                        "3. Eliminar cita\n"
                        "4. Registrar cita\n"
                        "0. Volver al menu principal\n"
                        "Seleccione una opcion: ");

                    switch(subopcion) {
                                    // ver citas
                        case 1: {
                            int subopcion2;
                            std::string servicio, nombre;
                            do {
                                subopcion2 = leerEntero(
                                "\n--- MENU VER CITAS ORDENADAS ---\n"
                                "1. Ver las citas ordenadas\n"
                                "2. Buscar citas por fecha\n"
                                "3. Buscar citas por urgencia\n"
                                "4. Ver citas pasadas o futuras segun una fecha\n"
                                "5. Citas pendientes por medico\n"
                                "6. Citas pendientes por servicio\n"
                                "0. Salir\n"
                                "Ingrese una opcion: ");

                                switch(subopcion2) {
                                    
                                    // Ver todas las citas ordenadas por fecha/urgencia
                                    case 1: {
                                        int subopcion3;
                                        do{
                                            subopcion3 = leerEntero(
                                            "\n--- VER CITAS POR FECHA O URGENCIA ---\n"
                                            "1. Ver citas por fecha\n"
                                            "2. Ver citas por urgencia\n"
                                            "0. Salir\n"
                                            "Ingrese una opcion: ");
                                            switch(subopcion3) {
                                                // Ver citas por fecha
                                                case 1: {
                                                    std::cout << "\n--- Citas ordenadas por fecha ---\n\n";
                                                    CitaMedica::ordenarPorFecha(citas);
                                                    CitaMedica::mostrarCitas(citas);
                                                    break;
                                                    
                                                }
                                                // Ver citas por urgencia
                                                case 2: {
                                                    std::cout << "\n--- Citas ordenadas por urgencia ---\n\n";
                                                    CitaMedica::ordenarPorUrgencia(citas);
                                                    CitaMedica::mostrarCitas(citas);
                                                    break;
                                                }
                                            }
                                        }while (subopcion3 != 0);
                                        break;
                                    }
                                    // Buscar citas por fecha
                                    case 2: {
                                        CitaMedica::buscarCitasPorFecha(citas);
                                        break;
                                    }
                                    // Buscar citas por urgencia
                                    case 3: {
                                        CitaMedica::buscarCitasPorUrgencia(citas);
                                        break;
                                    }
                                    // Ver citas pasadas o futuras segun una fecha
                                    case 4: {
                                        CitaMedica::buscarCitasPorFechaComparada(citas);
                                        break;
                                    }
                                    // Citas pendientes por medico
                                    case 5: {
                                        CitaMedica::listarCitasPendientesPorMedico(citas);
                                        break;
                                    }
                                    // Citas pendientes por servicio
                                    case 6: {
                                        CitaMedica::listarCitasPendientesPorServicio(citas);
                                        break;
                                    }
                                    
                                    case 0:
                                        std::cout << "Volviendo al menu de citas...\n";
                                        break;

                                    default:
                                        std::cout << "Opcion no valida. Intente de nuevo.\n";
                                }

                            } while (subopcion2 != 0);

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
                            // Registro de historial clinico
            case 4: {
                Reporte reporte;
                reporte.verHistorialClinico(citas);
                break;
            }
                            // Registrar enfermedad cronica
            case 5: {
                reporte.modificarEnfermedadCronica(pacientes);
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
    for (auto paciente : pacientes) {
        delete paciente;
    }
    
    return 0;
}
