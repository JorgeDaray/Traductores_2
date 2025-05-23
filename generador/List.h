#include <iostream>
#include "Node.h"
#include <string.h>
using namespace std;

template <class T> class List{
    Node<T>* head;
    string cadena;
    public: List();
    ~List();
    int isEmpty();
    void display();
    int length();
    void push(T);
    void reconocimiento(T);
    T pop();
    T top();
    void expresionFinal();
    void buscar(T, T);
    void removeAll();
    void setCadena();
};

template <class T> void List<T>::setCadena()
{
    cadena = "";
}

template <class T> List<T>::List()
{
    head = NULL;
}

template <class T> List<T>::~List(){
    Node<T> *p, *q;
    p = head;
    while(p != NULL){
        q = p->getNext();
        delete p;
        p = q;
    }
    delete head;
    head = 0;
}

template <class T> void List<T>::removeAll(){
    Node<T> *p, *q;
    p = head;
    while(p != NULL){
        q = p->getNext();
        delete p;
        p = q;
    }
    delete head;
    head = 0;
}

template <class T> void List<T>::expresionFinal()
{
    int tamano = this->length();
    for(int i = 1; i <= tamano; i++){
        if(top() == '(' || top() == ')')
        {
            cout << "Error de sintaxis en la expresion" << endl;
            return;
        }
        cadena = cadena + this->pop();
    }
    for(int j = 0; j < cadena.size(); j++){
        cout << cadena[j];
    }
    cadena = "";
    return;
}

template <class T> int List<T>::isEmpty()
{
    return (head == NULL);
}

template <class T> void List<T>::display()
{
    Note<T> *p;
    p = head;
    while(p != NULL){
        cout << p->getDato() << " ";
        p = p->getNext();
    }
    cout << endl;
}

template <class T> int List<T>::length(){
    Node<T> *p;
    int acum = 0;
    p = head;
    while(p != NULL){
        p = p->getNext();
        acum++;
    }
    return acum;
}

template <class T> void List<T>::reconocimiento(T obj)
{
    int n, i = 0, tamano = 0;
    switch(obj)
    {
        case '(':
        this->push('(');
        break;
        case ')':
        while(this->top() != '('){
            cadena = cadena + this->pop();
        }
        this->pop();
        break;
        case '+':
        while(this->top() == '*' || this->top() == '/' || this->top() == '^')
        {
            cadena = cadena + this->pop();
        }
        this->push('+');
        break;
        case '-':
        while(this->top() == '*' || this->top() == '/' || this->top() == '^')
        {
            cadena = cadena + this->pop();
        }
        this->push('-');
        break;
        case '*':
        while(this->top() == '^')
        {
            cadena = cadena + this->pop();
        }
        this->push('*');
        break;
        case '/':
        while(this->top() == '^')
        {
            cadena = cadena + this->pop();
        }
        this->push('/');
        break;
        case '^':
        this->push('^');
        break;
        default:
        cadena = cadena + obj;
        break;
    }
}

template <class T> void List<T>::buscar(T caracter1, T caracter2)
{
    int i = 0; Node<T> *p;
    p = head;
    this->pop();
    return;
    while( i < this->length())
    {
        if(this->top() == caracter1 || this->top() == caracter2)
        {
            cadena = cadena + this->top();
            this->pop();
        }
        i++;
    }
    return;
}

template <class T> void List<T>::push(T obj){
    Node<T> *nuevo;
    nuevo = new Node<T>;
    nuevo->setDato(obj);
    if(head == NULL)
    {
        nuevo->setNext(head);
        head = nuevo;
        return;
    }
    Node<T> *p;
    p = head;
    while(p->getNext() != NULL){
        p = p->getNext();
    }

    nuevo->setNext(p->getNext());
    p->setNext(nuevo);
}

template <class T> T List<T>::pop(){
    if(isEmpty())
    {
        return 0;
    }
    if(this->length == 1)
    {
        Node<T> *p;
        if (head != NULL)
        {
            p = head;
            T valor = p->getDato();
            head = head->getNext();
            delete p;
            return valor;
        }
        else
        {
            return 0;
        }
    }
    Node<T> *p, *q;
    if(head != NULL)
    {
        p = head;
        q = 0;
        while (p->getNext() != NULL){
            q = p;
            p = p->getNext();
        }
        T valor = p->getDato();

        q->setNext(p->getNext());
        delete p;
        return valor;
    } else {
        return 0;
    }
}

template <class T> T List<T>::top()
{
    if(isEmpty())
    {
        return 0;
    }
    Node<T> *p, *q;
    if(head != NULL){
        p = head;
        q = 0;
        while(p->getNext() != NULL){
            q = p;
            p = p->getNext();
        }
        T valor = p->getDato();
        return valor;
    } else{
        return 0;
    }
}