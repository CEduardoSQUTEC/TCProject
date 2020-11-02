//
// Created by ceduardosq on 11/1/20.
//

#ifndef TCPROJECT_AFD_H
#define TCPROJECT_AFD_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

class afd {
    using alphabet = bool;
    using Q = int;
    using transition = std::unordered_map<alphabet, Q>;

    Q initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<Q, transition> states_{};
public:
    // random afd constructor
    afd() = default;

    afd(Q initial, std::unordered_set<Q> &finalState) : initialState_(initial), finalStates_(finalState) {};

    void addTransition(Q beginState, alphabet symbol, Q endState) { states_[beginState][symbol] = endState; };
};


#endif //TCPROJECT_AFD_H
