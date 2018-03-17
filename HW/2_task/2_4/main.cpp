#include <iostream>
#include <assert.h>

int findIndex(const int* array, int arrayLength, int number);

int main() {
    int aLength = 0;

    std::cin >> aLength;
    assert(aLength > 0);

    int* aSortedList = new int[aLength];
    for ( int i = 0; i < aLength; ++i ) {
        std::cin >> aSortedList[i];
        if ( aSortedList[i] < 0 ) {
            delete[] aSortedList;
            assert(false);
        }
    }

    int bLength = 0;
    std::cin >> bLength;
    assert(bLength > 0);

    int number = 0;
    for ( int i = 0; i < bLength; ++i ) {
        std::cin >> number;
        if ( number < 0 ) {
            delete[] aSortedList;
            assert(false);
        }
        std::cout << findIndex(aSortedList, aLength, number) << " ";
    }
    delete[] aSortedList;

    return 0;
}


int findIndex(const int* array, int arrayLength, int number) {
    int leftBorder = 0;
    int rightBorder = arrayLength - 1;
    int middle = 0;
    while ( rightBorder - leftBorder > 1 ) {
        middle = (leftBorder + rightBorder) / 2;
        if (array[middle] < number) {
            leftBorder = middle;
        } else if (array[middle] > number) {
            rightBorder = middle;
        }
        else {
            return middle;
        }
    }
    if (abs(array[leftBorder] - number) > abs(array[rightBorder] - number)) {
        return rightBorder;
    }
    return leftBorder;
}