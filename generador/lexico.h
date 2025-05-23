#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h> // Cambiado <string> por <string.h> para utilizar funciones de cadena en C
#define TAM_BUFFER 100

using namespace std;

class Lexico {
    char *nombreFichero;
    FILE *entrada;
    int n1; // N�mero de l�nea
    int traza; // Control de traza
    char buffer[TAM_BUFFER]; // Buffer auxiliar de caracteres
    int pBuffer; // Posicion en el buffer

public:
    Lexico(char *unNombreFichero, int una_traza = 0);
    ~Lexico();
    char siguienteToken(void);
    void devuelveToken(char toke);
    int lineaActual(void) { return n1; }
    int existeTraza(void) {
        if (traza) return 1;
        else return 0;
    }
};

Lexico::Lexico(char *unNombreFichero, int una_traza) {
    entrada = fopen(unNombreFichero, "rt");
    if (entrada == NULL) {
        cout << "No se puede abrir el archivo" << endl;
        system("pause");
        exit(-2);
    }
    if (una_traza) traza = 1;
    else traza = 0;
    n1 = 1; // Se inicializa el contador de l�nea
    pBuffer = 0; // Se inicializa la posici�n del buffer
}

Lexico::~Lexico() {
    fclose(entrada);
}

char Lexico::siguienteToken(void) {
    char car;
    while ((car = ((pBuffer > 0) ? buffer[--pBuffer] : fgetc(entrada))) != EOF) {
        if (car == ' ') continue;
        if (car == '\n') { ++n1; continue; }
        break;
    }
    if (traza) cout << "ANALIZADOR LEXICO: Lee el token " << car << endl;
    switch (car) {
        case 'M':
        case 'R':
        case 'W':
        case '=':
        case '(':
        case ')':
        case ';':
        case '}':
        case '{':
        case '.':
        case '+':
        case '*':
        case '-':
        case '/':
        case '%':
            return (car);
    }

    if (islower(car)) return (car); // Variable
    else if (isdigit(car)) return (car); // Constante
    else {
        system("pause");
        exit(-4);
    }
    return (car);
}

void Lexico::devuelveToken(char token) {
    if (pBuffer > TAM_BUFFER) {
        cout << "ERROR: Desbordamiento del buffer del analizador lexico" << endl;
        system("pause");
        exit(-5);
    } else {
        buffer[pBuffer++] = token;
        if (existeTraza())
            cout << "ANALIZADOR LEXICO: Recibe en buffer el token " << token << endl;
        system("pause"); // Este system("pause") podr�a necesitar ser revisado dependiendo del entorno de ejecuci�n
    }
}
