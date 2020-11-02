//
//  character.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "character.hpp"

int Character::getHp() {
    return hp;
}

int Character::getAtk() {
    return atk;
}
int Character::getDef() {
    return def;
}
void Character::changeHp(int t) {
    hp += t;
}
