#include <iostream>>
template <class T> class Node{
    private:
    T data;
    Node<T> *next;
    public:
    Node<T> *getNext();
    T getDato();

    void setDato(T);
    void setNext(Node<T>*);
    Node();
    friend class List<T>;
};

template <class T> Node<T>::Node()
{
    this->next = 0;
}

template <class T> Node<T>* Node<T>::getNext()
{
    return next;
}

template <class T> void Node<T>::setNext(Node<T>* sig)
{
    this->next = sig;
}

template <class T> T Node<T>::getDato()
{
    return this->data;
}

template <class T> void Node<T>::setDato(T dato)
{
    this->data = dato;
}