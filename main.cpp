/*
7- En un instituto de investigaciones se necesita elaborar un sistema para el control de los medios (PC o laptop) que utilizan los trabajadores. De cada trabajador se conoce: Número de empelado, nombre y apellidos, categoría (jefe de grupo, investigador o técnico). De cada medio se conoce: nombre (PC de escritorio o laptop), número de inventario y estado (funcionando, roto o taller).
Defina e implemente las clases y los métodos que permitan:
 
•​Dar alta, baja y modificar trabajadores y medios.
 
•​A partir de los listados de los trabajadores y los medios:
 
a) Asignar un medio a cada trabajador. Para dicha asignación se debe guardar en una lista el número de empleado y el nombre del trabajador, así como el número de inventario del medio que le está siendo asignado. Sólo se asignarán medios que estén funcionando y las laptops son para ser asignadas únicamente a los investigadores, las cuales podrán utilizar fuera de la entidad.
b) Cambiar la categoría de un trabajador a investigador. En caso de tener asignado un medio anteriormente, se debe eliminar esta asignación y realizar una nueva con el medio que le corresponde según su nueva categoría de investigador (una laptop).
c) Cambiar el estado de un medio de trabajo a (roto o taller). En caso de estar asignado, se debe eliminar dicha asignación.
*/

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Funciones de utilidad
void limpiarEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpiarConsola() {
    system("cls");
}

void pausa() {
    cout << "Presione Enter para volver al menu...";
    cin.get();
}

// Declaración de clases 
class Empleado {
private:
    int id;
    string nombre;
    string categoria;

public:
    Empleado(int id, string nombre, string categoria) {
        this->setID(id);
        this->setNombre(nombre);
        this->setCategoria(categoria);
    }

    int getID() { return id; }
    string getNombre() { return nombre; }
    string getCategoria() { return categoria; }

    void setID(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setCategoria(string categoria) { this->categoria = categoria; }
};

class Medios {
private:
    string nombre;
    string inventario;
    string estado;
    int idEmpleadoAsignado;

public:
    Medios(string nombre, string inventario, string estado) {
        this->setNombre(nombre);
        this->setInventario(inventario);
        this->setEstado(estado);
        this->idEmpleadoAsignado = -1; 
    }

    string getNombre() { return nombre; }
    string getInventario() { return inventario; }
    string getEstado() { return estado; }
    int getAsignadoA() { return idEmpleadoAsignado; }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setInventario(string inventario) { this->inventario = inventario; }
    void setEstado(string estado) { this->estado = estado; }
    void asignarA(int idEmpleado) { this->idEmpleadoAsignado = idEmpleado; }
};

// Nodo para la lista de Empleados
struct NodoEmpleado {
    Empleado* empleado;
    NodoEmpleado* siguiente;
};

// Nodo para la lista de Medios
struct NodoMedios {
    Medios* medio;
    NodoMedios* siguiente;
};

// Cabezas de las listas enlazadas
NodoEmpleado* cabezaEmpleado = nullptr;
NodoMedios* cabezaMedios = nullptr;

// Funciones del menú
void altaEmpleado() {
    limpiarConsola();
    int id;
    string nombre;
    int categoriaOpcion;

    cout << "Ingrese ID del empleado (maximo 3 cifras): ";
    while (!(cin >> id) || id < 0 || id > 999) {
        cout << "Entrada invalida. Ingrese un ID numerico de hasta 3 cifras: ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    NodoEmpleado* temp = cabezaEmpleado;
    while (temp != nullptr) {
        if (temp->empleado->getID() == id) {
            cout << "El ID ya existe. Ingrese un ID unico: ";
            return;
        }
        temp = temp->siguiente;
    }

    cout << "Ingrese nombre completo del empleado: ";
    getline(cin, nombre);

    cout << "Seleccione categoria del empleado:\n";
    cout << "1 - Jefe de grupo\n";
    cout << "2 - Investigador\n";
    cout << "3 - Tecnico\n";
    cout << "Opcion: ";
    while (!(cin >> categoriaOpcion) || categoriaOpcion < 1 || categoriaOpcion > 3) {
        cout << "Entrada invalida. Seleccione una categoria valida (1, 2 o 3): ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    string categoria;
    switch (categoriaOpcion) {
        case 1:
            categoria = "Jefe de grupo";
            break;
        case 2:
            categoria = "Investigador";
            break;
        case 3:
            categoria = "Tecnico";
            break;
    }

    Empleado* nuevoEmpleado = new Empleado(id, nombre, categoria);
    NodoEmpleado* nuevoNodo = new NodoEmpleado;
    nuevoNodo->empleado = nuevoEmpleado;
    nuevoNodo->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoNodo;

    cout << "Empleado agregado exitosamente.\n";
    pausa();
}

void bajaEmpleado() {
    limpiarConsola();

    if (cabezaEmpleado == nullptr) {
        cout << "No hay empleados registrados.\n";
        pausa();
        return;
    }

    int id;
    cout << "Ingrese ID del empleado a eliminar: ";
    while (!(cin >> id)) {
        cout << "Entrada invalida. Ingrese ID del empleado a eliminar: ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    NodoEmpleado* temp = cabezaEmpleado;
    NodoEmpleado* prev = nullptr;

    while (temp != nullptr && temp->empleado->getID() != id) {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp == nullptr) {
        cout << "Empleado no encontrado.\n";
    } else {
        if (prev == nullptr) {
            cabezaEmpleado = temp->siguiente;
        } else {
            prev->siguiente = temp->siguiente;
        }
        delete temp->empleado;
        delete temp;
        cout << "Empleado eliminado exitosamente.\n";
    }
    pausa();
}

void asignarMedios() {
    limpiarConsola();

    if (cabezaEmpleado == nullptr) {
        cout << "No hay empleados registrados.\n";
        pausa();
        return;
    }

    if (cabezaMedios == nullptr) {
        cout << "No hay medios registrados.\n";
        pausa();
        return;
    }

    int id;
    cout << "Ingrese ID del empleado al que quiere asignar un medio: ";
    while (!(cin >> id)) {
        cout << "Entrada invalida. Ingrese ID del empleado: ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    NodoEmpleado* empleado = cabezaEmpleado;
    while (empleado != nullptr && empleado->empleado->getID() != id) {
        empleado = empleado->siguiente;
    }

    if (empleado == nullptr) {
        cout << "Empleado no encontrado.\n";
        pausa();
        return;
    }

    cout << "Empleado encontrado: " << empleado->empleado->getNombre() << "\n";
    cout << "Categoria: " << empleado->empleado->getCategoria() << "\n";
    cout << "---------------------------------------------\n";

    bool hayMediosDisponibles = false;
    NodoMedios* medio = cabezaMedios;

    cout << "Medios disponibles para asignar (en funcionamiento):\n";
    while (medio != nullptr) {
        if (medio->medio->getEstado() == "Funcionando" && medio->medio->getAsignadoA() == -1) {
            cout << "Nombre: " << medio->medio->getNombre() << " | Inventario: " << medio->medio->getInventario() << "\n";
            hayMediosDisponibles = true;
        }
        medio = medio->siguiente;
    }

    if (!hayMediosDisponibles) {
        cout << "No hay medios disponibles para asignar.\n";
        pausa();
        return;
    }

    string inventarioMedio;
    cout << "Ingrese numero de inventario del medio a asignar: ";
    getline(cin, inventarioMedio);

    medio = cabezaMedios;
    while (medio != nullptr && medio->medio->getInventario() != inventarioMedio) {
        medio = medio->siguiente;
    }

    if (medio == nullptr) {
        cout << "Medio no encontrado.\n";
    } else if (medio->medio->getEstado() != "Funcionando") {
        cout << "El medio no está en estado de funcionamiento.\n";
    } else if (medio->medio->getNombre() == "Laptop" && empleado->empleado->getCategoria() != "Investigador") {
        cout << "Solo los Investigadores pueden recibir Laptops.\n";
    } else {
        medio->medio->asignarA(empleado->empleado->getID());
        cout << "Medio con inventario '" << inventarioMedio << "' asignado al empleado '" << empleado->empleado->getNombre() << "' exitosamente.\n";
    }

    pausa();
}

void cambiarCategoria() {
    limpiarConsola();

    if (cabezaEmpleado == nullptr) {
        cout << "No hay empleados registrados.\n";
        pausa();
        return;
    }

    int id;
    cout << "Ingrese ID del empleado al que quiere cambiar la categoria: ";
    while (!(cin >> id)) {
        cout << "Entrada invalida. Ingrese ID del empleado: ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    NodoEmpleado* empleado = cabezaEmpleado;
    while (empleado != nullptr && empleado->empleado->getID() != id) {
        empleado = empleado->siguiente;
    }

    if (empleado == nullptr) {
        cout << "Empleado no encontrado.\n";
        pausa();
        return;
    }

    cout << "Empleado encontrado:\n";
    cout << "Nombre: " << empleado->empleado->getNombre() << "\n";
    cout << "Categoria actual: " << empleado->empleado->getCategoria() << "\n";
    cout << "---------------------------------------------\n";

    cout << "Seleccione la nueva categoria del empleado:\n";
    cout << "1 - Jefe de grupo\n";
    cout << "2 - Investigador\n";
    cout << "3 - Tecnico\n";
    cout << "Opcion: ";

    int opcion;
    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        cout << "Entrada invalida. Seleccione una categoria valida (1, 2 o 3): ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    string nuevaCategoria;
    switch (opcion) {
        case 1:
            nuevaCategoria = "Jefe de grupo";
            break;
        case 2:
            nuevaCategoria = "Investigador";
            break;
        case 3:
            nuevaCategoria = "Tecnico";
            break;
    }

    if (empleado->empleado->getCategoria() == nuevaCategoria) {
        cout << "La nueva categoria es la misma que la actual. No se realizan cambios.\n";
        pausa();
        return;
    }

    NodoMedios* medio = cabezaMedios;
    while (medio != nullptr) {
        if (medio->medio->getAsignadoA() == empleado->empleado->getID()) {
            medio->medio->asignarA(-1);
        }
        medio = medio->siguiente;
    }

    empleado->empleado->setCategoria(nuevaCategoria);
    cout << "Categoria del empleado '" << empleado->empleado->getNombre() << "' cambiada exitosamente a " << nuevaCategoria << "\n";
    pausa();
}

void altaMedios() {
    limpiarConsola();
    string nombre, inventario;
    string estado = "Funcionando";
    int nombreOpcion;

    cout << "Seleccione nombre del medio:\n";
    cout << "1 - PC de escritorio\n";
    cout << "2 - Laptop\n";
    cout << "Opcion: ";
    while (!(cin >> nombreOpcion) || nombreOpcion < 1 || nombreOpcion > 2) {
        cout << "Entrada invalida. Seleccione una opcion valida (1 o 2): ";
        cin.clear();
        limpiarEntrada();
    }
    limpiarEntrada();

    nombre = (nombreOpcion == 1) ? "PC de escritorio" : "Laptop";

    cout << "Ingrese numero de inventario del medio: ";
    getline(cin, inventario);

    NodoMedios* temp = cabezaMedios;
    while (temp != nullptr) {
        if (temp->medio->getInventario() == inventario) {
            cout << "El numero de inventario ya existe. Debe ingresar un numero unico.\n";
            pausa();
            return;
        }
        temp = temp->siguiente;
    }

    Medios* nuevoMedio = new Medios(nombre, inventario, estado);
    NodoMedios* nuevoNodo = new NodoMedios;
    nuevoNodo->medio = nuevoMedio;
    nuevoNodo->siguiente = cabezaMedios;
    cabezaMedios = nuevoNodo;

    cout << "Medio agregado exitosamente.\n";
    pausa();
}

void bajaMedios() {
    limpiarConsola();
    
    if (cabezaMedios == nullptr) {
        cout << "No hay medios registrados.\n";
        pausa();
        return;
    }
    
    string inventario;
    cout << "Ingrese numero de inventario del medio a eliminar: ";
    getline(cin, inventario);

    NodoMedios* temp = cabezaMedios;
    NodoMedios* prev = nullptr;

    while (temp != nullptr && temp->medio->getInventario() != inventario) {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp == nullptr) {
        cout << "Medio no encontrado.\n";
    } else {
        if (prev == nullptr) {
            cabezaMedios = temp->siguiente;
        } else {
            prev->siguiente = temp->siguiente;
        }
        delete temp->medio;
        delete temp;
        cout << "Medio eliminado exitosamente.\n";
    }
    pausa();
}

void cambiarEstado() {
    limpiarConsola();

    if (cabezaMedios == nullptr) {
        cout << "No hay medios registrados.\n";
        pausa();
        return;
    }

    string inventario;
    cout << "Ingrese numero de inventario del medio al que quiere cambiar el estado: ";
    getline(cin, inventario);

    NodoMedios* medio = cabezaMedios;
    while (medio != nullptr && medio->medio->getInventario() != inventario) {
        medio = medio->siguiente;
    }

    if (medio == nullptr) {
        cout << "Medio no encontrado.\n";
    } else {
        int estadoOpcion;
        cout << "Seleccione el nuevo estado del medio:\n";
        cout << "1 - Funcionando\n";
        cout << "2 - Roto\n";
        cout << "3 - Taller\n";
        cout << "Opcion: ";
        while (!(cin >> estadoOpcion) || estadoOpcion < 1 || estadoOpcion > 3) {
            cout << "Entrada invalida. Seleccione una opcion valida (1, 2 o 3): ";
            cin.clear();
            limpiarEntrada();
        }
        limpiarEntrada();

        string estado;
        switch (estadoOpcion) {
            case 1:
                estado = "Funcionando";
                break;
            case 2:
                estado = "Roto";
                break;
            case 3:
                estado = "Taller";
                break;
        }

        // Si el nuevo estado es "Roto" o "Taller" y el medio está asignado a algún empleado
        if ((estado == "Roto" || estado == "Taller") && medio->medio->getAsignadoA() != -1) {
            medio->medio->asignarA(-1); // Eliminar la asignación
            cout << "Asignación eliminada ya que el medio ha cambiado a estado '" << estado << "'.\n";
        }

        medio->medio->setEstado(estado);
        cout << "Estado del medio '" << medio->medio->getNombre() << "' cambiado exitosamente a '" << estado << "'.\n";
    }
    pausa();
}

void mostrarEmpleadosYMedios() {
    limpiarConsola();

    NodoEmpleado* empleado = cabezaEmpleado;

    if (empleado == nullptr) {
        cout << "No hay empleados registrados.\n";
    } else {
        while (empleado != nullptr) {
            cout << "Empleado ID: " << empleado->empleado->getID() << "\n";
            cout << "Nombre: " << empleado->empleado->getNombre() << "\n";
            cout << "Categoria: " << empleado->empleado->getCategoria() << "\n";

            bool tieneMedios = false;
            NodoMedios* medio = cabezaMedios;

            while (medio != nullptr) {
                if (medio->medio->getAsignadoA() == empleado->empleado->getID()) {
                    cout << "  Medio asignado:\n";
                    cout << "    Nombre: " << medio->medio->getNombre() << "\n";
                    cout << "    Inventario: " << medio->medio->getInventario() << "\n";
                    cout << "    Estado: " << medio->medio->getEstado() << "\n";
                    tieneMedios = true;
                }
                medio = medio->siguiente;
            }

            if (!tieneMedios) {
                cout << "  No tiene medios asignados.\n";
            }

            cout << "---------------------------------------------\n";
            empleado = empleado->siguiente;
        }
    }

    // Mostrar medios no asignados
    NodoMedios* medio = cabezaMedios;
    bool hayMediosNoAsignados = false;

    cout << "\nMedios no asignados:\n";
    cout << "---------------------------------------------\n";

    while (medio != nullptr) {
        if (medio->medio->getAsignadoA() == -1) {
            cout << "Nombre: " << medio->medio->getNombre() << "\n";
            cout << "Inventario: " << medio->medio->getInventario() << "\n";
            cout << "Estado: " << medio->medio->getEstado() << "\n";
            cout << "---------------------------------------------\n";
            hayMediosNoAsignados = true;
        }
        medio = medio->siguiente;
    }

    if (!hayMediosNoAsignados) {
        cout << "No hay medios no asignados.\n\n";
    }

    pausa();
}

// Función para inicializar los datos de ejemplo
void datos() {
    // Agregar empleados
    NodoEmpleado* nuevoEmpleado;

    // Empleado 1
    nuevoEmpleado = new NodoEmpleado;
    nuevoEmpleado->empleado = new Empleado(1, "Ana Pérez", "Jefe de grupo");
    nuevoEmpleado->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoEmpleado;

    // Empleado 2
    nuevoEmpleado = new NodoEmpleado;
    nuevoEmpleado->empleado = new Empleado(2, "Luis Gómez", "Investigador");
    nuevoEmpleado->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoEmpleado;

    // Empleado 3
    nuevoEmpleado = new NodoEmpleado;
    nuevoEmpleado->empleado = new Empleado(3, "Marta López", "Técnico");
    nuevoEmpleado->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoEmpleado;

    // Empleado 4
    nuevoEmpleado = new NodoEmpleado;
    nuevoEmpleado->empleado = new Empleado(4, "Carlos Fernández", "Investigador");
    nuevoEmpleado->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoEmpleado;

    // Empleado 5
    nuevoEmpleado = new NodoEmpleado;
    nuevoEmpleado->empleado = new Empleado(5, "Elena Ruiz", "Técnico");
    nuevoEmpleado->siguiente = cabezaEmpleado;
    cabezaEmpleado = nuevoEmpleado;

    // Agregar medios
    NodoMedios* nuevoMedio;

    // Medio 1
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("PC de escritorio", "PC001", "Funcionando");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Medio 2
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("Laptop", "LAP001", "Funcionando");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Medio 3
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("PC de escritorio", "PC002", "Roto");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Medio 4
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("Laptop", "LAP002", "Taller");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Medio 5
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("PC de escritorio", "PC003", "Funcionando");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Medio 6
    nuevoMedio = new NodoMedios;
    nuevoMedio->medio = new Medios("Laptop", "LAP003", "Funcionando");
    nuevoMedio->siguiente = cabezaMedios;
    cabezaMedios = nuevoMedio;

    // Asignaciones
    cabezaMedios->medio->asignarA(1); // PC001 a Ana Pérez
    cabezaMedios->siguiente->medio->asignarA(2); // LAP001 a Luis Gómez
    cabezaMedios->siguiente->siguiente->medio->asignarA(3); // PC002 a Marta López
    cabezaMedios->siguiente->siguiente->siguiente->medio->asignarA(4); // LAP002 a Carlos Fernández

    cout << "Datos iniciales cargados exitosamente.\n";
    pausa();
}

// Función principal
int main() {
    datos();

    int opcion;

    do {
        limpiarConsola();

        cout << "===== CONTROL DE TRABAJADORES Y MEDIOS =====\n" << endl;
        cout << "> Gestion de trabajadores:" << endl;
        cout << " 1 - Alta" << endl;
        cout << " 2 - Baja" << endl;
        cout << " 3 - Asignar medios" << endl;
        cout << " 4 - Cambiar categoria\n" << endl;
        cout << "> Gestion de medios: " <<endl;
        cout << " 5 - Alta" << endl;
        cout << " 6 - Baja" << endl;
        cout << " 7 - Cambiar estado\n" << endl;
        cout << "8 - Mostrar empleados y medios" << endl;
        cout << "0 - Salir\n" << endl;
        cout << "> ";

        while (!(cin >> opcion) || opcion < 0 || opcion > 8) {
            cout << "Entrada erronea, vuelva a intentarlo: ";
            cin.clear();
            limpiarEntrada();
        }
        limpiarEntrada();

        switch (opcion) {
            case 1:
                altaEmpleado();
                break;
            case 2:
                bajaEmpleado();
                break;
            case 3:
                asignarMedios();
                break;
            case 4:
                cambiarCategoria();
                break;
            case 5:
                altaMedios();
                break;
            case 6:
                bajaMedios();
                break;
            case 7:
                cambiarEstado();
                break;
            case 8:
                mostrarEmpleadosYMedios();
                break;
            case 0:
                break;
        }
    } while (opcion != 0);

    return 0;
}
