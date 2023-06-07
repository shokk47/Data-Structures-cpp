#ifndef LIST_VECTORLIST_H
#define LIST_VECTORLIST_H

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Linearlist.h"
using namespace std;

template <class T>
class VectorList : public LinearList<T, int> {
   public:
    typedef typename LinearList<T, int>::tipoelem tipoelem;
    typedef typename LinearList<T, int>::posizione posizione;

    //costruttore vuoto
    VectorList();
    //costruttore con dimensione elementi
    VectorList(int);
    //costruttore di copia
    VectorList(const VectorList<T>&);
    //distruttore
    ~VectorList();

    //operatori della lista
    void creaLista();
    bool listaVuota() const;
    tipoelem leggiLista(posizione) const;
    void scriviLista(const tipoelem&, posizione);
    posizione primoLista() const;
    bool fineLista(posizione) const;
    posizione succLista(posizione) const;
    posizione precLista(posizione) const;
    void insLista(const tipoelem&, posizione&);
    void cancLista(posizione&);

    //Sovrascrivo operatori

    VectorList<T>& operator=(const VectorList<T>&);
    bool operator==(const VectorList<T>&);

    //FUNZIONI ACCESSORIE
    void inserisciTesta(const tipoelem&);
    void inserisciCoda(const tipoelem&);
    void rimuoviTesta();
    void rimuoviCoda();
    posizione ultimoLista() const;
    int lunghezza() const;
    void scambiaElementi(posizione, posizione);

   private:
    int lunghezzaArray;  //lunghezza array che contiene la lista
    int lunghezzaLista;  //lunghezza lista
    tipoelem* elementi;  //array che contiene la lista
    void cambiaDimensione(tipoelem*&, int, int);
};

/*
 * Restituisce il numero di elementi della
 */
template <class T>
int VectorList<T>::lunghezza() const {
    return lunghezzaLista;
}

/*
 * Restituisce l'ultimo elemento della lista
 */
template <class T>
typename VectorList<T>::posizione VectorList<T>::ultimoLista() const {
    return lunghezzaLista;
}

/*
 * CREAZIONE DELLA LISTA
 * POST CONDIZIONE: Lista vuota
 */
template <class T>
VectorList<T>::VectorList() {
    this->lunghezzaArray = 10;  //lunghezza array arbitraria
    this->creaLista();
}

/*
 * CREAZIONE DELLA LISTA
 * POST CONDIZIONE: Lista vuota
 */
template <class T>
VectorList<T>::VectorList(int dim) {
    this->lunghezzaArray = dim;  //lunghezza definita dall'utente
    this->creaLista();
}

//costruttore di copia
template <class T>
VectorList<T>::VectorList(const VectorList<T>& L) {
    this->lunghezzaLista = L.lunghezzaLista;
    this->lunghezzaArray = L.lunghezzaArray;
    this->elementi = new tipoelem[lunghezzaArray];
    for (int i = 0; i < lunghezzaLista; i++) {
        this->elementi[i] = L.elementi[i];
    }
}

//Distruttore
template <class T>
VectorList<T>::~VectorList() {
    delete[] elementi;
}

//operatori

template <class T>
void VectorList<T>::creaLista() {
    this->lunghezzaLista = 0;
    elementi = new tipoelem[lunghezzaArray];
}

/*
 * Verifica se una lista è vuota
 * POST CONDIZIONE: Return TRUE se lista vuota, FALSE altrimenti
 */
template <class T>
bool VectorList<T>::listaVuota() const {
    return (lunghezzaLista == 0);
}

/*
 * Legge l'elemento in posizione p della lista
* PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return a=a(i)
 */
template <class T>
typename VectorList<T>::tipoelem VectorList<T>::leggiLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista) {
        return elementi[p - 1];
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Scrive l'elemento in posizione p della lista
* PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),a,(ai+1),...,an>
 */
template <class T>
void VectorList<T>::scriviLista(const tipoelem& e, posizione p) {
    if (p >= 1 && p <= lunghezzaLista) {
        elementi[p - 1] = e;
    } else
        throw std::out_of_range("POSIZIONE NON ESISTENTE");
}

/*
 * Restituisce la posizione del primo elemento della lista
 * POST CONDIZIONE: Return della posizione del primo elemento della lista
 */
template <class T>
typename VectorList<T>::posizione VectorList<T>::primoLista() const {
    return 1;
}

/*
 * Verifica se la lista è terminata
  * PRE CONDIZIONE: p=pos(i), 1<=i<=n+1 , n numero di elementi della lista
 * POST CONDIZIONE: return true se p=pos(n+1), false altrimenti
 */
template <class T>
bool VectorList<T>::fineLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista + 1) {
        return (p == lunghezzaLista + 1);
    } else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}

/*
 * Restituisce la posizione successiva a p nella lista
 * PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return di pos(i+1)
 */
template <class T>
typename VectorList<T>::posizione VectorList<T>::succLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista) {
        return p + 1;
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Restituisce la posizione precedente a p nella lista
 * PRE CONDIZIONE: p=pos(i), 2<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: return di pos(i-1)
 */
template <class T>
typename VectorList<T>::posizione VectorList<T>::precLista(posizione p) const {
    if (p >= 2 && p <= lunghezzaLista)  //precondizione -> p=pos(i) con 2<=i<=n
    {
        return p - 1;
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Inserire l'elemento in posizione p della lista
* PRE CONDIZIONE: p=pos(i), 1<=i<=n+1 , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),a,a(i),(ai+1),...,an> se 1<=i<=n, l=<a1,...,an,a> altrimenti
 */
template <class T>
void VectorList<T>::insLista(const tipoelem& e, posizione& p) {
    if (p >= 1 && p <= lunghezzaLista + 1) {
        if (lunghezzaLista == lunghezzaArray) {
            cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
            lunghezzaArray *= 2;
        }
        for (int i = lunghezzaLista; i >= p; i--) {
            elementi[i] = elementi[i - 1];
        }
        elementi[p - 1] = e;
        lunghezzaLista++;
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
 * Cancellare l'elemento in posizione p della lista
* PRE CONDIZIONE: p=pos(i), 1<=i<=n , n numero di elementi della lista
 * POST CONDIZIONE: l=<a1,...,a(i-1),(ai+1),...,an>
 */
template <class T>
void VectorList<T>::cancLista(posizione& p) {
    if (p >= 1 && p <= lunghezzaLista) {
        if (!listaVuota()) {
            for (int i = p - 1; i < lunghezzaLista - 1; i++) {
                elementi[i] = elementi[i + 1];
            }
            lunghezzaLista--;
        }
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}

template <class T>
void VectorList<T>::cambiaDimensione(tipoelem*& elementi, int vecchiaDimensione,
                                     int nuovaDimensione) {
    int numero;
    (vecchiaDimensione < nuovaDimensione) ? numero = vecchiaDimensione
                                          : numero = nuovaDimensione;
    tipoelem* tmp = new tipoelem[nuovaDimensione];
    for (int i = 0; i < numero; i++) {
        tmp[i] = this->elementi[i];
    }
    delete[] elementi;
    elementi = tmp;
}

//Inserisce in prima posizione
template <class T>
void VectorList<T>::inserisciTesta(const VectorList::tipoelem& e) {
    posizione p = primoLista();
    insLista(e, p);
}

//Inserisce in ultima posizione
template <class T>
void VectorList<T>::inserisciCoda(const VectorList::tipoelem& e) {
    posizione p = lunghezzaLista + 1;
    insLista(e, p);
}

//Rimuove dalla prima posizione
template <class T>
void VectorList<T>::rimuoviTesta() {
    posizione p = 1;
    cancLista(p);
}

//Rimuove dall'ultima posizione
template <class T>
void VectorList<T>::rimuoviCoda() {
    cancLista(lunghezzaLista);
}

template <class T>
bool VectorList<T>::operator==(const VectorList<T>& L) {
    if (this->lunghezzaLista != L.lunghezzaLista) {
        return false;
    } else {
        for (int i = 0; i < lunghezzaLista; i++) {
            if (!(this->elementi[i] != L.elementi[i]))
                return false;
        }
        return true;
    }
}

template <class T>
VectorList<T>& VectorList<T>::operator=(const VectorList<T>& L) {
    if (this != &L) {
        this->lunghezzaLista = L.lunghezzaLista;
        this->lunghezzaArray = L.lunghezzaArray;
        delete[] elementi;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = 0; i < lunghezzaLista; i++) {
            elementi[i] = L.elementi[i];
        }
    }
    return *this;
}

//scambia gli elementi in posizione p1 e p2
template <class T>
void VectorList<T>::scambiaElementi(posizione p1, posizione p2) {
    if ((p1 >= 1 && p1 <= lunghezzaLista) &&
        (p2 >= 1 && p2 <= lunghezzaLista)) {
        tipoelem tmp = elementi[p1 - 1];
        elementi[p1 - 1] = elementi[p2 - 1];
        elementi[p2 - 1] = tmp;
    }
}

#endif  //LIST_VECTORLIST_H
