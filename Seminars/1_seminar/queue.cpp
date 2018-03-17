/*
 *
 *  Сегодня мы писали очередь, реализованную с помощью односвязного списка.
 *
 */

#include <iostream>
#include <assert.h>

class CQueue {
public:
    ~CQueue();

    //Добавление в конец очереди
    void Push(int data);
    //Извлечение элемента. Если очередь пуста, assert
    int Pop();
    //Пуста ли очередь
    bool IsEmpty() const { return head == nullptr; };

private:
    // Узел односвзного списка
    struct CQueueNode {
        int Data;
        CQueueNode* Next;
        explicit CQueueNode(int data) : Data( data ), Next( nullptr ) {

        }
    };
    CQueueNode* head = nullptr;
    CQueueNode* tail = nullptr;
};

CQueue::~CQueue() {
    while (head != nullptr) {
        CQueueNode* toDelete = head;
        head = head->Next;
        delete toDelete;
    }
}

void CQueue::Push(int data) {
    CQueueNode* newNode = new CQueueNode(data);
    if (head == nullptr) {
        assert( tail == nullptr);
        head = tail = newNode;
    } else {
        assert( tail != nullptr);
        tail->Next = newNode;
        tail = newNode;
    }
}

int CQueue::Pop() {
    assert(head != nullptr);
    assert(tail != nullptr);

    const int data = head->Data;
    //Узел который хотим удалить
    CQueueNode* toDelete = head;
    head = head->Next;
    // Если head равен нулю после сдвига, то обнулить tail
    if( head == nullptr) {
        tail = nullptr;
    }
    delete toDelete;

    return data;
}


int main() {

    int commandsCount = 0;
    std::cin >> commandsCount;
    assert( commandsCount >= 0);

    CQueue queue;
    for(int i = 0; i < commandsCount; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch( command ) {
            case 3:
                queue.Push( value );
                break;
            case 2:
                if( queue.IsEmpty() && value != -1 || !queue.IsEmpty() && queue.Pop() != value)  {
                    std::cout << "NO";
                    return 0;
                }
                break;
            default:
                break;
//                assert(false);
        }
    }
    std::cout << "YES";
    return 0;
}
