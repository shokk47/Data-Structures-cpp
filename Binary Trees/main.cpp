#include <iostream>
#include "alberoBinario_Ptr.h"
int main() {
    AlberoBinario_ptr<int> albero;

    // Inserisci la radice dell'albero con valore 1
    albero.inserisciRadice(1);

    // Ottieni il nodo radice
    typename AlberoBinario_ptr<int>::nodo radice = albero.radice();

    // Inserisci i figli sinistro e destro alla radice
    albero.inserisciFiglioSinistro(radice, 2);
    albero.inserisciFiglioDestro(radice, 3);

    // Ottieni i nodi figli sinistro e destro
    typename AlberoBinario_ptr<int>::nodo figlioSinistro = albero.figlioSinistro(radice);
    typename AlberoBinario_ptr<int>::nodo figlioDestro = albero.figlioDestro(radice);

    // Inserisci figli ai nodi figlio sinistro e destro
    albero.inserisciFiglioSinistro(figlioSinistro, 4);
    albero.inserisciFiglioDestro(figlioSinistro, 5);
    albero.inserisciFiglioSinistro(figlioDestro, 6);
    albero.inserisciFiglioDestro(figlioDestro, 7);

    // Ottieni i nodi dei nuovi figli
    typename AlberoBinario_ptr<int>::nodo figlioSinistro2 = albero.figlioSinistro(figlioSinistro);
    typename AlberoBinario_ptr<int>::nodo figlioDestro2 = albero.figlioDestro(figlioSinistro);
    typename AlberoBinario_ptr<int>::nodo figlioSinistro3 = albero.figlioSinistro(figlioDestro);
    typename AlberoBinario_ptr<int>::nodo figlioDestro3 = albero.figlioDestro(figlioDestro);

    // Inserisci figli ai nodi figlio sinistro2 e figlio destro2
    albero.inserisciFiglioSinistro(figlioSinistro2, 8);
    albero.inserisciFiglioDestro(figlioSinistro2, 9);
    albero.inserisciFiglioSinistro(figlioDestro2, 10);
    albero.inserisciFiglioDestro(figlioDestro2, 11);

    // Inserisci figli ai nodi figlio sinistro3 e figlio destro3
    albero.inserisciFiglioSinistro(figlioSinistro3, 12);
    albero.inserisciFiglioDestro(figlioSinistro3, 13);
    albero.inserisciFiglioSinistro(figlioDestro3, 14);
    albero.inserisciFiglioDestro(figlioDestro3, 15);


    // Visualizza il numero di nodi nell'albero
    cout << "Numero di nodi: " << albero.ottieniNumeroNodi() << endl;
    albero.stampaSottoAlbero(albero.radice());
    cout << albero << endl;
    return 0;
}
