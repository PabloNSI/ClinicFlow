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
        // Verificar que la fecha tiene el formato correcto (DD-MM-AAAA)
        if (fecha.size() != 10 || fecha[2] != '-' || fecha[5] != '-') {
            return false;
        }

        // Extraer día, mes y año
        int dia = std::stoi(fecha.substr(0, 2));
        int mes = std::stoi(fecha.substr(3, 2));
        int año = std::stoi(fecha.substr(6, 4));

        // Validar día (1-31 dependiendo del mes)
        if (dia < 1 || dia > 31) return false;

        // Validar mes (1-12)
        if (mes < 1 || mes > 12) return false;

        // Validar año (año positivo)
        if (año < 1) return false;

        // Validaciones adicionales para los meses con menos de 31 días
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            if (dia > 30) return false;
        } else if (mes == 2) {
            // Verificar año bisiesto
            bool bisiesto = (año % 4 == 0 && (año % 100 != 0 || año % 400 == 0));
            if ((bisiesto && dia > 29) || (!bisiesto && dia > 28)) return false;
        }

        return true;
    }

// FUNCIONES ADICIONALES DE VER CITAS MEDICAS      
    // Función estática para ordenar por fecha (de mayor a menor)
    static void ordenarPorFecha(std::vector<CitaMedica*>& citas) {
        for (size_t i = 0; i < citas.size(); ++i) {
            for (size_t j = 0; j < citas.size() - i - 1; ++j) {
                // Dividir la fecha en componentes (día, mes, año)
                int dia1 = std::stoi(citas[j]->getFecha().substr(0, 2));
                int mes1 = std::stoi(citas[j]->getFecha().substr(3, 2));
                int año1 = std::stoi(citas[j]->getFecha().substr(6, 4));

                int dia2 = std::stoi(citas[j + 1]->getFecha().substr(0, 2));
                int mes2 = std::stoi(citas[j + 1]->getFecha().substr(3, 2));
                int año2 = std::stoi(citas[j + 1]->getFecha().substr(6, 4));

                // Comparar año, luego mes, luego día
                if (año1 < año2 || (año1 == año2 && mes1 < mes2) || (año1 == año2 && mes1 == mes2 && dia1 < dia2)) {
                    std::swap(citas[j], citas[j + 1]);
                }
            }
        }
    }

    // Función estática para ordenar por urgencia (de mayor a menor)
    static void ordenarPorUrgencia(std::vector<CitaMedica*>& citas) {
        for (size_t i = 0; i < citas.size(); ++i) {
            for (size_t j = 0; j < citas.size() - i - 1; ++j) {
                if (citas[j]->getUrgencia() < citas[j + 1]->getUrgencia()) {
                    std::swap(citas[j], citas[j + 1]);
                }
            }
        }
    }

    // Ver todas las citas
    static void mostrarCitas(const std::vector<CitaMedica*>& citas) {
        for (const auto& cita : citas) {
            cita->mostrarCita();
        }
    }

    // Buscar citas por fecha
    static void buscarCitasPorFecha(std::vector<CitaMedica*>& citas) {
        std::string fecha;
        std::cout << "Ingrese la fecha (DD-MM-AAAA) a buscar: ";
        std::cin.ignore();
        std::getline(std::cin, fecha);
        std::cout << "\n";

        bool encontrado = false;
        for (CitaMedica* cita : citas) {
            if (cita->getFecha() == fecha) {
                cita->mostrarCita();
                encontrado = true;
            }
        }

        if (!encontrado) {
            std::cout << "No se encontraron citas para la fecha ingresada.\n";
        }
    }

    // Buscar citas por urgencia
    static void buscarCitasPorUrgencia(std::vector<CitaMedica*>& citas) {
        int urgencia;
        std::cout << "Ingrese el nivel de urgencia (1-5) a buscar: ";
        std::cin >> urgencia;
        std::cin.ignore();
        std::cout << "\n";

        bool encontrado = false;
        for (CitaMedica* cita : citas) {
            if (cita->getUrgencia() == urgencia) {
                cita->mostrarCita();
                encontrado = true;
            }
        }

        if (!encontrado) {
            std::cout << "No se encontraron citas con el nivel de urgencia " << urgencia << ".\n";
        }
    }

    // Ver citas pasadas o futuras segun una fecha
    static void buscarCitasPorFechaComparada(std::vector<CitaMedica*>& citas) {
        std::string fechaComparada;
        bool esPasada;

        std::cout << "Ingrese la fecha (DD-MM-AAAA): ";
        std::cin.ignore();
        std::getline(std::cin, fechaComparada);

        std::cout << "Quieres buscar citas pasadas o futuras? (1 = pasadas / 0 = futuras): ";
        std::cin >> esPasada;
        std::cin.ignore();
        std::cout << "\n";

        bool encontrado = false;

        // Dividir la fecha ingresada por el usuario en componentes (día, mes, año)
        int diaComparado = std::stoi(fechaComparada.substr(0, 2));
        int mesComparado = std::stoi(fechaComparada.substr(3, 2));
        int añoComparado = std::stoi(fechaComparada.substr(6, 4));

        for (CitaMedica* cita : citas) {
            // Obtener la fecha de las citas
            std::string citaFecha = cita->getFecha();
            int diaCita = std::stoi(citaFecha.substr(0, 2));
            int mesCita = std::stoi(citaFecha.substr(3, 2));
            int añoCita = std::stoi(citaFecha.substr(6, 4));

            // Comparar las fechas (si son pasadas o futuras)
            bool esPasadaCita = (añoCita < añoComparado) || 
                                (añoCita == añoComparado && mesCita < mesComparado) || 
                                (añoCita == añoComparado && mesCita == mesComparado && diaCita < diaComparado);

            // Si queremos citas pasadas, comparamos si la cita es anterior a la fecha ingresada y viceversa
            if ((esPasada && esPasadaCita) || (!esPasada && !esPasadaCita)) {
                cita->mostrarCita();
                encontrado = true;
            }
        }

        if (!encontrado) {
            std::cout << "No se encontraron citas.\n";
        }
    }

    // Método para mostrar citas entre dos fechas -> ver pacientes
    static void buscarCitasEnIntervalo(const std::vector<CitaMedica*>& citas) {
        std::string fechaInicio, fechaFin;

        // Solicitar la fecha de inicio
        do {
            std::cout << "Ingrese la fecha de inicio (DD-MM-AAAA): ";
            std::cin.ignore();
            std::getline(std::cin, fechaInicio); // Leer la fecha de inicio
            if (!esFechaValida(fechaInicio)) {
                std::cout << "Fecha invalida, por favor intente de nuevo.\n";
            }
        } while (!esFechaValida(fechaInicio));

        do {
            std::cout << "Ingrese la fecha de fin (DD-MM-AAAA): ";
            std::getline(std::cin, fechaFin);  // Leer la fecha de fin
            if (!esFechaValida(fechaFin)) {
                std::cout << "Fecha invalida, por favor intente de nuevo.\n";
            }
        } while (!esFechaValida(fechaFin));

        // Convertir las fechas de inicio y fin a componentes numéricos
        int diaInicio, mesInicio, añoInicio;
        int diaFin, mesFin, añoFin;

            diaInicio = std::stoi(fechaInicio.substr(0, 2));
            mesInicio = std::stoi(fechaInicio.substr(3, 2));
            añoInicio = std::stoi(fechaInicio.substr(6, 4));

            diaFin = std::stoi(fechaFin.substr(0, 2));
            mesFin = std::stoi(fechaFin.substr(3, 2));
            añoFin = std::stoi(fechaFin.substr(6, 4));
        

        // Verificar si la fecha de inicio es mayor que la fecha de fin
        if (añoInicio > añoFin || (añoInicio == añoFin && mesInicio > mesFin) || 
            (añoInicio == añoFin && mesInicio == mesFin && diaInicio > diaFin)) {
            std::cout << "La fecha de inicio no puede ser posterior a la fecha de fin.\n";
            return; // Salir si el intervalo es inválido
        }

        bool encontrado = false;

        std::cout << "\n";

        // Recorremos todas las citas existentes
        for (CitaMedica* cita : citas) {
            // Obtener la fecha de la cita
            std::string citaFecha = cita->getFecha();
            int diaCita, mesCita, añoCita;

            try {
                diaCita = std::stoi(citaFecha.substr(0, 2));
                mesCita = std::stoi(citaFecha.substr(3, 2));
                añoCita = std::stoi(citaFecha.substr(6, 4));
            } catch (const std::invalid_argument&) {
                std::cout << "Error al convertir la fecha de una cita. Verifique la validez de los datos.\n";
                continue; // Continuar con la siguiente cita si la fecha es inválida
            }

            // Verificar si la fecha de la cita está dentro del rango especificado
            bool dentroDelRango = 
                (añoCita > añoInicio || (añoCita == añoInicio && (mesCita > mesInicio || (mesCita == mesInicio && diaCita >= diaInicio)))) && // Fecha posterior a la de inicio
                (añoCita < añoFin || (añoCita == añoFin && (mesCita < mesFin || (mesCita == mesFin && diaCita <= diaFin))));  // Fecha anterior a la de fin

            if (dentroDelRango) {
                cita->mostrarCita();
                encontrado = true;
            }
        }

        if (!encontrado) {
            std::cout << "No se encontraron citas en el intervalo de fechas especificado.\n";
        }
    }

    // Función estática para listar las citas pendientes por médico
    static void listarCitasPendientesPorMedico(const std::vector<CitaMedica*>& citas) {
        std::string nombreMedico;
        std::cin.ignore();
        std::cout << "Ingrese el nombre del medico: ";
        std::getline(std::cin, nombreMedico);
        // Buscar si el medico existe en alguna de las citas
        bool medicoEncontrado = false;
        for (const auto& cita : citas) {
            if (cita->getMedico()->getNombre() == nombreMedico) {
                medicoEncontrado = true;
                break;
            }
        }
        if (!medicoEncontrado) {
            std::cout << "El medico ingresado no tiene citas pendientes.\n";
            std::cout << "Desea intentarlo nuevamente? (s = 1/n = 0): ";
            int opcion;
            std::cin >> opcion;
            if (opcion == 'n' || opcion == 'N' || opcion == '0') {
                return;
            } else {
                listarCitasPendientesPorMedico(citas);
            }
        } else {
            // Solicitar la fecha actual
            std::string fechaActual;
            while (true) {
                std::cout << "Ingrese la fecha actual (DD-MM-AAAA): ";
                std::cin >> fechaActual;

                if (esFechaValida(fechaActual)) {
                    break;
                } else {
                    std::cout << "Fecha invalida. Intente nuevamente.\n";
                }
            }

            // Extraer día, mes y año de la fecha actual
            int diaActual = std::stoi(fechaActual.substr(0, 2));
            int mesActual = std::stoi(fechaActual.substr(3, 2));
            int añoActual = std::stoi(fechaActual.substr(6, 4));

            bool citasEncontradas = false;
            for (const auto& cita : citas) {
                if (cita->getMedico()->getNombre() == nombreMedico) {
                    // Obtener la fecha de la cita
                    std::string citaFecha = cita->getFecha();
                    int diaCita = std::stoi(citaFecha.substr(0, 2));
                    int mesCita = std::stoi(citaFecha.substr(3, 2));
                    int añoCita = std::stoi(citaFecha.substr(6, 4));

                    // Comparar la fecha de la cita con la fecha actual
                    bool esFutura = (añoCita > añoActual) ||
                                    (añoCita == añoActual && mesCita > mesActual) ||
                                    (añoCita == añoActual && mesCita == mesActual && diaCita > diaActual);

                    if (esFutura) {
                        cita->mostrarCita();
                        citasEncontradas = true;
                    }
                }
            }

            if (!citasEncontradas) {
                std::cout << "No hay citas pendientes para  " << nombreMedico << ".\n";
            }
        }
    }

    // Función estática para listar las citas pendientes por servicio
    static void listarCitasPendientesPorServicio(const std::vector<CitaMedica*>& citas) {
        while (true) {
            std::string servicio;
            std::cin.ignore();
            std::cout << "Ingrese el servicio: ";
            std::getline(std::cin, servicio);
            // Verificar si el servicio es valido
            Medico tempMedico;
            if (!tempMedico.esServicioValido(servicio)) {
                std::cout << "El servicio ingresado no es valido.\n";
                std::cout << "Desea intentarlo nuevamente? (s = 1/n = 0): ";
                char opcion;
                std::cin >> opcion;
                if (opcion == 'n' || opcion == 'N' || opcion == '0') {
                    return;
                }
                continue;
            }
            // Solicitar la fecha actual
            std::string fechaActual;
            while (true) {
                std::cout << "Ingrese la fecha actual (DD-MM-AAAA): ";
                std::cin >> fechaActual;

                if (esFechaValida(fechaActual)) {
                    break;
                } else {
                    std::cout << "Fecha invalida. Intente nuevamente.\n";
                }
            }

            // Extraer día, mes y año de la fecha actual
            int diaActual = std::stoi(fechaActual.substr(0, 2));
            int mesActual = std::stoi(fechaActual.substr(3, 2));
            int añoActual = std::stoi(fechaActual.substr(6, 4));

            bool citasEncontradas = false;
            for (const auto& cita : citas) {
                if (cita->getMedico()->getServicio() == servicio) {
                    // Obtener la fecha de la cita
                    std::string citaFecha = cita->getFecha();
                    int diaCita = std::stoi(citaFecha.substr(0, 2));
                    int mesCita = std::stoi(citaFecha.substr(3, 2));
                    int añoCita = std::stoi(citaFecha.substr(6, 4));

                    // Comparar la fecha de la cita con la fecha actual
                    bool esFutura = (añoCita > añoActual) ||
                                    (añoCita == añoActual && mesCita > mesActual) ||
                                    (añoCita == añoActual && mesCita == mesActual && diaCita > diaActual);

                    if (esFutura) {
                        cita->mostrarCita();
                        citasEncontradas = true;
                    }
                }
            }

            if (!citasEncontradas) {
                std::cout << "No hay citas pendientes en este servicio.\n";
                std::cout << "Desea intentarlo nuevamente? (s = 1/n = 0): ";
                char opcion;
                std::cin >> opcion;
                std::cin.ignore();
                if (opcion == 'n' || opcion == 'N' || opcion == '0') {
                    return;
                }
                continue;
            }
            break;
        }
    }

// FUNCIONES DEL CRUD     
    // Ver cita
    void mostrarCita() const {
        std::cout << "Servicio: " << medico->getServicio() << "\n"
                  << "Fecha: " << fecha << "\n"
                  << "Paciente: " << paciente->getNombre()
                  << " (ID: " << paciente->getID() << ")" << "\n"
                  << "Medico: Dr. " << medico->getNombre()
                  << "( ID: " << medico->getID() << ")" << "\n"
                  << "Urgencia: " << urgencia << "\n"
                  << "-----------" << "\n";
    }

    // Registrar una cita
    static void registrarCita(std::vector<Paciente*>& pacientes, std::vector<Medico*>& medicos, std::vector<CitaMedica*>& citas) {
        std::string fecha;
        int urgencia, pacienteID, medicoID;

        while (true) {
            std::cin.ignore();
            std::cout << "Fecha de la cita (DD-MM-AAAA): ";
            std::getline(std::cin, fecha);
            if (esFechaValida(fecha)) {
                break;
            } else {
                std::cout << "Intentalo de nuevo (DD-MM-AAAA).\n";
            }
        }
        while (true) {
            std::cout << "Urgencia (1-5): ";
            std::cin >> urgencia;
            if (urgencia >= 1 && urgencia <= 5) {
                break;
            } else {
                std::cout << "Intentalo de nuevo (1-5).\n";
            }
        }
        std::cin.ignore();
        while (true) {
            std::cout << "Pacientes disponibles:\n";
            for (Paciente* p : pacientes) {
                std::cout << "ID: " << p->getID() << ", Nombre: " << p->getNombre() << "\n";
            }
            std::cout << "ID del paciente: ";
            std::cin >> pacienteID;
            
            std::cout << "Medicos disponibles:\n";
            for (Medico* m : medicos) {
                std::cout << "Dr. " << m->getNombre() << ", Servicio: " << m->getServicio() << ", ID: " << m->getID() << "\n";
            }
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
                std::cout << "Paciente o medico no encontrado. Intentalo de nuevo.\n";
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
        std::cin.ignore();
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
