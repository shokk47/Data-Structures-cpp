#include <iostream>
#include "QueuePtr.h"
#include "QueueVector.h"

void runTestsPtr() {
    QueuePtr<int> queue;

    // Test isEmpty() - Queue is initially empty
    if (queue.codaVuota()) {
        std::cout << "Test Passed: isEmpty() - Queue is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Queue is not empty\n";
    }

    // Test enqueue() and peek()
    queue.incoda(1);
    queue.incoda(2);
    queue.incoda(3);

    // Test getLength()
    if (queue.lunghezza() == 3) {
        std::cout << "Test Passed: getLength() - Queue length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Queue length is incorrect\n";
    }

    // Test peek()
    if (queue.leggiCoda() == 1) {
        std::cout << "Test Passed: peek() - Front of queue is correct\n";
    } else {
        std::cout << "Test Failed: peek() - Front of queue is incorrect\n";
    }

    // Test exists()
    if (queue.ricercaElemento(2)) {
        std::cout << "Test Passed: exists() - Element 2 exists in queue\n";
    } else {
        std::cout << "Test Failed: exists() - Element 2 does not exist in queue\n";
    }

    // Test dequeue()
    queue.fuoriCoda();
    if (queue.lunghezza() == 2 && queue.leggiCoda() == 2) {
        std::cout << "Test Passed: dequeue() - Element dequeued correctly\n";
    } else {
        std::cout << "Test Failed: dequeue() - Element not dequeued correctly\n";
    }

    // Test operator=()
    QueuePtr<int> anotherQueue = queue;
    if (anotherQueue == queue) {
        std::cout << "Test Passed: operator=() - Queue assignment is correct\n";
    } else {
        std::cout << "Test Failed: operator=() - Queue assignment is incorrect\n";
    }

    // Test operator!=()
    QueuePtr<int> differentQueue;
    if (differentQueue != queue) {
        std::cout << "Test Passed: operator!=() - Queues are different\n";
    } else {
        std::cout << "Test Failed: operator!=() - Queues are not different\n";
    }

    // Test clear()
    queue.clear();
    if (queue.codaVuota()) {
        std::cout << "Test Passed: clear() - Queue is empty after clearing\n";
    } else {
        std::cout << "Test Failed: clear() - Queue is not empty after clearing\n";
    }

    // Test enqueue() after clear()
    queue.incoda(4);
    if (!queue.codaVuota() && queue.lunghezza() == 1 && queue.leggiCoda() == 4) {
        std::cout << "Test Passed: enqueue() after clear() - Element enqueued correctly\n";
    } else {
        std::cout << "Test Failed: enqueue() after clear() - Element not enqueued correctly\n";
    }
}

void runTestsVector() {
    QueueVector<int> queue;

    // Test isEmpty() - Queue is initially empty
    if (queue.codaVuota()) {
        std::cout << "Test Passed: isEmpty() - Queue is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Queue is not empty\n";
    }

    // Test enqueue() and peek()
    queue.incoda(1);
    queue.incoda(2);
    queue.incoda(3);

    // Test getLength()
    if (queue.lunghezza() == 3) {
        std::cout << "Test Passed: getLength() - Queue length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Queue length is incorrect\n";
    }

    // Test peek()
    if (queue.leggiCoda() == 1) {
        std::cout << "Test Passed: peek() - Front of queue is correct\n";
    } else {
        std::cout << "Test Failed: peek() - Front of queue is incorrect\n";
    }

    // Test exists()
    if (queue.ricercaElemento(2)) {
        std::cout << "Test Passed: exists() - Element 2 exists in queue\n";
    } else {
        std::cout << "Test Failed: exists() - Element 2 does not exist in queue\n";
    }

    // Test dequeue()
    queue.fuoriCoda();
    if (queue.lunghezza() == 2 && queue.leggiCoda() == 2) {
        std::cout << "Test Passed: dequeue() - Element dequeued correctly\n";
    } else {
        std::cout << "Test Failed: dequeue() - Element not dequeued correctly\n";
    }

    // Test operator=()
    QueueVector<int> anotherQueue = queue;
    if (anotherQueue == queue) {
        std::cout << "Test Passed: operator=() - Queue assignment is correct\n";
    } else {
        std::cout << "Test Failed: operator=() - Queue assignment is incorrect\n";
    }

    // Test operator!=()
    QueueVector<int> differentQueue;
    if (differentQueue != queue) {
        std::cout << "Test Passed: operator!=() - Queues are different\n";
    } else {
        std::cout << "Test Failed: operator!=() - Queues are not different\n";
    }

    // Test clear()
    queue.clear();
    if (queue.codaVuota()) {
        std::cout << "Test Passed: clear() - Queue is empty after clearing\n";
    } else {
        std::cout << "Test Failed: clear() - Queue is not empty after clearing\n";
    }
    // Test enqueue() after clear()
    queue.incoda(4);
    if (!queue.codaVuota() && queue.lunghezza() == 1 && queue.leggiCoda() == 4) {
        std::cout << "Test Passed: enqueue() after clear() - Element enqueued correctly\n";
    } else {
        std::cout << "Test Failed: enqueue() after clear() - Element not enqueued correctly\n";
    }
}

int main() {
    cout << "RUN TESTS PTR\n";
    runTestsPtr();
    cout << "RUN TESTS VECTOR\n";
    runTestsVector();
}
