#include <iostream>
#include <assert.h>

#define MAX_QUANTITY 10000

int main() {
    int N = 0;
    int k = 0;
    assert(0 < N <= MAX_QUANTITY);
    assert(0 < k <= MAX_QUANTITY);

    std::cin >> N >> k;
    int *circlOfWarriors = new int[N];
    for (int i = 0; i < N; ++i) {
        circlOfWarriors[i] = i + 1;
    }
    int countOfAliveWarriors = N;
    int i = 0;
    while( countOfAliveWarriors > 1) {
        i = (i + k - 1) % countOfAliveWarriors;

        for (int j = i; j < countOfAliveWarriors - 1; ++j) {
            circlOfWarriors[j] = circlOfWarriors[j+1];
        }
            --countOfAliveWarriors;
        }
    std::cout << circlOfWarriors[0] << std::endl;
    delete[] circlOfWarriors;
    return 0;
}