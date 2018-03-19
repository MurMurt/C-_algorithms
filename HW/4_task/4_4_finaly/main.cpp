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
    Node()
    {
        value = 0;
        index = 0;
    }
};
bool operator < (const Node& node1, const Node& node2)
{
    return node1.value < node2.value;
}

template <class T>
class CHeap
{
public:
    CHeap();
    explicit CHeap( int heapCapacity );
    ~CHeap();
    void FillHeap( T* element );  // Добавление элемента в кучу без востановления свойств кучи
    void AddElementToHeap( T* element );
    void BuildHeap();
    T* GetTop() const;
    void DeleteTop();

private:
    void siftUp(int index);
    void siftDown( int index );

    int heapCapacity;
    int heapSize;
    T* heap;
};

int main()
{
    int arraySize = 0;
    std::cin >> arraySize;
    CHeap <Node> heap = CHeap <Node>( arraySize );

    int* unsortedArray = new int[arraySize];
    for( int i = 0; i < arraySize; ++i ) {
        std::cin >> unsortedArray[i];
    }
    int windowSize = 0;
    std::cin >> windowSize;
    Node temp;
    for( int i = 0; i < windowSize; ++i ) {
        temp.value = unsortedArray[i];
        temp.index = i;
        heap.FillHeap( &temp );
    }
    heap.BuildHeap();

    int counter = 0;
    int ind = windowSize;
//    Node* res = heap.GetTop();
    while( counter != arraySize - windowSize + 1 ) {
        Node* res = heap.GetTop();
        while( res->index <= ind - windowSize - 1 ) {
            heap.DeleteTop();
            res = heap.GetTop();
        }
        std::cout << res->value << " ";
        ++counter;
        if( ind < arraySize ) {
            temp.value = unsortedArray[ind];
            temp.index = ind;
            heap.AddElementToHeap( &temp );
        }
        ++ind;
    }
    delete[] unsortedArray;
}

template <class T>
CHeap<T>::CHeap():heapCapacity( 0 ), heapSize( 0 ), heap( nullptr )
{
}

template <class T>
CHeap<T>::CHeap( int heapCapacity ): heapCapacity( heapCapacity ), heapSize( 0 )
{
    heap = new T[heapCapacity];
}

template <class T>
CHeap<T>::~CHeap()
{
    delete[] heap;
}

template <class T>
void CHeap<T>::FillHeap( T* element )
{
    if( heapSize < heapCapacity ) {
        heap[heapSize++] = *element;
    }
}
template <class T>
void CHeap<T>::siftDown( int index ) {
    int ind = index;
    while( true ) {
        int leftChildIndex = ind * 2 + 1;
        int rightChildIndex = ind * 2 + 2;

        int largestElemIndex = ind;

        if( leftChildIndex < heapSize && heap[ind] < heap[leftChildIndex] ) {
            largestElemIndex = leftChildIndex;
        }
        if( rightChildIndex < heapSize && heap[largestElemIndex] < heap[rightChildIndex] ) {
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

template <class T>
void CHeap<T>::siftUp( int index )
{
    int child = index;
    while( child > 0 ) {
        int parent = ( child - 1 ) / 2;
        // a <= b  -->  !(b < a)
        if( !( heap[parent] < heap[child] ) ) {
            return;
        }
        std::swap(heap[child], heap[parent]);
        child = parent;
    }
}

template <class T>
void CHeap<T>::BuildHeap()
{
    for( int i = heapSize / 2 - 1; i >= 0; --i ) {
        siftDown( i );
    }
}
template <class T>
T* CHeap<T>::GetTop() const
{
    return &heap[0];
}

template <class T>
void CHeap<T>::DeleteTop()
{
    heap[0] = heap[--heapSize];
    siftDown( 0 );
}

template <class T>
void CHeap<T>::AddElementToHeap( T* element )
{
    if( heapSize < heapCapacity ) {
        heap[heapSize] = *element;
        siftUp( heapSize++ );
    }
}