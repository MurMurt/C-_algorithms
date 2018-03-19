// Автор: Ильнур Гатауллин

/*
 * Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 * ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
 */

#include <iostream>
#include <assert.h>

// Возвращает индекс ближайшего элемента в массива array к числу number
int findIndex( const int* array, int arrayLength, int number );

int main()
{
    int aLength = 0;
    std::cin >> aLength;
    assert( aLength > 0 );

    int* aSortedList = new int[aLength];
    for( int i = 0; i < aLength; ++i ) {
        std::cin >> aSortedList[i];
        if( aSortedList[i] < 0 ) {
            delete[] aSortedList;
            assert( false );
        }
    }
    int bLength = 0;
    std::cin >> bLength;
    assert( bLength > 0 );

    // Ввод элементов массива B и нахождение индекса ближайшего соседа
    int number = 0;
    for( int i = 0; i < bLength; ++i ) {
        std::cin >> number;
        if( number < 0 ) {
            delete[] aSortedList;
            assert( false );
        }
        std::cout << findIndex( aSortedList, aLength, number ) << " ";
    }
    delete[] aSortedList;
    return 0;
}


int findIndex( const int* array, int arrayLength, int number )
{
    int leftBorder = 0;
    int rightBorder =  arrayLength > 1 ? 1: arrayLength - 1;
    // Переменная для хранения значения степени 2
    int pow2 = 2;
    int middle = 0;
    // Определение границ по степени 2
    while( array[rightBorder] < number) {
        leftBorder = rightBorder;
        pow2 *= 2;
        if( pow2 > arrayLength ) {
            rightBorder = arrayLength - 1;
            break;
        } else {
            rightBorder = pow2 - 1;
        }
    }

    // Бинарный поиск ближайшего соседа
    // Пока не будут найдены минимальные границы
    while( rightBorder - leftBorder > 1 ) {
        middle = ( leftBorder + rightBorder ) / 2;
        if( array[middle] < number ) {
            leftBorder = middle;
        } else if( number < array[middle] ) {
            rightBorder = middle;
        }
        else {
            return middle;
        }
    }
    // Поиск ближайшего из 2х финальных границ
    if( abs(array[leftBorder] - number ) > abs( array[rightBorder] - number) ) {
        return rightBorder;
    }
    return leftBorder;
}