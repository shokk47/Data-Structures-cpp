#include <iostream>
#include "ClosedHash.h"
#include "../List/VectorList.h"
#include <string>


using namespace std;

void testClosedHash() {
    ClosedHash<int, string> dictionary;

    // Verifica che il dizionario sia inizialmente vuoto
    if (dictionary.dizionarioVuoto()) {
        cout << "Il dizionario e' inizialmente vuoto." << endl;
    } else {
        cout << "ERRORE: Il dizionario non e' inizialmente vuoto." << endl;
    }

    if (dictionary.lunghezza() == 0) {
        cout << "Il dizionario ha dimensione 0." << endl;
    } else {
        cout << "ERRORE: Il dizionario ha dimensione diversa da 0." << endl;
    }

    // Inserimento di coppie nel dizionario
    Couple<int, string> couple1(1, "One");
    Couple<int, string> couple2(2, "Two");
    Couple<int, string> couple3(3, "Three");

    dictionary.inserisci(couple1);
    dictionary.inserisci(couple2);
    dictionary.inserisci(couple3);

    cout << dictionary << endl;

    ClosedHash<int, string> d2 = dictionary;
    cout << d2 << endl;

    if (d2 == dictionary) {
        cout << "I dizionari sono uguali" << endl;
    } else {
        cout << "ERRPRE: I dizionari sono diversi" << endl;
    }

    // Verifica che il dizionario non sia più vuoto
    if (!dictionary.dizionarioVuoto()) {
        cout << "Il dizionario non e' vuoto dopo l'inserimento delle coppie." << endl;
    } else {
        cout << "ERRORE: Il dizionario e' vuoto dopo l'inserimento delle coppie." << endl;
    }

    if (dictionary.lunghezza() == 3) {
        cout << "Il dizionario ha dimensione 3 dopo l'inserimento delle coppie." << endl;
    } else {
        cout << "ERRORE: Il dizionario ha dimensione diversa da 3 dopo l'inserimento delle coppie." << endl;
    }

    // Verifica l'ottenimento di un elemento dal dizionario
    string value1 = dictionary.recupera(1);
    string value2 = dictionary.recupera(2);
    string value3 = dictionary.recupera(3);

    if (value1 == "One") {
        cout << "Il valore associato alla chiave 1 e' corretto." << endl;
    } else {
        cout << "ERRORE: Il valore associato alla chiave 1 e' errato." << endl;
    }

    if (value2 == "Two") {
        cout << "Il valore associato alla chiave 2 e' corretto." << endl;
    } else {
        cout << "ERRORE: Il valore associato alla chiave 2 e' errato." << endl;
    }

    if (value3 == "Three") {
        cout << "Il valore associato alla chiave 3 e' corretto." << endl;
    } else {
        cout << "ERRORE: Il valore associato alla chiave 3 e' errato." << endl;
    }

    // Verifica che una chiave esista nel dizionario
    if (dictionary.appartiene(1)) {
        cout << "Il dizionario contiene la chiave 1." << endl;
    } else {
        cout << "ERRORE: Il dizionario non contiene la chiave 1." << endl;
    }

    if (dictionary.appartiene(2)) {
        cout << "Il dizionario contiene la chiave 2." << endl;
    } else {
        cout << "ERRORE: Il dizionario non contiene la chiave 2." << endl;
    }

    if (dictionary.appartiene(3)) {
        cout << "Il dizionario contiene la chiave 3." << endl;
    } else {
        cout << "ERRORE: Il dizionario non contiene la chiave 3." << endl;
    }

    if (!dictionary.appartiene(4)) {
        cout << "Il dizionario non contiene la chiave 4." << endl;
    } else {
        cout << "ERRORE: Il dizionario contiene la chiave 4." << endl;
    }

    // Verifica l'aggiornamento di un elemento nel dizionario
    dictionary.aggiorna(1, "New One");

    string updatedValue1 = dictionary.recupera(1);

    if (updatedValue1 == "New One") {
        cout << "Il valore associato alla chiave 1 e' stato correttamente aggiornato." << endl;
    } else {
        cout << "ERRORE: Il valore associato alla chiave 1 non e' stato correttamente aggiornato." << endl;
    }

    // Verifica la rimozione di un elemento dal dizionario
    dictionary.cancella(2);

    if (!dictionary.appartiene(2)) {
        cout << "La chiave 2 e' stata correttamente rimossa dal dizionario." << endl;
    } else {
        cout << "ERRORE: La chiave 2 non e' stata rimossa correttamente dal dizionario." << endl;
    }

    // Verifica che il dizionario sia correttamente ripulito
    dictionary.clear();

    if (dictionary.dizionarioVuoto()) {
        cout << "Il dizionario e' stato correttamente ripulito e risulta vuoto." << endl;
    } else {
        cout << "ERRORE: Il dizionario non e' stato correttamente ripulito." << endl;
    }

    if (dictionary.lunghezza() == 0) {
        cout << "Il dizionario ha dimensione 0 dopo essere stato ripulito." << endl;
    } else {
        cout << "ERRORE: Il dizionario ha dimensione diversa da 0 dopo essere stato ripulito." << endl;
    }
}

int main() {
    testClosedHash();
    return 0;
}