//
//  basicenemy.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "basicenemy.hpp"

Human::Human() {
    hp=140;
    atk=20;
    def=20;
    name = 'H';
    hostile=true;
    canMove=true;
}

Human::~Human() {}


Merchant::Merchant() {
    hp=30;
    atk=70;
    def=5;
    name = 'M';
    hostile=false;
    canMove=true;
}

Merchant::~Merchant() {}

Dragon::Dragon() {
    hp=150;
    atk=20;
    def=20;
    name = 'D';
    hostile=true;
    canMove=false;
    t=nullptr;
}

Dragon::~Dragon() {}

void Dragon::setTreasure(DragonHoard *tt) {
    t= tt;
}

DragonHoard* Dragon::getTreasure() {
    return t;
}












