#include <iostream>
#include "QueueVector.h"
#include "QueuePtr.h"
int main() {
    std::cout << "CODA PTR:" << std::endl;
    QueuePtr<int> q;
    q.enqueue(0);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << q << std::endl;
    q.dequeue();
    std::cout << q << std::endl;
    if (q.exists(0)) {
        std::cout << "0 exists" << std::endl;
    }
    else {
        std::cout << "0 doesn't exist" << std::endl;
    }
    if (q.exists(3))
        std::cout << "3 exists" << std::endl;
    else
        std::cout << "3 doesn't exist" << std::endl;
    std::cout << "head: " << q.peek() << std::endl;
    for (int i=4; i<15; i++){
        q.enqueue(i);
    }
    std::cout << q << std::endl;
    std::cout << "lenght: " << q.getLength() << std::endl;


    std::cout << "\nCODA VECTOR:" << std::endl;
    QueueVector<int> v;
    v.enqueue(0);
    v.enqueue(1);
    v.enqueue(2);
    v.enqueue(3);
    std::cout << v << std::endl;
    v.dequeue();
    std::cout << v << std::endl;
    if (v.exists(0)) {
        std::cout << "0 exists" << std::endl;
    }
    else {
        std::cout << "0 doesn't exist" << std::endl;
    }
    if (v.exists(3))
        std::cout << "3 exists" << std::endl;
    else
        std::cout << "3 doesn't exist" << std::endl;
    std::cout << "head: " << v.peek() << std::endl;
    for (int i=4; i<15; i++){
        v.enqueue(i);
    }
    std::cout << v << std::endl;
    std::cout << "lenght: " << q.getLength() << std::endl;
    return 0;
}
