#ifndef LIST_LINEARLIST_H
#define LIST_LINEARLIST_H

#include <ostream>
#include <iostream>
using namespace std;

/**
 * @brief Classe astratta Linear_List
 * testa -> [0,1,2,3,4,5,...] <- coda
 * <br>
 * Questa classe rappresenta un'interfaccia per una lista lineare generica.
 * Definisce le operazioni di base e i metodi comuni che possono essere utilizzati
 * con qualsiasi tipo di implementazione della lista.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T, class P>
class LinearList {

public:
    typedef T tipoelem;     /**< Tipo generico della lista */
    typedef P posizione;    /**< Indice dell'elemento nella lista */

    // Operatori della Lista
    virtual void creaLista() =0;
    virtual bool listaVuota() const=0;
    virtual tipoelem leggiLista(posizione) const=0;
    virtual void scriviLista(const tipoelem&, posizione) =0;
    virtual posizione primoLista() const=0;
    virtual bool fineLista(posizione)  const=0;
    virtual posizione succLista(posizione) const=0;
    virtual posizione precLista(posizione) const=0;
    virtual void insLista(const tipoelem&, posizione&) =0;
    virtual void cancLista(posizione&)=0;

    // Metodi aggiuntivi
    virtual void inserisciTesta(const tipoelem&)=0;
    virtual void inserisciCoda(const tipoelem&)=0;
    virtual void rimuoviTesta()=0;
    virtual void rimuoviCoda()=0;
    virtual posizione ultimoLista() const=0;
    virtual int lunghezza() const=0;
    virtual void scambiaElementi(posizione, posizione)=0;
    bool ricercaElemento(T&)const;
    void inverti();
    bool palindroma();

    // Overload di << per la stampa della lista
    template <class T1, class P1>
    friend ostream& operator<<(ostream& , const LinearList<T1,P1>&);

    // Metodi di ordinamento
    void bubbleSort();
    void quicksort();

private:
    posizione partition(posizione inizio, posizione fine);
    void runQuickSort(posizione inizio, posizione fine);
};

/**
 * @brief Operatore di output per la classe Linear_List.
 *
 * Questo operatore permette di stampare gli elementi della lista in un formato
 * specifico all'output stream specificato.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 * @param os L'oggetto ostream di output su cui stampare gli elementi.
 * @param l L'istanza di Linear_List da cui leggere gli elementi.
 * @return L'oggetto ostream aggiornato dopo la stampa degli elementi.
 */
template< class T, class P >
ostream& operator<<(ostream& os, const LinearList<T,P> &l){
    typename LinearList<T,P>::posizione p;
    p = l.primoLista();
    os << "[";
    while (!l.fineLista(p)){
        if (p != l.primoLista())
            os << "," <<l.leggiLista(p);
        else
            os << l.leggiLista(p);
        p = l.succLista(p);
    }
    os << "]" << endl;
    return os;
}
/**
 * @brief Inverte l'ordine degli elementi nella lista.
 *
 * La funzione `inverti` inverte l'ordine degli elementi nella lista.
 * Per farlo, utilizza due posizioni: una all'inizio della lista e una alla fine della lista.
 * Itera attraverso la metà degli elementi della lista e scambia l'elemento corrispondente
 * all'inizio con l'elemento corrispondente alla fine. Questo procedimento viene ripetuto
 * finché non viene invertito l'ordine di tutti gli elementi nella lista.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T, class P>
void LinearList<T, P>::inverti() {
    posizione prima=primoLista();
    posizione ultimo=ultimoLista();
    tipoelem e1,e2;
    for (int i=0;i<(lunghezza()/2);i++)
    {
        e1= leggiLista(prima);
        e2= leggiLista(ultimo);
        scriviLista(e2,prima);
        scriviLista(e1,ultimo);
        prima=succLista(prima);
        ultimo=precLista(ultimo);
    }
}
/**
 * @brief Verifica se la lista è palindroma.
 *
 * La funzione `palindroma` verifica se la lista è palindroma, ossia se gli elementi
 * nella lista possono essere letti nello stesso ordine sia da sinistra a destra che
 * da destra a sinistra. Per fare ciò, confronta gli elementi corrispondenti all'inizio
 * e alla fine della lista, avanzando e retrocedendo lungo la lista contemporaneamente.
 * Se gli elementi corrispondenti sono diversi, restituisce `false`. Se tutti gli elementi
 * corrispondenti sono uguali, restituisce `true`.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 * @return `true` se la lista è palindroma, `false` altrimenti.
 */
template <class T,class P>
bool LinearList<T, P>::palindroma() {
    posizione prima=primoLista();
    posizione ultimo=ultimoLista();
    for (int i=0;i<(lunghezza()/2);i++)
    {
        if (leggiLista(prima)!= leggiLista(ultimo))
        {
            return false;
        }
        prima=succLista(prima);
        ultimo= precLista(ultimo);
    }
    return true;
}
/**
 * @brief Ricerca un elemento nella lista.
 *
 * La funzione `ricercaElemento` esegue una ricerca lineare nella lista per trovare l'elemento specificato.
 * Itera attraverso la lista partendo dalla posizione iniziale, confrontando ogni elemento con l'elemento
 * di ricerca `e`. Se l'elemento viene trovato, la funzione restituisce `true`, altrimenti continua a cercare
 * fino alla fine della lista. Se l'elemento non viene trovato, la funzione restituisce `false`.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 * @param e L'elemento da cercare nella lista.
 * @return `true` se l'elemento viene trovato, `false` altrimenti.
 */
template <class T,class P>
bool LinearList<T,P>::ricercaElemento(T& e) const {
    posizione p=this->primoLista();
    while (!fineLista(p))
    {
        if (e==leggiLista(p))
            return true;
        else
            p= succLista(p);
    }
    return false;
}
/**
 * @brief Ordina la lista utilizzando l'algoritmo Bubble Sort.
 *
 * L'algoritmo confronta gli elementi adiacenti nella lista e, se necessario,
 * li scambia fino a quando l'intera lista è ordinata in ordine crescente.
 * L'implementazione segue i seguenti passaggi:
 *
 * 1. Inizia con il primo elemento della lista e confrontalo con l'elemento
 *    successivo. Se l'elemento successivo è minore, li scambia di posizione.
 *    Passa quindi all'elemento successivo e ripeti il confronto.
 *
 * 2. Continua a ripetere il passaggio 1 per ogni coppia di elementi
 *    adiacenti nella lista, fino a raggiungere la fine della lista.
 *    Questo garantisce che l'elemento più grande si sposti gradualmente
 *    verso la fine della lista durante ogni iterazione.
 *
 * 3. Ripeti i passaggi 1 e 2 per un numero di volte pari alla lunghezza
 *    della lista meno uno, in quanto l'elemento più grande viene posizionato
 *    correttamente alla fine della lista dopo ogni iterazione.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T,class P>
void LinearList<T,P>::bubbleSort() {
    posizione p, q;
    int lung = lunghezza();
    for (int i = 0; i < lung - 1; i++) {
        p = primoLista();
        q = succLista(p);
        for (int j = 0; j < lung - i - 1; j++) {
            tipoelem elem_p = leggiLista(p);
            tipoelem elem_q = leggiLista(q);
            if (elem_p > elem_q) {
                scambiaElementi(p, q);
            }
            p = q;
            q = succLista(q);
        }
    }
}
/**
 * @brief Ordina la lista utilizzando l'algoritmo Quick Sort.
 *
 * L'algoritmo Quick Sort è un algoritmo di ordinamento efficiente basato su confronti.
 * Si basa sul concetto di partizione, che seleziona un elemento pivot dalla lista
 * e riorganizza gli elementi in modo che gli elementi minori del pivot siano posizionati
 * a sinistra e gli elementi maggiori o uguali al pivot siano posizionati a destra.
 *
 * L'algoritmo ricorsivamente suddivide la lista in sottoarray più piccoli, ordinando
 * separatamente i sottoarray e combinandoli per ottenere la lista completamente ordinata.
 *
 * Il pivot viene scelto in modo strategico per cercare di bilanciare le partizioni in modo
 * equo e ridurre al minimo il numero di confronti richiesti.
 *
 * La funzione `quicksort` avvia il processo di ordinamento richiamando la funzione `runQuickSort`
 * passando la posizione iniziale e finale della lista come parametri.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 */
template <class T, class P>
void LinearList<T,P>::quicksort(){
    posizione inizio = primoLista();
    posizione fine = ultimoLista();
    runQuickSort(inizio, fine);
}
/**
 * @brief Funzione di partizione per l'algoritmo di quicksort.
 *
 * La partizione seleziona un elemento pivot e riorganizza gli elementi in modo che
 * gli elementi minori del pivot siano posizionati a sinistra e gli elementi maggiori
 * o uguali al pivot siano posizionati a destra. Alla fine della partizione, il pivot
 * viene collocato nella sua posizione finale.
 * Restituisce la posizione finale del pivot dopo la partizione.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 * @param inizio posizione posizione iniziale del sottoarray da partizionare
 * @param fine posizione posizione finale del sottoarray da partizionare
 * @return posizione finale del pivot dopo la partizione
 */
template <class T, class P>
typename LinearList<T,P>::posizione LinearList<T,P>::partition(posizione inizio, posizione fine){
    tipoelem pivot = leggiLista(fine);  // Scelgo l'elemento pivot come l'ultimo elemento della lista
    posizione i = inizio;               // posizione corrente in cui inserire il prossimo elemento minore del pivot

    for (posizione j = inizio; j != fine; j = succLista(j)) {
        if (leggiLista(j) <= pivot) {
            // Se l'elemento corrente è <= al pivot, lo scambio con l'elemento all'indice i
            // in modo da spostare l'elemento minore del pivot a sinistra
            scambiaElementi(i, j);
            i = succLista(i);
        }
    }

    scambiaElementi(i, fine);       // inserisco il pivot dopo l'ultimo elemento minore trovato
    return i;                       // i è l'indice del pivot dopo la partizione
}
/**
 * @brief Funzione ricorsiva utilizzata per eseguire l'algoritmo Quick Sort sulla lista.
 *
 * La funzione suddivide la lista in due parti rispetto al pivot e richiama
 * ricorsivamente se stessa per ordinare le due parti.
 *
 * @tparam T Il tipo generico degli elementi nella lista.
 * @tparam P Il tipo generico utilizzato per la posizione nella lista.
 * @param inizio posizione iniziale del sottoarray da ordinare
 * @param fine posizione finale del sottoarray da ordinare
 */
template <class T, class P>
void LinearList<T,P>::runQuickSort(posizione inizio, posizione fine){
    // se inizio==fine allora la sublist è composta al massimo da un elemento
    // o già completamente ordinata, quindi non è necessario eseguire altro.
    if (inizio != fine) {
        // Altrimenti si procede con la partizione della sotto-lista utilizzando un pivot
        posizione p = partition(inizio, fine); // p = pos del pivot
        if (inizio != p)
            // Vuol dire che ci sono elementi a sinistra del pivot che devono essere
            // ordinati. In questo modo, verrà eseguito il quick sort sulla
            // sotto-lista a sinistra del pivot.
            runQuickSort(inizio, precLista(p));
        if (fine != p)
            // Vuol dire che ci sono elementi a destra del pivot che devono essere
            // ordinati. In questo modo, verrà eseguito il quick sort sulla
            // sotto-lista a destra del pivot.
            runQuickSort(succLista(p), fine);
    }
}

#endif //LIST_LINEARLIST_H