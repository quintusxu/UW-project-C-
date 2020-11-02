//
//  dragonhoard.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/16.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "dragonhoard.hpp"


DragonHoard::~DragonHoard() {}

void DragonHoard::setDrag(Dragon *d) {
    drag = d;
}
bool DragonHoard::getDragDead() {
    return drag == nullptr;
}
DragonHoard:: DragonHoard(): Treasure(6) {}


