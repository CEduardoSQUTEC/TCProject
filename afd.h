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

    std::unordered_set<Q> cl(std::unordered_set<Q> &set) {
        std::unordered_set<Q> newSet;
        for (auto &q: set) {
            if(!states_[q].count(-1)){
                newSet.insert(q);
            }
            else for (auto &qe: states_[q][-1])
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


    friend nfa reverse(const dfa &a);

    friend dfa subset(nfa &na);

    auto minimization() {
        auto res = reverse(*this);
        auto sub = subset(res);
        res = reverse(sub);
        sub = subset(res);



        std::cout<<"asd";

        return sub;
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

nfa reverse(const dfa &a) {
    Q initialState = a.states_.size();
    std::unordered_set<Q> finalStates;
    finalStates.insert(a.initialState_);
    nfa na(initialState, finalStates);
    for (auto it: a.states_){
        na.states_[it.first];
        for (auto t2: it.second)
            na.addTransition(t2.second, t2.first, it.first);
    }
    for (auto &s: a.finalStates_)
        na.states_[initialState][-1].insert(s);
    return na;
}

dfa subset(nfa &na) {

    // initializing the dfa
    std::unordered_set<Q> qInitial;
    qInitial.insert(na.initialState_);
    std::unordered_set<Q> q0 = na.cl(qInitial);

    // container we are going to use
    std::queue<std::pair<std::unordered_set<Q>,Q>> delta;
    std::vector<std::unordered_set<Q>> vis;


    Q s = 0;
    delta.push({q0,s});
    vis.push_back(q0);

    std::unordered_set<Q> fs;
    dfa a(s, fs);



    while (!delta.empty()) {
        auto &states = delta.front();

        if(!a.states_.count(states.second)){
            for(auto it :  states.first){
                if(na.finalStates_.count(it)){
                    a.finalStates_.insert(states.second);
                }
            }

            std::unordered_set<Q> temp;
            //clousure in 0
            for (auto state : states.first)
                temp.insert(na.states_[state][0].begin(), na.states_[state][0].end());
            temp = na.cl(temp);


            auto it = std::find(vis.begin(), vis.end(), temp);
            if (it == vis.end()) {
                Q index = vis.size();
                a.addTransition(states.second, 0,  index);
                vis.push_back(temp);
                delta.push({temp,index});

            } else {
                Q index = it - vis.begin();
                a.addTransition(states.second, 0, index);
                delta.push({temp,index});

            }

            temp.clear();
            //clousure in 1
            for (auto state : states.first)
                temp.insert(na.states_[state][1].begin(), na.states_[state][1].end());
            temp = na.cl(temp);


            it = std::find(vis.begin(), vis.end(), temp);
            if (it == vis.end()) {
                Q index = vis.size();
                a.addTransition(states.second, 1,  index);
                vis.push_back(temp);
                delta.push({temp,index});

            } else {
                Q index = it - vis.begin();
                a.addTransition(states.second, 1, index);
                delta.push({temp,index});
            }

        }

        delta.pop();
    }

    return a;
}


#endif //TCPROJECT_AFD_H