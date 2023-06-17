#include <iostream>
#include "QueuePtr.h"
#include "QueueVector.h"

void runTestsPtr() {
    QueuePtr<int> queue;

    // Test isEmpty() - Queue is initially empty
    if (queue.isEmpty()) {
        std::cout << "Test Passed: isEmpty() - Queue is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Queue is not empty\n";
    }

    // Test enqueue() and peek()
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    // Test getLength()
    if (queue.getLength() == 3) {
        std::cout << "Test Passed: getLength() - Queue length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Queue length is incorrect\n";
    }

    // Test peek()
    if (queue.peek() == 1) {
        std::cout << "Test Passed: peek() - Front of queue is correct\n";
    } else {
        std::cout << "Test Failed: peek() - Front of queue is incorrect\n";
    }

    // Test exists()
    if (queue.exists(2)) {
        std::cout << "Test Passed: exists() - Element 2 exists in queue\n";
    } else {
        std::cout << "Test Failed: exists() - Element 2 does not exist in queue\n";
    }

    // Test dequeue()
    queue.dequeue();
    if (queue.getLength() == 2 && queue.peek() == 2) {
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
    if (queue.isEmpty()) {
        std::cout << "Test Passed: clear() - Queue is empty after clearing\n";
    } else {
        std::cout << "Test Failed: clear() - Queue is not empty after clearing\n";
    }

    // Test enqueue() after clear()
    queue.enqueue(4);
    if (!queue.isEmpty() && queue.getLength() == 1 && queue.peek() == 4) {
        std::cout << "Test Passed: enqueue() after clear() - Element enqueued correctly\n";
    } else {
        std::cout << "Test Failed: enqueue() after clear() - Element not enqueued correctly\n";
    }
}

void runTestsVector() {
    QueueVector<int> queue;

    // Test isEmpty() - Queue is initially empty
    if (queue.isEmpty()) {
        std::cout << "Test Passed: isEmpty() - Queue is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Queue is not empty\n";
    }

    // Test enqueue() and peek()
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    // Test getLength()
    if (queue.getLength() == 3) {
        std::cout << "Test Passed: getLength() - Queue length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Queue length is incorrect\n";
    }

    // Test peek()
    if (queue.peek() == 1) {
        std::cout << "Test Passed: peek() - Front of queue is correct\n";
    } else {
        std::cout << "Test Failed: peek() - Front of queue is incorrect\n";
    }

    // Test exists()
    if (queue.exists(2)) {
        std::cout << "Test Passed: exists() - Element 2 exists in queue\n";
    } else {
        std::cout << "Test Failed: exists() - Element 2 does not exist in queue\n";
    }

    // Test dequeue()
    queue.dequeue();
    if (queue.getLength() == 2 && queue.peek() == 2) {
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
    if (queue.isEmpty()) {
        std::cout << "Test Passed: clear() - Queue is empty after clearing\n";
    } else {
        std::cout << "Test Failed: clear() - Queue is not empty after clearing\n";
    }

    // Test enqueue() after clear()
    queue.enqueue(4);
    if (!queue.isEmpty() && queue.getLength() == 1 && queue.peek() == 4) {
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