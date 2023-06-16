#ifndef QUEUE_QUEUEVECTOR_H
#define QUEUE_QUEUEVECTOR_H

#include <iostream>
#include <stdexcept>

/**
 *  Realizzazione di una coda con vettore.
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
class QueueVector {

public:
    typedef T typeElem;
    QueueVector();
    ~QueueVector() {clear();}
    QueueVector(const QueueVector<T>&);
    bool isEmpty() const;
    typeElem peek() const;
    void dequeue();
    void enqueue(const typeElem&);
    void clear();

    // Funzioni aggiuntive:
    int getLength() const;
    bool exists(const typeElem&) const;
    QueueVector<T>& operator=(const QueueVector<T>&);
    bool operator==(const QueueVector<T>&) const;

    template<class T1>
    friend std::ostream &operator<<(std::ostream&, const QueueVector<T1>&);

private:
    int head;           // indice della testa
    int tail;           // indice della coda
    int length;         // dimensione totale dell'array, compresi gli spazi vuoti
    typeElem *elements; // array in cui memorizzare gli elementi
    void changeDimension(typeElem *&, int, int);
};

/**
 * Costruttore di default che crea
 * una coda vuota di 10 elementi.
 * <p>
 * Costruisce una coda vuota.
 */
template<class T>
QueueVector<T>::QueueVector() {
    length = 10;
    elements = new typeElem[length];
    head = tail = 0;
    length = 10;
}
/**
 * Costruttore di copia.
 * <p>
 * Costruisce una coda che è la copia di quella passata come parametro.
 *
 * @param q la coda da copiare.
 */
template<class T>
QueueVector<T>::QueueVector(const QueueVector<T> &q) {
    length = q.length;
    head = q.headh;
    tail = q.tail;
    elements = new typeElem[length];
    for (int i = head; i < tail; i++) {
        elements[(head+i)%length] = q.elements[(head+i)%length];
    }
}
/**
 * (codaVuota)
 * Controlla se la coda è vuota.
 * <p>
 * @return true se la coda è vuota, false altrimenti.
 */
template<class T>
bool QueueVector<T>::isEmpty() const {
    return tail <= 0;
}
/**
 * (leggiCoda)
 * Restituisce il valore dell'elemento in testa alla coda.
 * <p>
 * @return il valore dell'elemento in testa alla coda.
 * @throw std::out_of_range se la coda è vuota.
 */
template<class T>
typename QueueVector<T>::typeElem QueueVector<T>::peek() const {
    if (!isEmpty()) return elements[head];
    else throw std::out_of_range("Empty queue");
}
/**
 * (fuoriCoda)
 * Elimina l'elemento in testa alla coda.
 * <p>
 * @throw std::out_of_range se la coda è vuota.
 */
template<class T>
void QueueVector<T>::dequeue() {
    if (!isEmpty()) {
        head = (head+1)%length;
        tail--;
    } else throw std::out_of_range("Empty queue");
}
/**
 * (inCoda)
 * Inserisce un elemento in fondo alla coda.
 * <p>
 * @param el l'elemento da inserire.
 */
template<class T>
void QueueVector<T>::enqueue(const typeElem &el) {
    if (tail == length) {
        changeDimension(elements, length, length*2);
        length *= 2;
    }
    elements[(head+tail)%length] = el;
    tail++;
}
/**
 * (svuotaCoda)
 * Svuota la coda.
 */
template<class T>
void QueueVector<T>::clear() {
    head = tail = 0;
}
/**
 * (lunghezza)
 * Restituisce la lunghezza della coda.
 * <p>
 * @return la lunghezza della coda.
 */
template<class T>
int QueueVector<T>::getLength() const {
    return tail;
}
/**
 * (esiste)
 * Controlla se un elemento esiste nella coda.
 * <p>
 * @param el l'elemento da cercare.
 * @return true se l'elemento esiste, false altrimenti.
 */
template<class T>
bool QueueVector<T>::exists(const typeElem &el) const {
    if (!isEmpty()) {
        for (int i = head; i < tail; i++) {
            if (elements[(head+i)%length] == el) return true;
        }
        return false;
    } else throw std::out_of_range("Empty queue");
}
/**
 * Operatore di assegnamento.
 * <p>
 * @param q la coda da copiare.
 * @return la coda che è stata copiata.
 */
template<class T>
QueueVector<T> &QueueVector<T>::operator=(const QueueVector<T> &q) {
    if (this != &q) {
        delete[] elements;
        length = q.length;
        head = q.head;
        tail = q.tail;
        elements = new typeElem[length];
        for (int i = head; i < tail; i++) {
            elements[(head+i)%length] = q.elements[(head+i)%length];
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
bool QueueVector<T>::operator==(const QueueVector<T> &q) const {
    if (tail != q.tail) return false;
    for (int i=0; i<tail; i++) {
        if (elements[i] != q.elements[i]) return false;
    }
    return true;
}
/**
 * Operatore di stream.
 * <p>
 * @param os lo stream di output.
 * @param q la coda da stampare.
 * @return lo stream di output.
 */
template<class T>
std::ostream& operator<<(std::ostream& os, const QueueVector<T>& q) {
    os << "[";
    for (int i = q.head; i < q.tail; i++) {
        os << q.elements[(q.head+i)%q.length];
        if (i != q.tail-1) os << ",";
    }
    os << "]";
    return os;
}
/**
 * Cambia la dimensione dell'array.
 * <p>
 * @param arr l'array da ridimensionare.
 * @param oldDim la vecchia dimensione.
 * @param newDim la nuova dimensione.
 * @return il nuovo array ridimensionato.
 */
template<class T>
void QueueVector<T>::changeDimension(T*& arr, int oldDim, int newDim) {
    T* tmp = new T[newDim];
    int number = (oldDim < newDim) ? oldDim : newDim;
    for (int i = 0; i < number; i++) {
        tmp[i] = arr[(head + i) % length];
    }
    delete[] arr;
    arr = tmp;
    head = 0;
}

#endif //QUEUE_QUEUEVECTOR_H