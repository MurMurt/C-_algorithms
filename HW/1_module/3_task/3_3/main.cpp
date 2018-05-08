/*
 * следует написать структуру данных, обрабатывающую команды push* и pop*.
 * Формат входных данных.
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 * Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных,
 * то ожидается “-1”.
 * Формат выходных данных.
 * Требуется напечатать YES - если все ожидаемые значения совпали.
 * Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 */

#include <iostream>
#include <assert.h>

class Stack {
public:
    Stack();
    ~Stack();
    void Push( int value );
    int Pop();
    bool IsEmpty() const;

private:
    void resize();
    int* data;
    int size;
    int capacity;
};

class CQueue {
public:
    void PushBack(int value);
    int PopFront();
    bool IsEmpty() const;
private:
    Stack inputStack;
    Stack outputStack;
};


//================================================================================//

int main()
{
    CQueue queue;
    int countOfCommands = 0;
    std::cin >> countOfCommands;
    for( int i = 0; i < countOfCommands; ++i ) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch( command) {
            case 2:
                if( queue.IsEmpty() && value != -1 || !queue.IsEmpty() && queue.PopFront() != value ) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                queue.PushBack( value );
                break;
            default:
//                assert( false );
                break;
        }
    }
    std::cout << "YES";
    return 0;
}

//================================================================================//


Stack::Stack() : size(0), capacity(2)
{
    data = new int[capacity];
}

Stack::~Stack()
{
    delete[] data;
}

void Stack::Push(int value)
{
    if( size >= capacity ) {
        resize();
    }
    data[size++] = value;
}

bool Stack::IsEmpty() const
{
    return size == 0;
}

int Stack::Pop()
{
    assert(!IsEmpty());
    return data[--size];
}

void Stack::resize()
{
    int* newData = new int[capacity + capacity / 2];
    capacity += capacity / 2;
    for( int i = 0; i < size; ++i ) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void CQueue::PushBack( int value )
{
    inputStack.Push( value );
}

int CQueue::PopFront()
{
    if( outputStack.IsEmpty() ) {
        while( !inputStack.IsEmpty() ) {
            outputStack.Push( inputStack.Pop() );
        }
    }
    return outputStack.Pop();
}

bool CQueue::IsEmpty() const
{
    return inputStack.IsEmpty() && outputStack.IsEmpty();
}