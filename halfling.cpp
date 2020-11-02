//
//  halfling.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "halfling.hpp"


Halfling::Halfling() {
    hp = 100;
    atk = 15;
    def = 20;
    name = 'L';
    hostile = true;
    canMove = true;
}

Halfling::~Halfling() {}
