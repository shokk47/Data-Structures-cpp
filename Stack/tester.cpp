#include <iostream>
#include "StackVector.h"
#include "StackPtr.h"

void runTestsPtr() {
    StackPtr<int> stack;

    // Test isEmpty() - Stack is initially empty
    if (stack.pilaVuota()) {
        std::cout << "Test Passed: isEmpty() - Stack is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Stack is not empty\n";
    }

    // Test push() and top()
    stack.inpila(1);
    stack.inpila(2);
    stack.inpila(3);

    // Test getLength()
    if (stack.lunghezza() == 3) {
        std::cout << "Test Passed: getLength() - Stack length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Stack length is incorrect\n";
    }

    // Test top()
    if (stack.leggiPila() == 3) {
        std::cout << "Test Passed: top() - Top of stack is correct\n";
    } else {
        std::cout << "Test Failed: top() - Top of stack is incorrect\n";
    }

    // Test exist()
    if (stack.ricercaElemento(2)) {
        std::cout << "Test Passed: exist() - Element 2 exists in stack\n";
    } else {
        std::cout << "Test Failed: exist() - Element 2 does not exist in stack\n";
    }

    // Test pop()
    stack.fuoriPila();
    if (stack.lunghezza() == 2 && stack.leggiPila() == 2) {
        std::cout << "Test Passed: pop() - Element popped correctly\n";
    } else {
        std::cout << "Test Failed: pop() - Element not popped correctly\n";
    }

    // Test operator=()
    StackPtr<int> anotherStack;
    anotherStack = stack;
    if (anotherStack == stack) {
        std::cout << "Test Passed: operator=() - Stack assignment is correct\n";
    } else {
        std::cout << "Test Failed: operator=() - Stack assignment is incorrect\n";
    }

    // Test operator!=()
    StackPtr<int> differentStack;
    if (differentStack != stack) {
        std::cout << "Test Passed: operator!=() - Stacks are different\n";
    } else {
        std::cout << "Test Failed: operator!=() - Stacks are not different\n";
    }
}

void runTestsVector() {
    StackVector<int> stack;

    // Test isEmpty() - Stack is initially empty
    if (stack.pilaVuota()) {
        std::cout << "Test Passed: isEmpty() - Stack is initially empty\n";
    } else {
        std::cout << "Test Failed: isEmpty() - Stack is not empty\n";
    }

    // Test push() and top()
    stack.inpila(1);
    stack.inpila(2);
    stack.inpila(3);

    // Test getLength()
    if (stack.lunghezza() == 3) {
        std::cout << "Test Passed: getLength() - Stack length is correct\n";
    } else {
        std::cout << "Test Failed: getLength() - Stack length is incorrect\n";
    }

    // Test top()
    if (stack.leggiPila() == 3) {
        std::cout << "Test Passed: top() - Top of stack is correct\n";
    } else {
        std::cout << "Test Failed: top() - Top of stack is incorrect\n";
    }

    // Test exist()
    if (stack.ricercaElemento(2)) {
        std::cout << "Test Passed: exist() - Element 2 exists in stack\n";
    } else {
        std::cout << "Test Failed: exist() - Element 2 does not exist in stack\n";
    }

    // Test pop()
    stack.fuoriPila();
    if (stack.lunghezza() == 2 && stack.leggiPila() == 2) {
        std::cout << "Test Passed: pop() - Element popped correctly\n";
    } else {
        std::cout << "Test Failed: pop() - Element not popped correctly\n";
    }

    // Test operator=()
    StackVector<int> anotherStack;
    anotherStack = stack;
    if (anotherStack == stack) {
        std::cout << "Test Passed: operator=() - Stack assignment is correct\n";
    } else {
        std::cout << "Test Failed: operator=() - Stack assignment is incorrect\n";
    }

    // Test operator!=()
    StackVector<int> differentStack;
    if (differentStack != stack) {
        std::cout << "Test Passed: operator!=() - Stacks are different\n";
    } else {
        std::cout << "Test Failed: operator!=() - Stacks are not different\n";
    }
}
int main() {
    cout << "RUN TESTS PTR\n";
    runTestsPtr();
    cout << "RUN TESTS VECTOR\n";
    runTestsVector();
}
