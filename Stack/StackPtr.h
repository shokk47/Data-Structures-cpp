#ifndef STACK_STACKPTR_H
#define STACK_STACKPTR_H

#include <ostream>
#include <stdexcept>
#include <iostream>
#include "Node.h"
using namespace std;

/**
 * @brief Classe che rappresenta una pila implementata tramite puntatori.
 * <p><br>
 * Una pila è una sequenza di elementi di un certo tipo in cui è possibile
 * aggiungere e togliere elementi solo da un capo, detto cima della pila.
 * <p><br>
 * Può essere vista come una lista LIFO (Last In First Out), ovvero l'ultimo
 * elemento inserito è il primo ad essere estratto. Infatti, non è possibile
 * accedere ad alcun elemento che non sia quello in testa.
 * @tparam T tipo di dato.
 */
template <class T>
class StackPtr {
public:
    typedef T typeElem;

    StackPtr();
    StackPtr(const StackPtr<T>&);
    ~StackPtr();

    void create();          // creaPila()
    bool isEmpty() const;   // pilaVuota()
    typeElem top() const;   // leggiPila()
    void pop();             // fuoriPila()
    void push(typeElem);    // inPila()

    StackPtr<T>& operator=(const StackPtr<T>&);
    bool operator==(const StackPtr<T>&) const;
    bool operator!=(const StackPtr<T>&) const;

    template <class U>
    friend ostream& operator<<(ostream&, const StackPtr<U>&);

    int getLength() const;
    bool exist(typeElem) const;

private:
    Node<T>* head;
};

/**
 * @brief Costruttore di default che inizializza la pila con un puntatore nullo.
 * @tparam T tipo di dato.
 */
template <class T>
StackPtr<T>::StackPtr() {
    create();
}
/**
 * @brief Costruttore di copia.
 * @tparam T tipo di dato.
 * @param s pila da copiare.
 */
template <class T>
StackPtr<T>::StackPtr(const StackPtr<T>& s) {
    create();
    Node<T>* tmp = s.head;
    while (tmp != nullptr) {
        push(tmp->getValue());
        tmp = tmp->getNext();
    }
}
/**
 * @brief Distruttore.
 * @tparam T tipo di dato.
 */
template <class T>
StackPtr<T>::~StackPtr() {
    while (!isEmpty()) {
        pop();
    }
}
/**
 * @brief Crea la pila.
 * @tparam T tipo di dato.
 */
template <class T>
void StackPtr<T>::create() {
    head = nullptr;
}
/**
 * @brief Controlla se la pila è vuota.
 * @tparam T tipo di dato.
 * @return true se la pila è vuota, false altrimenti.
 */
template <class T>
bool StackPtr<T>::isEmpty() const {
    return head == nullptr;
}
/**
 * @brief Restituisce la lunghezza della pila.
 * @tparam T tipo di dato.
 * @return lunghezza della pila.
 */
template <class T>
typename StackPtr<T>::typeElem StackPtr<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("StackPtr<T>::top() const: empty stack");
    }
    return head->getValue();
}
/**
 * @brief Restituisce l'elemento in cima alla pila.
 * @tparam T tipo di dato.
 */
template <class T>
void StackPtr<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("StackPtr<T>::pop(): empty stack");
    }
    Node<T>* tmp = head;
    head = head->getNext();
    delete tmp;
}
/**
 * @brief Inserisce un elemento in cima alla pila.
 * @tparam T tipo di dato.
 * @param value valore da inserire.
 */
template <class T>
void StackPtr<T>::push(typeElem value) {
    Node<T>* tmp = new Node<T>(value);
    tmp->setNext(head);
    head = tmp;
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T tipo di dato.
 * @param s pila da assegnare.
 * @return pila assegnata.
 */
template <class T>
StackPtr<T>& StackPtr<T>::operator=(const StackPtr<T>& s) {
    if (this != &s) {
        // Pulisci la pila corrente
        while (!isEmpty()) {
            pop();
        }

        // Copia gli elementi dalla pila s alla pila corrente
        Node<T>* tmp = s.head;
        Node<T>* prev = nullptr;
        while (tmp != nullptr) {
            Node<T>* newNode = new Node<T>(tmp->getValue());
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->setNext(newNode);
            }
            prev = newNode;
            tmp = tmp->getNext();
        }
    }
    return *this;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam T tipo di dato.
 * @param s pila da confrontare.
 * @return true se le pile sono uguali, false altrimenti.
 */
template <class T>
bool StackPtr<T>::operator==(const StackPtr<T>& s) const {
    if (getLength() != s.getLength()) {
        return false;
    }
    Node<T>* tmp1 = head;
    Node<T>* tmp2 = s.head;
    while (tmp1 != nullptr) {
        if (tmp1->getValue() != tmp2->getValue()) {
            return false;
        }
        tmp1 = tmp1->getNext();
        tmp2 = tmp2->getNext();
    }
    return true;
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T tipo di dato.
 * @param s pila da confrontare.
 * @return true se le pile sono diverse, false altrimenti.
 */
template <class T>
bool StackPtr<T>::operator!=(const StackPtr<T>& s) const {
    return !(*this == s);
}
/**
 * @brief Stampa la pila.
 * La stampa avviene stampando il valore di ogni nodo della pila,
 * partendo dalla cima e andando verso il fondo.
 * top -> [],[],[],[],...,[] <- button
 * @tparam T tipo di dato.
 * @param os
 * @param s pila da stampare.
 * @return
 */
template <class T>
ostream& operator<<(ostream& os, const StackPtr<T>& s) {
    Node<T>* tmp = s.head;
    os << "[";
    while (tmp != nullptr) {
        if (tmp->getNext() == nullptr) {
            os << tmp->getValue();
        } else {
            os << tmp->getValue() << ",";
        }
        tmp = tmp->getNext();
    }
    os << "]";
    tmp = nullptr;
    delete tmp;
    return os;
}
/**
 * @brief Restituisce la lunghezza della pila.
 * @tparam T tipo di dato.
 * @return lunghezza della pila.
 */
template <class T>
int StackPtr<T>::getLength() const {
    int length = 0;
    Node<T>* tmp = head;
    while (tmp != nullptr) {
        length++;
        tmp = tmp->getNext();
    }
    return length;
}
/**
 * @brief Controlla se un elemento è presente nella pila.
 * @tparam T tipo di dato.
 * @param value valore da cercare.
 * @return true se l'elemento è presente, false altrimenti.
 */
template <class T>
bool StackPtr<T>::exist(typeElem value) const {
    Node<T>* tmp = head;
    while (tmp != nullptr) {
        if (tmp->getValue() == value) {
            return true;
        }
        tmp = tmp->getNext();
    }
    return false;
}
#endif //STACK_STACKPTR_H
