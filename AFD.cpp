//
// Created by Jean Paul on 29/10/2020.
//

#include "AFD.h"
#include "Random_generator.h"

AFD::AFD() {
    size_t Q = generateRandomInt(10);
    state_i = generateRandomInt(Q);
    size_t  N_state_e = generateRandomInt(Q);

}
