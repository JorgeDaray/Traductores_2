#ifndef GENERA_H
#define GENERA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class GeneraCodigo
{
    char *nombreFichero; // Nombre del fichero objeto de salida
    FILE *salida;        // Fichero objeto de salida

public:
    GeneraCodigo(const char *unNombreFichero);
    ~GeneraCodigo();
    void code();
    void pushc(char constante);
    void pusha(char direccion);
    void load();
    void store();
    void neg();
    void add();
    void mul();
    void div();
    void mod();
    void input(char direccion);
    void output(char direccion);  // Modificado para aceptar std::string
    void end();
};

#endif

