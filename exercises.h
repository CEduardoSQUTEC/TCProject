#ifndef EXERCISES_H
#define EXERCISES_H

#include "afd.cpp"

dfa buildAFN();
void exercise1(dfa &myAfd);
void exercise2(dfa &myAfd);

void execute()
{
    std::cout<<"PROYECTO TEORÍA DE LA COMPUTACIÓN\n\n";
    auto a = buildAFN();
    exercise1(a);
    exercise2(a);
}

dfa buildAFN()
{
    std::cout<<"Inserte un AFN:\n";
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
    return myAfd;
}

void exercise1(dfa &myAfd)
{
    std::cout<<"\nEJERCICIO 1: Brzozowski\n";
    auto min = myAfd.minimization();
    min.print();
}

void exercise2(dfa &myAfd)
{
    std::cout<<"\nEJERCICIO 2: Algoritmo de Equivalencia de estados\n";
    auto res = myAfd.equivalentStates();
    for(int  i = 0; i < res.size(); i++)
        {
            for(int j = 0; j < res.size();j++)
                std::cout<<res[i][j]<<' ';
            std::cout<<'\n';
        }
}

#endif