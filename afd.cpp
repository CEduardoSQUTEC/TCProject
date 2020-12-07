#include "afd.h"

std::unordered_set<Q> nfa::cl(std::unordered_set<Q> &set) {
    std::unordered_set<Q> newSet;
    for (auto &q: set) {
        if (!states_[q].count(-1))
            newSet.insert(q);
        else
            for (auto &qe: states_[q][-1])
                newSet.insert(qe);
    }
    return newSet;
}

dfa dfa::minimization() {
    auto res = reverse(*this);
    auto sub = subset(res);
    res = reverse(sub);
    sub = subset(res);

    return sub;
}

nfa reverse(const dfa &a) {
    Q initialState = a.states_.size();
    std::unordered_set<Q> finalStates;
    finalStates.insert(a.initialState_);
    nfa na(initialState, finalStates);
    for (auto it: a.states_) {
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
    std::queue<std::pair<std::unordered_set<Q>, Q>> delta;
    std::vector<std::unordered_set<Q>> vis;

    Q s = 0;
    delta.push({q0, s});
    vis.push_back(q0);

    std::unordered_set<Q> fs;
    dfa a(s, fs);

    while (!delta.empty()) {
        auto &states = delta.front();

        if (!a.states_.count(states.second)) {
            for (auto it :  states.first) {
                if (na.finalStates_.count(it)) {
                    a.finalStates_.insert(states.second);
                }
            }

            for (int i = 0; i <= 1; i++) {
                std::unordered_set<Q> temp;

                for (auto state : states.first)
                    temp.insert(na.states_[state][i].begin(), na.states_[state][i].end());
                temp = na.cl(temp);

                auto it = std::find(vis.begin(), vis.end(), temp);
                Q index;
                if (it == vis.end()) {
                    index = vis.size();
                    vis.push_back(temp);
                    delta.push({temp, index});
                } else {
                    index = it - vis.begin();
                }
                a.addTransition(states.second, i, index);
                temp.clear();
            }
        }
        delta.pop();
    }

    return a;
}

std::vector<std::vector<bool>> dfa::equivalentStates() {

    std::vector<std::vector<bool>> equivalent(states_.size(),
                                              std::vector<bool>(states_.size(), true));

    for (int i = 0; i < states_.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (finalStates_.count(i) && !finalStates_.count(j)
                || finalStates_.count(j) && !finalStates_.count(i)) {
                equivalent[i][j] = false;
                equivalent[j][i] = false;
            }

        }
    }

    while (true) {
        bool flag = true;
        for (int i = 0; i < states_.size(); i++) {
            for (int j = 0; j < i; j++) {
                std::vector<std::pair<int, int>> vec;
                vec.emplace_back(states_[i][0], states_[j][0]);
                vec.emplace_back(states_[i][1], states_[j][1]);

                for (auto it: vec) {
                    if (equivalent[i][j]) {
                        if (!equivalent[it.first][it.second]) {
                            equivalent[i][j] = false;
                            equivalent[j][i] = false;
                            flag = false;
                        }
                    }
                }
            }
        }
        if (flag) break;
    }


    return equivalent;
}

std::vector<std::vector<bool>> dfa::improvedEquivalentStates() {

    std::vector<std::vector<bool>> equivalent(states_.size(),
                                              std::vector<bool>(states_.size(), true));
    std::map<std::pair<Q, Q>, std::vector<std::pair<Q, Q> > > dependencies;
    std::queue<std::pair<Q, Q> > toProcess;

    // we begin by marking all trivial not equivalent states
    // we also create de map of dependecies
    for (int i = 0; i < states_.size(); i++) {
        for (int j = 0; j < i; j++) {
            dependencies[{states_[i][0], states_[j][0]}].push_back({i, j});
            dependencies[{states_[i][1], states_[j][1]}].push_back({i, j});
        }
    }

    for (int i = 0; i < states_.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (finalStates_.count(i) && !finalStates_.count(j)
                || finalStates_.count(j) &&
                   !finalStates_.count(i)) {
                equivalent[i][j] = false;
                equivalent[j][i] = false;
                toProcess.push({i, j});
                toProcess.push({j, i});
            }

            while (!toProcess.empty()) {
                for (auto it: dependencies[toProcess.front()]) {
                    if (equivalent[it.first][it.second]) {
                        equivalent[it.first][it.second] = false;
                        equivalent[it.second][it.first] = false;
                        toProcess.push(it);
                        toProcess.push({it.second, it.first});
                    }
                }
                toProcess.pop();
            }
        }
    }
    return equivalent;
}

dfa dfa::algorithmHuffman() {
    auto eq = improvedEquivalentStates();
    std::vector<std::unordered_set<int>> newStates;
    std::unordered_set<int> vis;
    for (int i = 0; i < eq.size(); ++i) {
        std::unordered_set<int> block;
        for (int j = 0; j < eq.size(); ++j)
            if (eq[i][j] && vis.find(j) != vis.end()) block.insert(j), vis.insert(j);
        newStates.push_back(block);
    }
    return dfa();
}

void dfa::printStates() {
    for (auto trans: states_) {
        for (auto delta : trans.second) {
            std::cout << trans.first << " " << delta.first << " " << delta.second << "\n";
        }
    }
}

void dfa::print() {
    std::cout << states_.size() << ' ' << initialState_ << ' ' << finalStates_.size() << ' ';
    for (auto it : finalStates_)
        std::cout << it << ' ';
    std::cout << '\n';
    printStates();
}

