#include <iostream>
#include "Albero_ptr.h" // Assumi che il file "AlberoPtr.h" sia incluso correttamente

int main() {
    AlberoPtr<int> albero;
    // Inserisci la radice
    albero.inserisciRadice(1);

    // Inserisci il primo figlio della radice
    AlberoPtr<int>::nodo radice = albero.radice();
    albero.insPrimoFiglio(radice, 2);

    // Inserisci un altro figlio della radice
    albero.insPrimoFiglio(radice, 3);  // Questa chiamata genererà un'eccezione perché la radice ha già un primo figlio
    albero.insPrimoFiglio(radice, 113);  // Questa chiamata genererà un'eccezione perché la radice ha già un primo figlio

    AlberoPtr<int>::nodo primoFiglioRadice = albero.primoFiglio(radice);
    albero.insFratelloSuccessivo(primoFiglioRadice, 4);

    // inserisci figlio al primo figlio della radice
    albero.insPrimoFiglio(primoFiglioRadice, 5);
    // aggiungi fratelli al primo figlio della radice
    AlberoPtr<int>::nodo primoNipoteRadice = albero.primoFiglio(albero.primoFiglio(radice));
    albero.insPrimoFiglio(primoNipoteRadice, 6);
    //albero.cancellaSottoAlbero(radice);
    cout << "il numero dei nodi e' " << albero.ottieniNumeroNodi() << endl;
    albero.stampaSottoAlbero(radice);
    cout << "profondita' : " << albero.profonditaAlbero() << endl;
    cout << "larghezza : " << albero.larghezzaAlbero() << endl;
    return 0;
}
