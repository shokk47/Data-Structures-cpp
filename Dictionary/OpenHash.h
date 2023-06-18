#ifndef DICTIONARY_OPENHASH_H
#define DICTIONARY_OPENHASH_H

#include "Dictionary.h"
#include "Hash.h"
#include "../List/VectorList.h"
#include <stdexcept>

/**
 * @brief Classe che rappresenta un dizionario implementato con hash aperto.
 * La struttura è composta da un certo numero (maxBuckets) di contenitori di uguale
 * dimensione denominati bucket. Ognuno di questi contenitori può mantenere al
 * proprio interno al massimo una coppia < K, E >.
 * <br>
 * Si utilizza un funzione aritmetica allo scopo di calcolare, partendo
 * dalla chiave, la posizione in tabella delle informazioni contenute nella coppia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template <class K, class E>
class OpenHash : public Dictionary<K,E> {
public:
    typedef typename Dictionary<K,E>::Key Key;
    typedef typename Dictionary<K,E>::Element Element;

    OpenHash();
    OpenHash(int);
    OpenHash(const OpenHash&);
    ~OpenHash();

    bool isEmpty() const;
    void insert(Couple<Key,Element>&);
    void remove(const Key&);
    Element get(const Key&) const;
    bool containsKey(const Key&) const;
    void update(const Key&, const Element&);

    void clear();
    int getSize() const {return bucketsUsed;}
    VectorList<K> keys() const;
    VectorList<E> values() const;

    OpenHash<K,E>& operator=(const OpenHash<K,E>&);
    bool operator==(const OpenHash<K,E>&) const;
    bool operator!=(const OpenHash<K,E>&) const;

    template<class K1, class E1>
    friend std::ostream& operator<<(std::ostream&, const OpenHash<K1,E1>&);

private:
    int calcPosition(const Key&) const;
    VectorList<Couple<Key,Element>>* table;
    int numElementi;        // numeri Elementi
    int divisore;         // divisore
    Hash<Key> hash;
};

template<class K, class E>
OpenHash<K,E>::OpenHash() {
    numElementi = 0;
    divisore = 20;
    table = new VectorList<Couple<Key,Element>>[divisore];
}
template<class K, class E>
OpenHash<K,E>::OpenHash(int n) {
    numElementi = 0;
    divisore = n;
    table = new VectorList<Couple<Key,Element>>[divisore];
}
template<class K, class E>
OpenHash<K,E>::OpenHash(const OpenHash& o) {
    numElementi = o.numElementi;
    divisore = o.divisore;
    table = new VectorList<Couple<Key,Element>>[divisore];
    for(int i = 0; i < divisore; i++)
        table[i] = o.table[i];
}
template<class K, class E>
OpenHash<K,E>::~OpenHash() {
    delete[] table;
}
template<class K, class E>
bool OpenHash<K,E>::isEmpty() const {
    return numElementi == 0;
}
template<class K, class E>
void OpenHash<K,E>::insert(Couple<Key,Element>& couple) {
    int position = calcPosition(couple.getKey());

    if (containsKey(couple.getKey())) {
        throw std::invalid_argument("Chiave già presente");
    } else {
        // Se non è presente una coppia identica nella lista in posizione "position",
        // inserisco la coppia in fondo alla lista.
        if (!table[position].ricercaElemento(couple)) {
            table[position].inserisciCoda(couple);
            numElementi++;
        }
    }
}
template <class K, class E>
void OpenHash<K,E>::remove(const Key& k) {
    if (!isEmpty() && containsKey(k)) {
        int i = hash(k) % divisore;
        posizione p = table[i].primoLista();
        while (table[i].leggiLista())
    }

}



template<class K, class E>
int OpenHash<K,E>::calcPosition(const Key& k) const {
    int pos = (int) hash(k) % divisore;
    return pos;
}

#endif //DICTIONARY_OPENHASH_H
