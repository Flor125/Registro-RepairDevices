# REGISTRO DE REPARACIÓN DE DISPOSITIVOS / / TRABAJO FINAL — PROGRAMACIÓN I / / 2024

- Desarrolló un sistema de consola en **C** para gestión de reparaciones de dispositivos electrónicos (PC, Notebook, Celular), implementando **listas enlazadas dinámicas** con manejo manual de memoria (`malloc`/`free`) y persistencia mediante **archivos binarios** (`fread`/`fwrite`).

- Diseñó estructuras de datos personalizadas con separación entre la representación en archivo y en memoria, cargando los registros de empleados y empresas desde archivos `.dat` preexistentes a listas enlazadas en tiempo de inicialización, evitando consultas repetidas a disco durante la ejecución.

- Implementó un menú interactivo con 8 funciones: ingreso de reparaciones, búsqueda por tipo de dispositivo, por empleado, por empresa, por fecha, obtención del mayor precio final y almacenamiento persistente de registros.
