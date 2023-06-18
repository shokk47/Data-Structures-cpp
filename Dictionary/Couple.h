#ifndef DICTIONARY_COUPLE_H
#define DICTIONARY_COUPLE_H

#include <iostream>
#include <ostream>

/**
 * @brief Classe che rappresenta una coppia < K, E >.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 */
template <class K, class E>
class Couple {
public:
    typedef K Key;
    typedef E Element;
    Couple() {}
    Couple(const Couple<K,E>& couple);
    Couple(const K& k, const E& e);
    const K getKey() const;
    const E getElement() const;
    void setKey(const K& k);
    void setElement(const E& e);

    // operatori
    bool operator==(const Couple<K,E>& couple) const;
    Couple<K,E>& operator=(const Couple<K,E>& couple);
    bool operator!=(const Couple<K,E>& couple) const;

    template<class K1, class E1>
    friend std::ostream& operator<<(std::ostream& os, const Couple<K1,E1>& couple);
private:
    K key;
    E element;
};
/**
 * @brief Costruttore copia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param couple coppia da copiare.
 */
template<class K, class E>
Couple<K,E>::Couple(const Couple<K,E>& couple) {
    key = couple.key;
    element = couple.element;
}
/**
 * @brief Costruttore che crea la coppia < K, E >.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param k chiave.
 * @param e elemento.
 */
template<class K, class E>
Couple<K,E>::Couple(const K& k, const E& e) {
    key = k;
    element = e;
}
/**
 * @brief Restituisce la chiave della coppia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @return chiave della coppia.
 */
template<class K, class E>
const K Couple<K,E>::getKey() const {
    return key;
}
/**
 * @brief Restituisce l'elemento della coppia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @return elemento della coppia.
 */
template<class K, class E>
const E Couple<K,E>::getElement() const {
    return element;
}
/**
 * @brief Imposta la chiave della coppia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param k chiave da impostare.
 */
template<class K, class E>
void Couple<K,E>::setKey(const K& k) {
    key = k;
}
/**
 * @brief Imposta l'elemento della coppia.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param e elemento da impostare.
 */
template<class K, class E>
void Couple<K,E>::setElement(const E& e) {
    element = e;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param couple coppia da confrontare.
 * @return true se le coppie sono uguali, false altrimenti.
 */
template<class K, class E>
bool Couple<K,E>::operator==(const Couple<K,E>& couple) const {
    return ((couple.getElement())==this->getElement() && (couple.getKey())==this->getKey());
}
/**
 * @brief Operatore di assegnamento.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param couple coppia da assegnare.
 * @return la coppia assegnata.
 */
template<class K, class E>
Couple<K,E>& Couple<K,E>::operator=(const Couple<K,E>& couple) {
    if (this != &couple) {
        key = couple.key;
        element = couple.element;
    }
    return *this;
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam K tipo della chiave.
 * @tparam E tipo dell'elemento.
 * @param couple coppia da confrontare.
 * @return true se le coppie sono diverse, false altrimenti.
 */
template<class K, class E>
bool Couple<K,E>::operator!=(const Couple<K,E>& couple) const {
    return !(*this == couple);
}
/**
 * @brief Operatore di output.
 * @tparam K1 tipo della chiave.
 * @tparam E1 tipo dell'elemento.
 * @param os stream di output.
 * @param couple coppia da stampare.
 * @return stream di output.
 */
template<class K1, class E1>
std::ostream& operator<<(std::ostream& os, const Couple<K1,E1>& couple) {
    os << "[Key:" << couple.key << ", Element: " << couple.element << "]";
    return os;
}

#endif //DICTIONARY_COUPLE_H
