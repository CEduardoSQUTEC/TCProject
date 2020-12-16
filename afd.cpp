#include "afd.h"

std::unordered_set<Q> nfa::cl(std::unordered_set<Q> &set) {
    std::unordered_set<Q> newSet;
    for (auto &q: set) {
        if(!states_[q].count(-1))
            newSet.insert(q);
        else for (auto &qe: states_[q][-1])
            newSet.insert(qe);
    }
    return newSet;
}

dfa dfa::brzozowski() {
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

            for (int i = 0; i <=1; i++)
            {
                std::unordered_set<Q> temp;

                for (auto state : states.first)
                    temp.insert(na.states_[state][i].begin(), na.states_[state][i].end());
                temp = na.cl(temp);

                auto it = std::find(vis.begin(), vis.end(), temp);
                Q index;
                if (it == vis.end()) {
                    index = vis.size();
                    vis.push_back(temp);
                    delta.push({temp,index});
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

std::vector<std::vector<bool>> dfa::equivalentStates(){

    std::vector<std::vector<bool>> equivalent (states_.size(),
                                               std::vector<bool>(states_.size(), true) );

    for(int i = 0; i < states_.size(); i++){
        for(int j = 0; j < i ; j++){
            if(finalStates_.count(i) && !finalStates_.count(j)
               || finalStates_.count(j) && !finalStates_.count(i)){
                equivalent[i][j] = false;
                equivalent[j][i] = false;
            }

        }
    }

    while (true){
        bool flag = true;
        for(int i = 0; i < states_.size(); i++){
            for(int j = 0; j < i ; j++){
                std::vector<std::pair<int,int>> vec;
                vec.emplace_back(states_[i][0], states_[j][0]);
                vec.emplace_back(states_[i][1], states_[j][1]);

                for(auto it: vec){
                    if(equivalent[i][j]) {
                        if (!equivalent[it.first][it.second]) {
                            equivalent[i][j] = false;
                            equivalent[j][i] = false;
                            flag = false;
                        }
                    }
                }
            }
        }
        if(flag) break;
    }


    return equivalent;
}

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const std::pair<T1, T2>& p) const
    { 
        auto hash1 = std::hash<T1>{}(p.first); 
        auto hash2 = std::hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

std::vector<std::vector<bool>> dfa::improvedEquivalentStates(){

    std::vector<std::vector<bool>> equivalent (states_.size(),
                                               std::vector<bool>(states_.size(), true) );
    std::unordered_map< std::pair< Q,Q >, std::vector<std::pair<Q,Q> >, hash_pair> dependencies;
    std::queue< std::pair<Q,Q> > toProcess;


    // we begin by marking all trivial not equivalent states
    // we also create de map of dependecies
    for(int i = 0; i < states_.size(); i++){
        for(int j = 0; j < i ; j++){
            dependencies[{states_[i][0] ,states_[j][0]}].push_back({i,j});
            dependencies[{states_[i][1] ,states_[j][1]}].push_back({i,j});
        }
    }


    for(int i = 0; i < states_.size(); i++){
        for(int j = 0; j < i ; j++){
            if(finalStates_.count(i) && !finalStates_.count(j) || finalStates_.count(j) && !finalStates_.count(i)){
                equivalent[i][j] = false;
                equivalent[j][i] = false;
                toProcess.push({i,j});
            }

            while(!toProcess.empty()){
              for(auto it: dependencies[toProcess.front()]){
                if(equivalent[it.first][it.second]){
                  equivalent[it.first][it.second] = false;   
                  equivalent[it.second][it.first] = false;
                  toProcess.push(it);
                }
              }
              toProcess.pop();
            }
        }
    }
    return equivalent;
}

std::vector<bool> dfa::reachableStates(){
    std::stack<Q> s;
    std::vector<bool> visited(states_.size(), false);
    s.push(initialState_);


    while (!s.empty()){
        auto t = s.top();
        visited[t] = true;
        s.pop();
        for(auto transition : states_[t]){
            if(!visited[transition.second]){
                s.push(transition.second);
            }
        }
    }


    return visited;
}

void dfa::erasedUnreachable(){
    // i just return a vector of bools because
    // i don't want to overcomplicated things
    auto reachable = reachableStates();
    int counter {};

    for(auto && i : reachable){
        if(i) counter++;
    }

    // if all are reachable just
    // don't
    if(counter == states_.size()) return;
    counter = {};
    std::unordered_map<Q, Q> newStates{};

    // create new keys for the old keys
    // because keys go from 0 to n - 1
    for(int i = 0; i < reachable.size();i++){
        if(reachable[i]){
            newStates[i] = counter;
            counter++;
        }
    }

    // modifiying the current states
    std::unordered_map<Q, std::unordered_map<alphabet, Q>> res{};
    for(int i = 0; i < reachable.size();i++){
        if(reachable[i]){
            res[newStates[i]][0] =  newStates[states_[i][0]];
            res[newStates[i]][1] =  newStates[states_[i][1]];
        }
    }
    initialState_ = newStates[initialState_];

    auto  temp = finalStates_;
    finalStates_.clear();
    for(auto it : temp){
        if(reachable[it]) finalStates_.insert(newStates[it]);
    }

    states_ = res;
}

dfa dfa::huffmanMoore() {
    // toDO
    // erased unreachable and modify afs

    erasedUnreachable();

    // eq states
    auto eq = improvedEquivalentStates();
    std::vector<std::unordered_set<int>> newStates;
    std::vector<bool> vis (states_.size() , false);
    int initS {};
    std::unordered_set<int> endS {};

    // creating the blocks
    for (int i = 0; i < eq.size() ; ++i) {
        std::unordered_set<int> block;
        if(!vis[i]){
            if(initialState_ == i) initS = newStates.size();
            if(finalStates_.find(i) != finalStates_.end()) endS.insert(newStates.size());
            block.insert(i);

            for (int j = eq.size() - 1; j > i ; --j)
                if (eq[j][i] && !vis[j]){
                    block.insert(j);
                    vis[j] = true;
                    if(initialState_ == j) initS = newStates.size();
                    if(finalStates_.find(j) != finalStates_.end()) endS.insert(newStates.size());
                }
            vis[i] = true;
            newStates.push_back(block);
        }
    }

    dfa minDfa(initS,endS);
    
    for(int i = 0 ; i < newStates.size(); i++){
        // getting any state from block n
        auto &block = newStates[i];
        int s = *block.begin();
        // gettin transitions
        std::vector<int> tran{};
        std::vector<bool> found(2, false);
        tran.push_back(states_[s][0]);
        tran.push_back(states_[s][1]);


        for(int j = 0; j < newStates.size(); j++){
            if(!found[0] && newStates[j].find(tran[0]) != newStates[j].end()){
                minDfa.states_[i][0] = j;
                found[0] = true;
            }
            if( !found[1] && newStates[j].find(tran[1]) != newStates[j].end() ){
                minDfa.states_[i][1] = j;
                found[1] = true;
            }
            if(found[0] && found[1]) break;
        }
    }
    return minDfa;
}

void dfa::printStates() {
    for (int i = 0 ; i < states_.size();i++) {
        for (auto delta :states_[i]) {
            std::cout << i << " " << delta.first << " " << delta.second << "\n";
        }
    }
}

void dfa::print() {
    std::cout<<states_.size()<<' '<<initialState_<<' '<<finalStates_.size()<<' ';
    for (auto it : finalStates_)
        std::cout<<it<<' ';
    std::cout<<'\n';
    printStates();
}