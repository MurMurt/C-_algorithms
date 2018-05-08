// Автор: Ильнур Гатауллин
/* Описание:
 *
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
    // Добавление элемента в кучу без восстановления свойств кучи
    void FillHeap( T* element );
    // Добавление элемента в кучу с восстановлением свойства кучи
    void AddElementToHeap( T* element );
    // Постройка кучи
    void BuildHeap();
    // Возвращает верхний элемент кучи
    T* GetTop() const;
    // Удаляет верхний элемент и восстанавливает свойство кучи
    void DeleteTop();

private:
    // Спускает элемент, который меньше дочерних
    void siftUp(int index);
    // Поднимает элемент, который больше родительского
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
    // Количество выведенных максимумов
    int counter = 0;
    int ind = windowSize;
    while( counter != arraySize - windowSize + 1 ) {
        Node* res = heap.GetTop();
        // удаляем максимальный элемент, пока его индекс не окажется в пределах окна
        while( res->index <= ind - windowSize - 1 ) {
            heap.DeleteTop();
            res = heap.GetTop();
        }
        std::cout << res->value << " ";
        ++counter;
        // Добавление нового элемента в кучу при смещении окна
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

// Проталкивание элемента вниз
template <class T>
void CHeap<T>::siftDown( int index ) {
    int ind = index;
    while( true ) {
        int leftChildIndex = ind * 2 + 1;
        int rightChildIndex = ind * 2 + 2;

        int largestElemIndex = ind;
        // Ищем большего сына, если такой есть
        if( leftChildIndex < heapSize && heap[ind] < heap[leftChildIndex] ) {
            largestElemIndex = leftChildIndex;
        }
        if( rightChildIndex < heapSize && heap[largestElemIndex] < heap[rightChildIndex] ) {
            largestElemIndex = rightChildIndex;
        }
        // Если больший сын есть, то проталкиваем корень в него
        if( largestElemIndex != ind ) {
            std::swap( heap[ind], heap[largestElemIndex] );
            ind = largestElemIndex;
        } else {
            break;
        }
    }
}

// Проталкивание элемента наверх
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

// Построение кучи
template <class T>
void CHeap<T>::BuildHeap()
{
    for( int i = heapSize / 2 - 1; i >= 0; --i ) {
        siftDown( i );
    }
}

// Возвращает верхний элемент кучи
template <class T>
T* CHeap<T>::GetTop() const
{
    return &heap[0];
}

// Удаление верхнего элемента и восстанавление свойства кучи
template <class T>
void CHeap<T>::DeleteTop()
{
    heap[0] = heap[--heapSize];
    siftDown( 0 );
}

// Добавление элемента в кучу с восстановлением свойства кучи
template <class T>
void CHeap<T>::AddElementToHeap( T* element )
{
    if( heapSize < heapCapacity ) {
        heap[heapSize] = *element;
        siftUp( heapSize++ );
    }
}