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

    std::unordered_set<Q> cl(std::unordered_set<Q> &set) {
        std::unordered_set<Q> newSet;
        for (auto &q: set) {
            newSet.insert(q);
            for (auto &qe: states_[q][-1])
                newSet.insert(qe);
        }
        return newSet;
    }

    friend nfa reverse(const dfa &a);

    friend dfa subset(nfa &na);
};

class dfa {
    Q initialState_{};
    std::unordered_set<Q> finalStates_{};
    std::unordered_map<Q, std::unordered_map<alphabet, Q>> states_{};
public:
    // random afd constructor
    dfa() = default;

    dfa(Q initial, std::unordered_set<Q> &finalState) : initialState_(initial), finalStates_(finalState) {};

    void addTransition(Q beginState, alphabet symbol, Q endState) { states_[beginState][symbol] = endState; };

//    std::unordered_map<alphabet, std::unordered_multimap<alphabet, Q> > reverse() {
//        // i do this because afn
//        std::unordered_map<alphabet, std::unordered_multimap<alphabet, Q> > res;
//        for (auto it: states_) {
//            for (auto t2: it.second) {
//                res[t2.second].insert({t2.first, it.first});
//            }
//        }
//        return res;
//    }

    auto minimization() {
//        auto &g = subset(reverse());
//        initialState_ = g.initialState;
//        afn tAfn;
//        tAfn.states_ = invert();
//        tAfn.finalStates_.insert(initialState_);
//        Q newState = states_.size();
//        for (const auto &e: finalStates_) tAfn.states_[newState].insert({-1, e});
    }

    // =============================================================================

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

    friend nfa reverse(const dfa &a);

    friend dfa subset(nfa &na);
};

nfa reverse(const dfa &a) {
    Q initialState = a.states_.size();
    std::unordered_set<Q> finalStates;
    finalStates.insert(a.initialState_);
    nfa na(initialState, finalStates);
    for (auto it: a.states_)
        for (auto t2: it.second)
            na.addTransition(t2.second, t2.first, it.first);
    for (auto &s: a.finalStates_)
        na.states_[initialState][-1].insert(s);
    return na;
}

dfa subset(nfa &na) {
    std::unordered_set<Q> qInitial;
    qInitial.insert(na.initialState_);
    std::unordered_set<Q> q0 = na.cl(qInitial);
    std::queue<std::unordered_set<Q>> delta;
    delta.push(q0);
    Q s = 0;
    std::unordered_set<Q> fs;
    dfa a(s, fs);

    std::vector<std::unordered_set<Q>> vis;
    while (!delta.empty()) {
        auto &states = delta.front();
        if(std::find(vis.begin(), vis.end(), states) == vis.end()) //if not found
        {
            unordered_set<Q> temp0, temp1;
            for(auto state : states)
                temp0.insert(na.states_[state][0]);
            temp0 = cl(temp0);
            if(std::find(vis.begin(), vis.end(), temp0) == vis.end())
            {
                delta.push(temp0);
                
            }
            
            for(auto state : states)
                temp1.insert(na.states_[state][1]);
            //a.addTransition(s, 0, ++s);
            //void addTransition(Q beginState, alphabet symbol, Q endState) { states_[beginState][symbol] = endState; };
        }
        vis.emplace_back(states);
        delta.pop();
    }
    return;
}


#endif //TCPROJECT_AFD_H