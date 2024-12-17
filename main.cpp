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

Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, const std::string& id) {
    for (Medico* medico : medicos) {
        if (medico->compararID(id)) {
            return medico;
        }
    }
    return nullptr;
}

void cargarMedicos(std::vector<Medico*>& medicos) {
    std::ifstream archivo("medicos.txt");
    if (archivo.is_open()) {
        std::string linea, nombre, ID, especialidad;
        bool disponibilidad;

        while (std::getline(archivo, linea)) {
            if (linea.find("Nombre: ") != std::string::npos) {
                nombre = linea.substr(8); // Extraer el nombre
            } else if (linea.find("ID: ") != std::string::npos) {
                ID = linea.substr(4); // Extraer el ID
            } else if (linea.find("Especialidad: ") != std::string::npos) {
                especialidad = linea.substr(13); // Extraer la especialidad
            } else if (linea.find("Disponibilidad: ") != std::string::npos) {
                disponibilidad = (linea.substr(15) == "Si"); // Convertir a booleano
                // Crear un nuevo objeto Medico y añadirlo al vector
                medicos.push_back(new Medico(nombre, ID, especialidad, disponibilidad));
            }
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo medicos.txt.\n";
    }
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
    cargarMedicos(medicos);
    cargarServicios(servicios);

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Agregar o editar paciente\n";
        std::cout << "2. Registrar medico\n";
        std::cout << "3. (funcion 1)\n";
        std::cout << "4. Ver medicos registrados\n";
        std::cout << "5. Asignar cita en una fecha determinada\n";
        std::cout << "6. Agregar medico a un servicio\n";
        std::cout << "7. Mostrar medicos por servicio\n";
        std::cout << "8. Mostrar especialidad de cada medico\n";
        std::cout << "9. Mostrar medico en un servicio con especialidad\n";
        std::cout << "10. Pacientes atendidos entre fechas determinadas\n";
        std::cout << "11. Citas pendientes por medico\n";
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
                        case 1: {
                            std::cout << "\n--- Lista de Pacientes ---\n";
                            if (pacientes.empty()) {
                                std::cout << "No hay pacientes registrados.\n";
                            } else {
                                for (const auto& paciente : pacientes) {
                                    paciente->mostrarPaciente();
                                }
                            }
                            break;
                        }
                        case 2: {
                            int idPaciente;
                            std::cout << "Ingrese el ID del paciente a editar: ";
                            std:: cin >> idPaciente;

                            auto it = std::find_if(pacientes.begin(), pacientes.end(),
                                [&idPaciente](Paciente* p) { return p->getID() == idPaciente; });

                            if (it != pacientes.end()) {
                                (*it)->editarPaciente();
                            } else {
                                std::cout << "Paciente no encontrado.\n";
                            }
                            break;
                        }
                        case 3: {
                            int idPaciente;
                            std::cout << "Ingrese el ID del paciente a eliminar: ";
                            std:: cin >> idPaciente;

                            std::cout << "Estas seguro de eliminar al paciente con ID " << idPaciente << "? (1 para confirmar, 0 para cancelar): ";
                            int confirmar;
                            std::cin >> confirmar;
                            std::cin.ignore(); // Limpiar el buffer de entrada

                            if (confirmar == 1) {
                                Paciente::eliminarPaciente(pacientes, idPaciente);
                                std::cout << "Paciente eliminado correctamente.\n";
                            } else {
                                std::cout << "Eliminacion cancelada.\n";
                            }
                            break;
                        }
                        case 4: {
                            std::string nombre, fechaIngreso;
                            int ID;
                            std::cout << "Nombre del paciente: ";
                            std::getline(std::cin >> std::ws, nombre);
                            std::cout << "ID del paciente (1234): ";
                            std::cin >> ID;

                            std::cout << "Ingrese la fecha de ingreso (dd-MM-AAAA): ";
                            std::getline(std::cin, fechaIngreso);

                            Paciente* nuevoPaciente = new Paciente(nombre, ID, fechaIngreso);
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
                                // Registrar medico
            case 2: {
                std::string nombre, ID, especialidad;
                bool disponibilidad;
                std::cout << "Nombre del medico: ";
                std::getline(std::cin >> std::ws, nombre);
                std::cout << "ID del medico (1234): ";
                std::getline(std::cin, ID);
                std::cout << "Especialidad del medico: ";
                std::getline(std::cin, especialidad);
                std::cout << "Medico disponible (1 para si, 0 para no): ";
                std::cin >> disponibilidad;
                Medico* nuevoMedico = new Medico(nombre, ID, especialidad, disponibilidad);
                nuevoMedico->registrarMedico();
                medicos.push_back(nuevoMedico);
                break;
            }
                            // Ver pacientes registrados
            case 3: {
                std::ifstream archivo("pacientes.txt");
                if (archivo.is_open()) {
                    std::cout << "\nLista de pacientes registrados:\n";
                    std::string linea;
                    while (std::getline(archivo, linea)) {
                        std::cout << linea << "\n";
                    }
                    archivo.close();
                } else {
                    std::cerr << "Error al abrir el archivo de pacientes.\n";
                }
                break;
            }
                            // Ver medicos registrados
            case 4: {
                std::ifstream archivo("medicos.txt");
                if (archivo.is_open()) {
                    std::cout << "\nLista de medicos registrados:\n";
                    std::string linea;
                    while (std::getline(archivo, linea)) {
                        std::cout << linea << "\n";
                    }
                    archivo.close();
                } else {
                    std::cerr << "Error al abrir el archivo de medicos.\n";
                }
                break;
            }
                            // Asignar cita en una fecha determinada
            case 5: {
                std::string fecha;
                int urgencia;
                int  pacienteID;
                std::string medicoID;
                std::cout << "Fecha de la cita: ";
                std::getline(std::cin >> std::ws, fecha);

                std::cout << "Urgencia (1-5): ";
                while (!(std::cin >> urgencia) || urgencia < 1 || urgencia > 5) {
                    std::cout << "Por favor, ingrese un valor valido para la urgencia (1-5): ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "ID del paciente: ";
                std::cin >> pacienteID;
                std::cout << "ID del medico: ";
                std::getline(std::cin >> std::ws, medicoID);
                std::cout << "Pacientes cargados:\n";

                for (Paciente* p : pacientes) {
                    std::cout << "ID: " << p->getID() << "\n";
                }

                std::cout << "Medicos cargados:\n";
                for (Medico* m : medicos) {
                    std::cout << "ID: " << m->getID() << "\n";
                }

                Paciente* paciente = buscarPacientePorID(pacientes, pacienteID);
                Medico* medico = buscarMedicoPorID(medicos, medicoID);

                if (paciente && medico) {
                    CitaMedica* nuevaCita = new CitaMedica(fecha, urgencia, paciente, medico);
                    nuevaCita->asignarCita();
                    citas.push_back(nuevaCita);
                    paciente->añadirCita(nuevaCita);
                    medico->añadirCita(nuevaCita);
                    std::cout << "Cita asignada correctamente.\n";
                } else {
                    std::cout << "Paciente o medico no encontrado.\n";
                    std::cout << "Pacientes registrados: " << pacientes.size() << "\n";
                    std::cout << "Medicos registrados: " << medicos.size() << "\n";
                }
                break;
            }
                            // Agregar medico a un servicio
            case 6: {
                std::string servicioNombre, medicoID;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin >> std::ws, servicioNombre);
                std::cout << "ID del medico: ";
                std::getline(std::cin >> std::ws, medicoID);

                std::cout << "Buscando medico con ID: [" << medicoID << "]\n";
                // Buscar medico por ID
                Medico* medico = nullptr;
                for (auto& m : medicos) {
                    if (m->getID() == medicoID) {
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
            case 7: {
                std::string servicioNombre;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin >> std::ws, servicioNombre);

                // Convertir a minus para comparacion
                std::transform(servicioNombre.begin(), servicioNombre.end(), servicioNombre.begin(), ::tolower);

                std::ifstream archivo("medicos_por_servicio.txt");
                if (!archivo.is_open()) {
                    std::cerr << "Error al abrir el archivo medicos_por_servicio.txt.\n";
                    break;
                }

                std::string linea, servicioActual, medicoActual, idActual;
                bool servicioEncontrado = false;
                std::set<std::string> medicosUnicos; // Para evitar duplicados

                while (std::getline(archivo, linea)) {
                    if (linea.rfind("Servicio: ", 0) == 0) {  // Linea de servicio
                        servicioActual = linea.substr(10);   // Extraer el nombre del servicio
                        std::transform(servicioActual.begin(), servicioActual.end(), servicioActual.begin(), ::tolower);
                    } else if (linea.rfind("Medico: ", 0) == 0) {  // Línea de médico
                        medicoActual = linea.substr(8);  // Extraer el nombre del médico
                    } else if (linea.rfind("ID: ", 0) == 0) {  // Línea de ID
                        idActual = linea.substr(4);  // Extraer el ID

                        // Verificar si ya tenemos un servicio valido
                        if (!servicioActual.empty() && servicioActual == servicioNombre) {
                            if (!servicioEncontrado) {
                                std::cout << "Medicos en el servicio " << servicioNombre << ":\n";
                                servicioEncontrado = true;
                            }

                            // Validar que tanto el medico como el ID esten completos
                            if (!medicoActual.empty() && !idActual.empty()) {
                                std::string claveMedico = medicoActual + " (ID: " + idActual + ")";
                                if (medicosUnicos.find(claveMedico) == medicosUnicos.end()) {
                                    medicosUnicos.insert(claveMedico);
                                    std::cout << "- " << claveMedico << "\n";
                                }
                            }
                        }
                        // Reiniciar las variables de médico e ID para evitar arrastrar datos incorrectos
                        medicoActual.clear();
                        idActual.clear();
                    }
                }
                if (!servicioEncontrado) {
                    std::cout << "Servicio no encontrado.\n";
                }
                archivo.close();
                break;
            }

                            // Mostrar especialidad de cada medico
            case 8: {
                std::cout << "Especialidad de cada medico:\n";
                for (auto& medico : medicos) {
                    std::cout << "Medico: " << medico->getNombre() << " - Especialidad: " << medico->getEspecialidad() << "\n";
                }
                break;
            }
                            // Mostrar medico en un servicio con especialidad
            case 9: {
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
            case 10: {
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
            case 11: {
                std::string medicoID;
                std::cout << "ID del medico: ";
                std::getline(std::cin, medicoID);
                Reporte reporte;
                reporte.listarCitasPendientes(citas, "medico");
                break;
            }
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no valida. Intenta de nuevo.\n";
                break;
        }
    } while (opcion != 0);

    // Guardar pacientes en archivos
    gestor.guardarDatosPacientes(pacientes);

    // Liberar memoria
    for (Paciente* p : pacientes) {
        delete p;
    }

    return 0;
}
