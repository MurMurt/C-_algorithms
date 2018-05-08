//  Автор: Ильнур Гатауллин

/*
 * “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 * затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.)
 * Необходимо определить номер уцелевшего. N, k ≤ 10000.
 */


#include <iostream>
#include <assert.h>

const int maxQuantity = 10000;

int main()
{
    int N = 0;
    int k = 0;
    assert( 0 < N <= maxQuantity );
    assert( 0 < k <= maxQuantity );

    std::cin >> N >> k;
    // Массив войнов (номера с 1 до N)
    int *circleOfWarriors = new int[N];
    for( int i = 0; i < N; ++i ) {
        circleOfWarriors[i] = i + 1;
    }
    int countOfAliveWarriors = N;
    int indexOfKilledWarrior = 0;
    while( countOfAliveWarriors > 1 ) {
        // Вычисление номера война
        indexOfKilledWarrior = ( indexOfKilledWarrior + k - 1 ) % countOfAliveWarriors;

        //Перемещение живых войнов на место убитого
        for( int j = indexOfKilledWarrior; j < countOfAliveWarriors - 1; ++j ) {
            circleOfWarriors[j] = circleOfWarriors[j+1];
        }
            --countOfAliveWarriors;
    }
    std::cout << circleOfWarriors[0] << std::endl;
    delete[] circleOfWarriors;
    return 0;
}