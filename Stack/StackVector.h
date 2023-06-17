#ifndef STACK_STACKVECTOR_H
#define STACK_STACKVECTOR_H

#include <ostream>
#include <stdexcept>
#include <iostream>
using namespace std;

/**
 * @brief Classe che rappresenta una pila implementata tramite vettore.
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
class StackVector {
public:
    typedef T typeElem;

    StackVector();
    StackVector(int);
    StackVector(const StackVector<T>&);
    ~StackVector();

    void create();          // creaPila()
    bool isEmpty() const;   // pilaVuota()
    typeElem top() const;   // leggiPila()
    void pop();             // fuoriPila()
    void push(typeElem);    // inPila()

    StackVector<T>& operator=(const StackVector<T>&);
    bool operator==(const StackVector<T>&) const;
    bool operator!=(const StackVector<T>&) const;

    template <class U>
    friend ostream& operator<<(ostream&, const StackVector<U>&);

    int getLength() { return head;}
    bool exist(typeElem);

private:
    typeElem* array;
    int lengthArray;
    int head;
    void changeDimension(typeElem*& , int, int);
};

/**
 * @brief Costruttore di default che inizializza la pila con una lunghezza di 10.
 * @tparam T  tipo di dato.
 */
template <class T>
StackVector<T>::StackVector() {
    lengthArray = 10;
    array = new typeElem[10];
    create();
}
/**
 * @brief Costruttore che inizializza la pila con una lunghezza passata come parametro.
 * @tparam T tipo di dato.
 * @param n lunghezza della pila.
 */
template <class T>
StackVector<T>::StackVector(int n) {
    lengthArray = n;
    array = new typeElem[lengthArray];
    create();
}
/**
 * @brief Costruttore di copia.
 * @tparam T tipo di dato.
 * @param s pila da copiare.
 */
template <class T>
StackVector<T>::StackVector(const StackVector<T>& s) {
    lengthArray = s.lengthArray;
    array = new typeElem[lengthArray];
    for (int i = 0; i < lengthArray; i++) {
        array[i] = s.array[i];
    }
    head = s.head;
}
/**
 * @brief Distruttore.
 * @tparam T tipo di dato.
 */
template <class T>
StackVector<T>::~StackVector() {
    delete[] array;
}
/**
 * @brief Crea una pila vuota.
 * @tparam T
 */
template <class T>
void StackVector<T>::create() {
    head = 0;
}
/**
 * @brief Controlla se la pila è vuota.
 * @tparam T tipo di dato.
 * @return true se la pila è vuota, false altrimenti.
 */
template <class T>
bool StackVector<T>::isEmpty() const {
    return head == 0;
}
/**
 * @brief Restituisce l'elemento in cima alla pila.
 * @tparam T tipo di dato.
 * @return elemento in cima alla pila.
 */
template <class T>
typename StackVector<T>::typeElem StackVector<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return array[head - 1];
}
/**
 * @brief Elimina l'elemento in cima alla pila.
 * @tparam T tipo di dato.
 */
template <class T>
void StackVector<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    head--;
}
/**
 * @brief Inserisce un elemento in cima alla pila.
 * @tparam T tipo di dato.
 * @param e elemento da inserire.
 */
template <class T>
void StackVector<T>::push(typeElem e) {
    if (head == lengthArray) {
        changeDimension(array, lengthArray, 2 * lengthArray);
        lengthArray = 2 * lengthArray;
    }
    array[head] = e;
    head++;
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T tipo di dato.
 * @param s pila da assegnare.
 * @return pila assegnata.
 */
template <class T>
StackVector<T>& StackVector<T>::operator=(const StackVector<T>& s) {
    if (this != &s) {
        delete[] array;
        lengthArray = s.lengthArray;
        head = s.head;
        array = new T[lengthArray];
        for (int i = 0; i < lengthArray; i++) {
            array[i] = s.array[i];
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
bool StackVector<T>::operator==(const StackVector<T>& s) const {
    if (head != s.head) {
        return false;
    }
    for (int i = 0; i < head; i++) {
        if (array[i] != s.array[i]) {
            return false;
        }
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
bool StackVector<T>::operator!=(const StackVector<T>& s) const {
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
ostream& operator<<(ostream& os, const StackVector<T>& s) {
    os << "[";
    for (int i = s.head-1; i>=0; i--) {
        if (i != s.head-1) os << "," << s.array[i];
        else               os << s.array[i];
    }
    os << "]";
    return os;
}
/**
 * @brief Cambia la dimensione della pila.
 * @tparam T tipo di dato.
 * @param el Pila da modificare.
 * @param oldDim dimensione attuale.
 * @param newDim nuova dimensione.
 */
template <class T>
void StackVector<T>::changeDimension(StackVector::typeElem *&el, int oldDim, int newDim) {
    int numero = (oldDim < newDim) ? oldDim : newDim;
    typeElem *tmp = new typeElem[newDim];
    for (int i = 0; i < numero; i++) {
        tmp[i] = el[i];
    }
    delete[] el;
    el = tmp;
}
/**
 * @brief Controlla se un elemento è presente nella pila.
 * @tparam T tipo di dato.
 * @param e elemento da cercare.
 * @return true se l'elemento è presente, false altrimenti.
 */
template <class T>
bool StackVector<T>::exist(typeElem e) {
    for (int i = 0; i < head; i++) {
        if (array[i] == e) {
            return true;
        }
    }
    return false;
}

#endif //STACK_STACKVECTOR_H
