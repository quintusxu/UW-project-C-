//
//  treasure.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "treasure.hpp"
#include "player.hpp"

Treasure::Treasure(int val): value(val) {}

Treasure::~Treasure() {}

void Treasure::accept(Player *p) {
    p->visit(this);
}

int Treasure::getVal() {
    return value;
}
