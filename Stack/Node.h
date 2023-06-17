#ifndef STACK_NODE_H
#define STACK_NODE_H

#include <ostream>
#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    typedef T typeElem;

    Node();
    Node(typeElem);
    Node(const Node<T>&);
    ~Node();

    typeElem getValue() const;
    void setValue(typeElem);

    Node<T>* getNext() const;
    void setNext(Node<T>*);

private:
    typeElem value;
    Node<T>* next;
};
/**
 * @brief Costruttore di default che inizializza il nodo con un valore nullo e un puntatore nullo.
 * @tparam T tipo di dato.
 */
template <class T>
Node<T>::Node() {
    value = 0;
    next = nullptr;
}
/**
 * @brief Costruttore che inizializza il nodo con un valore passato come parametro e un puntatore nullo.
 * @tparam T  tipo di dato.
 * @param value valore del nodo.
 */
template <class T>
Node<T>::Node(typeElem value) {
    this->value = value;
    next = nullptr;
}
/**
 * @brief Costruttore di copia.
 * @tparam T tipo di dato.
 * @param node nodo da copiare.
 */
template <class T>
Node<T>::Node(const Node<T>& node) {
    value = node.value;
    next = node.next;
}
/**
 * @brief Distruttore.
 * @tparam T tipo di dato.
 */
template <class T>
Node<T>::~Node() {
    value = 0;
    next = nullptr;
}
/**
 * @brief Restituisce il valore del nodo.
 * @tparam T tipo di dato.
 * @return valore del nodo.
 */
template <class T>
typename Node<T>::typeElem Node<T>::getValue() const {
    return value;
}
/**
 * @brief Imposta il valore del nodo.
 * @tparam T tipo di dato.
 * @param value valore del nodo.
 */
template <class T>
void Node<T>::setValue(typeElem value) {
    this->value = value;
}
/**
 * @brief Restituisce il puntatore al nodo successivo.
 * @tparam T tipo di dato.
 * @return puntatore al nodo successivo.
 */
template <class T>
Node<T>* Node<T>::getNext() const {
    return next;
}
/**
 * @brief Imposta il puntatore al nodo successivo.
 * @tparam T tipo di dato.
 * @param next puntatore al nodo successivo.
 */
template <class T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

#endif //STACK_NODE_H
