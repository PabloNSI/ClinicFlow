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
#include "servicio.h"
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

void cargarServicios(std::vector<Servicio*>& servicios) {
    std::ifstream archivoServicios("servicios.txt");
    if (archivoServicios.is_open()) {
        std::string nombreServicio;
        while (std::getline(archivoServicios, nombreServicio)) {
            servicios.push_back(new Servicio(nombreServicio));
        }
        archivoServicios.close();
    } else {
        std::cerr << "Error al abrir el archivo de servicios.\n";
    }
}


int main() {
    std::vector<Paciente*> pacientes;
    std::vector<CitaMedica*> citas;
    std::vector<Medico*> medicos;
    std::vector<Servicio*> servicios;
    int opcion;
    GestorArchivos gestor;

    gestor.recuperarDatosPacientes(pacientes);
    gestor.recuperarDatosMedicos(medicos);
    gestor.recuperarDatosCitas(citas, pacientes, medicos);
    cargarServicios(servicios);

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Agregar o editar paciente\n";
        std::cout << "2. Agregar o editar medico\n";
        std::cout << "3. Agregar o editar citas medicas\n";
        std::cout << "4. Agregar medico a un servicio\n";
        std::cout << "5. Mostrar medicos por servicio\n";
        std::cout << "6. Mostrar especialidad de cada medico\n";
        std::cout << "7. Mostrar medico en un servicio con especialidad\n";
        std::cout << "8. Pacientes atendidos entre fechas determinadas\n";
        std::cout << "9. Citas pendientes por medico\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
                            // Agregar o editar paciente
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
                            std::cout << "\n--- Lista de Pacientes ---\n";
                            if (pacientes.empty()) {
                                std::cout << "No hay pacientes registrados.\n";
                            }else {
                                for (const auto& paciente : pacientes) {
                                    paciente->mostrarPaciente();
                                }
                            }break;
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
                            // Agregar o editar medico
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
                            std::cout << "\n--- Lista de Medicos ---\n";
                            if (medicos.empty()) {
                                std::cout << "No hay medicos en el sistema.\n";
                            }else {
                                for (const auto& medico : medicos) {
                                    medico->mostrarMedico();
                                }
                            }break;
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
                    }
                } while (subopcion != 0);
                break;
            }
                            // Agregar o editar  citas medicas
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
                            std::cout << "\n--- Lista de Citas ---\n";
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
                    }
                } while (subopcion != 0);
                break;
            }
                            // Agregar medico a un servicio
            case 4: {
                std::string servicioNombre;
                int medicoID;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin >> std::ws, servicioNombre);
                std::cout << "ID del medico: ";
                std::cin >> medicoID;

                std::cout << "Buscando medico con ID: [" << medicoID << "]\n";
                // Buscar medico por ID
                Medico* medico = nullptr;
                for (auto& m : medicos) {
                    if (medico->getID() == medicoID) {
                        medico = m;
                        break;
                    }
                }
                if (medico) {
                    std::cout << "Medico encontrado: " << medico->getNombre() << "\n";
                    // Buscar servicio por nombre
                    Servicio* servicio = nullptr;
                    for (auto& s : servicios) {
                        std::string servicioActual = s->getNombreServicio();
                        // Convertir ambos a minus para compararlos
                        std::transform(servicioActual.begin(), servicioActual.end(), servicioActual.begin(), ::tolower);
                        std::transform(servicioNombre.begin(), servicioNombre.end(), servicioNombre.begin(), ::tolower);

                        if (servicioActual == servicioNombre) {
                            servicio = s;
                            break;
                        }
                    }
                    if (!servicio) {
                        std::cout << "Servicio no encontrado. Creando nuevo servicio...\n";
                        servicio = new Servicio(servicioNombre);
                        servicios.push_back(servicio);
                    }
                    servicio->agregarMedico(medico);
                } else {
                    std::cout << "Medico no encontrado.\n";
                }
                break;
            }
                            // Mostrar medicos por servicio 
            case 5: {
                std::string servicioNombre;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin >> std::ws, servicioNombre);

                // Convertir a minus para comparación
                std::transform(servicioNombre.begin(), servicioNombre.end(), servicioNombre.begin(), ::tolower);

                std::ifstream archivo("medicos_por_servicio.txt");
                if (!archivo.is_open()) {
                    std::cerr << "Error al abrir el archivo medicos_por_servicio.txt.\n";
                    break;
                }

                std::string linea, servicioActual, medicoActual;
                int idActual;
                bool servicioEncontrado = false;
                std::set<std::string> medicosUnicos; // Para evitar duplicados

                while (std::getline(archivo, linea)) {
                    if (linea.rfind("Servicio: ", 0) == 0) {  // Linea de servicio
                        servicioActual = linea.substr(10);   // Extraer el nombre del servicio
                        std::transform(servicioActual.begin(), servicioActual.end(), servicioActual.begin(), ::tolower);
                    } else if (linea.rfind("Medico: ", 0) == 0) {  // Línea de médico
                        medicoActual = linea.substr(8);  // Extraer el nombre del médico
                    } else if (linea.rfind("ID: ", 0) == 0) {  // Línea de ID
                        idActual = std::stoi(linea.substr(4));  // Extraer el ID

                        // Verificar si ya tenemos un servicio valido
                        if (!servicioActual.empty() && servicioActual == servicioNombre) {
                            if (!servicioEncontrado) {
                                std::cout << "Medicos en el servicio " << servicioNombre << ":\n";
                                servicioEncontrado = true;
                            }

                            // Validar que tanto el medico como el ID esten completos
                            if (!medicoActual.empty() && idActual > 0) {
                                std::string idActualStr = std::to_string(idActual);
                                std::string claveMedico = medicoActual + " (ID: " + idActualStr + ")";
                                if (medicosUnicos.find(claveMedico) == medicosUnicos.end()) {
                                    medicosUnicos.insert(claveMedico);
                                    std::cout << "- " << claveMedico << "\n";
                                }
                            }
                        }
                        // Reiniciar las variables de médico e ID para evitar arrastrar datos incorrectos
                        medicoActual.clear();
                    }
                }
                if (!servicioEncontrado) {
                    std::cout << "Servicio no encontrado.\n";
                }
                archivo.close();
                break;
            }
                            // Mostrar especialidad de cada medico
            case 6: {
                std::cout << "Especialidad de cada medico:\n";
                for (auto& medico : medicos) {
                    std::cout << "Medico: " << medico->getNombre() << " - Especialidad: " << medico->getEspecialidad() << "\n";
                }
                break;
            }
                            // Mostrar medico en un servicio con especialidad
            case 7: {
                std::string servicioNombre, especialidad;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin, servicioNombre);
                std::cout << "Especialidad: ";
                std::getline(std::cin, especialidad);

                for (auto& servicio : servicios) {
                    if (servicio->getNombreServicio() == servicioNombre) {
                        servicio->buscarMedicosPorEspecialidad(especialidad);
                        break;
                    }
                }
                break;
            }
                            // Pacientes atendidos entre fechas determinadas
            case 8: {
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
            case 9: {
                int medicoID;
                std::cout << "ID del medico: ";
                std::cin >> medicoID;
                Reporte reporte;
                reporte.listarCitasPendientes(citas, "medico");
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

    // Guardar datos de pacientes y medicos en sus archivos
    gestor.guardarDatosPacientes(pacientes);
    gestor.guardarDatosMedicos(medicos);
    gestor.guardarDatosCitas(citas);

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
