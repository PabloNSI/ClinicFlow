#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class CitaMedica;

class Paciente {
private:
    std::string nombre;
    std::string ID;
    std::string fechaIngreso;
    std::vector<CitaMedica*> citas;

public:
    Paciente(std::string _nombre, std::string _ID, std::string _fechaIngreso)
        : nombre(_nombre), ID(_ID), fechaIngreso(_fechaIngreso) {}

    void registrarPaciente() {
        std::cout << "Paciente " << nombre << " registrado." << std::endl;
    }

    void eliminarPaciente() {
        std::cout << "Paciente " << nombre << " eliminado." << std::endl;
    }

    void modificarPaciente(std::string nuevoNombre, std::string nuevaID) {
        nombre = nuevoNombre;
        ID = nuevaID;
        std::cout << "Paciente modificado a " << nombre << " con ID " << ID << std::endl;
    }

    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }

    std::string getNombre() { return nombre; }
    std::string getID() { return ID; }
};

class Medico {
private:
    std::string nombre;
    std::string ID;
    std::string especialidad;
    bool disponibilidad;
    std::vector<CitaMedica*> citas;

public:
    Medico(std::string _nombre, std::string _ID, std::string _especialidad, bool _disponibilidad)
        : nombre(_nombre), ID(_ID), especialidad(_especialidad), disponibilidad(_disponibilidad) {}

    void registrarMedico() {
        std::cout << "Medico " << nombre << " registrado." << std::endl;
    }

    void modificarMedico(std::string nuevoNombre, std::string nuevaEspecialidad) {
        nombre = nuevoNombre;
        especialidad = nuevaEspecialidad;
        std::cout << "Medico modificado a " << nombre << " con especialidad " << especialidad << std::endl;
    }

    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }

    std::string getNombre() { return nombre; }
    std::string getEspecialidad() { return especialidad; }
};

class CitaMedica {
private:
    std::string fecha;
    int urgencia;
    Paciente* paciente;
    Medico* medico;

public:
    CitaMedica(std::string _fecha, int _urgencia, Paciente* _paciente, Medico* _medico)
        : fecha(_fecha), urgencia(_urgencia), paciente(_paciente), medico(_medico) {}

    void asignarCita() {
        std::cout << "Cita asignada para el paciente en la fecha " << fecha << std::endl;
    }

    void cancelarCita() {
        std::cout << "Cita cancelada para el paciente." << std::endl;
    }

    void modificarCita(std::string nuevaFecha, int nuevaUrgencia) {
        fecha = nuevaFecha;
        urgencia = nuevaUrgencia;
        std::cout << "Cita modificada a la fecha " << fecha << " con urgencia " << urgencia << std::endl;
    }

    std::string getFecha() { return fecha; }
    int getUrgencia() { return urgencia; }
};

class Servicio {
private:
    std::string nombreServicio;
    std::vector<Medico*> medicos;

public:
    Servicio(std::string _nombreServicio) : nombreServicio(_nombreServicio) {}

    void agregarMedico(Medico* medico) {
        medicos.push_back(medico);
        std::cout << "Medico " << medico->getNombre() << " agregado al servicio " << nombreServicio << std::endl;
    }

    void listarMedicosPorServicio() {
        std::cout << "Medicos en el servicio " << nombreServicio << ":\n";
        for (auto medico : medicos) {
            std::cout << "- " << medico->getNombre() << " (Especialidad: " << medico->getEspecialidad() << ")\n";
        }
    }
};

class GestorArchivos {
public:
    void guardarDatosPacientes(const std::vector<Paciente*>& pacientes) {
        std::ofstream archivo("pacientes.txt");
        for (auto paciente : pacientes) {
            archivo << paciente->getNombre() << "," << paciente->getID() << "\n";
        }
        archivo.close();
    }

    void recuperarDatosPacientes(std::vector<Paciente*>& pacientes) {
        std::ifstream archivo("pacientes.txt");
        std::string linea;
        while (std::getline(archivo, linea)) {
        }
        archivo.close();
    }
};

int main() {
    Paciente paciente1("Juan Perez", "123", "2023-10-21");
    Medico medico1("Dr. Gomez", "M456", "Cardiologia", true);

    paciente1.registrarPaciente();
    medico1.registrarMedico();

    CitaMedica cita1("2024-10-25", 5, &paciente1, &medico1);
    cita1.asignarCita();

    paciente1.añadirCita(&cita1);
    medico1.añadirCita(&cita1);

    Servicio servicio1("Cardiologia");
    servicio1.agregarMedico(&medico1);
    servicio1.listarMedicosPorServicio();

    return 0;
}
