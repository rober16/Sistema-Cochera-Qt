# Sistema de Gestión de Estacionamientos (Qt/C++)

Este proyecto presenta una aplicación desarrollada en C++ utilizando el framework Qt para la gestión de estacionamientos o cocheras.  

## Funcionalidades

La aplicación permite:

* **Login de usuario:**  Acceso seguro mediante nombre de usuario y contraseña.
* **Registro de vehículos:** Ingreso de nuevos vehículos con su patente, descripción (marca y modelo), fecha y hora de entrada.
* **Registro de salida de vehículos:**  Selección de un vehículo estacionado para registrar su salida con la fecha y hora correspondiente.
* **Visualización de vehículos:** Listado de vehículos estacionados y un registro histórico de todos los vehículos que han utilizado el estacionamiento.
* **Control de capacidad:**  La aplicación lleva un registro de la cantidad de vehículos estacionados y advierte al usuario cuando se acerca al límite de capacidad.

## Implementación

* **Lenguaje:** C++
* **Framework:** Qt
* **Base de datos:** SQLite. Se utiliza una base de datos SQLite para almacenar la información de usuarios, vehículos y estacionamientos. Se incluye una clase `AdminDB` para la gestión de la base de datos.


## Formularios

La aplicación cuenta con los siguientes formularios:

* **Login:**  Para el acceso de usuarios.
* **Menú Principal:**  Con opciones para ingresar vehículos, registrar salidas y visualizar el registro de vehículos.
* **Ingreso de Vehículos:**  Para registrar la entrada de un nuevo vehículo.
* **Salida de Vehículos:**  Para registrar la salida de un vehículo.
* **Registro de Vehículos:**  Muestra un listado de todos los vehículos registrados.


## Base de datos

La base de datos "tested.db" (SQLite) contiene las siguientes tablas:

* **usuarios:**  Almacena la información de los usuarios (id, nombre, clave, id_estacionamiento).
* **Descripciones:**  Almacena las descripciones de los modelos de vehículos (id, descripcion).
* **Estacionamientos:**  Almacena la información de los estacionamientos (id, nombre, capacidad).
* **Autos:**  Almacena el registro de los vehículos que han utilizado el estacionamiento (id, patente, id_descripcion, fecha_ingreso, fecha_salida, id_estacionamiento).
