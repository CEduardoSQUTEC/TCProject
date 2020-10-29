//
// Created by Jean Paul on 29/10/2020.
//

#ifndef TEO_PY_RANDOM_GENERATOR_H
#define TEO_PY_RANDOM_GENERATOR_H

#include <random>

int generateRandomInt(int max) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,max);
    return distribution(generator);
}


#endif //TEO_PY_RANDOM_GENERATOR_H
