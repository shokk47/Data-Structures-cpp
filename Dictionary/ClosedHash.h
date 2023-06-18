#ifndef DICTIONARY_CLOSEDHASH_H
#define DICTIONARY_CLOSEDHASH_H

#include "Dictionary.h"
#include "Hash.h"
#include <stdexcept>

/**
 * @brief Classe che rappresenta un dizionario implementato con hash chiuso.
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
class ClosedHash : public Dictionary<K,E> {
public:
    typedef typename Dictionary<K,E>::Key Key;
    typedef typename Dictionary<K,E>::Element Element;

    ClosedHash();
    ClosedHash(int);
    ClosedHash(const ClosedHash&);
    ~ClosedHash();

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

    ClosedHash<K,E>& operator=(const ClosedHash<K,E>&);
    bool operator==(const ClosedHash<K,E>&) const;
    bool operator!=(const ClosedHash<K,E>&) const;

    template<class K1, class E1>
    friend std::ostream& operator<<(std::ostream&, const ClosedHash<K1,E1>&);

private:
    void changeMaxBuckets(int);
    int calcPosition(const Key&) const;
    Couple <K,E>** buckets;
    int bucketsUsed;        // numeri Elementi
    int maxBuckets;         // divisore
    Hash<K> hash;
};
/**
 * @brief Costruttore di default che inizializza un dizionario con 20 bucket.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template<class K, class E>
ClosedHash<K,E>::ClosedHash() {
    maxBuckets = 20;
    bucketsUsed = 0;
    buckets = new Couple<K,E>*[maxBuckets];
    for(int i = 0; i < maxBuckets; i++)
        buckets[i] = nullptr;
}
/**
 * @brief Costruttore che inizializza un dizionario con un numero di bucket pari a maxBuckets.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param maxBuckets numero di bucket.
 */
template<class K, class E>
ClosedHash<K,E>::ClosedHash(int maxBuckets) {
    this->maxBuckets = maxBuckets;
    bucketsUsed = 0;
    buckets = new Couple<K,E>*[maxBuckets];
    for(int i = 0; i < maxBuckets; i++)
        buckets[i] = nullptr;
}
/**
 * @brief Costruttore di copia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param h dizionario da copiare.
 */
template<class K, class E>
ClosedHash<K,E>::ClosedHash(const ClosedHash& h) {
    maxBuckets = h.maxBuckets;
    bucketsUsed = h.bucketsUsed;
    buckets = new Couple<K,E>*[maxBuckets];
    for(int i = 0; i < maxBuckets; i++) {
        if (h.buckets[i] == nullptr) {
            buckets[i] = nullptr;
        }
        else {
            Couple<K,E> couple(h.buckets[i]->getKey(), h.buckets[i]->getElement());
            buckets[i] = new Couple<Key, Element>(couple);
        }
    }
}
/**
 * @brief Distruttore.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template<class K, class E>
ClosedHash<K,E>::~ClosedHash() {
    for(int i = 0; i < maxBuckets; i++) {
        delete buckets[i];
    }
    delete[] buckets;
}
/**
 * @brief Metodo che controlla se il dizionario è vuoto.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @return true se il dizionario è vuoto, false altrimenti.
 */
template<class K, class E>
bool ClosedHash<K,E>::isEmpty() const {
    return bucketsUsed == 0;
}
/**
 * @brief Metodo che inserisce una coppia < K, E > nel dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave.
 * @param element elemento.
 */
template<class K, class E>
void ClosedHash<K,E>::insert(Couple<Key,Element>& couple) {
    // Se il numero di bucket occupati è maggiore o uguale al 75% del numero di bucket
    if ((double)bucketsUsed >= (double)maxBuckets * 0.75) {
        changeMaxBuckets(maxBuckets * 2);
        maxBuckets *= 2;
    }
    // Individua l'indice del bucket in cui inserire la coppia
    int i = calcPosition(couple.getKey());
    int j = i;
    bool inserted = false;
    do {
        if (buckets[j] == nullptr) {
            // Se il bucket è vuoto inserisce la coppia
            buckets[j] = new Couple<K, E>(couple);
            bucketsUsed++;
            inserted = true;
        } else if (buckets[j]->getKey() == couple.getKey()) {
            throw std::runtime_error("Error: esiste gia' una coppia con la stessa chiave");
        }
        j = (j + 1) % maxBuckets;  // Probing lineare
    } while (j != i && !inserted);

    if (!inserted) {
        throw std::runtime_error("Error: impossibile inserire la coppia");
    }
}
/**
 * @brief Metodo che rimuove una coppia < K, E > dal dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave.
 */
template<class K, class E>
void ClosedHash<K,E>::remove(const Key& key) {
    if (!isEmpty()) {
        if (containsKey(key)) {
            int i = hash(key) % maxBuckets;
            int j = i;
            bool removed = false;
            do {
                if (buckets[j] != nullptr && buckets[j]->getKey() == key) {
                    delete buckets[j];
                    buckets[j] = nullptr;
                    bucketsUsed--;
                    removed = true;
                }
                j = (j + 1) % maxBuckets;
            } while (j != i && !removed);
        } else {
            throw std::out_of_range("Error: la chiave non e' presente.");
        }
    } else {
        throw std::out_of_range("Il dizionario è vuoto.");
    }
}
/**
 * @brief Metodo che restituisce l'elemento associato alla chiave key.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave.
 * @return elemento associato alla chiave key.
 */
template<class K, class E>
typename ClosedHash<K,E>::Element ClosedHash<K,E>::get(const ClosedHash::Key& key) const {
    if (!isEmpty()) {
        if (containsKey(key)) {
            int i = hash(key) % maxBuckets;
            int j = i;
            do {
                if (buckets[j] != nullptr && buckets[j]->getKey() == key)
                    return buckets[j]->getElement();
                j = (j + 1) % maxBuckets;
            } while (j != i);
        } else {
            throw std::out_of_range("Error: la chiave non e' presente.");
        }
    } else {
        throw std::out_of_range("Il dizionario è vuoto.");
    }
}
/**
 * @brief Metodo che verifica se il dizionario contiene una coppia con chiave key.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave.
 * @return true se il dizionario contiene una coppia con chiave key, false altrimenti.
 */
template<class K, class E>
bool ClosedHash<K,E>::containsKey(const Key& key) const {
    int i = hash(key) % maxBuckets;
    int j = i;
    do {
        if (buckets[j] != nullptr && buckets[j]->getKey() == key)
            return true;
        j = (j + 1) % maxBuckets;
    } while (j != i);
    return false;
}
/**
 * @brief Metodo che aggiorna il valore associato a una chiave esistente.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave.
 * @param element nuovo elemento.
 */
template<class K, class E>
void ClosedHash<K,E>::update(const Key& key, const Element& element) {
    if (!isEmpty()) {
        if (containsKey(key)) {
            int i = hash(key) % maxBuckets;
            int j = i;
            do {
                if (buckets[j] != nullptr && buckets[j]->getKey() == key)
                    buckets[j]->setElement(element);
                j = (j + 1) % maxBuckets;
            } while (j != i);
        } else {
            throw std::out_of_range("Error: la chiave non e' presente.");
        }
    } else {
        throw std::out_of_range("Il dizionario è vuoto.");
    }
}
/**
 * @brief Metodo che resetta il dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template<class K, class E>
void ClosedHash<K,E>::clear() {
    for (int i = 0; i < maxBuckets; i++) {
        delete buckets[i];
        buckets[i] = nullptr;
    }
    bucketsUsed = 0;
}
/**
 * @brief Metodo che restituisce una lista contenente tutte le chiavi del dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @return lista contenente tutte le chiavi del dizionario.
 */
template <class K, class E>
VectorList<K> ClosedHash<K,E>::keys() const {
    VectorList<K> keys;
    for (int i = 0; i < maxBuckets; i++) {
        if (buckets[i] != nullptr)
            keys.inserisciCoda(buckets[i]->getKey());
    }
    return keys;
}
/**
 * @brief Metodo che restituisce una lista contenente tutti gli elementi del dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @return lista contenente tutti gli elementi del dizionario.
 */
template <class K, class E>
VectorList<E> ClosedHash<K,E>::values() const {
    VectorList<E> values;
    for (int i = 0; i < maxBuckets; i++) {
        if (buckets[i] != nullptr)
            values.inserisciCoda(buckets[i]->getElement());
    }
    return values;
}
/**
 * @brief Operatore di assegnamento.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param mp dizionario da assegnare.
 * @return true se i dizionari sono uguali, false altrimenti.
 */
template<class K, class E>
ClosedHash<K,E> &ClosedHash<K,E>::operator=(const ClosedHash<K,E> &mp) {
    if (this != &mp) {
        clear();
        maxBuckets = mp.maxBuckets;
        bucketsUsed = mp.bucketsUsed;
        buckets = new Couple<Key,Element>* [maxBuckets];
        for (int i = 0; i < maxBuckets; i++) {
            if (mp.buckets[i] != nullptr)
                buckets[i] = new Couple<Key, Element>(mp.buckets[i]->getKey(), mp.buckets[i]->getElement());
            else
                buckets[i] = nullptr;
        }
    }
    return *this;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param mp dizionario da confrontare.
 * @return true se i dizionari sono uguali, false altrimenti.
 */
template <class K, class E>
bool ClosedHash<K,E>::operator==(const ClosedHash<K,E>& mp) const {
    if (this->getSize() != mp.getSize())
        return false;
    else {
        for (int i = 0; i < maxBuckets; i++) {
            if (buckets[i] != nullptr && !mp.containsKey(buckets[i]->getKey()))
                return false;
        }
        return true;
    }
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param mp dizionario da confrontare.
 * @return true se i dizionari sono diversi, false altrimenti.
 */
 template <class K, class E>
bool ClosedHash<K,E>::operator!=(const ClosedHash<K,E>& mp) const {
    return !(*this == mp);
}
/**
 * @brief Operatore di stream.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param os stream di output.
 * @param mp dizionario da stampare.
 * @return stream di output.
 */
template <class K, class E>
ostream& operator<<(ostream& os, const ClosedHash<K,E>& mp) {
    os << "{";
    for (int i = 0; i < mp.maxBuckets; i++) {
        if (mp.buckets[i] != nullptr) {
            os << mp.buckets[i]->getKey() << ": " << mp.buckets[i]->getElement();
            if (i != mp.maxBuckets - 1)
                os << ", ";
        }
    }
    os << "}";
    return os;
}
/**
 * @brief Metodo che modifica la dimensione del dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param newDim nuova dimensione del dizionario.
 */
template <class K, class E>
void ClosedHash<K,E>::changeMaxBuckets(int newDim) {
    if (newDim <= maxBuckets)
        throw std::invalid_argument("Error: La nuova dimensione deve essere maggiore di quella attuale.");

    Couple<K, E>** newBuckets = new Couple<K, E>*[newDim];
    for (int i = 0; i < newDim; i++)
        newBuckets[i] = nullptr;

    for (int i = 0; i < maxBuckets; i++) {
        if (buckets[i] != nullptr) {
            int j = calcPosition(buckets[i]->getKey());
            int k = j;
            while (newBuckets[k] != nullptr)
                k = (k + 1) % newDim;

            newBuckets[k] = new Couple<K, E>(*buckets[i]);
            delete buckets[i];
        }
    }

    delete[] buckets;
    buckets = newBuckets;
    maxBuckets = newDim;
}
/**
 * @brief Metodo che calcola la posizione di una chiave all'interno del dizionario.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param key chiave da cercare.
 * @return posizione della chiave all'interno del dizionario.
 */
template <class K, class E>
int ClosedHash<K,E>::calcPosition(const Key& key) const {
    int i = static_cast<int>(hash(key) % maxBuckets);
    for (int j = i;; j = (j + 1) % maxBuckets) {
        if (buckets[j] == nullptr || buckets[j]->getKey() == key)
            return j;
        if (j == i)
            break;
    }
    return -1; // Posizione non trovata
}

#endif //DICTIONARY_CLOSEDHASH_H
