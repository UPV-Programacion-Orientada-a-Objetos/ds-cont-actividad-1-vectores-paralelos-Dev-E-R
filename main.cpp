#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

void cargar_regiones(ifstream& archivo);
void cargar_america(string region_pais);
void cargar_asia(string region_pais);
void cargar_europa(string region_pais);
void cargar_oceania(string region_pais);
void update();
void generar_reporte();
void estadisticas_globales();

int main() {
    // Leer regiones
    string name_archive_master = "data/regiones.txt";
    ifstream archivo(name_archive_master);
    cargar_regiones(archivo);
    cargar_america(regiones[0]);
    cargar_asia(regiones[1]);
    cargar_europa(regiones[2]);
    cargar_oceania(regiones[3]);
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
        std::cin >> option;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (option) {
            case 1:
                update();
                break;
            case 2:
                break;
            case 3:
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
void update() {
    string nombre_buscar;
    std::cout << "Ingrese el nombre del atleta a buscar: ";
    getline(cin, nombre_buscar);

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
                      << std::endl;
            int option;
            std::cout << "\n--- Selecciona Medallas y Participaciones ---\n"
                    << "1. Medalla Oro \n"
                    << "2. Medalla Plata \n"
                    << "3. Medalla Bronce n"
                    << "4. Participaciones\n"
                    << "5. Salir \n"
                    << "Seleccione una opcion (1-5): ";
            std::cin >> option;
            std::cin.ignore(); // Limpiar el buffer de entrada
            switch (option) {
                case 1:
                    std::cout << "Ingrese la cantidad de medallas de oro a modificar: ";
                    int medallas_oro;
                    std::cin >> medallas_oro;
                    g_medallas_oro[i] = medallas_oro;
                    std::cout << "Medallas de oro actualizadas a " << g_medallas_oro[i] << ".\n";
                    break;
                case 2:
                    std::cout << "Ingrese la cantidad de medallas de plata a modificar: ";
                    int medallas_plata;
                    std::cin >> medallas_plata;
                    g_medallas_plata[i] = medallas_plata;
                    std::cout << "Medallas de plata actualizadas a " << g_medallas_plata[i] << ".\n";
                    break;
                case 3:
                    std::cout << "Ingrese la cantidad de medallas de bronce a modificar: ";
                    int medallas_bronce;
                    std::cin >> medallas_bronce;
                    g_medallas_bronce[i] = medallas_bronce;
                    std::cout << "Medallas de bronce actualizadas a " << g_medallas_bronce[i] << ".\n";
                    break;
                case 4:
                    std::cout << "Ingrese la cantidad de participaciones a modificar: ";
                    int participaciones;
                    std::cin >> participaciones;
                    g_participaciones[i] = participaciones;
                    std::cout << "Participaciones actualizadas a " << g_participaciones[i] << ".\n";
                    break; 
                case 5:
                    std::cout << "Saliendo del programa.\n";
                    break;
                default:
                    std::cout << "Opcion no valida. Intente de nuevo.\n";
                    break;
            }
        }
            break; // Salir del bucle una vez que se encuentra el atleta
        
    }

    if (!encontrado) {
        std::cout << "Atleta no encontrado.\n";
    }
}


void cargar_regiones(ifstream& archivo) {
    string linea;
    int indice = 0;

    while (getline(archivo, linea) && indice < 500) {
        std::cout << linea << std::endl; 
        regiones[indice++] = linea;
    }
}
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