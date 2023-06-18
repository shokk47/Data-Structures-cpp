#ifndef QUEUE_QUEUEVECTOR_H
#define QUEUE_QUEUEVECTOR_H

#include <iostream>
#include <stdexcept>

/**
 *  @brief Classe che rappresenta una coda implementata con un vettore.
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
class QueueVector {

public:
    typedef T typeElem;
    QueueVector();
    QueueVector(int);
    QueueVector(const QueueVector<T>&);
    ~QueueVector();

    // Metodi di servizio:
    bool codaVuota() const;         // restituisce true se la coda è vuota, false altrimenti
    typeElem leggiCoda() const;     // restituisce l'elemento in testa alla coda
    void fuoriCoda();               // elimina l'elemento in testa alla coda
    void incoda(const typeElem&);   // inserisce un elemento in coda

    // Overload operatori:
    QueueVector<T>& operator=(const QueueVector<T>&);
    bool operator==(const QueueVector<T>&) const;
    bool operator!=(const QueueVector<T>&) const;

    template<class T1>
    friend std::ostream &operator<<(std::ostream&, const QueueVector<T1>&);

    // Metodi aggiuntivi:
    int lunghezza() const { return tailIndex; }
    bool ricercaElemento(const typeElem&) const;
    void clear();

private:
    int headIndex;      // indice della testa
    int tailIndex;      // dimensione effettiva utilizzata
    int maxLength;      // dimensione massima dell'array
    typeElem *elements; // array in cui memorizzare gli elementi
    void changeDimension(typeElem *&, int, int);
};

/**
 * @brief Costruttore di default che crea una coda vuota di 10 elementi.
 * @tparam T tipo di dato.
 */
template<class T>
QueueVector<T>::QueueVector() {
    maxLength = 10;
    elements = new typeElem[maxLength];
    headIndex = tailIndex = 0;
}
/**
 * @brief Costruttore che crea una coda vuota di n elementi.
 * @tparam T tipo di dato.
 * @param n numero di elementi.
 */
template<class T>
QueueVector<T>::QueueVector(int n) {
    maxLength = n;
    elements = new typeElem[maxLength];
    headIndex = tailIndex = 0;
}
/**
 * @brief Costruttore di copia.
 * @tparam T tipo di dato.
 * @param q la coda da copiare.
 */
template<class T>
QueueVector<T>::QueueVector(const QueueVector<T> &q) {
    maxLength = q.maxLength;
    headIndex = q.headIndex;
    tailIndex = q.tailIndex;
    elements = new typeElem[maxLength];
    for (int i = headIndex; i != (headIndex+tailIndex)%maxLength; i++) {
        elements[i] = q.elements[i];
    }
}
/**
 * @brief Distruttore.
 * @tparam T tipo di dato.
 */
template<class T>
QueueVector<T>::~QueueVector() {
    delete[] elements;
}
/**
 * @brief Restituisce true se la coda è vuota, false altrimenti.
 * @tparam T tipo di dato.
 */
template<class T>
bool QueueVector<T>::codaVuota() const {
    return tailIndex == 0;
}
/**
 * @brief Restituisce l'elemento in testa alla coda senza rimuoverlo.
 * @tparam T tipo di dato.
 */
template<class T>
typename QueueVector<T>::typeElem QueueVector<T>::leggiCoda() const {
    if (!codaVuota()) return elements[headIndex];
    else throw std::out_of_range("Empty queue");
}
/**
 * @brief Rimuove l'elemento in testa alla coda.
 * @tparam T tipo di dato.
 */
template<class T>
void QueueVector<T>::fuoriCoda() {
    if (!codaVuota()) {
        headIndex = (headIndex+1)%maxLength;
        tailIndex--;
    } else throw std::out_of_range("Empty queue");
}
/**
 * @brief Aggiunge un elemento in fondo alla coda.
 * @tparam T tipo di dato.
 */
template<class T>
void QueueVector<T>::incoda(const typeElem &el) {
    if (tailIndex == maxLength) {
        changeDimension(elements, maxLength, maxLength*2);
        maxLength *= 2;
    }
    elements[(headIndex+tailIndex)%maxLength] = el;
    tailIndex++;
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T tipo di dato.
 * @param q la coda da assegnare.
 * @return la coda assegnata.
 */
template<class T>
QueueVector<T> &QueueVector<T>::operator=(const QueueVector<T> &q) {
    if (this != &q) {
        this->~QueueVector();
        maxLength = q.maxLength;
        headIndex = q.headIndex;
        tailIndex = q.tailIndex;
        elements = new typeElem[maxLength];
        for (int i = headIndex; i != (headIndex+tailIndex)%maxLength; i++) {
            elements[i] = q.elements[i];
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
template<class T>
bool QueueVector<T>::operator==(const QueueVector<T> &q) const {
    if (tailIndex != q.tailIndex) return false;
    for (int i=headIndex; i<tailIndex; i++) {
        if (elements[i] != q.elements[i]) return false;
    }
    return true;
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T tipo di dato.
 * @param q la coda da confrontare.
 * @return true se le code sono diverse, false altrimenti.
 */
template <class T>
bool QueueVector<T>::operator!=(const QueueVector<T> &q) const {
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
template<class T>
std::ostream& operator<<(std::ostream& os, const QueueVector<T>& q) {
    os << "[";
    if (q.tailIndex > 0) {
        os << q.elements[q.headIndex % q.maxLength];
        for (int i = (q.headIndex + 1) % q.maxLength;
             i != (q.headIndex + q.tailIndex) % q.maxLength;
             i = (i + 1) % q.maxLength) {
            os << "," << q.elements[i];
        }
    }
    os << "]" << endl;
    return os;
}
/**
 * @brief Verifica se un elemento è presente nella coda.
 * @tparam T tipo di dato.
 * @param el l'elemento da cercare.
 * @return true se l'elemento è presente, false altrimenti.
 */
template <class T>
bool QueueVector<T>::ricercaElemento(const typeElem &el) const {
    if (codaVuota()) return false;
    for (int i = headIndex; i < tailIndex; i++) {
        if (elements[(headIndex+i)%maxLength] == el) return true;
    }
}
/**
 * @brief Svuota la coda.
 * @tparam T tipo di dato.
 */
template <class T>
void QueueVector<T>::clear() {
    delete[] elements;
    elements = new typeElem[maxLength];
    headIndex = tailIndex = 0;
}
/**
 * @brief Cambia la dimensione dell'array.
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
        tmp[i] = arr[(headIndex + i) % maxLength];
    }
    delete[] arr;
    arr = tmp;
    headIndex = 0;
}

#endif //QUEUE_QUEUEVECTOR_H