#ifndef LIST_LINKEDLIST_H
#define LIST_LINKEDLIST_H

#include "LinearList.h"

template <class T>
class Linked_list;

/**
 * @brief Classe per la rappresentazione di un nodo all'interno di una Linked List.
 * Questa classe rappresenta un nodo all'interno di una Linked List, che contiene un valore
 * di tipo generico e i puntatori al nodo precedente e successivo.
 *
 * @tparam T Il tipo generico degli elementi memorizzati nel nodo.
 */
template <class T>
class Nodo_lista {
    friend class Linked_list<T>;

   public:
    typedef T tipoelem;                 // Tipo generico degli elementi memorizzati nel nodo

   private:
    tipoelem valore;                   // Valore memorizzato nel nodo
    Nodo_lista<tipoelem>* precedente;  // Puntatore al nodo precedente
    Nodo_lista<tipoelem>* successivo;  // Puntatore al nodo successivo
};

/**
 * @brief Classe per la rappresentazione di una Linked List.
 * testa -> [0,1,2,3,4,5,...] <- coda
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T>
class Linked_list : public LinearList<T, Nodo_lista<T>*> {
   public:
    typedef typename LinearList<T, Nodo_lista<T>*>::tipoelem tipoelem;
    typedef typename LinearList<T, Nodo_lista<T>*>::posizione posizione;

    Linked_list();
    Linked_list(const Linked_list<T>&);
    ~Linked_list();

    //operatori della lista
    void creaLista();                                   // Crea una lista vuota
    bool listaVuota() const;                            // Verifica se la lista è vuota
    tipoelem leggiLista(posizione) const;               // Legge il valore di un elemento della lista
    void scriviLista(const tipoelem&, posizione);       // Scrive il valore di un elemento della lista
    posizione primoLista() const;                       // Restituisce la posizione del primo elemento della lista
    bool fineLista(posizione) const;                    // Verifica se la posizione è la fine della lista
    posizione succLista(posizione) const;               // Restituisce la posizione dell'elemento successivo
    posizione precLista(posizione) const;               // Restituisce la posizione dell'elemento precedente
    void insLista(const tipoelem&, posizione&);         // Inserisce un elemento nella lista
    void cancLista(posizione&);                         // Cancella un elemento dalla lista

    //Sovrascrivo operatori
    Linked_list<T>& operator=(const Linked_list<T>&);
    bool operator==(const Linked_list<T>&);
    bool operator!=(const Linked_list<T>&);

    //FUNZIONI ACCESSORIE
    void inserisciTesta(const tipoelem&);               // Inserisce un elemento in prima posizione
    void inserisciCoda(const tipoelem&);                // Inserisce un elemento in ultima posizione
    void rimuoviTesta();                                // Rimuove l'elemento in prima posizione
    void rimuoviCoda();                                 // Rimuove l'elemento in ultima posizione
    posizione ultimoLista() const;                      // Restituisce la posizione dell'ultimo elemento della lista
    int lunghezza() const;                              // Restituisce la lunghezza della lista
    void scambiaElementi(posizione, posizione);         // Scambia due elementi della lista

private:
    Nodo_lista<T>* testa;                               // Puntatore alla sentinella
    int lunghezzaLista;                                 // Lunghezza lista, parte da 1
};

/**
 * @brief Crea una lista vuota.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void Linked_list<T>::creaLista() {
    testa = new Nodo_lista<T>;
    testa->successivo = testa;
    testa->precedente = testa;
    lunghezzaLista = 0;
}
/**
 * @brief Costruttore di default.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
Linked_list<T>::Linked_list() {
    creaLista();
}
/**
 * @brief Costruttore per copia.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da copiare.
 */
template <class T>
Linked_list<T>::Linked_list(const Linked_list<T>& L) {
    testa = new Nodo_lista<T>;
    testa->successivo = testa;
    testa->precedente = testa;
    posizione p = L.primoLista();
    posizione p1 = this->primoLista();
    while (!L.fineLista(p)) {
        this->insLista(L.leggiLista(p), p1);
        p1 = this->succLista(p1);
        p = L.succLista(p);
    }
}
/**
 * @brief Distruttore.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
Linked_list<T>::~Linked_list() {
    posizione tmp, p = ultimoLista();
    while (!fineLista(p)) {
        tmp = p;
        p = p->precedente;
        delete tmp;
    }
    delete testa;
}
/**
 * @brief Verifica se la lista è vuota.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return true se la lista è vuota, false altrimenti.
 */
template <class T>
bool Linked_list<T>::listaVuota() const {
    // se la sentinella sta puntando a se stessa, allora la lista è vuota
    return (testa == testa->successivo);
}
/**
 * @brief Restituisce la posizione del primo elemento della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La posizione del primo elemento della lista.
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::primoLista() const {
    return (testa->successivo);
}
/**
 * @brief Restituisce la posizione dell'ultimo elemento della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La posizione dell'ultimo elemento della lista.
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::ultimoLista() const {
    return (testa->precedente);
}
/**
 * @brief Restituisce la posizione successiva a p nella lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione di cui si vuole conoscere il successivo.
 * @return La posizione successiva a p nella lista.
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::succLista(Linked_list::posizione p) const {
    return p->successivo;
}
/**
 * @brief Restituisce la posizione precedente a p nella lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione di cui si vuole conoscere il precedente.
 * @return La posizione precedente a p nella lista.
 */
template <class T>
typename Linked_list<T>::posizione
Linked_list<T>::precLista(Linked_list::posizione p) const {
    if (p != testa->successivo)
        return (p->precedente);
    else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}
/**
 * @brief Verifica se p è la posizione dell'ultimo elemento della lista.
 * @tparam T
 * @param p
 * @return
 */
template <class T>
bool Linked_list<T>::fineLista(Linked_list<T>::posizione p) const {
    //se p == sentinella allora p è l'ultimo elemento fine della lista
    return (p == testa);
}
/**
 * @brief Restituisce l'elemento in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione dell'elemento da restituire.
 * @return L'elemento in posizione p della lista.
 */
template <class T>
typename Linked_list<T>::tipoelem
Linked_list<T>::leggiLista(Linked_list::posizione p) const {
    if (!fineLista(p))
        return (p->valore);
    else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}
/**
 * @brief Sovrascrive l'elemento e in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da scrivere.
 * @param p Posizione in cui scrivere l'elemento.
 */
template <class T>
void Linked_list<T>::scriviLista(const Linked_list::tipoelem& e,
                                 Linked_list::posizione p) {
    if (!fineLista(p))
        p->valore = e;
    else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}
/**
 * @brief Inserisce l'elemento e in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da inserire.
 * @param p Posizione in cui inserire l'elemento.
 */
template <class T>
void Linked_list<T>::insLista(const Linked_list::tipoelem& e,
                              Linked_list::posizione& p) {
    posizione t = new Nodo_lista<T>;
    t->valore = e;
    t->precedente = p->precedente;
    t->successivo = p;
    p->precedente->successivo = t;
    p->precedente = t;
    lunghezzaLista++;
    p=p->precedente;
}
/**
 * @brief Cancella l'elemento in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione dell'elemento da cancellare.
 */
template <class T>
void Linked_list<T>::cancLista(Linked_list<T>::posizione& p) {
    if (!listaVuota() && !fineLista(p)) {
        posizione tmp = p->successivo;
        p->precedente->successivo = p->successivo;
        p->successivo->precedente = p->precedente;
        delete p;
        p = tmp;
        lunghezzaLista--;
    } else
        throw std::out_of_range("POSIZIONE NON VALIDA");
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da copiare.
 * @return La lista copiata.
 */
template <class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& L) {
    if (this != &L) {
        this->~Linked_list();
        testa = new Nodo_lista<T>;
        testa->successivo = testa;
        testa->precedente = testa;
        posizione pl = L.primoLista();
        posizione p1 = this->primoLista();
        while (!L.fineLista(pl)) {
            this->insLista(L.leggiLista(pl), p1);
            p1 = this->succLista(p1);
            pl = L.succLista(pl);
        }
    }
    return *this;
}
/**
 * @brief Operatore di uguaglianza.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da confrontare.
 * @return True se le due liste sono uguali, false altrimenti.
 */
template <class T>
bool Linked_list<T>::operator==(const Linked_list<T>& L) {
    if (L.lunghezzaLista != this->lunghezzaLista)
        return false;
    posizione p, pL;
    p = primoLista();
    pL = L.primoLista();
    while (!fineLista(p)) {
        if (p->valore != pL->valore)
            return false;
        p = p->successivo;
        pL = pL->successivo;
    }
    return true;
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da confrontare.
 * @return True se le due liste sono diverse, false altrimenti.
 */
template <class T>
bool Linked_list<T>::operator!=(const Linked_list<T>& L) {
    return !(*this == L);
}
/**
 * @brief Aggiunge e in prima posizione della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da aggiungere.
 */
template <class T>
void Linked_list<T>::inserisciTesta(const tipoelem& e) {
    Nodo_lista<T>* p = new Nodo_lista<T>;
    p->valore = e;
    testa->successivo->precedente = p;
    p->successivo = testa->successivo;
    p->precedente = testa;
    testa->successivo = p;
    lunghezzaLista++;
}
/**
 * @brief Aggiunge e in ultima posizione della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da aggiungere.
 */
template <class T>
void Linked_list<T>::inserisciCoda(const tipoelem& e) {
    posizione p = new Nodo_lista<T>;
    p->valore = e;
    posizione pu = ultimoLista();
    p->precedente = pu;
    p->successivo = testa;
    pu->successivo = p;
    testa->precedente = p;
    lunghezzaLista++;
}
/**
 * @brief Rimuove l'elemento in prima posizione.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void Linked_list<T>::rimuoviTesta() {
    posizione p = new Nodo_lista<T>;
    p = testa->successivo;
    testa->successivo = testa->successivo->successivo;
    p = nullptr;
    delete p;
    lunghezzaLista--;
}
/**
 * @brief Rimuove l'elemento in ultima posizione.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void Linked_list<T>::rimuoviCoda() {
    posizione p = new Nodo_lista<T>;
    p = ultimoLista();
    p->precedente->successivo = testa;
    p = nullptr;
    delete p;
    lunghezzaLista--;
}
/**
 * @brief Restituisce la lunghezza della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La lunghezza della lista.
 */
template <class T>
int Linked_list<T>::lunghezza() const {
    return lunghezzaLista;
};
/**
 * @brief Scambia gli elementi in posizione p1 e p2.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p1 posizione del primo elemento da scambiare.
 * @param p2 posizione del secondo elemento da scambiare.
 */
template <class T>
void Linked_list<T>::scambiaElementi(Linked_list::posizione p1,
                                     Linked_list::posizione p2) {

    if (p1 != p2 && (p1 != nullptr && p2 != nullptr)) {
        tipoelem temp = leggiLista(p1);
        scriviLista(leggiLista(p2), p1);
        scriviLista(temp, p2);
    }
}

#endif  //LIST_LINKEDLIST_H
