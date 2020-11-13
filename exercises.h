#ifndef EXERCISES_H
#define EXERCISES_H

#include <iostream>
#include "afd.h"

void exercise1()
{
    std::cout<<"EXERCISE 1: Brzozowski\n";
    int n, iState, nFStates;
    std::cin >> n >> iState >> nFStates;
    std::unordered_set<int> fState;
    while (nFStates--) {
        int i{};
        std::cin >> i;
        fState.insert(i);
    }
    dfa myAfd(iState, fState);

    int tmp = 2 * n;
    while (tmp--) {
        int p, a, q;
        std::cin >> p >> a >> q;
        myAfd.addTransition(p, a, q);
    }
    
    auto min = myAfd.minimization();
    min.print();
}

#endif