#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "citaMedica.h"
#include "gestorArchivos.h"
#include "paciente.h"
#include "medico.h"
#include "servicio.h"
#include "reporte.h"

Paciente* buscarPacientePorID(const std::vector<Paciente*>& pacientes, const std::string& idBuscado) {
    for (auto& p : pacientes) {
        if (p->getID() == idBuscado) {
            return p;
        }
    }
    return nullptr;
}

Medico* buscarMedicoPorID(const std::vector<Medico*>& medicos, const std::string& idBuscado) {
    for (auto& m : medicos) {
        if (m->getID() == idBuscado) {
            return m;
        }
    }
    return nullptr;
}

int main() {
    std::vector<Paciente*> pacientes;
    std::vector<Medico*> medicos;
    std::vector<Servicio*> servicios;
    std::vector<CitaMedica*> citas;

    int opcion;

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Registrar paciente\n";
        std::cout << "2. Registrar medico\n";
        std::cout << "3. Ver pacientes registrados\n";
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
                            // Registrar paciente
            case 1: {
                std::string nombre, ID, fechaIngreso;
                std::cout << "Nombre del paciente: ";
                std::getline(std::cin >> std::ws, nombre);
                std::cout << "ID del paciente (1234): ";
                std::getline(std::cin, ID);
                std::cout << "Fecha de ingreso (dd-MM-AAAA): ";
                std::getline(std::cin, fechaIngreso);
                Paciente* nuevoPaciente = new Paciente(nombre, ID, fechaIngreso);
                nuevoPaciente->registrarPaciente();
                pacientes.push_back(nuevoPaciente);
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
                    std::cerr << "Error al abrir el archivo de médicos.\n";
                }
                break;
            }
                                        // Asignar cita en una fecha determinada
            case 5: {
                std::string fecha;
                int urgencia;
                std::string pacienteID, medicoID;
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
                // Solicitar ID
                std::cout << "ID del paciente: ";
                std::getline(std::cin >> std::ws, pacienteID);
                std::cout << "ID del medico: ";
                std::getline(std::cin >> std::ws, medicoID);
                // Buscar paciente y médico
                Paciente* paciente = buscarPacientePorID(pacientes, pacienteID);
                Medico* medico = buscarMedicoPorID(medicos, medicoID);
                // Validar y asignar cita
                if (paciente && medico) {
                    CitaMedica* nuevaCita = new CitaMedica(fecha, urgencia, paciente, medico);
                    nuevaCita->asignarCita();
                    citas.push_back(nuevaCita);
                    paciente->añadirCita(nuevaCita);
                    medico->añadirCita(nuevaCita);
                    std::cout << "Cita asignada correctamente.\n";
                } else {
                    std::cout << "Paciente o medico no encontrado. \n";
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

                std::cout << "Buscando medico con ID: [" << medicoID << "]\n";  // Depuración del ID
                // Buscar medico por ID
                Medico* medico = nullptr;
                for (auto& m : medicos) {
                    if (m->getID() == medicoID) {
                        medico = m;
                        break;
                    }
                }
                if (medico) {
                    // Buscar servicio por nombre
                    Servicio* servicio = nullptr;
                    for (auto& s : servicios) {
                        if (s->getNombreServicio() == servicioNombre) {
                            servicio = s;
                            break;
                        }
                    }
                    if (!servicio) {
                        servicio = new Servicio(servicioNombre);
                        servicios.push_back(servicio);
                    }
                    servicio->agregarMedico(medico);
                    std::cout << "Medico agregado al servicio exitosamente.\n";
                } else {
                    std::cout << "Medico no encontrado.\n";
                }
                break;
            }
            // Mostrar medicos por servicio
            case 7: {
                std::string servicioNombre;
                std::cout << "Nombre del servicio: ";
                std::getline(std::cin, servicioNombre);

                bool servicioEncontrado = false;
                for (auto& servicio : servicios) {
                    std::string servicioActual = servicio->getNombreServicio();
                    std::transform(servicioActual.begin(), servicioActual.end(), 
                    servicioActual.begin(), ::tolower);
                    std::transform(servicioNombre.begin(), servicioNombre.end(), 
                    servicioNombre.begin(), ::tolower);

                    if (servicioActual == servicioNombre) {
                        servicio->listarMedicosPorServicio();  
                        servicioEncontrado = true;
                        break;
                    }
                }
                if (!servicioEncontrado) {
                    std::cout << "Servicio no encontrado.\n";
                }
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

    return 0;
}
