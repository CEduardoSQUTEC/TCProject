#include <iostream>
#include "afd.h"

int main() {
    int n, iState, nFStates;
    std::cin >> n >> iState >> nFStates;
    std::unordered_set<int> fState;
    while (nFStates--) {
        int i{};
        std::cin >> i;
        fState.insert(i);
    }
    afd myAfd(iState, fState);

    int tmp = 2 * n;
    while (tmp--) {
        int p, a, q;
        std::cin >> p >> a >> q;
        myAfd.addTransition(p, a, q);
    }

//    auto res = myAfd.equivalentStates();
//
//    for(int i = 0; i < n; i++){
//        for(int j = 0; j < n;j++){
//            std::cout<<res[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }

    myAfd.minimization();

    return 0;
}
