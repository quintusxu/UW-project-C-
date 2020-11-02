//
//  mascot.cpp
//  cc3k
//
//  Created by Aurora Jin on 2018-07-21.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "mascot.hpp"

Mascot::Mascot() {
    hp = 10000;
    atk = 0;
    def= 0;
    name = 'A';
    hostile = false;
    canMove = true;
}

Mascot::~Mascot() {}
