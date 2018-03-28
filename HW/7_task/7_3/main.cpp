#include <iostream>
#include <assert.h>

// Количество битов - 1
const int countOfbites = 63;

// Проверка на наличие 1 в числе num на позиции pos
bool bitInPos(unsigned long long num, int pos)
{
    bool res = (num >> pos) & 1;
    return res;
}

// Сортировка по старшему биту (MSD)
void quickBinarySort(unsigned long long* nums, int start,int size, int bitePos)
{
    // индекс начала массива
    int i = start;
    // индекс конца массива
    int j = start + size - 1;

    if( size < 2 || bitePos < 1) {
        return;
    }

    while( j != i ) {
        // пока не найдено число с 1 в позиции bitPos
        while( !bitInPos(nums[i], bitePos) && i < j) {
            ++i;
        }
        // пока не найдено число с 0 в позиции bitPos
        while( bitInPos(nums[j], bitePos) && i < j) {
            --j;
        }
        if( i != j ) {
            std::swap( nums[i], nums[j] );
        }
    }
    // Если число в массиве под индексом j не имело 1 в позиции bitPos, возвращаем j на 1 назад
    if( !bitInPos(nums[j], bitePos)) {
        j++;
    }

    quickBinarySort(nums, start, j - start, bitePos - 1);
    quickBinarySort(nums, j, size - (j - start), bitePos - 1);

}

int main() {
    int size = 6;
    std::cin >> size;
    assert(size > 0);
    unsigned long long *nums = new unsigned long long[size];

    for( int i = 0; i < size; ++i ) {
        std::cin >> nums[i];
    }

    quickBinarySort(nums, 0, size, countOfbites);

    for( int i = 0; i < size; ++i) {
        std::cout << nums[i] << " ";
    }
    delete[] nums;
    return 0;
}