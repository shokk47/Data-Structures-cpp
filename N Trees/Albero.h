#ifndef N_TREES_ALBERO_H
#define N_TREES_ALBERO_H

#include <vector>
#include <algorithm>
using namespace std;

template <class T, class N>
class Albero {
public:
    typedef T tipoElem;
    typedef N nodo;

    //virtual void crea()=0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoVuoto() const = 0;
    virtual nodo radice() const = 0;
    virtual nodo padre(nodo) const = 0;
    virtual bool foglia(nodo) const = 0;
    virtual nodo primoFiglio(nodo) const = 0;
    virtual bool ultimoFratello(nodo) const = 0;
    virtual nodo fratelloSuccessivo(nodo) const = 0;

    virtual void inserisciRadice(tipoElem) = 0;
    virtual void cancellaSottoAlbero(nodo) = 0;

    virtual int ottieniNumeroNodi() const = 0;
    virtual void scriviNodo(nodo, tipoElem) = 0;
    virtual tipoElem leggiNodo(nodo) const = 0;

    int profonditaAlbero();
    int larghezzaAlbero();
private:
    int profondita(nodo);
    void larghezza(nodo, vector<int>& v, int liv);
};
/**
 * @brief Funzione che restituisce la profondità di un albero
 * La profondità di un albero è il cammino di lunghezza massima
 * che parte dalla radice e arriva a una foglia)
 * @tparam I tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @return intero che rappresenta la profondità dell'albero.
 */
template<class I,class N>
int Albero<I, N>::profonditaAlbero() {
    if (alberoVuoto())
        return 0;
    else {
        return profondita(radice());
    }
}
/**
 * @brief Funzione che restituisce la larghezza di un albero
 * La larghezza di un albero è il numero massimo di nodi presenti sullo stesso livello
 * @tparam I tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @return intero che rappresenta la larghezza dell'albero.
 */
template <class I,class N>
int Albero<I, N>::larghezzaAlbero() {
    if (!alberoVuoto()) {
        vector<int> v;
        larghezza(radice(),v,0);
        return *max_element(v.begin(),v.end());
    }
    else return 0;
}
/**
 * @brief Funzione che restituisce la profondità di un nodo
 * La profondità di un nodo è il cammino di lunghezza massima
 * che parte dal nodo e arriva a una foglia)
 * @tparam I tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo di cui si vuole calcolare la profondità.
 * @return intero che rappresenta la profondità del nodo.
 */
template <class I, class N>
int Albero<I,N>::profondita(Albero::nodo n) {
    //se il nodo è foglia ritorno 0
    if (foglia(n)) return 0;
    //se il nodo non è foglia allora richiamo la funzione sui suoi figli e fratelli
    //inizializzo un variabile m=1. Questa indica la profondità attuale
    int m = 1;
    int c;
    nodo k = primoFiglio(n);
    while (!ultimoFratello(k)) {
        //calcolo la profondità di ogni fratello del nodo n.
        // Se questa è maggiare della profondità attuale allora aggiorno la profondità attuale
        c = profondita(k);
        if (c > m) {
            m = c;
        }
        k = fratelloSuccessivo(k);
    }
    c = profondita(k);
    if (c > m) {
        m = c;
    }
    //ritorno la profondità attuale piu 1
    return (m + 1);
}
/**
 * @brief Funzione che restituisce la larghezza di un nodo
 * La larghezza di un nodo è il numero massimo di nodi presenti sullo stesso livello.
 * @tparam I tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo di cui si vuole calcolare la larghezza.
 * @param v vettore che contiene il numero di nodi per ogni livello.
 * @param liv livello del nodo.
 */
template <class I,class N>
void Albero<I,N>::larghezza(nodo n, vector<int> &v, int liv) {
    //se il livello è maggiore della dimensione del vettore
    // allora inseriamo un nuovo contatore all'interno del vettore (è stato raggiungo un livello non visitato)
    if (liv >= v.size()) v.push_back(1);
    else v[liv]++;

    if (!foglia(n)) {
        nodo c = primoFiglio(n);
        int newLiv = liv + 1;
        while (!ultimoFratello(c)) {
            larghezza(c, v, newLiv);
            c = fratelloSuccessivo(c);
        }
        larghezza(c, v, newLiv);
    }
}

#endif //N_TREES_ALBERO_H
