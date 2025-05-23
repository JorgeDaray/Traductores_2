#ifndef sintacti_H
#define sintacti_H
#include "lexico.h"
#include <stdlib.h>
#include "genera.h"
using namespace std;
class Sintactico{
	 void programa (void);
	 void bloque (void);
	 void sentencia (void);
	 void otra_sentencia (void);
	 void asignacion(void);
	 void lectura (void);
	 void escritura(void);
	 void variable(void);
	 void expresion(void);
	 void termino(void);
	 void mas_terminos(void);
	 void factor(void);
	 void mas_factores(void);
	 void constante(void);
	 void errores (int codigo);
	 Lexico lexico; //objeto l�xico miembro de la clase
	 GeneraCodigo generador;
	 public:
	 Sintactico(char *fuente, int traza, char *destino);
	 ~Sintactico(void);
};
Sintactico::Sintactico(char *fuente, int traza, char *destino): lexico(fuente, traza), generador(destino)
//se inicializa el constructor de la clase l�xico
{
 if (lexico.existeTraza())
 	cout<<"INICIO DE ANALISIS SINTACTICO"<<endl;
	programa();
}
/***********************************************************/
Sintactico::~Sintactico(void)
{
 if (lexico.existeTraza())
 {
 	cout<<"FIN DE ANALISIS SINTACTICO"<<endl;
 	cout<<"FIN DE COMPILACION"<<endl;
 }
}
/***********************************************************/
void Sintactico::programa(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <PROGRAMA>"<<endl;
	 generador.code();
	 token=lexico.siguienteToken();
	 if (token=='M') cout <<"M";
	 else errores(8);
	 token=lexico.siguienteToken();
	 if (token!='{') errores(9);
	 bloque();
	 token=lexico.siguienteToken();
	 if (token=='}')
	 {
	 	cout<<"}";
	 }
	 else errores(2);
}
/***********************************************************/
void Sintactico::bloque(void)
{
	 char token=' ';
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <BLOQUE>"<<endl;
	 sentencia();
	 otra_sentencia();
}
/***********************************************************/
void Sintactico::otra_sentencia(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <OTRA_SENTENCIA>"<<endl;
	 token=lexico.siguienteToken();
	 if (token==';')
	 {
	 	sentencia();
	 	otra_sentencia();
	 }
	 else lexico.devuelveToken(token); //vacio
}
/***********************************************************/
void Sintactico::sentencia(void)
{
	 char token;
	 if (lexico.existeTraza())
	 	cout<<"ANALISIS SINTACTICO: <SENTENCIA>"<<endl;
	 token=lexico.siguienteToken();
	 if ((token>='a') && (token<='z'))
	 {
	 	lexico.devuelveToken(token);
	 	asignacion();
	 }
	else if (token== 'R') lectura();
	else if (token== 'W') escritura();
	 
}
/***********************************************************/
void Sintactico::asignacion()
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <ASIGNACION>"<<endl;
	 generador.add();
	 variable();
	 token=lexico.siguienteToken();
	 if (token!='=') errores(3);
	 expresion();
}
/***********************************************************/
void Sintactico::variable(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <VARIABLE>"<<endl;
	 token=lexico.siguienteToken();
	 if ((token>='a') && (token<='z')) cout<<token;
	 else errores(5);
}
/***********************************************************/
void Sintactico::expresion(void)
{
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <EXPRESION>"<<endl;
	 termino();
	 mas_terminos();
}
/***********************************************************/
void Sintactico::termino(void)
{
	if (lexico.existeTraza())
	 cout <<"ANALISIS SINTACTICO: <TERMINO>"<<endl;
	 factor();
	 mas_factores();
}
/***********************************************************/
void Sintactico::mas_terminos(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <MAS_TERMINOS>"<<endl;
	 token=lexico.siguienteToken();
	 if (token=='+')
	 {
	 	termino();
	 	mas_terminos();
	 }
	 else if (token =='-')
	 {
	 	termino();
	 	mas_terminos();
	 }
	 else lexico.devuelveToken(token); // <vacio>
}
/***********************************************************/
void Sintactico::factor(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <FACTOR>"<<endl;
	 token=lexico.siguienteToken();
	 if ((token>='0') && (token<='9'))
	 {
	 	lexico.devuelveToken(token);
	 	constante();
	 }
	 else if (token=='(')
	 {
	 	expresion();
	 	token=lexico.siguienteToken();
	 	if (token!=')') errores(4);
	 }
	 else
	 {
	 	lexico.devuelveToken(token);
	 	variable();
	 }
}
/***********************************************************/void 
Sintactico::mas_factores(void)
{
	 char token;
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <MAS_FACTORES>"<<endl;
	 token=lexico.siguienteToken();
	 switch (token)
	 {
		 case '*':factor();
		 mas_factores();
		 break;
		 case '/':factor();
		 mas_factores();
		 break;
		 case '%':factor();
		 mas_factores();
		 break;
		 default: //<vacio>
		 lexico.devuelveToken(token);
	 }
}
/***********************************************************/
void Sintactico::lectura(void)
{
	 char token;
	 token=lexico.siguienteToken();
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <LECTURA> "<<token<<endl;
	 generador.input(token);
	 if ((token<'a')||(token>'z')) errores(5);
}
/***********************************************************/
void Sintactico::escritura(void)
{
	 char token;
	 token=lexico.siguienteToken();
	 if (lexico.existeTraza())
	 cout<<"ANALISIS SINTACTICO: <ESCRITURA> "<<token<<endl;
	 generador.output(token);
	 if ((token<'a') || (token>'z')) errores(5);
}
/************************************************/
void Sintactico::constante(void)
{
	char token;
	if (lexico.existeTraza())
	cout<<"ANALISIS SINTACTICO: <CONSTANTE>"<<endl;
	token=lexico.siguienteToken();
	if ((token>='0') && (token<='9')) cout<<token;
	else errores(7);
}
/***********************************************************/
void Sintactico::errores(int codigo)
{
	 int x;
	 cout<<"LINEA "<<lexico.lineaActual();
	 cout<<" ERROR SINTACTICO "<<codigo;
	 switch (codigo)
	 {
		 case 1 :cout<<" :ESPERABA UN ;"<<endl;break;
		 case 2 :cout<<" :ESPERABA UNA }"<<endl;break;
		 case 3 :cout<<" :ESPERABA UN ="<<endl;break;
		 case 4 :cout<<" :ESPERABA UN )"<<endl;break;
		 case 5 :cout<<" :ESPERABA UN IDENTIFICADOR"<<endl;break;
		 case 6 :cout<<" :INSTRUCCION DESCONOCIDA"<<endl;break;
		 case 7 :cout<<" :ESPERABA UNA CONSTANTE"<<endl;break;
		 case 8 :cout<<" :ESPERABA UNA M DE MAIN"<<endl;break;
		 case 9 :cout<<" :ESPERABA UNA {"<<endl;break;
		 default:
		 cout<<" :NO DOCUMENTADO"<<endl;
	 }
	 cin>>x;
	 exit(-(codigo+100));
}
#endif
