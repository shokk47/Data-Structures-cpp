#ifndef LIST_ORDEREDLIST_H
#define LIST_ORDEREDLIST_H

#include <iostream>
#include <ostream>
#include "VectorList.h"

template <class T>
class OrderedList {
   public:
    typedef typename VectorList<T>::tipoelem tipoelem;
    typedef typename VectorList<T>::posizione posizione;

    void insList(const tipoelem&);         // Inserisce un elemento
    void cancLista(const tipoelem&);       // Rimuove un elemento
    bool ricerca(const tipoelem&);         // Cerca un elemento
    void fusione(const OrderedList<T>&);   // Fonde con una lista ordinata
    bool sottoLista(
        const OrderedList<T>& S1,
        const OrderedList<T>& S2);          // Restituisce TRUE se S2 è sottolista di S1, FALSE altrimenti
    void differenza(
        OrderedList<T>& S1,
        const OrderedList<T>& S2);          // Cancella da S1 tutti gli elementi di S2

    // FUNZIONI CLASSICHE DI VECTORLIST
    tipoelem leggiLista(posizione) const;
    posizione primoLista() const;
    posizione ultimoLista() const;
    posizione precLista(posizione) const;
    posizione succLista(posizione) const;
    bool fineLista(posizione) const;

    //Costruttore
    OrderedList();
    //Distruttore
    ~OrderedList();

    //override operatori
    template <class T1>
    friend ostream& operator<<(ostream&, const OrderedList<T1>&);

   private:
    VectorList<T> L;
};

template <class T1>
ostream& operator<<(ostream& os, const OrderedList<T1>& l) {
    os << l.L;
    return os;
}
template <class T>
OrderedList<T>::OrderedList() {}

template <class T>
OrderedList<T>::~OrderedList() {}

template <class T>
void OrderedList<T>::insList(const tipoelem& e) {
    posizione pos = L.primoLista();
    while (!L.fineLista(pos) && L.leggiLista(pos) < e) {
        pos = L.succLista(pos);
    }
    L.insLista(e, pos);
}

template <class T>
bool OrderedList<T>::ricerca(const tipoelem& e) {
    posizione pos = L.primoLista();
    bool trov = false;
    while (!L.fineLista(pos) && !trov) {
        if (L.leggiLista(pos) == e)
            trov = true;
        else
            pos = L.succLista(pos);
    }
    return trov;
}

template <class T>
void OrderedList<T>::cancLista(const tipoelem& e) {
    if (ricerca(e)) {
        posizione p = L.primoLista();
        bool continua = true;
        while (continua) {
            if (e == L.leggiLista(p)) {
                L.cancLista(p);
                continua = false;
            } else
                p = L.succLista(p);
        }
    }
}
template <class T>
void OrderedList<T>::fusione(const OrderedList<T>& l) {
    posizione p = l.L.primoLista();
    while (!l.L.fineLista(p)) {
        this->insList(l.L.leggiLista(p));
        p = l.L.succLista(p);
    }
}

template <class T>
bool OrderedList<T>::sottoLista(const OrderedList<T>& S1,
                                const OrderedList<T>& S2) {
    if (S2.L.lunghezza() > S1.L.lunghezza())
        return false;
    bool isSottolista = true;
    posizione p1 = S1.L.primoLista();
    posizione p2 = S2.L.primoLista();
    while (isSottolista && !S2.L.fineLista(p2) && !S1.L.fineLista(p1)) {
        while (!S2.L.fineLista(p2) && !S1.L.fineLista(p1) &&
               (S2.L.leggiLista(p2) == S1.L.leggiLista(p1))) {
            p1 = S1.L.succLista(p1);
            p2 = S2.L.succLista(p2);
        }
        if (!S1.L.fineLista(p1)) {
            p1 = S1.L.succLista(p1);
        }
        if (!S2.L.fineLista(p2)) {
            p2 = S2.L.primoLista();
        }
    }
    if (!S2.L.fineLista(p2))
        isSottolista = false;
    return isSottolista;
}

template <class T>
void OrderedList<T>::differenza(OrderedList<T>& S1,
                                const OrderedList<T>& S2) {
    posizione p2 = S2.L.primoLista();
    while (!S2.L.fineLista(p2)) {
        T elem = S2.L.leggiLista(p2);
        while (S1.L.ricercaElemento(elem))
            S1.cancLista(elem);
        p2 = S2.L.succLista(p2);
    }
}

template <class T>
typename OrderedList<T>::tipoelem OrderedList<T>::leggiLista(posizione p) const {
    return L.leggiLista(p);
}

template <class T>
typename OrderedList<T>::posizione OrderedList<T>::primoLista() const {
    return L.primoLista();
}
template <class T>
typename OrderedList<T>::posizione OrderedList<T>::ultimoLista() const {
    return L.ultimoLista();
}
template <class T>
typename OrderedList<T>::posizione OrderedList<T>::precLista(posizione p) const {
    return L.precLista(p);
}
template <class T>
typename OrderedList<T>::posizione OrderedList<T>::succLista(posizione p) const {
    return L.succLista(p);
}
template <class T>
bool OrderedList<T>::fineLista(posizione p) const {
    return L.fineLista(p);
}

#endif  //LIST_ORDEREDLIST_H
