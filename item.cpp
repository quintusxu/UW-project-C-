//
//  item.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "item.hpp"
int Item::getX() {
    return x;
}

int Item::getY() {
    return y;
}

void Item::setX(int r) {
    x = r;
}

void Item::setY(int c) {
    y = c;
}

void Item::setFloor(Floor *fl) {
    f = fl;
}
