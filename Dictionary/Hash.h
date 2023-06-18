#ifndef DICTIONARY_HASH_H
#define DICTIONARY_HASH_H

#include <string>
using std::string;

/**
 * @brief Classe che implementa una funzione di hash generica.
 * La funzione hash è definita come un operatore di chiamata ().
 * Prende un valore "key" e restituisce un valore "size_t" che rappresenta
 * il valore hash calcolato per la chiave.
 * <br>
 * Questa definizione può essere utilizzata come base per una funzione di hash
 * specializzata per un particolare tipo di dato.
 * @tparam T
 */
template <class T>
class Hash {
public:
    size_t operator()(const T key) const {
        return size_t(key);
    }
};
/**
 * @brief Classe che implementa una specializzazione parziale del template Hash per il tipo string.
 */
template<>
class Hash<string> {
public:
    /**
     * @brief Funzione hash per il tipo string.
     * La funzione hash è definita come un operatore di chiamata ().
     * Prende una stringa "key" e restituisce un valore "size_t" che rappresenta
     * il valore hash calcolato per la stringa.
     * <br>
     * All'interno della funzione hash, viene utilizzato l'algoritmo di hashing denominato
     * "polynomial rolling hash". Viene calcolato un valore hash per la stringa iterando
     * attraverso tutto i suoi caratteri. Il valore di hash viene calcolato moltiplicando
     * il valore hash precedente per 5 e aggiungendo il valore ASCII del carattere corrente
     * utilizzando la funzione key.at(i).
     * <br>
     * Infine, il valore hash calcolato viene convertito in size_t e restituito.
     * @param key
     * @return
     */
    size_t operator()(const string key) const {
        unsigned long hashValue = 0;
        int length = (int) key.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + key.at(i);
        return size_t(hashValue);
    }
};

#endif //DICTIONARY_HASH_H
