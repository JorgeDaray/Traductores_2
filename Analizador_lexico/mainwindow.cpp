#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QTableWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

QString cadena;
QString palabras_reservadas;
string palabras_reservadas_s;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct Token
{
    QString nombre;
};
Token token;

//Función para verificar si un carácter es un operador
int esOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//Funcion para verificar si es un numero
int esnumero(char c)
{
    int x = (int)c;
    if(x >= 48 && x <= 57)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Funcion para verificar si es parentesis
int esparentesis(char c)
{
    return (c == '(' || c == ')' );
}

int esllave(char c)
{
    return (c == '{' || c == '}' );
}

int espuntoycoma(char c)
{
    return (c == ';');
}

int esnot(char c)
{
    return (c == '!');
}

int escoma(char c)
{
    return (c == ',');
}

int esigual(char c)
{
    return ( c == '=');
}

int esand(string c)
{
    cout << "Entro a &&"<<endl;
    return (c == "&&");
}

int esor(string c)
{
    cout << "Entro a ||"<<endl;
    return (c == "||");
}

int esigualdad(string c)
{
    return (c == "==" || c == "!=");
}

int esoperadorrelacional(char c)
{
    return (c == '<' || c == '>');
}

int esoperadorrelacional2(string c)
{
    return (c == "<=" || c == ">=");
}

int espalabra_reservada (string c)
{
    string nombreArchivo = "C:/Qt/Escuela_proyects/seminario_tra_2/Subproducto1/build-Analizador_lexico-Desktop_Qt_6_5_2_MinGW_64_bit-Debug/palabras_reservadas.txt";
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea))
    {
        // Lo vamos imprimiendo
        if(c == linea)
        {
            return true;
        }
    }
    return false;
}

//Funcion para ver longitud de cadena
int longitud = 0;
void longitud_cadena(QString cadena)
{
    longitud = cadena.length();
}

int contador_ingresados = 0;
int contador_in_cadenas = 0;
int contador_cadenas = 0;
int saltos_linea = 0;
char letra[100];
char enteros[11], flotantes[32];
string cadena_momento[500];

void inicializar()
{
    contador_ingresados = 0;
    contador_in_cadenas = 0;
    contador_cadenas = 0;
    saltos_linea = 0;
}

//Funcion analizar toda la cadena
void recorrido(QString cadena)
{
    char letras[longitud];
    //limpia el buffer del registro
    for (int i = 0; i < longitud; letras[i++] = '\0')
        ;
    char cadenas[longitud];
    //limpia el buffer del registro
    for (int i = 0; i < longitud; cadenas[i++] = '\0')
        ;
    cout <<"Longitud: "<<longitud<<endl;
    string cadena_tempo;
    string cadena_c;
    cadena_c = cadena.toStdString();
    cout << "Cadena"<<cadena_c<<endl;
    // Quitar espacios
    cadena_c.erase(std::remove(cadena_c.begin(), cadena_c.end(), ' '), cadena_c.end());
    cadena_c.erase(std::remove(cadena_c.begin(), cadena_c.end(), '\n'), cadena_c.end());
    cout << "Sin espacios:"<<cadena_c<<endl;
    strcpy(letras,cadena_c.c_str());
    cout << "Letras:"<<letras<<endl;
    int i = 0;
    while(i < longitud)
    {
        cout << "letras dentro while:"<<letras<<endl;
        cout << "letras dentro while[i]:"<<letras[i]<<endl;
        if(esOperador(letras[i]))
        {
            cout << "Es operador: "<<letras[i]<<endl;
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esnumero(letras[i]))
        {
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cout <<"Es entero: "<<letras[i]<<endl;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esparentesis(letras[i]))
        {
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cout <<"Es parentesis: "<<letras[i]<<endl;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esllave(letras[i]))
        {
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cout <<"Es llave: "<<letras[i]<<endl;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(espuntoycoma(letras[i]))
        {
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cout <<"Es punto y coma: "<<letras[i]<<endl;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esnot(letras[i]))
        {
            if(esigual(letras[++i]))
            {
                cadena_momento[contador_ingresados] = "!=";
                cout << "Igualdad "<<cadena_tempo<<endl;
                contador_ingresados++;
            }
            else
            {
                i--;
                letra[contador_ingresados] = letras[i];
                contador_ingresados++;
                cout <<"Es operador not: "<<letras[i]<<endl;
            }
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(escoma(letras[i]))
        {
            letra[contador_ingresados] = letras[i];
            contador_ingresados++;
            cout <<"Es coma: "<<letras[i]<<endl;
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esigual(letras[i]))
        {
            cout <<"entrandoi:"<<i<<endl;
            cout<<"Letras[i] =:"<<letras[i]<<endl;
            if(esigual(letras[++i]))
            {
                cadena_momento[contador_ingresados] = "==";
                cout << "Igualdad "<<cadena_tempo<<endl;
                contador_ingresados++;
            }
            else
            {
                i--;
                cout <<"saliendo_igual_i:"<<i<<endl;
                letra[contador_ingresados] = letras[i];
                contador_ingresados++;
                cout <<"Es igual: "<<letras[i]<<endl;
            }
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else if(esoperadorrelacional(letras[i]))
        {
            cout <<"entrandoi:"<<i<<endl;
            cout<<"Letras[i] operador < >:"<<letras[i]<<endl;
            if(esigual(letras[++i]))
            {
                i--;
                if(letras[i] == '<')
                {
                    cadena_momento[contador_ingresados] = "<=";
                    cout << "Es operador relacional <= "<<cadena_momento[contador_ingresados]<<endl;
                    contador_ingresados++;
                    i++;
                }
                else
                {
                    cadena_momento[contador_ingresados] = ">=";
                    cout << "Es operador relacional >= "<<cadena_momento[contador_ingresados]<<endl;
                    contador_ingresados++;
                    i++;
                }
            }
            else
            {
                i--;
                cout <<"else i:"<<i<<endl;
                letra[contador_ingresados] = letras[i];
                contador_ingresados++;
                cout <<"Es operador relacional: "<<letras[i]<<endl;
            }
            cadena_tempo.erase(contador_in_cadenas);
            //limpia el buffer del registro
            for (int i = 0; i < longitud; cadenas[i++] = '\0')
                ;
            contador_in_cadenas = 0;
            saltos_linea = 0;
        }
        else
        {
            //limpia el buffer del registro
            for (int x = longitud; x > contador_in_cadenas; cadenas[x--] = '\0')
                ;
            strcpy(letras,cadena_c.c_str());
            cout << "letras dentro else[i]:"<<letras[i]<<endl;
            cout<< "Limpia i:"<<i<<endl;
            cadenas[contador_in_cadenas] = letras[i];
            cadena_tempo = cadenas;
            cout << "letras dentro else:"<<letras<<endl;
            cout << "Cadenas:"<<cadenas<<endl;
            cout << "cadena_tempo:" <<cadena_tempo<<endl;
            contador_in_cadenas++;
            /*int x = 0;
            while(x < cadena_tempo.length())
            {
                if(cadena_tempo == "\n")
                {
                    saltos_linea++;
                }
                x++;
            }
            // Quitar saltos
            cadena_tempo.erase(std::remove(cadena_tempo.begin(), cadena_tempo.end(), '\n'), cadena_tempo.end());*/
            if(esand(cadena_tempo))
            {
                cadena_momento[contador_ingresados] = cadena_tempo;
                cout << "And "<<cadena_tempo<<endl;
                contador_ingresados++;
                cadena_tempo.erase(contador_in_cadenas - 1);
                //limpia el buffer del registro
                for (int i = 0; i < longitud; cadenas[i++] = '\0')
                    ;
                contador_in_cadenas = 0;
                saltos_linea = 0;
            }
            if(esor(cadena_tempo))
            {
                cadena_momento[contador_ingresados] = cadena_tempo;
                cout << "or "<<cadena_tempo<<endl;
                contador_ingresados++;
                cadena_tempo.erase(contador_in_cadenas - 1);
                //limpia el buffer del registro
                for (int i = 0; i < longitud; cadenas[i++] = '\0')
                    ;
                contador_in_cadenas = 0;
                saltos_linea = 0;
            }
            if(espalabra_reservada(cadena_tempo))
            {
                cadena_momento[contador_ingresados] = cadena_tempo;
                cout << "Es palabra reservada: "<<cadena_tempo<<endl;
                contador_ingresados++;
                cadena_tempo.erase(contador_in_cadenas - 1);
                //limpia el buffer del registro
                for (int i = 0; i < longitud; cadenas[i++] = '\0')
                    ;
                contador_in_cadenas = 0;
                saltos_linea = 0;
            }
        }
        i++;
    }
}

void MainWindow::on_pushButton_guardar_clicked()
{
    inicializar();
    cadena = ui ->plainTextEdit_Ingresar_ca->toPlainText();
    ui->plainTextEdit_Ingresar_ca->clear();
    cout << cadena.toStdString()<<endl;
    ui->plainTextEdit_Ingresar_ca->setPlainText("Guardado de manera correcta");
    //Inicializar
    contador_in_cadenas = 0;
}

void MainWindow::on_pushButton_imprimir_clicked()
{
    int contador = 0;
    //ui->agregar_info->setPlainText("ID invalido o repetido, porfavor vuelve a intentarlo");
    ui->plainTextEdit_Ingresar_ca->setPlainText(cadena);
    ui->tableWidget->setColumnCount(3);
    QStringList headers = {"Lexema", "Token", "#"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    token.nombre = cadena;
    longitud_cadena(token.nombre);
    recorrido(token.nombre);
    cout << "Contador_ingresados: "<<contador_ingresados<<endl;
    ui->tableWidget->setRowCount(contador_ingresados);
    for (int z = 0; z < contador_ingresados; z++)
    {
        if(esnumero(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString(letra[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("numero entero");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("1");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esOperador(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString(letra[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            if(letra[z] == '+' || letra[z] == '-')
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador suma + or -");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("5");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
            else
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador multiplicacion * or /");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("6");
                ui->tableWidget->setItem(0,++contador,tipo);
            }

        }
        else if(esparentesis(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString(letra[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            if(letra[z] == '(')
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("parentesis izquierdo (");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("14");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
            else
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("parentesis derecho )");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("15");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
        }
        else if(esllave(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString(letra[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            if(letra[z] == '{')
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("llave izquierda {");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("16");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
            else
            {
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("llave derecha }");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("17");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
        }
        else if(espuntoycoma(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(";");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Punto y coma");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("12");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esnot(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText("!");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Operador not !");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("10");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esoperadorrelacional(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString(letra[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Operador relacional < or >");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("7");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(escoma(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(",");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Coma ,");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("13");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esigual(letra[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText("=");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Igual =");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("18");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esand(cadena_momento[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText("&&");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Operador and &&");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("9");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esor(cadena_momento[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText("||");
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Operador or ||");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("8");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(espalabra_reservada(cadena_momento[z]))
        {
            QTableWidgetItem *lexema = new QTableWidgetItem;
            lexema->setText(QString::fromStdString(cadena_momento[z]));
            ui->tableWidget->setItem(0,contador,lexema);
            QTableWidgetItem *token = new QTableWidgetItem;
            token->setText("Palabra reservada");
            ui->tableWidget->setItem(0,++contador,token);
            QTableWidgetItem *tipo = new QTableWidgetItem;
            tipo->setText("20");
            ui->tableWidget->setItem(0,++contador,tipo);
        }
        else if(esigualdad(cadena_momento[z]))
        {
            if(cadena_momento[z] == "==")
            {
                QTableWidgetItem *lexema = new QTableWidgetItem;
                lexema->setText("==");
                ui->tableWidget->setItem(0,contador,lexema);
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador igualdad ==");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("11");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
            else
            {
                QTableWidgetItem *lexema = new QTableWidgetItem;
                lexema->setText("!=");
                ui->tableWidget->setItem(0,contador,lexema);
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador igualdad !=");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("11");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
        }
        else if(esoperadorrelacional2(cadena_momento[z]))
        {
            if(cadena_momento[z] == "<=")
            {
                QTableWidgetItem *lexema = new QTableWidgetItem;
                lexema->setText("<=");
                ui->tableWidget->setItem(0,contador,lexema);
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador relacional <=");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("7");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
            else
            {
                QTableWidgetItem *lexema = new QTableWidgetItem;
                lexema->setText(">=");
                ui->tableWidget->setItem(0,contador,lexema);
                QTableWidgetItem *token = new QTableWidgetItem;
                token->setText("Operador relacional >=");
                ui->tableWidget->setItem(0,++contador,token);
                QTableWidgetItem *tipo = new QTableWidgetItem;
                tipo->setText("7");
                ui->tableWidget->setItem(0,++contador,tipo);
            }
        }
        contador++;
    }
    contador_ingresados = 0;
}

