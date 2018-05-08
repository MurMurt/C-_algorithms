/*
 * Выполнил: Ильнур Гатауллин
 *
 * Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием.
 * Общее время работы алгоритма O(n log n).
 * 5_1. Реклама.
 * В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей
 * (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать
 * только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента
 * ухода из магазина.
 * В каждый момент времени может показываться только одна реклама.
 * Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода,
 * то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
 */
#include <iostream>
#include <cstring>


struct Visitor {
    int timeIn = 0;
    int timeOut = 0;
    Visitor(): timeIn( 0 ), timeOut( 0 )
    {
    }

    Visitor( int in, int out ): timeIn( in ), timeOut( out )
    {
    };
};

bool operator < ( const Visitor& vis1, const Visitor& vis2 )
{
    if( vis1.timeOut == vis2.timeOut ) {
        return vis1.timeIn > vis2.timeIn;
    }
    else {
        return vis1.timeOut < vis2.timeOut;
    }
}

// Функция слияния
template <class T>
void merge( T* firstList, int firstListLen, T* secondList, int secondListLen, T* bufferList );

// Сортировка слиянием
template <class T>
void mergeSort( T* list, int listLen );

// Функция подсчета количества реклам
int countOfAdds( Visitor* visitorsList, int listLen );

int main()
{
    int listLen = 0;
    std::cin >> listLen;
    Visitor* visitorsList = new Visitor[listLen];

    for( int i = 0; i < listLen; ++i) {
        int timeIn = 0;
        int timeOut = 0;
        std::cin >> timeIn >> timeOut;
        visitorsList[i] = Visitor( timeIn, timeOut );
    }
    std::cout << countOfAdds( visitorsList, listLen );
    delete[] visitorsList;
    return 0;
}

template <class T>
void mergeSort( T* list, int listLen )
{
    if( listLen <= 1 ) {
        return;
    }
    int firstPartLen = listLen / 2;
    int secondPartLen = listLen - firstPartLen;

    mergeSort( list, firstPartLen );
    mergeSort( list + firstPartLen, secondPartLen );

    T* bufferList = new T[listLen];

    merge( list, firstPartLen, list + firstPartLen, secondPartLen, bufferList );
    memcpy( list, bufferList, sizeof(T) * listLen );
    delete[] bufferList;
}

template <class T>
void merge( T* firstList, int firstListLen, T* secondList, int secondListLen, T* bufferList )
{
    int firstIter = 0;
    int secondIter = 0;
    int buffIter = 0;
    // Пока не дошли до конца одного из массивов
    while( firstIter < firstListLen && secondIter < secondListLen ) {
        if( firstList[firstIter] < secondList[secondIter] ) {
            bufferList[buffIter++] = firstList[firstIter++];
        } else {
            bufferList[buffIter++] = secondList[secondIter++];
        }
    }
    // Дописываем оставшиеся элементы
    while( firstIter < firstListLen ) {
        bufferList[buffIter++] = firstList[firstIter++];
    }
    while( secondIter < secondListLen ) {
        bufferList[buffIter++] = secondList[secondIter++];
    }
}

int countOfAdds( Visitor* visitorsList, int listLen )
{
    // Сортировка данных о посетителях по времени выхода
    mergeSort( visitorsList, listLen );

    int first = visitorsList[0].timeOut - 1;
    int last = visitorsList[0].timeOut;
    int count = 2;

    for( int i = 1; i < listLen; ++i ) {
        if ( visitorsList[i].timeIn > first ) {
            if( visitorsList[i].timeIn > last ) {
                count += 2;
                first = visitorsList[i].timeOut - 1;
                last = visitorsList[i].timeOut;
            } else {
                count++;
                first = last;
                last = visitorsList[i].timeOut;
                if ( first == last ) {
                    --first;
                    ++count;
                }
            }
        }
    }
    return count;
}