#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// CONSTANTES: 

const int PUNTOS_GANADOR = 3,
const int PUNTOS_EMPATE = 1;
const int PUNTOS_PERDIO = 0;


// Estructuras

struct Pais {
    char nombre[50];
    char grupo[2];
};

// pre: recibe los datos de 

struct Etapas {
    char nombre[50];
    char grupo[2];
    int ganados = 0;
    int empatados= 0;
    int perdidos = 0;
    int puntaje = 0;
};


void leerArchivo(Pais*& paises, int& n) {
    ifstream archivo("paises.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    char linea[100];
    while (archivo.getline(linea, 100)) {
        char* nombre = strtok(linea, " ");
        char* grupo = strtok(NULL, " ");

        Pais nuevoPais;
        strcpy(nuevoPais.nombre, nombre);
        strcpy(nuevoPais.grupo, grupo);

        // reemplazar guiones bajos

        int a = 0;
        while (nuevoPais.nombre[a] != '\0'){
        char * guion_bajo = strchr(nuevoPais.nombre, '_');
        if(guion_bajo != NULL){
            *guion_bajo = ' ';
        }    
        a++;
        }
            

        if (n == 0) {
            paises = new Pais[1];
            paises[0] = nuevoPais;
        } else {
            Pais* nuevosPaises = new Pais[n + 1];
            for (int i = 0; i < n; i++) {
                nuevosPaises[i] = paises[i];
            }
            nuevosPaises[n] = nuevoPais;
            delete[] paises;
            paises = nuevosPaises;
        }

        n++;
    }

    archivo.close();
}



void ordenarPaises(Pais* paises, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(paises[i].nombre, paises[j].nombre) > 0) {
                Pais temp = paises[i];
                paises[i] = paises[j];
                paises[j] = temp;
            }
        }
    }
}

void imprimirPaises(Pais* paises, int n) {
    for (int i = 0; i < n; i++) {
        cout << paises[i].nombre << " " << paises[i].grupo << endl;
    }
}














int main() {
    Pais* paises = NULL;
    int filas = 0;

    leerArchivo(paises, filas);
    ordenarPaises(paises, filas);
    imprimirPaises(paises, filas);


    cout << "La cantidad de filas quedo: " << filas << endl;
    


    // se elimina la memoria comprada de la primera parte.
    delete[] paises;
    return 0;
}
