#include <iostream>
#include "LinkedList.h"

int main() {
    Linked_list<int> list;
    list.inserisciCoda(10);
    list.inserisciCoda(11);
    list.inserisciCoda(12);
    list.inserisciCoda(13);
    cout << list;
    return 0;
}
