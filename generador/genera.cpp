#include <iostream>
#include <cstring>  
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "genera.h"
using namespace std;

GeneraCodigo::GeneraCodigo(const char *unNombreFichero)
{
    if ((salida = fopen(unNombreFichero, "w")) == NULL)
    {
        cout << "No se puede crear el fichero " << nombreFichero << endl;
        exit(-3);
    }
}

GeneraCodigo::~GeneraCodigo(void)
{
    fclose(salida);
}

void GeneraCodigo::code()
{
    cout << ".CODE" << endl;
    fputs(".CODE\n", salida);
}

void GeneraCodigo::pushc(char constante)
{
    cout << "PUSHC " << constante << endl;
    fputs("PUSHC ", salida);
    fputc(constante, salida);
    fputc('\n', salida);
}

void GeneraCodigo::pusha(char direccion)
{
    cout << "PUSHA " << direccion << endl;
    fputs("PUSHA ", salida);
    fputc(direccion, salida);
    fputc('\n', salida);
}

void GeneraCodigo::load()
{
    cout << "LOAD" << endl;
    fputs("LOAD\n", salida);
}

void GeneraCodigo::store()
{
    cout << "STORE" << endl;
    fputs("STORE\n", salida);
}

void GeneraCodigo::neg()
{
    cout << "NEG" << endl;
    fputs("NEG\n", salida);
}

void GeneraCodigo::add()
{
    cout << "ADD" << endl;
    fputs("ADD\n", salida);
}

void GeneraCodigo::mul()
{
    cout << "MUL" << endl;
    fputs("MUL\n", salida);
}

void GeneraCodigo::div()
{
    cout << "DIV" << endl;
    fputs("DIV\n", salida);
}

void GeneraCodigo::mod()
{
    cout << "MOD" << endl;
    fputs("MOD\n", salida);
}

void GeneraCodigo::input(char direccion)
{
    cout << "INPUT " << direccion << endl;
    fputs("INPUT ", salida);
    fputc(direccion, salida);
    fputc('\n', salida);
}

void GeneraCodigo::output(char direccion)
{
    cout << "OUTPUT " << direccion << endl;
    fputs("OUTPUT ", salida);
    fputc(direccion, salida);
    fputc('\n', salida);
}

void GeneraCodigo::end()
{
    cout << "END" << endl;
    fputs("END\n", salida);
}
