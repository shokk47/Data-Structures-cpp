#ifndef BINARY_TREES_ALBEROBINARIO_PTR_H
#define BINARY_TREES_ALBEROBINARIO_PTR_H

#include "alberoBinario.h"
#include <stdexcept>

template<class T>
class AlberoBinario_ptr;

template<class T>
class Nodo {
    friend class AlberoBinario_ptr<T>;
private:
    T valore;
    Nodo<T>* padre;
    Nodo<T>* figlioSinistro;
    Nodo<T>* figlioDestro;
};

template<class T>
class AlberoBinario_ptr : public AlberoBinario<T, Nodo<T>*> {
public:
    typedef typename AlberoBinario<T, Nodo<T>*>::tipoElem tipoElem;
    typedef typename AlberoBinario<T, Nodo<T>*>::nodo nodo;

    AlberoBinario_ptr();
    AlberoBinario_ptr(AlberoBinario_ptr<T>&);
    ~AlberoBinario_ptr();

    bool alberoVuoto() const;                               // restituisce true se l'albero è vuoto

    nodo radice() const;                                    // restituisce il nodo radice
    nodo padre(nodo) const;                                 // restituisce il nodo padre del nodo passato
    nodo figlioSinistro(nodo) const;                        // restituisce il nodo figlio sinistro del nodo passato
    nodo figlioDestro(nodo) const;                          // restituisce il nodo figlio destro del nodo passato
    bool sinistroVuoto(nodo) const;                         // restituisce true se il nodo passato ha un figlio sinistro
    bool destroVuoto(nodo) const;                           // restituisce true se il nodo passato ha un figlio destro
    void cancellaSottoAlbero(nodo);                         // cancella il sotto-albero radicato nel nodo passato
    tipoElem leggiNodo(nodo) const;                         // restituisce il valore del nodo passato
    void scriviNodo(nodo, tipoElem);                        // scrive il valore passato nel nodo passato

    void inserisciRadice(tipoElem);                         // inserisce la radice dell'albero
    void inserisciFiglioSinistro(const nodo, tipoElem);     // inserisce un nodo figlio sinistro al nodo passato
    void inserisciFiglioDestro(const nodo, tipoElem);       // inserisce un nodo figlio destro al nodo passato

    void inverti();                                         // Scambia i figli sinistri con i figli destri di ogni nodo
    int ottieniNumeroNodi() { return numeroNodi; }

    bool operator== (const AlberoBinario_ptr<T>&) const;
    bool operator!= (const AlberoBinario_ptr<T>&) const;
    AlberoBinario_ptr<T>& operator= (const AlberoBinario_ptr<T>&);

    void stampaSottoAlbero(nodo) const;
private:
    Nodo<T>* root;                                          // puntatore alla radice dell'albero

    int numeroNodi;
    void stampaRicorsiva(Nodo<T>*, bool, std::string) const;
    Nodo<T>* copiaNodo(Nodo<T>*, Nodo<T>*);                 // restituisce il nodo passato e tutti i suoi discendenti
    void cancellaNodo(Nodo<T>*);                            // cancella il nodo passato e tutti i suoi discendenti
    void cancellaSinistro(Nodo<T>*);                        // cancella il figlio sinistro del nodo passato
    void cancellaDestro(Nodo<T>*);                          // cancella il figlio destro del nodo passato
    void invertiRicorsivo(Nodo<T>*);                        // Scambia i figli sinistri con i figli destri di ogni nodo
    bool confrontaNodi(Nodo<T>*, Nodo<T>*) const;           // restituisce true se i due nodi passati sono uguali
};
/**
 * @brief Costruttore di default.
 * @tparam T il tipo di dato dell'albero binario.
 */
template<class T>
AlberoBinario_ptr<T>::AlberoBinario_ptr() {
    numeroNodi = 0;
    root = nullptr;
}
/**
 * @brief Costruttore di copia.
 * @tparam T il tipo di dato dell'albero binario.
 * @param albero l'albero da copiare.
 */
template<class T>
AlberoBinario_ptr<T>::AlberoBinario_ptr(AlberoBinario_ptr<T>& albero) {
    numeroNodi = 0;
    root = copiaNodo(albero.radice(), nullptr);
}
/**
 * @brief Distruttore.
 * @tparam T il tipo di dato dell'albero binario.
 */
template <class T>
AlberoBinario_ptr<T>::~AlberoBinario_ptr() {
    if (!alberoVuoto())
        cancellaSottoAlbero(radice());
    else {
        root = nullptr;
        delete root;
    }
}
/**
 * @brief Restituisce true se l'albero è vuoto, false altrimenti.
 * @tparam T il tipo di dato dell'albero binario.
 * @return true se l'albero è vuoto, false altrimenti.
 */
template<class T>
bool AlberoBinario_ptr<T>::alberoVuoto() const {
    return (root == nullptr);
}
/**
 * @brief Restituisce il nodo radice dell'albero.
 * @tparam T il tipo di dato dell'albero binario.
 * @return il nodo radice dell'albero.
 */
template<class T>
typename AlberoBinario_ptr<T>::nodo AlberoBinario_ptr<T>::radice() const {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else
        return root;
}
/**
 * @brief Restituisce il nodo padre del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere il padre.
 * @return il nodo padre del nodo passato come parametro.
 */
template<class T>
typename AlberoBinario_ptr<T>::nodo AlberoBinario_ptr<T>::padre(nodo n) const {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == root)
        throw std::runtime_error("Il nodo radice non ha un genitore");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return n->padre;
}
/**
 * @brief Restituisce il nodo figlio sinistro del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere il figlio sinistro.
 * @return il nodo figlio sinistro del nodo passato come parametro.
 */
template<class T>
typename AlberoBinario_ptr<T>::nodo AlberoBinario_ptr<T>::figlioSinistro(nodo n) const {
    if (!sinistroVuoto(n))
        return n->figlioSinistro;
    else
        throw std::runtime_error("Il nodo passato come parametro non ha un figlio sinistro");
}
/**
 * @brief Restituisce il nodo figlio destro del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere il figlio destro.
 * @return il nodo figlio destro del nodo passato come parametro.
 */
template<class T>
typename AlberoBinario_ptr<T>::nodo AlberoBinario_ptr<T>::figlioDestro(nodo n) const {
    if (!destroVuoto(n))
        return n->figlioDestro;
    else
        throw std::runtime_error("Il nodo passato come parametro non ha un figlio destro");
}
/**
 * @brief Verifica se il nodo passato come parametro ha un figlio sinistro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere l'esistenza del figlio sinistro.
 * @return true se il nodo passato come parametro ha un figlio sinistro, false altrimenti.
 */
template<class T>
bool AlberoBinario_ptr<T>::sinistroVuoto(nodo n) const {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return (n->figlioSinistro == nullptr);
}
/**
 * @brief Verifica se il nodo passato come parametro ha un figlio destro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere l'esistenza del figlio destro.
 * @return true se il nodo passato come parametro ha un figlio destro, false altrimenti.
 */
template<class T>
bool AlberoBinario_ptr<T>::destroVuoto(nodo n) const {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return (n->figlioDestro == nullptr);
}
/**
 * @brief Cancello il sotto-albero radicato nel nodo passato come parametro.
 * Cancella il nodo n e tutti i suoi discendenti.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo radice del sotto-albero da cancellare.
 */
template<class T>
void AlberoBinario_ptr<T>::cancellaSottoAlbero(nodo n) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else {
        if (n->padre == nullptr) {
            cancellaNodo(n);
            root = nullptr;
        } else {
            if (n->padre->figlioSinistro == n)
                cancellaSinistro(n->padre);
            else
                cancellaDestro(n->padre);
        }
    }
}
/**
 * @brief Restituisce il valore associato al nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo di cui si vuole conoscere il valore.
 * @return il valore associato al nodo passato come parametro.
 */
template<class T>
typename AlberoBinario_ptr<T>::tipoElem
AlberoBinario_ptr<T>::leggiNodo(nodo n) const {
    return n->valore;
}
/**
 * @brief Assegna il valore passato come parametro al nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo a cui assegnare il valore.
 * @param v il valore da assegnare al nodo.
 */
template<class T>
void AlberoBinario_ptr<T>::scriviNodo(nodo n, tipoElem v) {
    n->valore = v;
}
/**
 * @brief Inserisce un nodo come radice dell'albero binario.
 * @tparam T il tipo di dato dell'albero binario.
 * @param v il valore da assegnare al nodo radice.
 */
template<class T>
void AlberoBinario_ptr<T>::inserisciRadice(tipoElem v) {
    if (!alberoVuoto())
        throw std::runtime_error("L'albero ha già una radice");
    else {
        root = new Nodo<T>;
        root->padre = nullptr;
        root->figlioSinistro = nullptr;
        root->figlioDestro = nullptr;
        root->valore = v;
        numeroNodi++;
    }
}
/**
 * @brief Inserisce un nodo come figlio sinistro del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo a cui aggiungere il figlio sinistro.
 * @param v il valore da assegnare al nodo figlio sinistro.
 */
template<class T>
void AlberoBinario_ptr<T>::inserisciFiglioSinistro(nodo n, tipoElem v) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else if (!sinistroVuoto(n))
        throw std::runtime_error("Il nodo passato come parametro ha già un figlio sinistro");
    else {
        Nodo<T>* nuovoNodo = new Nodo<T>;
        nuovoNodo->valore = v;
        nuovoNodo->padre = n;
        nuovoNodo->figlioSinistro = nullptr;
        nuovoNodo->figlioDestro = nullptr;
        n->figlioSinistro = nuovoNodo;
        numeroNodi++;
    }
}
/**
 * @brief Inserisce un nodo come figlio destro del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo a cui aggiungere il figlio destro.
 * @param v il valore da assegnare al nodo figlio destro.
 */
 template<class T>
void AlberoBinario_ptr<T>::inserisciFiglioDestro(nodo n, tipoElem v) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else if (!destroVuoto(n))
        throw std::runtime_error("Il nodo passato come parametro ha già un figlio destro");
    else {
        Nodo<T> *nuovoNodo = new Nodo<T>;
        nuovoNodo->valore = v;
        nuovoNodo->padre = n;
        nuovoNodo->figlioSinistro = nullptr;
        nuovoNodo->figlioDestro = nullptr;
        n->figlioDestro = nuovoNodo;
        numeroNodi++;
    }
}
/**
 * @brief Inverte l'albero scambiando i figli sinistri con i figli destri.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo radice del sotto-albero da invertire.
 */
template<class T>
void AlberoBinario_ptr<T>::inverti() {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else invertiRicorsivo(radice());
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam T il tipo di dato dell'albero binario.
 * @param t l'albero binario da confrontare con l'albero binario corrente.
 * @return true se i due alberi binari sono uguali, false altrimenti.
 */
template<class T>
bool AlberoBinario_ptr<T>::operator==(const AlberoBinario_ptr<T> &t) const {
    if (alberoVuoto() && t.alberoVuoto())
        return true;
    else if (alberoVuoto() || t.alberoVuoto())
        return false;
    else {
        return confrontaNodi(root, t.root);
    }
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T il tipo di dato dell'albero binario.
 * @param t l'albero binario da confrontare con l'albero binario corrente.
 * @return true se i due alberi binari sono diversi, false altrimenti.
 */
template<class T>
bool AlberoBinario_ptr<T>::operator!=(const AlberoBinario_ptr<T> &t) const {
    return !(*this == t);
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T il tipo di dato dell'albero binario.
 * @param t l'albero binario da copiare.
 * @return l'albero binario corrente dopo la copia.
 */
template<class T>
AlberoBinario_ptr<T> &AlberoBinario_ptr<T>::operator=(const AlberoBinario_ptr<T> &t) {
    if (this != &t) {
        numeroNodi = 0;
        root = copiaNodo(t.root, nullptr);
    }
    return *this;
}
/**
 * @brief Metodo che stampa il sotto-albero radicato nel nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo radice del sotto-albero da stampare.
 */
template<class T>
void AlberoBinario_ptr<T>::stampaSottoAlbero(nodo n) const {
    stampaRicorsiva(n, false, "");
}
/**
 * @brief Stampa in modo ricorsivo l'albero binario.
 * @tparam T il tipo di dato dell'albero binario.
 * @param root il nodo radice del sotto-albero da stampare.
 * @param figlioDestro flag che indica se il nodo da stampare è figlio destro o sinistro.
 * @param spazio la stringa di spazi da stampare prima del nodo.
 */
template<class T>
void AlberoBinario_ptr<T>::stampaRicorsiva(Nodo<T>* root, bool figlioDestro, std::string spazio) const {
    if (root != nullptr) {
        std::cout << spazio;
        if (figlioDestro) {
            std::cout << "-->d:";
            spazio += "    ";
        } else {
            std::cout << "-->s:";
            spazio += "|   ";
        }
        std::cout << "[" << root->valore << "]" << std::endl;
        stampaRicorsiva(root->figlioSinistro, false, spazio);
        stampaRicorsiva(root->figlioDestro, true, spazio);
    }
}
/**
 * @brief Restituisce la copia del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param daCopiare il nodo da copiare.
 * @param padre il padre del nodo da copiare.
 * @return la copia del nodo passato come parametro.
 */
template<class T>
Nodo<T>* AlberoBinario_ptr<T>::copiaNodo(Nodo<T>* daCopiare, Nodo<T>* padre) {
    if (daCopiare == nullptr)
        return nullptr;
    else {
        Nodo<T>* nuovoNodo = new Nodo<T>;
        nuovoNodo->valore = daCopiare->valore;
        nuovoNodo->padre = padre;
        nuovoNodo->figlioSinistro = copiaNodo(daCopiare->figlioSinistro, daCopiare);
        nuovoNodo->figlioDestro = copiaNodo(daCopiare->figlioDestro, daCopiare);
        numeroNodi++;
        return nuovoNodo;
    }
}
/**
 * @brief La funzione cancella il nodo passato come parametro e tutti i suoi discendenti.
 * @tparam T il tipo di dato dell'albero binario.
 * @param daCancellare il nodo da cancellare.
 */
template<class T>
void AlberoBinario_ptr<T>::cancellaNodo(Nodo<T>* daCancellare) {
    if (daCancellare != nullptr) {
        cancellaNodo(daCancellare->figlioSinistro);
        cancellaNodo(daCancellare->figlioDestro);
        delete daCancellare;
        numeroNodi--;
    }
}
/**
 * @brief La funzione cancella il sotto-albero sinistor del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param nd il nodo radice del sotto-albero da cancellare.
 */
template<class T>
void AlberoBinario_ptr<T>::cancellaDestro(Nodo<T> *nd) {
    if (nd != nullptr) {
        cancellaNodo(nd->figlioDestro);
        nd->figlioDestro = nullptr;
    }
}
/**
 * @brief La funzione cancella il sotto-albero destro del nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param nd il nodo radice del sotto-albero da cancellare.
 */
template<class T>
void AlberoBinario_ptr<T>::cancellaSinistro(Nodo<T> *nd) {
    if (nd != nullptr) {
        cancellaNodo(nd->figlioSinistro);
        nd->figlioSinistro = nullptr;
    }
}
/**
 * @brief Inverte l'albero in modo ricorsivo scambiando i figli sinistri con i figli destri.
 * La funzione esegue una visita ricorsiva post-ordine dell'albero e scambia i nodi figlio
 * sinistro e destro per ciascun nodo.
 * @tparam T il tipo di dato dell'albero binario.
 * @param r il nodo radice del sotto-albero da invertire.
 */
template<class T>
void AlberoBinario_ptr<T>::invertiRicorsivo(Nodo<T>* r) {
    if (r->figlioSinistro != nullptr) {
        invertiRicorsivo(r->figlioSinistro);
    }
    if (r->figlioDestro != nullptr) {
        invertiRicorsivo(r->figlioDestro);
    }

    Nodo<T> *tmp = r->figlioSinistro;
    r->figlioSinistro = r->figlioDestro;
    r->figlioDestro = tmp;
}
/**
 * @brief Confronta due nodi di un albero binario e determina se sono uguali.
 * La funzione esegue una visita ricorsiva pre-ordine dell'albero. Comincia confrontando
 * i valori dei due nodi passati come parametro. Se i valori sono uguali, continua il confronto.
 * Se entrambi i nodi hanno un figlio sinistro, continua il confronto ricorsivamente.
 * Se entrambi i nodi hanno un figlio destro, continua il confronto ricorsivamente.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n1 nodo del primo sotto-albero da confrontare.
 * @param n2 nodo del secondo sotto-albero da confrontare.
 * @return true se i due sotto-alberi sono uguali, false altrimenti.
 */
template <class T>
bool AlberoBinario_ptr<T>::confrontaNodi(Nodo<T> *n1, Nodo<T> *n2) const {
    bool uguali = true;
    if (n1->valore == n2->valore) {
        if (n1->figlioSinistro != nullptr && n2->figlioSinistro != nullptr) {
            uguali = confrontaNodi(n1->figlioSinistro, n2->figlioSinistro);
        } else if (n1->figlioSinistro != nullptr || n2->figlioSinistro != nullptr) {
            uguali = false;
        }

        if (uguali && n1->figlioDestro != nullptr && n2->figlioDestro != nullptr) {
            uguali = confrontaNodi(n1->figlioDestro, n2->figlioDestro);
        } else if (n1->figlioDestro != nullptr || n2->figlioDestro != nullptr) {
            uguali = false;
        }
    } else {
        uguali = false;
    }
    return uguali;
}

#endif //BINARY_TREES_ALBEROBINARIO_PTR_H
