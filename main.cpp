#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits> // Necesario para la validación de entrada numérica

using namespace std;

// Declaración de variables globales
string regiones[500];
string g_nombres[500];
string g_paises[500];
string g_disciplinas[500];
string g_generos[500];
string g_region[500];
int g_medallas_oro[500]; 
int g_medallas_plata[500];
int g_medallas_bronce[500];
int g_participaciones[500];

// Declaración de funciones
void cargar_regiones(ifstream& archivo);
void cargar_america(string region_pais);
void cargar_asia(string region_pais);
void cargar_europa(string region_pais);
void cargar_oceania(string region_pais);
void cargar_africa(string region_pais);
void update();
void generar_reporte();
void estadisticas_globales();
void update_csv(string nombre, string pais, string region);

int main() {
    // Leer regiones
    string name_archive_master = "data/regiones.txt";
    ifstream archivo(name_archive_master);
    cargar_regiones(archivo);
    cargar_america(regiones[0]);
    cargar_europa(regiones[1]);
    cargar_asia(regiones[2]);
    cargar_oceania(regiones[3]);
    cargar_africa(regiones[4]);

    // for (int i = 0; i < 500; i++) {
    //     std::cout << g_nombres[i] << std::endl;
    // }

    int option;
    do {
        std::cout << "\n--- Menu de opciones ---\n"
                  << "1. Buscar y actualizar atleta \n"
                  << "2. Generar reporte analítico por país \n"
                  << "3. Ver estadísticas globales detalladas \n"
                  << "4. Salir\n"
                  << "Seleccione una opcion (1-4): ";
        // validación de entrada numérica
        while (!(cin >> option) || option < 1 || option > 4) {
            cout << "Entrada no válida. Por favor, ingrese un número entre 1 y 4: ";
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer para futuros getline

        switch (option) {
            case 1:
                update();
                break;
            case 2:
                generar_reporte();
                break;
            case 3:
                estadisticas_globales();
                break;
            case 4:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (option != 4);
    
    return 0;
}

// Función para calcular y mostrar estadísticas globales
void estadisticas_globales() {
    int total_atletas = 0;

    int max_medallas = -1;
    int atleta_max_idx = -1;

    // Para país con más medallas
    string paises_unicos[500];
    int medallas_por_pais[500] = {0};
    int num_paises = 0;

    for (int i = 0; i < 500; i++) {
        if (g_paises[i] != "") {
            int medallas = g_medallas_oro[i] + g_medallas_plata[i] + g_medallas_bronce[i];

            if (medallas > max_medallas) {
                max_medallas = medallas;
                atleta_max_idx = i;
            }

            // Acumular medallas por pais
            int idx = -1;
            for (int j = 0; j < num_paises; j++) {
                if (paises_unicos[j] == g_paises[i]) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                paises_unicos[num_paises] = g_paises[i];
                medallas_por_pais[num_paises] = medallas;
                num_paises++;
            } else {
                medallas_por_pais[idx] += medallas;
            }
        }
    }

    // Encontrar país con más medallas
    int max_medallas_pais = -1;
    string pais_max = "";
    for (int i = 0; i < num_paises; i++) {
        if (medallas_por_pais[i] > max_medallas_pais) {
            max_medallas_pais = medallas_por_pais[i];
            pais_max = paises_unicos[i];
        }
    }

    if (atleta_max_idx != -1) {
        std::cout << "\nAtleta con más medallas:\n";
        std::cout << "Nombre: " << g_nombres[atleta_max_idx] << "\n";
        std::cout << "Pais: " << g_paises[atleta_max_idx] << "\n";
        std::cout << "Total Medallas: " << max_medallas << "\n";
        std::cout << "Oro: " << g_medallas_oro[atleta_max_idx]
                  << ", Plata: " << g_medallas_plata[atleta_max_idx]
                  << ", Bronce: " << g_medallas_bronce[atleta_max_idx] << "\n";
    }

    if (pais_max != "") {
        std::cout << "\nPaís con más medallas: " << pais_max
                  << " (" << max_medallas_pais << " medallas)\n";
    }
}

// Función para generar reporte analítico por país
void generar_reporte() {
    std::ofstream reporte;
    string pais_buscar;
    std::cout << "Ingrese el nombre del país a buscar: ";
    do {
        cout << "Ingrese el nombre del país a buscar: ";
        getline(cin, pais_buscar);
        if (pais_buscar.empty()) {
            cout << "El nombre del país no puede estar vacío. Intente de nuevo.\n";
        }
    } while (pais_buscar.empty());
    reporte.open("reporte_"+ pais_buscar + ".txt");

    int medallas_oro_total = 0;
    int medallas_plata_total = 0;
    int medallas_bronce_total = 0;
    int participaciones_total = 0;

    reporte << endl << "\n--- Reporte para el país: " << pais_buscar << " ---\n";
    reporte << endl << "----------  Atletas  -------------\n";

    bool encontrado = false;
    for (int i = 0; i < 500; i++) {
        if (g_paises[i] == pais_buscar) {
            encontrado = true;
            reporte << endl << "Nombre: " << g_nombres[i] << "\n"
                      << "Disciplina: " << g_disciplinas[i] << "\n"
                      << "Genero: " << g_generos[i] << "\n"
                      << "Medallas Oro: " << g_medallas_oro[i] << "\n"
                      << "Medallas Plata: " << g_medallas_plata[i] << "\n"
                      << "Medallas Bronce: " << g_medallas_bronce[i] << "\n"
                      << "Participaciones: " << g_participaciones[i] << "\n"
                      << "--------------------------\n";
            medallas_oro_total += g_medallas_oro[i];
            medallas_plata_total += g_medallas_plata[i];
            medallas_bronce_total += g_medallas_bronce[i];
            participaciones_total += g_participaciones[i];
        }
    }

    reporte << endl << "El pais " + pais_buscar + " tiene un total de:\n";
    reporte << "Medallas de Oro: " << medallas_oro_total << "\n";
    reporte << "Medallas de Plata: " << medallas_plata_total << "\n";
    reporte << "Medallas de Bronce: " << medallas_bronce_total << "\n";
    reporte << "Participaciones: " << participaciones_total << "\n";

    if (!encontrado) {
        std::cout << "No se encontraron atletas para el país especificado.\n";
    }
}

// Función para buscar y actualizar datos de un atleta
void update() {
    string nombre_buscar;
    do {
        cout << "Ingrese el nombre del atleta a buscar: ";
        getline(cin, nombre_buscar);
        if (nombre_buscar.empty()) {
            cout << "Error. Intente de nuevo.\n";
        }
    } while (nombre_buscar.empty());

    bool encontrado = false;
    for (int i = 0; i < 500; i++) {
        if (g_nombres[i] == nombre_buscar) {
            encontrado = true;
            std::cout << "\n--- Atleta Encontrado ---\n"
                      << "Nombre: " << g_nombres[i] << "\n"
                      << "Pais: " << g_paises[i] << "\n"
                      << "Region: " << g_region[i] << "\n"
                      << "Disciplina: " << g_disciplinas[i] << "\n"
                      << "Genero: " << g_generos[i] << "\n"
                      << "Medallas Oro: " << g_medallas_oro[i] << "\n"
                      << "Medallas Plata: " << g_medallas_plata[i] << "\n"
                      << "Medallas Bronce: " << g_medallas_bronce[i] << "\n"
                      << "Participaciones: " << g_participaciones[i] << "\n"
                      << std::endl;
            int option;
            std::cout << "\n--- Selecciona Medallas y Participaciones ---\n"
                    << "1. Medalla Oro \n"
                    << "2. Medalla Plata \n"
                    << "3. Medalla Bronce \n"
                    << "4. Participaciones \n"
                    << "5. Salir \n"
                    << "Seleccione una opcion (1-5): ";
            while (!(cin >> option) || option < 1 || option > 5) {
                cout << "Entrada no válida. Por favor, ingrese un número entre 1 y 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (option) {
                case 1:
                    std::cout << "Ingrese la cantidad de medallas de oro a modificar: ";
                    int medallas_oro;
                    while (!(cin >> medallas_oro) || medallas_oro < 0) {
                        cout << "Entrada no válida. Por favor, ingrese un número positivo: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    g_medallas_oro[i] = medallas_oro;
                    update_csv(g_nombres[i], g_paises[i], g_region[i]);
                    std::cout << "Medallas de oro actualizadas a " << g_medallas_oro[i] << ".\n";
                    break;
                case 2:
                    std::cout << "Ingrese la cantidad de medallas de plata a modificar: ";
                    int medallas_plata;
                    while (!(cin >> medallas_plata) || medallas_plata < 0) {
                        cout << "Entrada no válida. Por favor, ingrese un número positivo: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    g_medallas_plata[i] = medallas_plata;
                    update_csv(g_nombres[i], g_paises[i], g_region[i]);
                    std::cout << "Medallas de plata actualizadas a " << g_medallas_plata[i] << ".\n";
                    break;
                case 3:
                    std::cout << "Ingrese la cantidad de medallas de bronce a modificar: ";
                    int medallas_bronce;
                    while (!(cin >> medallas_bronce) || medallas_bronce < 0) {
                        cout << "Entrada no válida. Por favor, ingrese un número positivo: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    g_medallas_bronce[i] = medallas_bronce;
                    update_csv(g_nombres[i], g_paises[i], g_region[i]);
                    std::cout << "Medallas de bronce actualizadas a " << g_medallas_bronce[i] << ".\n";
                    break;
                case 4:
                    std::cout << "Ingrese la cantidad de participaciones a modificar: ";
                    int participaciones;
                    while (!(cin >> participaciones) || participaciones < 0) {
                        cout << "Entrada no válida. Por favor, ingrese un número positivo: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    g_participaciones[i] = participaciones;
                    update_csv(g_nombres[i], g_paises[i], g_region[i]);
                    std::cout << "Participaciones actualizadas a " << g_participaciones[i] << ".\n";
                    break; 
                case 5:
                    std::cout << "Saliendo del programa.\n";
                    break;
                default:
                    std::cout << "Opcion no valida. Intente de nuevo.\n";
                    break;
            }
            break; // Salir del ciclo una vez encontrado y procesado el atleta.
        }        
    }

    if (!encontrado) {
        std::cout << "Atleta no encontrado.\n";
    }
}

// Función para actualizar el archivo CSV del atleta modificado 
void update_csv(string nombre, string pais, string region) {
    if (region == "America") {
        region = "america";
    } else if (region == "Asia") {
        region = "asia";
    } else if (region == "Europa") {
        region = "europa";
    } else if (region == "Oceania") {
        region = "oceania";
    } else if (region == "Africa") {
        region = "africa";
    } else {
        cerr << "Error: Región desconocida." << endl;
        return;
    }
    string filename = "data/" + region + ".csv";
    string temp_filename = "data/temp_update.csv";

    // Creamos un archivo temporal para escribir los datos actualizados y el original para leer    
    ifstream infile(filename);
    ofstream outfile(temp_filename);

    // Validación de apertura de archivos
    if (!infile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo original: " << filename << endl;
        return;
    }
    if (!outfile.is_open()) {
        cerr << "Error: No se pudo crear el archivo temporal." << endl;
        infile.close(); // Cerrar el archivo que sí se abrió.
        return;
    }

    // Buscar el índice del atleta en los arreglos globales para acceder a sus datos actualizados.
    int athlete_idx = -1;
    for (int i = 0; i < 500; ++i) {
        if (g_nombres[i] == nombre) {
            athlete_idx = i;
            break; // Salir del ciclo una vez encontrado el atleta.
        }
    }

    // Si no se encontró al atleta en los datos globales, no se puede continuar.
    if (athlete_idx == -1) {
        cerr << "Error: No se encontró al atleta en los datos globales para actualizar el CSV." << endl;
        infile.close();
        outfile.close();
        return;
    }

    // Leer el archivo original línea por línea, copiar al archivo temporal,
    // y reemplazar la línea del atleta objetivo con los datos actualizados.
    string line;
    bool header = true;
    while (getline(infile, line)) {
        // La primera línea es el encabezado, copiarla directamente.
        if (header) {
            outfile << line << endl;
            header = false;
            continue;
        }

        stringstream ss(line);
        string current_name;
        // Extraer solo el nombre de la línea actual para comparar.
        getline(ss, current_name, ',');

        if (current_name == nombre) {
            // Esta es la línea a actualizar. Construir la nueva línea desde los arreglos globales.
            outfile << g_nombres[athlete_idx] << ","
                    << g_paises[athlete_idx] << ","
                    << g_disciplinas[athlete_idx] << ","
                    << g_generos[athlete_idx] << ","
                    << g_medallas_oro[athlete_idx] << ","
                    << g_medallas_plata[athlete_idx] << ","
                    << g_medallas_bronce[athlete_idx] << ","
                    << g_participaciones[athlete_idx] << endl;
        } else {
            // Si no es el atleta que buscamos, copiar la línea original.
            outfile << line << endl;
        }
    }

    cout << "Archivo actualizado exitosamente: " << filename << endl;
    // Cerrar ambos archivos para asegurar que los datos se escriban y liberar recursos.
    infile.close();
    outfile.close();

    // Eliminar el archivo original y renombrar el archivo temporal al nombre original.
    if (remove(filename.c_str()) != 0) {
        perror("Error al eliminar el archivo original");
    }
    if (rename(temp_filename.c_str(), filename.c_str()) != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}
// Función para cargar las regiones desde el archivo
void cargar_regiones(ifstream& archivo) {
    string linea;
    int indice = 0;

    while (getline(archivo, linea) && indice < 500) {
        std::cout << linea << std::endl; 
        regiones[indice++] = linea;
    }
}

// Las demas funciones es para cargar los datos de cada region
void cargar_america(string region_pais) {
    string line;
    std::cout << "Procesando '" + region_pais + "'..." << std::endl;

    ifstream arch_america("data/" + region_pais);
    getline(arch_america, line); // Saltar la línea del encabezado

    while (getline(arch_america, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaOro, medallaPlata, medallaBronce, participaciones;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaOro, ',');
        getline(ss, medallaPlata, ',');
        getline(ss, medallaBronce, ',');
        getline(ss, participaciones, ',');
        


        // agrega los datos a los vectores globales
        for(int i = 0; i < 500; i++){
            if(g_paises[i] == ""){
                g_nombres[i] = nombre;
                g_paises[i] = pais;
                g_disciplinas[i] = disciplina;
                g_generos[i] = genero;
                g_region[i] = "America";
                g_medallas_oro[i] = stoi(medallaOro);
                g_medallas_plata[i] = stoi(medallaPlata);
                g_medallas_bronce[i] = stoi(medallaBronce);
                g_participaciones[i] = stoi(participaciones);
                break;
            }
        }
    }
}
void cargar_asia(string region_pais) {
    string line;
    std::cout << "Procesando '" + region_pais + "'..." << std::endl;

    ifstream arch_region("data/" + region_pais);
    getline(arch_region, line); // Saltar la línea del encabezado

    while (getline(arch_region, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaOro, medallaPlata, medallaBronce, participaciones;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaOro, ',');
        getline(ss, medallaPlata, ',');
        getline(ss, medallaBronce, ',');
        getline(ss, participaciones, ',');
        


        // agrega los datos a los vectores globales
        for(int i = 0; i < 500; i++){
            if(g_paises[i] == ""){
                g_nombres[i] = nombre;
                g_paises[i] = pais;
                g_disciplinas[i] = disciplina;
                g_generos[i] = genero;
                g_region[i] = "Asia";
                g_medallas_oro[i] = stoi(medallaOro);
                g_medallas_plata[i] = stoi(medallaPlata);
                g_medallas_bronce[i] = stoi(medallaBronce);
                g_participaciones[i] = stoi(participaciones);
                break;
            }
        }
    }
}
void cargar_europa(string region_pais) {
    string line;
    std::cout << "Procesando '" + region_pais + "'..." << std::endl;

    ifstream arch_region("data/" + region_pais);
    getline(arch_region, line); // Saltar la línea del encabezado

    while (getline(arch_region, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaOro, medallaPlata, medallaBronce, participaciones;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaOro, ',');
        getline(ss, medallaPlata, ',');
        getline(ss, medallaBronce, ',');
        getline(ss, participaciones, ',');
        


        // agrega los datos a los vectores globales
        for(int i = 0; i < 500; i++){
            if(g_paises[i] == ""){
                g_nombres[i] = nombre;
                g_paises[i] = pais;
                g_disciplinas[i] = disciplina;
                g_generos[i] = genero;
                g_region[i] = "Europa";
                g_medallas_oro[i] = stoi(medallaOro);
                g_medallas_plata[i] = stoi(medallaPlata);
                g_medallas_bronce[i] = stoi(medallaBronce);
                g_participaciones[i] = stoi(participaciones);
                break;
            }
        }
    }
}
void cargar_oceania(string region_pais) {
    string line;
    std::cout << "Procesando '" + region_pais + "'..." << std::endl;

    ifstream arch_region("data/" + region_pais);
    getline(arch_region, line); // Saltar la línea del encabezado

    while (getline(arch_region, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaOro, medallaPlata, medallaBronce, participaciones;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaOro, ',');
        getline(ss, medallaPlata, ',');
        getline(ss, medallaBronce, ',');
        getline(ss, participaciones, ',');
        


        // agrega los datos a los vectores globales
        for(int i = 0; i < 500; i++){
            if(g_paises[i] == ""){
                g_nombres[i] = nombre;
                g_paises[i] = pais;
                g_disciplinas[i] = disciplina;
                g_generos[i] = genero;
                g_region[i] = "Oceania";
                g_medallas_oro[i] = stoi(medallaOro);
                g_medallas_plata[i] = stoi(medallaPlata);
                g_medallas_bronce[i] = stoi(medallaBronce);
                g_participaciones[i] = stoi(participaciones);
                break;
            }
        }
    }
}
void cargar_africa (string region_pais) {
    string line;
    std::cout << "Procesando '" + region_pais + "'..." << std::endl;

    ifstream arch_region("data/" + region_pais);
    getline(arch_region, line); // Saltar la línea del encabezado

    while (getline(arch_region, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaOro, medallaPlata, medallaBronce, participaciones;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaOro, ',');
        getline(ss, medallaPlata, ',');
        getline(ss, medallaBronce, ',');
        getline(ss, participaciones, ',');
        


        // agrega los datos a los vectores globales
        for(int i = 0; i < 500; i++){
            if(g_paises[i] == ""){
                g_nombres[i] = nombre;
                g_paises[i] = pais;
                g_disciplinas[i] = disciplina;
                g_generos[i] = genero;
                g_region[i] = "Africa";
                g_medallas_oro[i] = stoi(medallaOro);
                g_medallas_plata[i] = stoi(medallaPlata);
                g_medallas_bronce[i] = stoi(medallaBronce);
                g_participaciones[i] = stoi(participaciones);
                break;
            }
        }
    }
}
