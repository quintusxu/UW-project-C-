//
//  turtle.cpp
//  cc3k
//
//  Created by Aurora Jin on 2018-07-21.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "turtle.hpp"
#include "floor.hpp"
Turtle::Turtle() {
    hp = 200;
    atk = 10;
    def = 100;
    maxHp = 200;
    race = "Turtle";
}

Turtle::~Turtle() {}

void Turtle::visit(Potion *p) {
    TypeofPotion t = p->getType();
    std::string type;
    if (t == TypeofPotion::RH) {
        hp += 10;
        if (hp >maxHp) {
            hp = maxHp;
        }
        type = "RH";
    } else if (t == TypeofPotion::BA) {
        tAtk += 5;
        type = "BA";
    } else if (t == TypeofPotion::BD) {
        tDef += 5;
        type = "BD";
    } else if (t == TypeofPotion::PH) {
        type = "PH";
    } else if (t == TypeofPotion::WA) {
        type = "WA";
    } else {
        type = "WD";
    }
    f->clearAction();
    f->addaction("PC uses " + type + ". ");
    f->notified();
}
