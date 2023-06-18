#ifndef QUEUE_QUEUEPTR_H
#define QUEUE_QUEUEPTR_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

/**
 *  @brief Classe che rappresenta una coda implementata tramite puntatori.
 *  <p><br>
 *  Realizzazione di una coda con vettore.
 *  queue: Head -> [1,2,3,4,5] <- Tail
 *  <p><br>
 *  Una coda è un tipo di astratto che consente di rappresentare una sequenza
 *  di elementi con accesso agli estremi:
 *  <ul>
 *  <li> è possibile aggiungere elementi in fondo alla coda (tail). </li>
 *  <li> è possibile leggere l'elemento in testa alla coda (head). </li>
 *  <li> è possibile eliminare l'elemento in testa alla coda (head). </li>
 *  </ul>
 *  <p><br>
 *  Detta anche Queue, è un insieme dinamico in cui l'elemento rimosso dall'operazione
 *  di cancellazione è predeterminato, cioè quello che per più tempo è rimasto
 *  nell'insieme (<b>FIFO</b>, first in, first out).
 *  <p><br>
 *  E' particolarmente adatta a rappresentare sequenze nelle quali l'elemento viene elaborato
 *  secondo l'ordine di arrivo.
 */
template<class T>
class QueuePtr {

public:
    typedef T typeElem;
    QueuePtr();
    QueuePtr(const QueuePtr<T>&);
    ~QueuePtr();

    // Metodi di servizio:
    bool codaVuota() const;         // restituisce true se la coda è vuota, false altrimenti
    typeElem leggiCoda() const;     // restituisce l'elemento in testa alla coda
    void fuoriCoda();               // elimina l'elemento in testa alla coda
    void incoda(const typeElem&);   // inserisce un elemento in coda

    // Overload operatori:
    QueuePtr<T>& operator=(const QueuePtr<T>&);
    bool operator==(const QueuePtr<T>&) const;
    bool operator!=(const QueuePtr<T>&) const;

    template<class T1>
    friend std::ostream &operator<<(std::ostream&, const QueuePtr<T1>&);

    // Metodi aggiuntivi:
    int lunghezza() const {return length;};
    bool ricercaElemento(const typeElem&) const;
    void clear();

private:
    Node<T> *head;
    Node<T> *tail;
    int length;
};

/**
 * @brief Costruttore di default che crea una coda vuota.
 * @tparam T tipo di dato.
 */
template <class T>
QueuePtr<T>::QueuePtr() {
    head = tail = nullptr;
    length = 0;
}
/**
 * @brief Costruttore di copia.
 * @tparam T tipo di dato.
 * @param q la coda da copiare.
 */
template <class T>
QueuePtr<T>::QueuePtr(const QueuePtr<T> &q) {
    head = nullptr;
    tail = nullptr;
    length = 0;

    Node<T>* nodeCopy = q.head;
    while (nodeCopy != nullptr) {
        incoda(nodeCopy->getValue());
        nodeCopy = nodeCopy->getNext();
    }
}
/**
 * @brief Distruttore.
 * @tparam T tipo di dato.
 */
template <class T>
QueuePtr<T>::~QueuePtr() {
    clear();
}
/**
 * @brief Restituisce true se la coda è vuota, false altrimenti.
 * @tparam T tipo di dato.
 */
template <class T>
bool QueuePtr<T>::codaVuota() const {
    return head == nullptr;
}
/**
 * @brief Restituisce l'elemento in testa alla coda senza rimuoverlo.
 * @tparam T tipo di dato.
 */
template <class T>
typename QueuePtr<T>::typeElem QueuePtr<T>::leggiCoda() const {
    if (codaVuota())
        throw std::runtime_error("QueuePtr vuota, impossibile leggere.");
    return head->getValue();
}
/**
 * @brief Rimuove l'elemento in testa alla coda.
 * @tparam T tipo di dato.
 */
template <class T>
void QueuePtr<T>::fuoriCoda() {
    if (codaVuota())
        throw std::runtime_error("QueuePtr vuota, impossibile eliminare.");
    Node<T>* node = head;
    head = head->getNext();
    delete node;
    if (head == nullptr)
        tail = nullptr;
    length--;
}
/**
 * @brief Aggiunge un elemento in fondo alla coda.
 * @tparam T tipo di dato.
 */
template <class T>
void QueuePtr<T>::incoda(const typeElem &el) {
    Node<T>* newNode = new Node<T>(el);
    if (codaVuota())
        head = newNode;
    else
        tail->setNext(newNode);
    tail = newNode;
    length++;
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T tipo di dato.
 * @param q la coda da assegnare.
 * @return la coda assegnata.
 */
template <class T>
QueuePtr<T>& QueuePtr<T>::operator=(const QueuePtr<T>& q) {
    if (this != &q) {
        clear();
        Node<T>* nodeCopy = q.head;
        while (nodeCopy != nullptr) {
            incoda(nodeCopy->getValue());
            nodeCopy = nodeCopy->getNext();
        }
    }
    return *this;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam T tipo di dato.
 * @param q la coda da confrontare.
 * @return true se le code sono uguali, false altrimenti.
 */
template <class T>
bool QueuePtr<T>::operator==(const QueuePtr<T> &q) const {
    if (length != q.length)
        return false;

    Node<T>* node1 = head;
    Node<T>* node2 = q.head;
    while (node1 != nullptr && node2 != nullptr) {
        if (node1->getValue() != node2->getValue())
            return false;
        node1 = node1->getNext();
        node2 = node2->getNext();
    }

    // Se entrambi i puntatori dei nodi sono nulli, allora i valori dei nodi confrontati sono uguali
    return (node1 == nullptr && node2 == nullptr);
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T tipo di dato.
 * @param q la coda da confrontare.
 * @return true se le code sono diverse, false altrimenti.
 */
template <class T>
bool QueuePtr<T>::operator!=(const QueuePtr<T> &q) const {
    return !(*this == q);
}
/**
 * @brief Stampa la coda.
 * La stampa avviene stampando il valore di ogni elemento della coda,
 * partendo dalla testa e terminando con la coda.
 * head -> [1,2,3,4,5] <- tail
 * @tparam T tipo di dato.
 * @param os stream di output.
 * @param q la coda da stampare.
 * @return lo stream di output.
 */
template <class T>
std::ostream &operator<<(std::ostream &os, const QueuePtr<T> &q) {
    Node<T>* node = q.head;
    os << "[";
    while (node != nullptr) {
        os << node->getValue();
        if (node->getNext() != nullptr)
            os << ",";
        node = node->getNext();
    }
    os << "]";
    return os;
}
/**
 * @brief Verifica se un elemento è presente nella coda.
 * @tparam T tipo di dato.
 * @param el l'elemento da cercare.
 * @return true se l'elemento è presente, false altrimenti.
 */
template <class T>
bool QueuePtr<T>::ricercaElemento(const typeElem &el) const {
    Node<T>* node = head;
    while (node != nullptr) {
        if (node->getValue() == el)
            return true;
        node = node->getNext();
    }
    return false;
}
/**
 * @brief Svuota la coda.
 * @tparam T tipo di dato.
 */
template <class T>
void QueuePtr<T>::clear() {
    while (!codaVuota())
        fuoriCoda();
}

#endif //QUEUE_QUEUEPTR_H
