#ifndef EXERCISES_H
#define EXERCISES_H

#include "afd.cpp"
#include <chrono>

dfa buildAFN();

void exercise1(dfa &myAfd);

void exercise2(dfa &myAfd);

void exercise3(dfa &myAfd);

void exercise5(dfa &myAfd);

void execute() {
    std::cout << "PROYECTO TEORÍA DE LA COMPUTACIÓN\n\n";
    int t;
    std::cout << "Ingrese el número de autómatas: ";
    std::cin >> t;
    while (t--) {
        auto a = buildAFN();
        exercise1(a);
//        exercise2(a);
//        exercise3(a);
        exercise5(a);
        std::cout << '\n';
    }
}

dfa buildAFN() {
    std::cout << "Inserte un AFN:\n";
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

void exercise1(dfa &myAfd) {
    std::cout << "\nEJERCICIO 1: Brzozowski\n";
    auto start = std::chrono::steady_clock::now();
    auto min = myAfd.minimization();
    auto end = std::chrono::steady_clock::now();
    min.print();
    auto diff = end - start;
    std::cout << "Tiempo de ejecución: " << std::chrono::duration<double, std::milli>(diff).count() << " ms"
              << std::endl;
}

void exercise2(dfa &myAfd) {
    std::cout << "\nEJERCICIO 2: Algoritmo de Equivalencia de estados\n";
    auto start = std::chrono::steady_clock::now();
    auto res = myAfd.equivalentStates();
    auto end = std::chrono::steady_clock::now();

    for (int i = 0; i < res.size(); i++) {
        std::cout << i << " :";
        for (int j = 0; j < res.size(); j++)
            std::cout << res[i][j] << ' ';
        std::cout << '\n';
    }

    std::cout << "   ";
    for (int j = 0; j < res.size(); j++)
        std::cout << j << ' ';
    std::cout << std::endl;

    auto diff = end - start;
    std::cout << "Tiempo de ejecución: " << std::chrono::duration<double, std::milli>(diff).count() << " ms"
              << std::endl;
    auto res1 = myAfd.improvedEquivalentStates();


    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res.size(); j++)
            if (res1[i][j] != res[i][j]) throw ("XD");
    }
}

void exercise3(dfa &myAfd) {
    std::cout << "\nEJERCICIO 3: Algoritmo de Equivalencia de estados mejorado\n";
    auto start = std::chrono::steady_clock::now();
    auto res = myAfd.improvedEquivalentStates();
    auto end = std::chrono::steady_clock::now();
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res.size(); j++)
            std::cout << res[i][j] << ' ';
        std::cout << '\n';
    }
    auto diff = end - start;
    std::cout << "Tiempo de ejecución: " << std::chrono::duration<double, std::milli>(diff).count() << " ms"
              << std::endl;
}

void exercise5(dfa &myAfd) {
    std::cout << "\nEJERCICIO 5: Algoritmo de Equivalencia de Hopcroft\n";
    auto start = std::chrono::steady_clock::now();
    auto res = myAfd.hopcroftMinimization();
    auto end = std::chrono::steady_clock::now();
    res.print();
    auto diff = end - start;
    std::cout << "Tiempo de ejecución: " << std::chrono::duration<double, std::milli>(diff).count() << " ms"
              << std::endl;
}

#endif