#include <iostream>
#include <assert.h>

class Stack {
public:
    Stack();
    ~Stack();
    void Push(int value);
    int Pop();
    bool IsEmpty();
    void resize();
private:
    int* data;
    int size;
    int capacity;
};

class CQueue {
public:
//    CQueue();
    void PushBack(int value);
    int PopFront();
    bool IsEmpty();
private:
    Stack inputStack;
    Stack outputStack;
};

//===========================================================//
//                          MAIN_START
//===========================================================//

int main() {
    CQueue queue;
    int countOfCommands = 0;
    std::cin >> countOfCommands;
    for (int i = 0; i < countOfCommands; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch (command) {
            case 2:
                if( queue.IsEmpty() && value != -1 || !queue.IsEmpty() && queue.PopFront() != value ) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                queue.PushBack(value);
                break;
            default:
                assert(false);
        }
    }
    std::cout << "YES";
    return 0;
}

//===========================================================//
//                          MAIN_END
//===========================================================//


Stack::Stack() : size(0), capacity(2) {
    data = new int[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::Push(int value) {
    if (size + 1 >= capacity) {
        resize();
        data[size++] = value;
    } else {
        data[size++] = value;
    }
}

bool Stack::IsEmpty() {
    return size == 0;
}

int Stack::Pop() {
    if (!IsEmpty()) {
        return data[--size];
    }
    return -1;
}

void Stack::resize() {
    int* newData = new int[capacity + capacity / 2];
    capacity += capacity / 2;
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void CQueue::PushBack(int value) {
    inputStack.Push(value);
}

int CQueue::PopFront() {
    if (outputStack.IsEmpty()) {
        while (!inputStack.IsEmpty()) {
            outputStack.Push(inputStack.Pop());
        }
    }
    return outputStack.Pop();
}

bool CQueue::IsEmpty() {
    return inputStack.IsEmpty() && outputStack.IsEmpty();
}