[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/39oPPDFL)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20670461)
# Continuación - Actividad 1 - Vectores Paralelos

## Problema: Sistema Avanzado de Gestión y Análisis de Medallas Olímpicas

### Definición del Problema

El sistema de gestión de la federación de atletismo requiere una actualización crítica para un análisis más profundo. Ahora, no solo se necesita registrar las medallas de oro, sino también las de plata y bronce, así como el número de participaciones de cada atleta en los Juegos Olímpicos. El sistema deberá procesar un archivo maestro que contiene la lista de archivos de datos de atletas, uno por región. La información de cada atleta debe ser procesada y consolidada para generar reportes analíticos complejos y estadísticas detalladas.

El sistema debe manejar los siguientes datos para cada atleta, utilizando arreglos estáticos paralelos:

  * Nombre: El nombre del atleta.
  * País: El país de origen.
  * Disciplina: La disciplina en la que compite.
  * Género: El género del atleta (M o F).
  * Medallas de Oro: El número de medallas de oro ganadas.
  * Medallas de Plata: El número de medallas de plata ganadas.
  * Medallas de Bronce: El número de medallas de bronce ganadas.
  * Participaciones Olímpicas: El número de veces que ha participado en los Juegos Olímpicos.

#### Estructura de los archivos:

  * Archivo Maestro (regiones.txt): Contiene una lista de los nombres de los archivos de datos de atletas, uno por línea.
  * Archivos de Datos de Atletas (america.csv, europa.csv, etc.): Cada uno de estos archivos sigue la estructura Nombre,País,Disciplina,Género,Oro,Plata,Bronce,Participaciones y contiene la información de los atletas de esa región.

**Requisitos Funcionales y No Funcionales**

  * Requisitos Funcionales
    * Lectura y Consolidación de Múltiples Archivos: El programa debe leer el archivo maestro (regiones.txt) y, a partir de este, procesar y consolidar los datos de cada archivo .csv en un único conjunto de arreglos estáticos paralelos en memoria.
    * Reporte Analítico por País: El usuario podrá ingresar un nombre de país y el sistema generará un nuevo archivo de texto (reporte_[país].txt) con un resumen analítico. Este reporte debe incluir el nombre de cada atleta de ese país, el total de sus medallas (suma de oro, plata y bronce), y un desglose de las medallas por tipo.
    * Estadísticas Globales Detalladas: El programa debe calcular y mostrar en la consola: El atleta con la mayor cantidad de medallas totales (oro + plata + bronce).
    * El país con la mayor cantidad total de medalla: Un listado de los atletas que no han ganado medallas, ordenados por el número de participaciones, de mayor a menor.
    * Búsqueda y Actualización de Atletas: El usuario podrá buscar un atleta por nombre. Si se encuentra, el sistema deberá mostrar toda su información y permitir al usuario modificar el número de medallas (oro, plata, bronce) y participaciones. Los cambios deben ser guardados y reflejados en el archivo .csv de origen, sobrescribiendo el archivo.

  * Requisitos No Funcionales
    * Estructura de Datos: Se debe utilizar exclusivamente arreglos estáticos paralelos. El tamaño máximo de atletas a manejar es de 500. No se permiten estructuras de datos dinámicas.
    * Manejo de Archivos: La lectura y escritura de archivos debe ser precisa y robusta, manejando correctamente los delimitadores de coma y los saltos de línea.
    * Robustez y Validación: El programa debe manejar la ausencia de archivos, datos incompletos o corruptos, y entradas de usuario inválidas.
    * Eficiencia: El procesamiento de datos y la generación de reportes deben ser eficientes.

----

#### Entregables

1. Un único archivo .cpp que contenga la implementación completa del programa.
2. Un archivo regiones.txt con la lista de los archivos de datos.
3. Varios archivos .csv con los datos de los atletas (ej. america.csv, europa.csv).

---

#### Ejemplo de Salida del Sistema

```bash
--- Sistema de Análisis de Atletas Olímpicos ---

Cargando datos de regiones...
Procesando 'america.csv'... 150 atletas cargados.
Procesando 'europa.csv'... 200 atletas cargados.
Procesando 'asia.csv'... 100 atletas cargados.
Datos consolidados exitosamente.

Seleccione una opción:
1. Buscar y actualizar atleta
2. Generar reporte analítico por país
3. Ver estadísticas globales detalladas
4. Salir

Opción seleccionada: 3

--- Estadísticas Globales ---
Atleta con más medallas totales: Michael Phelps (EEUU) con 28 medallas.
País con más medallas totales: EEUU con 121 medallas.

Atletas sin medallas (ordenados por participaciones):
- Fernando Alonso (España), 4 participaciones
- Ana García (México), 2 participaciones
- ...

--- Menú principal ---

Opción seleccionada: 2

Ingrese el nombre del país para el reporte: México

Generando reporte analítico para México...
Archivo 'reporte_México.txt' creado exitosamente.

--- Contenido de 'reporte_México.txt' ---
Reporte Analítico para México

Atleta: Pablo
  Medallas Totales: 3
  Desglose: 2 Oro, 1 Plata, 0 Bronce

Atleta: Ana García
  Medallas Totales: 0
  Desglose: 0 Oro, 0 Plata, 0 Bronce
```