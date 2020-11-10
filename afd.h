//
// Created by ceduardosq on 11/1/20.
//

#ifndef TCPROJECT_AFD_H
#define TCPROJECT_AFD_H

#include <vector>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <set>

using alphabet = int;
using Q = int;
using transition = std::unordered_map<alphabet, Q>;

class af {};

struct afn {
    std::unordered_set<Q> initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<alphabet, std::unordered_multimap<alphabet, Q>> states_;
};

class afd {
    Q initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<Q, transition> states_{};
public:
    // random afd constructor
    afd() = default;

    afd(Q initial, std::unordered_set<Q> &finalState) : initialState_(initial), finalStates_(finalState) {};

    void addTransition(Q beginState, alphabet symbol, Q endState) {
        states_[beginState][symbol] = endState;
    };

    std::unordered_map<alphabet, std::unordered_multimap<alphabet, Q> > invert() {
        // i do this because afn
        std::unordered_map<alphabet, std::unordered_multimap<alphabet, Q> > res;
        for (auto it: states_) {
            for (auto t2: it.second) {
                res[t2.second].insert({t2.first, it.first});
            }
        }
        return res;
    }

    auto minimization() {
        afn tAfn;
        tAfn.states_ = invert();
        tAfn.finalStates_.insert(initialState_);
    }

    auto equivalentStates() {
        std::unordered_map<Q, std::unordered_map<Q, bool>> equivalent;
        std::vector<Q> states;
        for (auto it: states_) {
            equivalent[it.first][it.first] = true;
            for (auto t2: states_) {
                equivalent[it.first][t2.first] = true;
            }
        }
        for (auto i: equivalent) {
            equivalent[i.first][i.first] = true;
            for (auto j :i.second) {
                if (finalStates_.count(i.first) && !finalStates_.count(j.first)
                    || finalStates_.count(j.first) && !finalStates_.count(i.first)) {
                    equivalent[i.first][j.first] = false;
                    equivalent[j.first][i.first] = false;
                }

            }
        }
        for (auto i: equivalent) {
            for (auto j : i.second) {
                std::vector<std::pair<Q, Q>> vec;
                vec.push_back({states_[i.first][0], states_[j.first][0]});
                vec.push_back({states_[i.first][1], states_[j.first][1]});
                for (auto it: vec) {
                    if (it.first != it.second && !equivalent[it.first][it.second]) {
                        equivalent[i.first][j.first] = false;
                        equivalent[j.first][i.first] = false;
                    }
                }
            }
        }
        return equivalent;
    }

    void printStates() {
        for (auto trans: states_) {
            for (auto delta : trans.second) {
                std::cout << trans.first << " " << delta.first << " " << delta.second << "\n";
            }
        }
    }
};


#endif //TCPROJECT_AFD_H
