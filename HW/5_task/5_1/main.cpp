#include <iostream>
#include <cstring>

struct Visitor {
    int timeIn = 0;
    int timeOut = 0;
    Visitor()
    {
        timeIn = 0;
        timeOut = 0;
    }

    Visitor(int in, int out): timeIn(in), timeOut(out)
    {
    };
};

bool operator < ( const Visitor& vis1, const Visitor& vis2 )
{
    if (vis1.timeOut == vis2.timeOut){
        return vis1.timeIn > vis2.timeIn;
    }
    else {
        return vis1.timeOut < vis2.timeOut;
    }
}

std::ostream& operator << (std::ostream& os, const Visitor& vs)
{
    os << "[" << vs.timeIn << " | " << vs.timeOut << ']';
    return os;
}

template <class T>
void merge( T* firstList, int firstListLen, T* secondList, int secondListLen, T* bufferList);

template <class T>
void mergeSort(T* list, int listLen);


int main() {
    int listLen = 0;
    std::cin >> listLen;
    Visitor* list = new Visitor[listLen];

    for( int i = 0; i < listLen; ++i) {
        int timeIn = 0;
        int timeOut = 0;
        std::cin >> timeIn >> timeOut;
        list[i] = Visitor(timeIn, timeOut);
    }

    mergeSort(list, listLen);


    int first = list[0].timeOut - 1;
    int last = list[0].timeOut;
    int count = 2;
    int may_be = -1;

    for (int i = 1; i < listLen; ++i) {
        int b = list[i].timeIn;
        if (list[i].timeIn > first) {
            if (list[i].timeIn > last) {
                count += 2;
                first = list[i].timeOut - 1;
                last = list[i].timeOut;
            } else {
                count++;
                first = last;
                last = list[i].timeOut;
                if (first == last) {
                    --first;
                    ++count;
                }

            }
        }
    }
    std::cout << count;
    delete[] list;
    return 0;
}

template <class T>
void mergeSort(T* list, int listLen)
{
    if( listLen <= 1) {
        return;
    }
    int firstPartLen = listLen / 2;
    int secondPartLen = listLen - firstPartLen;

    mergeSort(list, firstPartLen);
    mergeSort(list + firstPartLen, secondPartLen);

    T* bufferList = new T[listLen];

    merge(list, firstPartLen, list + firstPartLen, secondPartLen, bufferList);
    memcpy(list, bufferList, sizeof(T) * listLen);
    delete[] bufferList;
}

template <class T>
void merge( T* firstList, int firstListLen, T* secondList, int secondListLen, T* bufferList)
{
    int firstIter = 0;
    int secondIter = 0;
    int buffIter = 0;

    while( firstIter < firstListLen && secondIter < secondListLen ) {
        if( firstList[firstIter] < secondList[secondIter] ) {
            bufferList[buffIter++] = firstList[firstIter++];
        } else {
            bufferList[buffIter++] = secondList[secondIter++];
        }
    }
    while( firstIter < firstListLen ) {
        bufferList[buffIter++] = firstList[firstIter++];
    }
    while( secondIter < secondListLen ) {
        bufferList[buffIter++] = secondList[secondIter++];
    }
}
