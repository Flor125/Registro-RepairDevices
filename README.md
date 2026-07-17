# 🛠️ Registro de Reparación de Dispositivos Electrónicos

> **Trabajo Final — Programación I** | C · Estructuras de Datos · Archivos Binarios · Gestión de Memoria

[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-C11-lightgrey?style=flat-square)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![IDE](https://img.shields.io/badge/IDE-Code::Blocks-orange?style=flat-square)](http://www.codeblocks.org/)
[![Build](https://img.shields.io/badge/Build-CMake-red?style=flat-square&logo=cmake)](https://cmake.org/)

---

## 📋 Descripción

Sistema de consola desarrollado en **C puro** para la gestión y registro del historial de reparaciones de dispositivos electrónicos (PC, Notebook y Celular) en un taller técnico.

El programa permite registrar cada reparación vinculando el **empleado responsable**, la **empresa/cliente**, el **tipo de dispositivo**, los **costos de hardware y software**, y la **fecha de servicio** — todo persistido en archivos binarios y cargado en memoria mediante listas enlazadas dinámicas.

---

## 🎯 Funcionalidades del sistema

| # | Función | Descripción |
|---|---------|-------------|
| 1 | **Ingresar reparaciones** | Alta de reparaciones con selección de dispositivo, empleado y empresa |
| 2 | **Buscar por tipo de dispositivo** | Filtrado de registros por PC, Notebook o Celular |
| 3 | **Mayor precio final** | Búsqueda de la reparación con el costo total más alto |
| 4 | **Reparaciones por empleado** | Listado de trabajos asignados a un empleado específico |
| 5 | **Reparaciones por empresa** | Historial de reparaciones de un cliente/empresa |
| 6 | **Reparaciones por fecha** | Consulta de todos los registros en una fecha determinada |
| 7 | **Almacenamiento persistente** | Escritura de todas las reparaciones al archivo `.dat` |
| 8 | **Salir** | Cierre controlado del programa |

---

## 🧠 Conceptos técnicos aplicados

### Estructuras de datos personalizadas

Se definieron tres estructuras principales con sus equivalentes para lista enlazada:

```c
// Estructura de reparación
struct datos {
    int    dispositivo;
    int    codigoEmpleado;
    char   fecha[11];
    float  costoH;          // costo hardware
    float  costoS;          // costo software
    char   nombEmpresa[100];
    int    codigoEmpresa;
    float  precioFinal;
    struct datos *sig;      // puntero al siguiente nodo
};

// Estructura de empleado (para archivo binario)
struct empleados {
    int  cod;
    char dni[9];
    char cuil[15];
    char nombres[40];
    char apellidos[40];
};

// Estructura de empresa (para archivo binario)
struct empresas {
    int  cod;
    char cuit[15];
    char nombreE[40];
};
```

### Listas enlazadas simples

Se implementaron **cuatro punteros globales** para mantener el estado de las listas en memoria durante la ejecución:

- `empleados_primero` / `empleados_ultimo`
- `empresas_primero` / `empresas_ultimo`
- `datos_primero` / `datos_ultimo`
- `memoria_primero` / `memoria_ultimo`

Cada nodo de las listas incluye un campo `*sig` (siguiente), permitiendo recorrer, insertar y buscar en tiempo lineal O(n).

### Persistencia con archivos binarios

Los datos de empleados y empresas se leen desde archivos `.dat` preexistentes usando `fread()` con vectores dinámicos como buffer intermedio, y luego se migran a listas enlazadas en memoria:

```c
struct empleados *Edinamico = malloc(11 * sizeof(struct empleados));
fread(Edinamico, sizeof(struct empleados), 11, Empleados);
// → se itera el vector y se insertan nodos en la lista enlazada
free(Edinamico); // liberación explícita
```

Las reparaciones se persisten en modo append binario (`"ab"`) para no sobreescribir registros anteriores.

### Gestión manual de memoria

Se utiliza `malloc()` y `free()` de forma explícita para:
- Alocar cada nodo nuevo de las listas
- Crear buffers intermedios para la lectura de archivos
- Alocar cadenas de retorno en funciones (`mostrarNombreEmpresa`)

Se verifica el retorno de `malloc()` ante posibles fallas de asignación.

---

## 🗂️ Estructura del proyecto

```
Registro-RepairDevices/
│
├── main.c                  # Código fuente completo (lógica, estructuras, menú)
├── empleados (1).dat       # Archivo binario preexistente con datos de empleados
├── empresas.dat            # Archivo binario preexistente con datos de empresas
├── reparacion.dat          # Archivo binario generado en tiempo de ejecución
│
├── CMakeLists.txt          # Configuración de build con CMake
├── Trabajo Final Programacion 1.cbp   # Proyecto para Code::Blocks
└── README.md
```

---

## ⚙️ Cómo compilar y ejecutar

### Con CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./Trabajo_Final_Programacion_1
```

### Con Code::Blocks
Abrir el archivo `Trabajo Final Programacion 1.cbp` y ejecutar con **Build & Run** (F9).

> ⚠️ Los archivos `empleados (1).dat` y `empresas.dat` deben estar en el mismo directorio que el ejecutable para que el programa cargue los datos correctamente.

---

## 🚀 Habilidades demostradas

- ✅ **Programación estructurada en C** — funciones, módulos, menú interactivo con `switch`
- ✅ **Manejo de punteros** — punteros simples, dobles y de función
- ✅ **Listas enlazadas dinámicas** — inserción al final, recorrido, búsqueda por código
- ✅ **Archivos binarios** — apertura, lectura (`fread`), escritura (`fwrite`/`ab`), cierre y manejo de errores
- ✅ **Gestión dinámica de memoria** — `malloc`, `free`, verificación de fallos de asignación
- ✅ **Separación de datos y representación** — estructuras independientes para archivo vs. lista
- ✅ **Localización** — `setlocale(LC_ALL, "")` para soporte de caracteres especiales

---

## 👩‍💻 Autora

**Florencia Sombra**
Estudiante de Programación · Argentina

> *Este proyecto fue desarrollado como Trabajo Final de la materia Programación I.*

---

*Escrito íntegramente en español, como requerido por la cátedra.*
