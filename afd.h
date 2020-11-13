//
// Created by ceduardosq on 11/1/20.
//

#ifndef TCPROJECT_AFD_H
#define TCPROJECT_AFD_H

#include <vector>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>


using alphabet = int;
using Q = int;

class dfa;

class nfa {
    Q initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<Q, std::unordered_map<alphabet, std::unordered_set<Q>>> states_{};

public:
    nfa(Q initialState, std::unordered_set<Q> &finalState) : initialState_(initialState), finalStates_(finalState) {};

    void addTransition(Q beginState, alphabet symbol, Q endState) { states_[beginState][symbol].insert(endState); };

    friend nfa reverse(const dfa &a);
    
    friend dfa subset(nfa &na);

    std::unordered_set<Q> cl(std::unordered_set<Q> &set);

};

class dfa {
    Q initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<Q, std::unordered_map<alphabet, Q>> states_{};
public:
    
    dfa() = default;

    dfa(Q initial, std::unordered_set<Q> &finalState) : initialState_(initial), finalStates_(finalState) {};

    void addTransition(Q beginState, alphabet symbol, Q endState) { states_[beginState][symbol] = endState; };

    friend nfa reverse(const dfa &a);

    friend dfa subset(nfa &na);

    dfa minimization();

    std::unordered_map<Q, std::unordered_map<Q, bool>> equivalentStates();

    void printStates();

    void print();

};

nfa reverse(const dfa &a);

dfa subset(nfa &na);

#endif //TCPROJECT_AFD_H