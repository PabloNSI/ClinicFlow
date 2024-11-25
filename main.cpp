#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "citaMedica.h"
#include "gestorArchivos.h"
#include "paciente.h"
#include "medico.h"
#include "servicio.h"
#include "reporte.h"

int main() {
    Paciente paciente1("Juan Perez", "0001", "2023-10-21");
    Paciente paciente2("Ana Gomez", "0003", "2023-10-22");
    Medico medico1("Dr. Gomez", "M456", "Cardiologia", true);
    Medico medico2("Dr. Lopez", "M457", "Neurologia", true);

    paciente1.registrarPaciente();
    paciente2.registrarPaciente();
    medico1.registrarMedico();
    medico2.registrarMedico();

    CitaMedica cita1("2024-10-25", 5, &paciente1, &medico1);
    CitaMedica cita2("2024-11-01", 3, &paciente2, &medico2);
    
    cita1.asignarCita();
    cita2.asignarCita();

    paciente1.añadirCita(&cita1);
    paciente2.añadirCita(&cita2);
    medico1.añadirCita(&cita1);
    medico2.añadirCita(&cita2);

    Servicio servicio1("Cardiologia");
    servicio1.agregarMedico(&medico1);
    servicio1.agregarMedico(&medico2);
    servicio1.listarMedicosPorServicio();

    Reporte reporte;

    std::vector<CitaMedica*> citas = { &cita1, &cita2 };

    reporte.listarPacientesPorRangoFechas(citas, "2024-10-01", "2024-10-31");

    reporte.listarCitasPendientes(citas, "medico");

    std::vector<Paciente*> pacientes = { &paciente1, &paciente2 };
    reporte.reportePacientesCronicos(pacientes);

GestorArchivos gestor;

    gestor.guardarDatosPacientes(pacientes);

    std::vector<Paciente*> pacientesRecuperados;
    gestor.recuperarDatosPacientes(pacientesRecuperados);

    for (auto paciente : pacientesRecuperados) {
        std::cout << "Paciente: " << paciente->getNombre() << ", ID: " << paciente->getID() << std::endl;
    }
    return 0;
}
