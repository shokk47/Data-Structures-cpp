#ifndef QUEUE_QUEUEPTR_H
#define QUEUE_QUEUEPTR_H

#include <iostream>
#include <stdexcept>

template<class T>
class QueuePtr;

/**
 * Questa classe rappresenta un nodo generico utilizzato per la realizzazione
 * di una struttura dati a coda. Ogni nodo contiene un valore di tipo generico
 * e un puntatore al nodo successivo della sequenza.
 *
 * @tparam T il tipo di elemento contenuto nel nodo.
 */
template<class T>
class Node {

private: friend class QueuePtr<T>;
public:
    typedef T typeElem;
    typeElem getValue() const {return value;}
    Node<T> *getNext() const {return next;}
    void setValue(typeElem val) {value = val;}
    void setNext(Node<T> *nextNode) {next = nextNode;}

private:
    typeElem value; // valore del nodo
    Node<T> *next;  // puntatore al nodo successivo
};

/**
 *  Realizzazione di una coda con Puntatori e nodi.
 *  queue: Head:[1]-[2]-[3]-[4]-[5]:Tail
 *  <p>
 *  Una coda è un tipo di astratto che consente di rappresentare una sequenza
 *  di elementi con accesso agli estremi:
 *  <ul>
 *  <li> è possibile aggiungere elementi in fondo alla coda (tail). </li>
 *  <li> è possibile eliminare elementi dalla testa (head). </li>
 *  </ul>
 *  <p>
 *  Detta anche Queue, è un insieme dinamico in cui l'elemento rimosso dall'operazione
 *  di cancellazione è predeterminato, cioè quello che per più tempo è rimasto
 *  nell'insieme (<b>FIFO</b>, first in, first out).
 *  <p>
 *  E' particolarmente adatta a rappresentare sequenze nelle quali l'elemento viene elaborato
 *  secondo l'ordine di arrivo.
 */
template<class T>
class QueuePtr {

public:
    typedef T typeElem;
    QueuePtr();
    ~QueuePtr() {clear();}
    QueuePtr(const QueuePtr<T>&);
    bool isEmpty() const;
    typeElem peek() const;
    void dequeue();
    void enqueue(const typeElem&);
    void clear();

    // Funzioni aggiuntive:
    int getLength() const {return length;}
    bool exists(const typeElem&) const;
    QueuePtr<T>& operator=(const QueuePtr<T>&);
    bool operator==(const QueuePtr<T>&) const;

    template<class T1>
    friend std::ostream &operator<<(std::ostream&, const QueuePtr<T1>&);

private:
    Node<T> *head;
    Node<T> *tail;
    int length;
};

/**
 * Costruttore di default.
 * <p>
 * Costruisce una coda vuota.
 */
template<class T>
QueuePtr<T>::QueuePtr() {
    head = tail = nullptr;
    length = 0;
}
/**
 * Costruttore di copia.
 * <p>
 * Costruisce una coda che è la copia di quella passata come parametro.
 *
 * @param q la coda da copiare.
 */
template<class T>
QueuePtr<T>::QueuePtr(const QueuePtr<T> &q) {
    head = tail = nullptr;
    length = 0;
    if (!q.isEmpty()) {
        Node<T> *tmp = q.head;
        while (tmp != nullptr) {
            enqueue(tmp->getValue());
            tmp = tmp->getNext();
        }
    }
}
/**
 * (codaVuota)
 * Controlla se la coda è vuota.
 * <p>
 * @return true se la coda è vuota, false altrimenti.
 */
template<class T>
bool QueuePtr<T>::isEmpty() const {
    return head == nullptr;
}
/**
 * (leggiCoda)
 * Restituisce il valore dell'elemento in testa alla coda.
 * <p>
 * @return il valore dell'elemento in testa alla coda.
 * @throw std::out_of_range se la coda è vuota.
 */
template<class T>
typename QueuePtr<T>::typeElem QueuePtr<T>::peek() const {
    if (!isEmpty()) {
        return head->getValue();
    } else throw std::out_of_range("Empty queue");
}
/**
 * (fuoriCoda)
 * Elimina l'elemento in testa alla coda.
 * <p>
 * @throw std::out_of_range se la coda è vuota.
 */
template<class T>
void QueuePtr<T>::dequeue() {
    if (!isEmpty()) {
        Node<T> *tmp = head;
        head = head->getNext();
        delete tmp;
        if (isEmpty()) tail = nullptr;
        length--;
    } else throw std::out_of_range("Empty queue");
}
/**
 * (inCoda)
 * Inserisce un elemento in fondo alla coda.
 * <p>
 * @param el l'elemento da inserire.
 */
template<class T>
void QueuePtr<T>::enqueue(const typeElem &el) {
    Node<T> *tmp = new Node<T>;
    tmp->setValue(el);
    tmp->setNext(nullptr);
    if (isEmpty()) {
        head = tmp;
        tail = tmp;
    } else {
        tail->setNext(tmp);
        tail = tmp;
    }
    length++;
}
/**
 * (svuotaCoda)
 * Svuota la coda.
 */
template<class T>
void QueuePtr<T>::clear() {
    while (!isEmpty()) dequeue();
}
/**
 * (esiste)
 * Controlla se un elemento esiste nella coda.
 * <p>
 * @param el l'elemento da cercare.
 * @return true se l'elemento esiste, false altrimenti.
 */
template<class T>
bool QueuePtr<T>::exists(const typeElem &el) const {
    if (!isEmpty()) {
        Node<T> *tmp = head;
        while (tmp != nullptr) {
            if (tmp->getValue() == el) return true;
            tmp = tmp->getNext();
        }
        return false;
    }
    return false;
}
/**
 * Operatore di assegnamento.
 * <p>
 * @param q la coda da copiare.
 * @return la coda che è stata copiata.
 */
template<class T>
QueuePtr<T> &QueuePtr<T>::operator=(const QueuePtr<T> &q) {
    if (this != &q) {
        clear();
        head = tail = nullptr;
        if (!q.isEmpty()) {
            Node<T> *tmp = q.head;
            while (tmp != nullptr) {
                enqueue(tmp->getValue());
                tmp = tmp->getNext();
            }
        }
    }
    return *this;
}
/**
 * Operatore di uguaglianza.
 * <p>
 * @param q la coda da confrontare.
 * @return true se le code sono uguali, false altrimenti.
 */
template<class T>
bool QueuePtr<T>::operator==(const QueuePtr<T> &q) const {
    if (length == q.length) {
        Node<T> *tmp1 = head;
        Node<T> *tmp2 = q.head;
        while (tmp1 != nullptr) {
            if (tmp1->getValue() != tmp2->getValue()) return false;
            tmp1 = tmp1->getNext();
            tmp2 = tmp2->getNext();
        }
        return true;
    }
    return false;
}
/**
 * Operatore di stream.
 * <p>
 * @param os lo stream di output.
 * @param q la coda da stampare.
 * @return lo stream di output.
 */
template<class T>
std::ostream &operator<<(std::ostream &os, const QueuePtr<T> &q) {
    os << "[";
    if (!q.isEmpty()) {
        Node<T> *tmp = q.head;

        while (tmp != nullptr) {
            if (tmp != q.tail)
                os << tmp->getValue() << ",";
            else os << tmp->getValue();
            tmp = tmp->getNext();
        }
    }
    os << "]";
    return os;
}

#endif //QUEUE_QUEUEPTR_H
