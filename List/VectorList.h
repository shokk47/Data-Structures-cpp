#ifndef LIST_VECTORLIST_H
#define LIST_VECTORLIST_H

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "Linearlist.h"
using namespace std;

/**
 * @brief Classe per la rappresentazione di una lista tramite array.
 * testa -> [0,1,2,3,4,5,...] <- coda
 * Si può accedere direttamente solo al primo e all'ultimo elemento della lista.
 * Per accedere al generico occorre scandire sequenzialmente gli elementi della lista.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T>
class VectorList : public LinearList<T, int> {
   public:
    typedef typename LinearList<T, int>::tipoelem tipoelem;
    typedef typename LinearList<T, int>::posizione posizione;
    /** (!!) le posizioni partono da 1. **/

    VectorList();
    VectorList(const VectorList<T>&);
    ~VectorList();

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
    VectorList<T>& operator=(const VectorList<T>&);
    bool operator==(const VectorList<T>&);
    bool operator!=(const VectorList<T>&);

    //FUNZIONI ACCESSORIE
    void inserisciTesta(const tipoelem&);               // Inserisce un elemento in prima posizione
    void inserisciCoda(const tipoelem&);                // Inserisce un elemento in ultima posizione
    void rimuoviTesta();                                // Rimuove l'elemento in prima posizione
    void rimuoviCoda();                                 // Rimuove l'elemento in ultima posizione
    posizione ultimoLista() const;                      // Restituisce la posizione dell'ultimo elemento della lista
    int lunghezza() const;                              // Restituisce la lunghezza della lista
    void scambiaElementi(posizione, posizione);         // Scambia due elementi della lista

private:
    int lunghezzaArray;  //lunghezza array che contiene la lista, parte da 0.
    int lunghezzaLista;  //lunghezza lista, parte da 1.
    tipoelem* elementi;  //array che contiene la lista
    void cambiaDimensione(tipoelem*&, int, int);
};

/**
 * @brief Crea una lista vuota.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void VectorList<T>::creaLista() {
    lunghezzaLista = 0;
    elementi = new tipoelem[lunghezzaArray];
}
/**
 * @brief Costruttore di default.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
VectorList<T>::VectorList() {
    lunghezzaArray = 20;
    creaLista();
}
/**
 * @brief Costruttore per copia.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da copiare.
 */
template <class T>
VectorList<T>::VectorList(const VectorList<T>& L) {
    lunghezzaArray = L.lunghezzaArray;
    lunghezzaLista = L.lunghezzaLista;
    elementi = new tipoelem[lunghezzaArray];
    for (int i = 0; i < lunghezzaLista; i++)
        elementi[i] = L.elementi[i];
}
/**
 * @brief Distruttore.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
VectorList<T>::~VectorList() {
    delete[] elementi;
}
/**
 * @brief Verifica se la lista è vuota.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return true se la lista è vuota, false altrimenti.
 */
template <class T>
bool VectorList<T>::listaVuota() const {
    return (lunghezzaLista == 0);
}
/**
 * @brief Restituisce la posizione del primo elemento della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La posizione del primo elemento della lista.
 */
template <class T>
typename VectorList<T>::posizione
VectorList<T>::primoLista() const {
    return (1);
}
/**
 * @brief Restituisce la posizione dell'ultimo elemento della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La posizione dell'ultimo elemento della lista.
 */
template <class T>
typename VectorList<T>::posizione
VectorList<T>::ultimoLista() const {
    return (lunghezzaLista);
}
/**
 * @brief Restituisce la posizione successiva a p nella lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione di cui si vuole conoscere il successivo.
 * @return La posizione successiva a p nella lista.
 */
template <class T>
typename VectorList<T>::posizione
VectorList<T>::succLista(VectorList::posizione p) const {
    if (p>=1 && p<=lunghezzaLista) {
        return (p+1);
    } else {
        throw std::out_of_range("2POSIZIONE NON VALIDA");
    }
}
/**
 * @brief Restituisce la posizione precedente a p nella lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione di cui si vuole conoscere il precedente.
 * @return La posizione precedente a p nella lista.
 */
template <class T>
typename VectorList<T>::posizione
VectorList<T>::precLista(VectorList::posizione p) const {
    if (p>=2 && p<=lunghezzaLista) {
        return (p-1);
    } else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}
/**
 * @brief Verifica se p è la posizione dell'ultimo elemento della lista.
 * @tparam T
 * @param p
 * @return
 */
template <class T>
bool VectorList<T>::fineLista(VectorList<T>::posizione p) const {
    if (p>=1 && p<=lunghezzaLista+1)
        return (p == lunghezzaLista+1);
    else
        throw std::out_of_range("3POSIZIONE NON VALIDA");
}
/**
 * @brief Restituisce l'elemento in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione dell'elemento da restituire.
 * @return L'elemento in posizione p della lista.
 */
template <class T>
typename VectorList<T>::tipoelem
VectorList<T>::leggiLista(VectorList::posizione p) const {
    if (p>=1 && p<= lunghezzaLista) {
        return (elementi[p-1]);
    } else {
        throw std::out_of_range("1POSIZIONE NON VALIDA");
    }
}
/**
 * @brief Sovrascrive l'elemento e in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da scrivere.
 * @param p Posizione in cui scrivere l'elemento.
 */
template <class T>
void VectorList<T>::scriviLista(const VectorList::tipoelem& e,
                                VectorList::posizione p) {
    if (p>= 1 && p<=lunghezzaLista) {
        elementi[p-1] = e;
    } else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}
/**
 * @brief Inserisce l'elemento e in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da inserire.
 * @param p Posizione in cui inserire l'elemento.
 */
template <class T>
void VectorList<T>::insLista(const VectorList::tipoelem& e,
                             VectorList::posizione& p) {
    if (p>=1 && p<=lunghezzaLista+1) {
        if (lunghezzaLista==lunghezzaArray) {
            cambiaDimensione(elementi,lunghezzaArray,lunghezzaArray*2);
            lunghezzaArray*=2;}
        for (int i = lunghezzaLista; i >= p; i--) {
            elementi[i]=elementi[i-1];
        }
        elementi[p-1]=e;
        lunghezzaLista++;
    }
    else throw std::out_of_range("POSIZIONE NON VALIDA" );
}
/**
 * @brief Cancella l'elemento in posizione p della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p Posizione dell'elemento da cancellare.
 */
template <class T>
void VectorList<T>::cancLista(VectorList<T>::posizione& p) {
    if (p>=1 && p<=lunghezzaLista) {
        if (!listaVuota()) {
            for (int i = p-1; i < lunghezzaLista-1; i++) {
                elementi[i]=elementi[i+1];
            }
            lunghezzaLista--;
        }
    }
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}
/**
 * @brief Operatore di assegnamento.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da copiare.
 * @return La lista copiata.
 */
template <class T>
VectorList<T>& VectorList<T>::operator=(const VectorList<T>& L) {
    if (this!=&L) {
        this->lunghezzaLista = L.lunghezzaLista;
        this->lunghezzaArray = L.lunghezzaArray;
        delete [] elementi;
        elementi = new tipoelem[lunghezzaArray];
        for (int i=0;i<lunghezzaLista;i++) {
            elementi[i]=L.elementi[i];
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
bool VectorList<T>::operator==(const VectorList<T>& L) {
    if (this->lunghezzaLista!=L.lunghezzaLista) {
        return false;
    } else {
        for (int i=0;i<lunghezzaLista;i++) {
            if (!(this->elementi[i]!=L.elementi[i]))
                return false;
        }
        return true;
    }
}
/**
 * @brief Operatore di disuguaglianza.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param L Lista da confrontare.
 * @return True se le due liste sono diverse, false altrimenti.
 */
template <class T>
bool VectorList<T>::operator!=(const VectorList<T>& L) {
    return !(*this == L);
}
/**
 * @brief Aggiunge e in prima posizione della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da aggiungere.
 */
template <class T>
void VectorList<T>::inserisciTesta(const tipoelem& e) {
    posizione p = primoLista();
    insLista(e,p);
}
/**
 * @brief Aggiunge e in ultima posizione della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param e Elemento da aggiungere.
 */
template <class T>
void VectorList<T>::inserisciCoda(const tipoelem& e) {
    posizione p = lunghezzaLista + 1;
    insLista(e,p);
}
/**
 * @brief Rimuove l'elemento in prima posizione.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void VectorList<T>::rimuoviTesta() {
    posizione p = 1;
    cancLista(p);
}
/**
 * @brief Rimuove l'elemento in ultima posizione.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 */
template <class T>
void VectorList<T>::rimuoviCoda() {
    cancLista(lunghezzaLista);
}
/**
 * @brief Restituisce la lunghezza della lista.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @return La lunghezza della lista.
 */
template <class T>
int VectorList<T>::lunghezza() const {
    return lunghezzaLista;
};
/**
 * @brief Scambia gli elementi in posizione p1 e p2.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param p1 posizione del primo elemento da scambiare.
 * @param p2 posizione del secondo elemento da scambiare.
 */
template <class T>
void VectorList<T>::scambiaElementi(VectorList::posizione p1,
                                    VectorList::posizione p2) {

    if ((p1>=1 && p1<=lunghezzaLista) && (p2>=1 && p2<=lunghezzaLista) ) {
        tipoelem tmp = elementi[p1 - 1];
        elementi[p1 - 1] = elementi[p2 - 1];
        elementi[p2 - 1] = tmp;
    }
}
/**
 * @brief Cambia la dimensione dell'array.
 * @tparam T Tipo generico degli elementi memorizzati nella lista.
 * @param elementi array da modificare.
 * @param vecchiaDimensione dimensione attuale dell'array.
 * @param nuovaDimensione nuova dimensione dell'array.
 */
template<class T>
void VectorList<T>::cambiaDimensione(tipoelem *&elementi, int vecchiaDimensione, int nuovaDimensione) {
    int numero;
    (vecchiaDimensione<nuovaDimensione) ? numero=vecchiaDimensione : numero=nuovaDimensione;
    tipoelem * tmp=new tipoelem[nuovaDimensione];
    for (int i=0;i<numero;i++) {
        tmp[i]=this->elementi[i];
    }
    delete [] elementi;
    elementi=tmp;

}

#endif  //LIST_VECTORLIST_H