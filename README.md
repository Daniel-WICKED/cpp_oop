# Sistema de Control de Medios en Instituto de Investigaciones

Este sistema está diseñado para el control de los medios (PC o laptop) utilizados por los trabajadores en un instituto de investigaciones. El sistema permite gestionar trabajadores y medios, asignar medios a trabajadores, y cambiar la categoría y estado de los medios.

## Descripción del Código

El código está escrito en C++ y utiliza listas enlazadas para almacenar y gestionar los empleados y los medios. Los empleados tienen un ID, nombre, y categoría (Jefe de grupo, Investigador, Técnico). Los medios tienen un nombre (PC de escritorio o laptop), un número de inventario y un estado (Funcionando, Roto, Taller).

## Clases

### `Empleado`

- **Atributos**:
  - `int id`: Identificador del empleado.
  - `string nombre`: Nombre completo del empleado.
  - `string categoria`: Categoría del empleado (Jefe de grupo, Investigador, Técnico).

- **Métodos**:
  - `getID()`: Obtiene el ID del empleado.
  - `getNombre()`: Obtiene el nombre del empleado.
  - `getCategoria()`: Obtiene la categoría del empleado.
  - `setID(int id)`: Establece el ID del empleado.
  - `setNombre(string nombre)`: Establece el nombre del empleado.
  - `setCategoria(string categoria)`: Establece la categoría del empleado.

### `Medios`

- **Atributos**:
  - `string nombre`: Nombre del medio (PC de escritorio o Laptop).
  - `string inventario`: Número de inventario del medio.
  - `string estado`: Estado del medio (Funcionando, Roto, Taller).
  - `int idEmpleadoAsignado`: ID del empleado al que está asignado el medio.

- **Métodos**:
  - `getNombre()`: Obtiene el nombre del medio.
  - `getInventario()`: Obtiene el número de inventario del medio.
  - `getEstado()`: Obtiene el estado del medio.
  - `getAsignadoA()`: Obtiene el ID del empleado al que está asignado el medio.
  - `setNombre(string nombre)`: Establece el nombre del medio.
  - `setInventario(string inventario)`: Establece el número de inventario del medio.
  - `setEstado(string estado)`: Establece el estado del medio.
  - `asignarA(int idEmpleado)`: Asigna el medio a un empleado.

## Funciones Principales

- **`altaEmpleado()`**: Agrega un nuevo empleado al sistema.
- **`bajaEmpleado()`**: Elimina un empleado del sistema.
- **`asignarMedios()`**: Asigna un medio a un empleado.
- **`cambiarCategoria()`**: Cambia la categoría de un empleado y actualiza la asignación de medios si es necesario.
- **`altaMedios()`**: Agrega un nuevo medio al sistema.
- **`bajaMedios()`**: Elimina un medio del sistema.
- **`cambiarEstado()`**: Cambia el estado de un medio y elimina la asignación si es necesario.
- **`mostrarEmpleadosYMedios()`**: Muestra la información de todos los empleados y los medios asignados, así como los medios no asignados.
- **`datos()`**: Inicializa el sistema con datos de ejemplo para facilitar las pruebas.
