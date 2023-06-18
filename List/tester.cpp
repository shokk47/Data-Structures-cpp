#include <iostream>
#include "LinkedList.h"
#include "VectorList.h"

int main() {
    Linked_list<int> linkedlist;
    linkedlist.inserisciCoda(0);
    linkedlist.inserisciCoda(1);
    linkedlist.inserisciCoda(2);
    linkedlist.inserisciCoda(3);
    linkedlist.inserisciCoda(4);
    linkedlist.inserisciCoda(5);
    linkedlist.inserisciCoda(6);
    cout << "new LinkedList: " << linkedlist;    // output: [0, 1, 2, 3, 4, 5, 6]

    // Individuare posizione di un elemento specifico:
    int el = 2;
    cout << "1) Il valore " << el << " si trova in pos: ";
    Linked_list<int>::posizione pos = linkedlist.primoLista();
    while(linkedlist.leggiLista(pos)!=el){
        pos = linkedlist.succLista(pos);
    }
    cout << linkedlist.leggiLista(pos) << endl;

    // Verifica presenza elemento
    int val = 51;
    cout << "2) " << val << " e' presente? ";
    if(linkedlist.ricercaElemento(val)==true)
        cout << "si" << endl;
    else cout << "no" << endl;

    // Modificare un elemento in una posizione specifica
    int posEl = 3;
    int newEl = 103;
    cout << "3) Modifico il valore in pos " << posEl << " assegnando " << newEl << endl;
    pos = linkedlist.primoLista();
    for(int i=0; i<posEl; i++){
        pos = linkedlist.succLista(pos);
    }
    linkedlist.scriviLista(newEl, pos);
    cout << "   Risultato: " << linkedlist;

    // Scambiare due elementi
    int firstPos = 4;
    int secondPos = 1;

    cout << "4) Scambio elemento in pos " << firstPos << " con elemento in pos " << secondPos << endl;

    Linked_list<int>::posizione fpos = linkedlist.primoLista();
    Linked_list<int>::posizione spos = linkedlist.primoLista();

    for(int i=0; i<firstPos; i++){
        fpos = linkedlist.succLista(fpos);
    }
    for(int i=0; i<secondPos; i++){
        spos = linkedlist.succLista(spos);
    }
    linkedlist.scambiaElementi(fpos,spos);
    cout << "   Risultato: " << linkedlist;

    // Ordinamento
    cout << "5) Ordinamento: ";
    linkedlist.quicksort();
    cout << linkedlist;
    return 0;
}
