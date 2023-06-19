#ifndef N_TREES_ALBERO_PTR_H
#define N_TREES_ALBERO_PTR_H

#include "Albero.h"
#include <stdexcept>
#include <iostream>

template<class T>
class AlberoPtr;

template<class T>
class Nodo {
    friend class AlberoPtr<T>;
    T valore;
    Nodo<T>* padre;
    Nodo<T>* primoFiglio;
    Nodo<T>* fratelloSuccessivo;
};

template<class T>
class AlberoPtr : public Albero<T, Nodo<T> *> {
public:
    typedef typename Albero<T, Nodo<T> *>::tipoElem tipoElem;
    typedef typename Albero<T, Nodo<T> *>::nodo nodo;

    AlberoPtr();
    AlberoPtr(const AlberoPtr<T>&);
    ~AlberoPtr();

    bool alberoVuoto() const;                                   // restituisce true se l'albero è vuoto
    nodo radice() const;                                        // restituisce la radice dell'albero
    nodo padre(nodo) const;                                     // restituisce il padre del nodo passato come parametro
    bool foglia(nodo) const;                                    // restituisce true se il nodo passato come parametro è una foglia
    nodo primoFiglio(nodo) const;                               // restituisce il primo figlio del nodo passato come parametro
    bool ultimoFratello(nodo) const;                            // restituisce true se il nodo passato come parametro è l'ultimo fratello
    nodo fratelloSuccessivo(nodo) const;                        // restituisce il fratello successivo del nodo passato come parametro

    void inserisciRadice(tipoElem);                             // inserisce la radice dell'albero
    void insPrimoFiglio(nodo, tipoElem);                        // inserisce il primo figlio del nodo passato come parametro
    void insFratelloSuccessivo(nodo, tipoElem);                 // inserisce il fratello successivo del nodo passato come parametro
    void insPrimoSottoAlbero(nodo, AlberoPtr<T> &);             // inserisce il primo sotto-albero del nodo passato come parametro
    void insSottoAlbero(nodo, AlberoPtr<T> &);                  // inserisce il sotto-albero del nodo passato come parametro
    void cancellaSottoAlbero(nodo);                             // cancella il sotto-albero del nodo passato come parametro

    int ottieniNumeroNodi() const { return numeroNodi; }
    void scriviNodo(nodo, tipoElem);                            // scrive il valore del nodo passato come parametro
    tipoElem leggiNodo(nodo) const;                             // legge il valore del nodo passato come parametro

    bool operator==(const AlberoPtr<T>&) const;
    bool operator!=(const AlberoPtr<T>&) const;
    AlberoPtr<T>& operator=(const AlberoPtr<T>&);

    void stampaSottoAlbero(nodo) const;
private:
    Nodo<T>* root;
    int numeroNodi;

    void copiaNodo(nodo, nodo);
    void stampaRicorsiva(Nodo<T>*, std::string) const;
    bool confrontaNodi(nodo, nodo) const;
};
/**
 * @brief Costruttore di default dell'albero.
 * @tparam T il tipo di dato dell'albero.
 */
template<class T>
AlberoPtr<T>::AlberoPtr() {
    numeroNodi = 0;
    root = nullptr;
}
/**
 * @brief Costruttore di copia dell'albero.
 * @tparam T il tipo di dato dell'albero.
 * @param a l'albero da copiare.
 */
template<class T>
AlberoPtr<T>::AlberoPtr(const AlberoPtr<T>& a) {
    root = new Nodo<T>;
    numeroNodi = 0;
    scriviNodo(root, a.leggiNodo(a.radice()));
    if (!a.foglia(a.radice()))
        copiaNodo(root, a.primoFiglio(a.radice()));
    numeroNodi++;
}
/**
 * @brief Distruttore dell'albero.
 * @tparam T il tipo di dato dell'albero.
 */
template<class T>
AlberoPtr<T>::~AlberoPtr() {
    if (!alberoVuoto())
        cancellaSottoAlbero(radice());
    else {
        delete root;
        root = nullptr;
    }
}
/**
 * @brief Controlla se l'albero è vuoto.
 * @tparam T il tipo di dato dell'albero.
 * @return true se l'albero è vuoto, false altrimenti.
 */
template<class T>
bool AlberoPtr<T>::alberoVuoto() const{
    return root == nullptr;
}
/**
 * @brief Restituisce la radice dell'albero.
 * @tparam T il tipo di dato dell'albero.
 * @return la radice dell'albero.
 */
template<class T>
typename AlberoPtr<T>::nodo AlberoPtr<T>::radice() const{
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else
        return root;
}
/**
 * @brief Restituisce il padre del nodo n.
 * @details Se n è la radice dell'albero, viene sollevata un'eccezione.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo di cui si vuole conoscere il padre.
 * @return il padre del nodo n.
 */
template<class T>
typename AlberoPtr<T>::nodo AlberoPtr<T>::padre(nodo n) const{
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
 * @brief Verifica se il nodo n è una foglia.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo da verificare.
 * @return true se il nodo n è una foglia, false altrimenti.
 */
template<class T>
bool AlberoPtr<T>::foglia(nodo n) const{
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return n->primoFiglio == nullptr;
}
/**
 * @brief Restituisce il primo figlio del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo di cui si vuole conoscere il primo figlio.
 * @return il primo figlio del nodo n.
 */
template<class T>
typename AlberoPtr<T>::nodo AlberoPtr<T>::primoFiglio(nodo n) const{
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return n->primoFiglio;
}
/**
 * @brief Verifica se il nodo n è l'ultimo fratello del suo genitore.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo da verificare.
 * @return true se il nodo n è l'ultimo fratello del suo genitore, false altrimenti.
 */
template<class T>
bool AlberoPtr<T>::ultimoFratello(nodo n) const{
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else return (n->fratelloSuccessivo == nullptr);
}
/**
 * @brief Restituisce il fratello successivo del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo di cui si vuole conoscere il fratello successivo.
 * @return il fratello successivo del nodo n.
 */
template<class T>
typename AlberoPtr<T>::nodo AlberoPtr<T>::fratelloSuccessivo(nodo n) const{
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else if (n->fratelloSuccessivo == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non ha fratelli successivi");
    else
        return n->fratelloSuccessivo;
}
/**
 * @brief Inserisce la radice dell'albero.
 * @tparam T il tipo di dato dell'albero.
 * @param val il valore da inserire nella radice.
 */
template<class T>
void AlberoPtr<T>::inserisciRadice(tipoElem val) {
    if (!alberoVuoto())
        throw std::runtime_error("L'albero ha gia' una radice");
    else {
        root = new Nodo<T>();
        root->valore = val;
        root->fratelloSuccessivo = nullptr;
        root->padre = nullptr;
        root->primoFiglio = nullptr;
        numeroNodi++;
    }
}
/**
 * @brief Inserisce un nodo come primo figlio del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui aggiungere il primo figlio.
 * @param val il valore da inserire nel nodo primo figlio di n.
 */
template<class T>
void AlberoPtr<T>::insPrimoFiglio(nodo n, tipoElem val) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else {
        nodo nuovoNodo = new Nodo<T>();
        nuovoNodo->fratelloSuccessivo = n->primoFiglio;
        n->primoFiglio = nuovoNodo;
        nuovoNodo->valore = val;
        nuovoNodo->padre = n;
        numeroNodi++;
    }
}
/**
 * @brief Inserisce un nodo come fratello successivo del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui aggiungere il fratello successivo.
 * @param val il valore da inserire nel nodo fratello successivo di n.
 */
template<class T>
void AlberoPtr<T>::insFratelloSuccessivo(nodo n, tipoElem val) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else if (n == root)
        throw std::runtime_error("La ridice non puo' avere fratelli successivi");
    else {
        nodo nuovoNodo = new Nodo<T>();
        nuovoNodo->fratelloSuccessivo = n->fratelloSuccessivo;
        n->fratelloSuccessivo = nuovoNodo;
        nuovoNodo->valore = val;
        nuovoNodo->padre = n->padre;
        numeroNodi++;
    }
}
/**
 * @brief Inserisce un albero come primo figlio del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui aggiungere il primo figlio.
 * @param a l'albero da inserire come primo figlio di n.
 */
template<class T>
void AlberoPtr<T>::insPrimoSottoAlbero(nodo n, AlberoPtr<T> &a) {
    if (alberoVuoto() && a.alberoVuoto()) {
        throw std::out_of_range("Uno dei due alberi e' vuoto");
    } else {
        //creo un nuovo nodo e vi copio il contenuto della radice di a
        Nodo<T>* sub = new Nodo<T>();
        scriviNodo(sub,a.leggiNodo(a.radice()));
        //se a non è foglia copio tutto il suo sotto-albero in sub
        if (!a.foglia(a.radice())) copiaNodo(sub,a.primoFiglio(a.radice()));
        //inserisco il nuovo albero come primoFiglio di n
        sub->padre = n;
        sub->fratelloSuccessivo = n->primoFiglio;
        n->primoFiglio = sub;
        numeroNodi += a.numeroNodi;
    }
}
/**
 * @brief Inserisce un albero come fratello successivo del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui aggiungere il fratello successivo.
 * @param a l'albero da inserire come fratello successivo di n.
 */
template<class T>
void AlberoPtr<T>:: insSottoAlbero(nodo n, AlberoPtr<T> &a) {
    if (alberoVuoto() && a.alberoVuoto()) {
        throw std::out_of_range("Uno dei due alberi e' vuoto");
    } else if (n == nullptr) {
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    } else {
        //creo un nuovo nodo e vi copio il contenuto della radice di a
        Nodo<T>* sub = new Nodo<T>();
        scriviNodo(sub,a.leggiNodo(a.radice()));
        //se a non è foglia copio tutto il suo sotto-albero in sub
        if (!a.foglia(a.radice())) copiaNodo(sub,a.primoFiglio(a.radice()));
        //inserisco il nuovo albero come primoFiglio di n
        sub->padre = n;
        sub->fratelloSuccessivo = n->primoFiglio;
        n->primoFiglio = sub;
        numeroNodi += a.numeroNodi;
    }
}
/**
 * @brief Cancella l'albero a partire dal nodo n (compreso n).
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui cancellare il primo figlio.
 */
template <class T>
void AlberoPtr<T>::cancellaSottoAlbero(nodo n) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else {
        while (n->primoFiglio != nullptr) {
            // Finchè n ha ancora figli cancello tutti i sotto-alberi
            // che hanno come radice il primo figlio di n
            cancellaSottoAlbero(n->primoFiglio);
        }
        if (n != root) {
            // Se devo cancellare un nodo che non ha fratelli successivi, allora aggiorno il fratello precedente.
            if (n->fratelloSuccessivo == nullptr) n->padre->primoFiglio->fratelloSuccessivo = nullptr;
            // Se devo cancellare il primo figlio di un padre, allora aggiorno il primo figlio del padre.
            if (n->padre->primoFiglio == n) n->padre->primoFiglio = n -> fratelloSuccessivo;
            delete n;
            numeroNodi--;
        } else {
            root = nullptr;
            numeroNodi = 0;
        }
    }
}
/**
 * @brief Assegna il valore val al nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo a cui assegnare il valore.
 * @param val il valore da assegnare al nodo n.
 */
template<class T>
void AlberoPtr<T>::scriviNodo(nodo n, tipoElem val) {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        n->valore = val;
}
/**
 * @brief Restituisce il valore del nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo di cui restituire il valore.
 * @return il valore del nodo n.
 */
template<class T>
typename AlberoPtr<T>::tipoElem AlberoPtr<T>::leggiNodo(nodo n) const {
    if (alberoVuoto())
        throw std::runtime_error("Albero vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo passato come parametro non esiste");
    else
        return n->valore;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam T il tipo di dato dell'albero.
 * @param a l'albero da confrontare con l'albero corrente.
 * @return true se i due alberi sono uguali, false altrimenti.
 */
template<class T>
bool AlberoPtr<T>::operator==(const AlberoPtr<T> &a) const {
    if (alberoVuoto() && a.alberoVuoto())
        return true;
    else if (alberoVuoto() || a.alberoVuoto())
        return false;
    else {
        return confrontaNodi(radice(),a.radice());
    }
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T il tipo di dato dell'albero.
 * @param a l'albero da confrontare con l'albero corrente.
 * @return true se i due alberi sono diversi, false altrimenti.
 */
template<class T>
bool AlberoPtr<T>::operator!=(const AlberoPtr<T> &a) const {
    return !(*this == a);
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T il tipo di dato dell'albero.
 * @param a l'albero da assegnare.
 * @return l'albero corrente dopo l'assegnamento.
 */
template<class T>
AlberoPtr<T> &AlberoPtr<T>::operator=(const AlberoPtr<T> &a) {
    if (this != &a) {
        if (!alberoVuoto()) {
            // Cancello l'albero corrente
            cancellaSottoAlbero(radice());
        }
        root = new Nodo<T>;
        numeroNodi = 0;
        scriviNodo(root, a.leggiNodo(a.radice()));
        if (!a.foglia(a.radice()))
            copiaNodo(root, a.primoFiglio(a.radice()));
        numeroNodi++;
    }
    return *this;
}
/**
 * @brief Metodo che stampa il sotto-albero radicato nel nodo passato come parametro.
 * @tparam T il tipo di dato dell'albero binario.
 * @param n il nodo radice del sotto-albero da stampare.
 */
template<class T>
void AlberoPtr<T>::stampaSottoAlbero(nodo n) const {
    stampaRicorsiva(n, "");
}
/**
 * @brief Copia il nodo daCopiare nel nodo n.
 * @tparam T il tipo di dato dell'albero.
 * @param n il nodo in cui copiare il nodo daCopiare.
 * @param daCopiare il nodo da copiare.
 */
template<class T>
void AlberoPtr<T>::copiaNodo(nodo n, nodo daCopiare) {
    if (daCopiare != nullptr) {
        if (daCopiare->fratelloSuccessivo != nullptr)
            copiaNodo(n, daCopiare->fratelloSuccessivo);
        insPrimoFiglio(n, daCopiare->valore);
        if (daCopiare->primoFiglio != nullptr)
            copiaNodo(n->primoFiglio, daCopiare->primoFiglio);
    }
}
/**
 * @brief Stampa in modo ricorsivo l'albero n-ario.
 * @tparam T il tipo di dato dell'albero binario.
 * @param nodo il nodo radice del sotto-albero da stampare.
 * @param spazio la stringa di spazi da stampare prima del nodo.
 */
template<class T>
void AlberoPtr<T>::stampaRicorsiva(Nodo<T> *nodo, std::string spazio) const {
    if (nodo != nullptr) {
        std::cout << spazio;
        if (nodo->padre == nullptr) {
            // Se il nodo è la radice
            std::cout << "-->r:";
            spazio += "    ";
        } else {
            // Se il nodo è un figlio
            std::cout << "--> ";
            spazio += "|   ";
        }
        std::cout << "[" << nodo->valore << "]" << std::endl;

        // Stampa tutti i figli del nodo corrente
        Nodo<T>* figlio = nodo->primoFiglio;
        while (figlio != nullptr) {
            stampaRicorsiva(figlio, spazio);
            figlio = figlio->fratelloSuccessivo;
        }
    }
}
template<class T>
bool AlberoPtr<T>::confrontaNodi(nodo n1, nodo n2) const {
    if (n1 == n2) {
        // I due nodi sono gli stessi
        return true;
    }

    // Confronta i valori dei due nodi
    if (leggiNodo(n1) != leggiNodo(n2)) {
        return false;
    }

    // Confronta i sotto-alberi dei due nodi
    nodo figlio1 = primoFiglio(n1);
    nodo figlio2 = primoFiglio(n2);
    while (figlio1 != nullptr && figlio2 != nullptr) {
        if (!confrontaNodi(figlio1, figlio2)) {
            return false;
        }
        figlio1 = fratelloSuccessivo(figlio1);
        figlio2 = fratelloSuccessivo(figlio2);
    }

    // I due nodi hanno lo stesso numero di figli e i figli sono uguali
    return figlio1 == nullptr && figlio2 == nullptr;
}



#endif //N_TREES_ALBERO_PTR_H
