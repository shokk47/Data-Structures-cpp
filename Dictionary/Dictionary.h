#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include "Couple.h"
#include "../List/VectorList.h"

/**
 * @brief Interfaccia che rappresenta un dizionario.
 * Un dizionario è una collezione di elementi, ognuno dei quali è identificato da una chiave.
 * Gli elementi assumono la forma di una coppia < K, E >, dove K è la chiave e E è l'elemento.
 * <br>
 * La chiave è unica per ogni elemento e serve per accedere all'elemento.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template <class K, class E>
class Dictionary {
public:
    typedef K Key;
    typedef E Element;

    // virtual void create() = 0; Rimpiazzato dal costruttore

    virtual bool isEmpty() const = 0;                       // dizionarioVuoto()
    virtual void insert(Couple<Key,Element> &) = 0;         // inserisci()
    virtual void remove(const Key&) = 0;                    // cancella()
    virtual Element get(const Key&) const = 0;              // recupera()
    virtual bool containsKey(const Key&) const = 0;         // appartiene()
    virtual void update(const Key&, const Element&) = 0;    // aggiorna Valore associato

    virtual void clear() = 0;                               // svuota()
    virtual int getSize() const = 0;                        // dimensione()
    virtual VectorList<Key> keys() const = 0;               // restituisce un vettore contenente tutte le chiavi
    virtual VectorList<Element> values() const = 0;         // restituisce un vettore contenente tutti gli elementi
};

#endif //DICTIONARY_DICTIONARY_H
