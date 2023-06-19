#ifndef BINARY_TREES_ALBEROBINARIO_H
#define BINARY_TREES_ALBEROBINARIO_H

#include <iostream>
#include <ostream>
#include <algorithm>
using namespace std;

template <class T, class N>
class AlberoBinario {
public:
    typedef T tipoElem;
    typedef N nodo;

    //virtual void crea()=0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoVuoto() const = 0;
    virtual nodo radice() const = 0;
    virtual nodo padre(nodo) const = 0;
    virtual nodo figlioSinistro(nodo) const = 0;
    virtual nodo figlioDestro(nodo) const = 0;
    virtual bool sinistroVuoto(nodo) const = 0;
    virtual bool destroVuoto(nodo) const = 0;
    virtual void cancellaSottoAlbero(nodo) = 0;
    virtual tipoElem leggiNodo(nodo) const = 0;
    virtual void scriviNodo(nodo, tipoElem) = 0;

    virtual void inserisciRadice(tipoElem) = 0;
    virtual void inserisciFiglioSinistro(const nodo, tipoElem) = 0;
    virtual void inserisciFiglioDestro(const nodo, tipoElem) = 0;

    void visita(int) const;
    int profondita_nodo(AlberoBinario<T,N>&,nodo) const;
    int altezza_nodo(AlberoBinario<T,N>&,nodo) const;

    // La stampa utilizza la visita in pre-Ordine.
    template <class T1,class N1>
    friend ostream& operator<<(ostream &, AlberoBinario<T1,N1>&);

private:
    void stampa(nodo, std::ostream&);
    void visitaPreOrdine(nodo) const;
    void visitaPostOrdine(nodo) const;
    void visitaSimmetrica(nodo) const;
};
/**
 * @brief Scelta del tipo di visita da eseguire.
 * Se scelta = 1, viene eseguita la visita in pre-ordine.
 * Se scelta = 2, viene eseguita la visita in post-ordine.
 * Se scelta = 3, viene eseguita la visita simmetrica.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param scelta intero che rappresenta la scelta dell'utente.
 */
template <class T,class N>
void AlberoBinario<T, N>::visita(int scelta) const {
    if (!alberoVuoto()) {
        switch (scelta) {
            case 1:
                cout<<"[ ";
                visitaPreOrdine(radice());
                cout<<"]"<<endl;
                break;
            case 2:
                cout<<"[ ";
                visitaPostOrdine(radice());
                cout<<"]"<<endl;
                break;
            case 3:
                cout<<"[ ";
                visitaSimmetrica(radice());
                cout<<"]"<<endl;
                break;
            default:
                throw std::out_of_range("SCELTA NON ESISTENTE");
        }
    }
    else cout<<"ALBERO VUOTO"<<endl;
}
/**
 * @brief Stampa in pre-ordine.
 * L'ordine di stampa è il seguente:
 * 1. stampa il nodo corrente.
 * 2. stampa ricorsivamente il sotto-albero sinistro.
 * 3. stampa ricorsivamente il sotto-albero destro.
 * @tparam T1 tipo di dato contenuto nel nodo.
 * @tparam N1 tipo di dato che rappresenta il nodo.
 * @param os stream di output.
 * @param T albero da stampare.
 * @return stream di output.
 */
template <class T1,class N1>
ostream& operator<<(ostream & os, AlberoBinario<T1,N1>& T)
{
    if (T.alberoVuoto())
        os<<"ALBERO VUOTO"<<endl;
    else {
        os << "[ ";
        T.stampa(T.radice(), os);
        os << "] " << endl;
    }
    return os;
}
/**
 * @brief Stampa in pre-ordine ricorsiva.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo radice dell'albero.
 * @param os stream di output.
 */
template <class T,class N>
void AlberoBinario<T, N>::stampa(nodo n, std::ostream & os)  {
    os<< leggiNodo(n)<<" ";
    if(!sinistroVuoto(n)) stampa(figlioSinistro(n),os);
    if(!destroVuoto(n)) stampa(figlioDestro(n),os);
}
/**
 * @brief il nodo corrente viene visitato prima di visitare i suoi figli.
 *
 * L'ordine delle operazioni è il seguente:
 * 1. visita il nodo corrente.
 * 2. visita ricorsivamente il sotto-albero sinistro.
 * 3. visita ricorsivamente il sotto-albero destro.
 * <br>
 * La visita pre-ordine è utile per copiare un albero binario,
 * calcolare l'altezza o eseguire una visita in profondità.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo radice dell'albero.
 */
template <class T, class N>
void AlberoBinario<T,N>::visitaPreOrdine(nodo n) const {
    cout << leggiNodo(n) << " ";
    if(!sinistroVuoto(n))
        visitaPreOrdine(figlioSinistro(n));
    if(!destroVuoto(n))
        visitaPreOrdine(figlioDestro(n));
}
/**
 * @brief il nodo corrente viene visitato dopo aver visitato i suoi figli.
 *
 * L'ordine delle operazioni è il seguente:
 * 1. visita ricorsivamente il sotto-albero sinistro.
 * 2. visita ricorsivamente il sotto-albero destro.
 * 3. visita il nodo corrente.
 * <br>
 * La visita post-ordine è utile per cancellare un albero binario o per
 * eseguire operazioni di elaborazione o di esplorazione dopo aver
 * visitato i nodi figli.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo radice dell'albero.
 */
template <class T, class N>
void AlberoBinario<T,N>::visitaPostOrdine(nodo n) const {
    if(!sinistroVuoto(n))
        visitaPostOrdine(figlioSinistro(n));
    if(!destroVuoto(n))
        visitaPostOrdine(figlioDestro(n));
    cout << leggiNodo(n) << " ";
}
/**
 * @brief Il nodo corrente viene visitato tra la visita del sotto-albero
 * sinistro e la visita del sotto-albero destro.
 * L'ordine delle operazioni è il seguente:
 * 1. visita ricorsivamente il sotto-albero sinistro.
 * 2. visita il nodo corrente.
 * 3. visita ricorsivamente il sotto-albero destro.
 * <br>
 * La visita simmetrica è utilizzata principalmente per attraversare gli alberi
 * binari di ricerca (BST), poichè restituisce i valori dei nodi in ordine
 * crescente.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param n nodo radice dell'albero.
 */
template <class T, class N>
void AlberoBinario<T,N>::visitaSimmetrica(nodo n) const {
    if(!sinistroVuoto(n))
        visitaSimmetrica(figlioSinistro(n));
    cout << leggiNodo(n) << " ";
    if(!destroVuoto(n))
        visitaSimmetrica(figlioDestro(n));
}
/**
 * @brief Restituisce la profondità del nodo n nell'albero a.
 * La lunghezza del cammino che parte dalla radice e arriva al nodo n.
 * La radice ha profondità 0, mentre i suoi figli hanno profondità >=1.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param a albero binario.
 * @param n nodo dell'albero.
 * @return profondità del nodo n.
 */
template <class T, class N>
int AlberoBinario<T,N>::profondita_nodo(AlberoBinario<T,N>& a, nodo n) const {
    if (!alberoVuoto()) {
        int c=0;
        while (n!=a.radice()) {
            c++;
            n=a.padre(n);
        }
        return c;
    } else throw std::out_of_range("ALBERO VUOTO");
}
/**
 * @brief Restituisce la lunghezza del cammino più lungo che parte dal nodo n e arriva ad una foglia.
 * @tparam T tipo di dato contenuto nel nodo.
 * @tparam N tipo di dato che rappresenta il nodo.
 * @param a albero binario.
 * @param n nodo dell'albero.
 * @return altezza del nodo n.
 */
template <class T, class N>
int AlberoBinario<T,N>::altezza_nodo(AlberoBinario<T,N>& a, nodo n) const {
    //procedo se l'albero non è vuoto
    if (!alberoVuoto()) {
        if(destroVuoto(n) && sinistroVuoto(n))
            //se il nodo è foglia allora ha profondità 0 per definizione
            return 0;
        else {
            int sx = 0, dx = 0;
            if (!sinistroVuoto(n)) {
                //calcolo altezza sotto-albero sinistro
                sx= altezza_nodo(a, a.figlioSinistro(n));
                sx++;
            }
            if (!destroVuoto(n)) {
                //calcolo altezza destro sinistro
                dx= altezza_nodo(a, a.figlioDestro(n));
                dx++;
            }
            //l'altezza del nodo è data dall'altezza del suo sottoalbero piu alto
            return max(sx, dx);
        }
    } else throw std::out_of_range("ALBERO VUOTO");
}

#endif //BINARY_TREES_ALBEROBINARIO_H
