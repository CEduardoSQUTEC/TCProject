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

    void addTransition(Q beginState, alphabet symbol, Q endState) { 
        states_[beginState][symbol] = endState;
    };


    auto equivalentStates(){
        std::vector<std::vector<bool>> equivalent;


        for (int i = 0; i < states_.size(); i++){
            std::vector<bool> temp (states_.size(), false);
            equivalent.push_back(temp);
        }



        for(int i = 0; i < states_.size(); i++){
            equivalent[i][i] = true;
            for(int j = 0; j < i ; j++){
                if(finalStates_.count(i) && !finalStates_.count(j)
                || finalStates_.count(j) && !finalStates_.count(i)){
                    equivalent[i][j] = true;
                    equivalent[j][i] = true;
                }

            }
        }

        for(int i = 0; i < states_.size(); i++){
            for(int j = 0; j < i ; j++){
                std::vector<std::pair<int,int>> vec;
                vec.push_back({states_[i][0], states_[j][0]});
                vec.push_back({states_[i][1], states_[j][1]});

                for(auto it: vec){
                    if(it.first != it.second && equivalent[it.first][it.second]){
                        equivalent[i][j] = true;
                        equivalent[j][i] = true;
                    }
                }
            }
        }

        return equivalent;
    }


    void printStates(){
        for(auto trans: states_){
            for(auto delta : trans.second){
                std::cout<<trans.first<<" "<<delta.first<<" "<<delta.second<<"\n";
            }
        }
    }
    
};


#endif //TCPROJECT_AFD_H
