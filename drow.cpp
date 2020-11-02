//
//  drow.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-12.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "drow.hpp"
#include <cmath>
#include "floor.hpp"

Drow::Drow() {
    hp = 150;
    atk = 25;
    def = 25;
    maxHp = 150;
    race = "Drow";
}

void Drow::visit(Potion *po) {
    TypeofPotion t = po->getType();
    std::string type;
    if (t == TypeofPotion::RH) {
        hp += 15;
        if (hp > maxHp) {
            hp = maxHp;
        }
        type = "RH";
    } else if (t == TypeofPotion::BA) {
        tAtk += ceil(1.5 * 5);
        type = "BA";
    } else if (t == TypeofPotion::BD) {
        tDef += ceil(1.5 * 5);
        type = "BD";
    } else if (t == TypeofPotion::PH) {
        hp -= 15;
        if (hp < 0) {
            hp = 0;
        }
        type = "PH";
    } else if (t == TypeofPotion::WA) {
        tAtk -= ceil(1.5 * 5);
        type = "WA";
    } else {
        tDef -= ceil(1.5 * 5);
        type = "WD";
    }
    f->clearAction();
    f->addaction("PC uses " + type + ".");
    f->notified();
}
Drow::~Drow() {}
