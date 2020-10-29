//
// Created by Jean Paul on 29/10/2020.
//

#ifndef TEO_PY_AFD_H
#define TEO_PY_AFD_H



#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

class AFD {


    typedef int state;

    // By Default Sigma = {0,1}
    std::unordered_set<std::string> Sigma;
    // Chosen by de user
    state state_i;
    std::unordered_set<state> state_e;
    std::unordered_map<state, std::unordered_map<std::string, state>> transition;

private:

    AFD();



};


#endif //TEO_PY_AFD_H
