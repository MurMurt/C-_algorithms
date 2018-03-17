/*
 * Дан массив натуральных чисел A[0..n), n не превосходит 100 000.
 * Так же задан размер некотрого окна (последовательно расположенных элементов массива)
 * в этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести
 * значение максимума в окне. Скорость работы O(n log n), память O(n).
 */

#include <iostream>


struct Node {
    int value;
    int index;
};

class CHeap
{
public:
    CHeap();
    explicit CHeap( int heapCapacity );
    ~CHeap();
    void FillHeap( int value );
    void AddElementToHeap( int value );
    void BuildHeap();
    Node* GetTop();
    void DeleteTop();
private:
    void siftUp(int index);
    void siftDown( int index );

    int heapCapacity;
    int heapSize;
    int lastValueIndex;
    Node* heap;
};

int main()
{
    int arraySize = 0;
    std::cin >> arraySize;
    CHeap heap = CHeap( arraySize );

    int* unsortedArray = new int[arraySize];
    for( int i = 0; i < arraySize; ++i ) {
        std::cin >> unsortedArray[i];
    }
    int windowSize = 0;
    std::cin >> windowSize;
    for( int i = 0; i < windowSize; ++i ) {
        heap.FillHeap( unsortedArray[i] );
    }
    heap.BuildHeap();

    int counter = 0;
    int ind = windowSize;
    while( counter != arraySize - windowSize + 1 ) {
        Node* res = heap.GetTop();
        while( res->index <= ind - windowSize - 1 ) {
            heap.DeleteTop();
            res = heap.GetTop();
        }
        std::cout << res->value << " ";
        ++counter;
        if( ind < arraySize ) {
            heap.AddElementToHeap( unsortedArray[ind] );
        }
        ++ind;
    }
    delete[] unsortedArray;
}


CHeap::CHeap():heapCapacity( 0 ), heapSize( 0 ), lastValueIndex( 0 ), heap( nullptr )
{
}

CHeap::CHeap( int heapCapacity ): heapCapacity( heapCapacity ), heapSize( 0 ), lastValueIndex( 0 )
{
    heap = new Node[heapCapacity];
}

CHeap::~CHeap()
{
    delete[] heap;
}

void CHeap::FillHeap( int value )
{
    if( heapSize < heapCapacity ) {
        heap[heapSize].value = value;
        heap[heapSize++].index = lastValueIndex++;
    }
}

void CHeap::siftDown( int index ) {
    int ind = index;
    while( true ) {
        int leftChildIndex = ind * 2 + 1;
        int rightChildIndex = ind * 2 + 2;

        int largestElemIndex = ind;

        if( leftChildIndex < heapSize && heap[leftChildIndex].value > heap[ind].value ) {
            largestElemIndex = leftChildIndex;
        }
        if( rightChildIndex < heapSize && heap[rightChildIndex].value > heap[largestElemIndex].value ) {
            largestElemIndex = rightChildIndex;
        }

        if( largestElemIndex != ind ) {
            std::swap( heap[ind], heap[largestElemIndex] );
            ind = largestElemIndex;
        } else {
            break;
        }
    }
}

void CHeap::siftUp( int index )
{
    int child = index;
    while( child > 0 ) {
        int parent = ( child - 1 ) / 2;
        if( heap[child].value <= heap[parent].value ) {
            return;
        }
        std::swap(heap[child], heap[parent]);
        child = parent;
    }
}

void CHeap::BuildHeap()
{
    for( int i = heapSize / 2 - 1; i >= 0; --i ) {
        siftDown( i );
    }
}

Node* CHeap::GetTop()
{
    Node res = heap[0];
    return &heap[0];
}

void CHeap::DeleteTop()
{
    heap[0] = heap[--heapSize];
    siftDown( 0 );
}

void CHeap::AddElementToHeap( int value )
{
    if( heapSize < heapCapacity ) {
        heap[heapSize].value = value;
        heap[heapSize].index = lastValueIndex++;
        siftUp( heapSize++ );
    }
}