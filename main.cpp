#include <iostream>
#include "afd.h"

int main() {
    int n, iState, nFStates;
    std::cin >> n >> iState >> nFStates;
    std::unordered_set<int> fState;
    afd myAfd(iState, fState);
    while (nFStates--) {
        int i{};
        std::cin >> i;
        fState.insert(i);
    }
    int tmp = 2 * n;
    while (tmp--) {
        int p, a, q;
        std::cin >> p >> a >> q;
        myAfd.addTransition(p, a, q);
    }
    return 0;
}
