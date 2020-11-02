//
//  player.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "player.hpp"
#include "floor.hpp"
#include "dragonhoard.hpp"
#include <iostream>
#include <cmath>
using namespace std;
class Character;
class Enemy;

void Player::visit(Potion *po) {
    TypeofPotion t = po->getType();
    string type;
    if (t == TypeofPotion::RH) {
        hp += 10;
        if (hp > maxHp) {
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
        hp -= 10;
        if (hp < 0) {
            hp = 0;
        }
        type = "PH";
    } else if (t == TypeofPotion::WA) {
        tAtk -= 5;
        type = "WA";
    } else {
        tDef -= 5;
        type = "WD";
    }
    f->clearAction();
    f->addaction("PC uses " + type + ". ");
    f->notified();
}


void Player::visit(Enemy *e) {
    int damage = ceil(float(100)/(100 + def) * e->getAtk() );
    int t = hp - damage;
    if (t <= 0) {
        hp = 0;
    } else {
        hp = t;
    }
    char name = e->getName();
    string n;
    if (name == 'H') {
        n = "H";
    } else if (name == 'O') {
        n = "O";
    } else if (name == 'D') {
        n = "D";
    } else if (name == 'L') {
        n = "L";
    } else if (name == 'M') {
        n = "M";
    } else if (name == 'W') {
        n = "W";
    } else if (name == 'E') {
        n = "E";
    }
    if (race == "Goblin" && name == 'O') {
        damage = ceil(1.5 * damage);
    }
    string s = n + " deals " + to_string(damage) + " damage to PC. ";
    f->addaction(s);
}


void Player::clearTemp() {
    tAtk = 0;
    tDef = 0;
}

string Player::getRace() {
    return race;
}

void Player::move(std::string s) {
    int r = 0, c = 0;
    std::string direction;
    if (s == "no") {
        r = -1;
        c = 0;
        direction = "North";
    } else if (s == "ne") {
        r = -1;
        c = 1;
        direction = "North East";
    } else if (s == "ea") {
        r = 0;
        c = 1;
        direction = "East";
    } else if (s == "se") {
        r = 1;
        c = 1;
        direction = "South East";
    } else if (s == "so") {
        r = 1;
        c = 0;
        direction = "South";
    } else if (s == "sw") {
        r = 1;
        c = -1;
        direction = "South West";
    } else if (s == "we") {
        r = 0;
        c = -1;
        direction = "West";
    } else if (s == "nw") {
        r = -1;
        c = -1;
        direction = "North West";
    }
    f->clearAction();
    if (f->display.at(getX() + r)[getY() + c] == '.' || f->display.at(getX() + r)[getY() + c] == '#' ||
        f->display.at(getX() + r)[getY() + c] == '+') {
        f->display.at(getX())[getY()] = walkedOn;
        setX(getX() + r);
        setY(getY() + c);
        walkedOn = f->display.at(getX())[getY()];
        f->addaction("PC moves " + direction);
        if (race == "Troll") {
            hp += 5;
            if (hp > maxHp) {
                hp = maxHp;
            }
        }
        f->notified(s);
    } else if (f->display.at(getX() + r)[getY() + c] == 'G') {
        for (unsigned i = 0; i < f->treasures.size(); i++) {
            if(f->treasures.at(i)->getX() == getX() + r && f->treasures.at(i)->getY() == getY() + c) {
                int val = f->treasures.at(i)->getVal();
                if (val == 6) {
                    if (!static_cast<DragonHoard*>(f->treasures.at(i))->getDragDead()) {
                        f->addaction("Dragon is guarding its hoard. PC cannot pick up the hoard until dragon is dead. ");
                        return;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        f->display.at(getX())[getY()] = walkedOn;
        setX(getX() + r);
        setY(getY() + c);
        walkedOn = '.';
        f->addaction("PC moves " + direction);
        if (race == "Troll") {
            hp += 5;
            if (hp > maxHp) {
                hp = maxHp;
            }
        }
        f->notified(s);
        for(unsigned i = 0; i < f->treasures.size(); i++) {
            if (f->treasures.at(i)->getX() == getX() && f->treasures.at(i)->getY() == getY()) {
                f->treasures.at(i)->accept(this);
            }
        }
    } else if (f->display.at(getX() + r)[getY() + c] == '\\') {
        f->display.at(getX())[getY()] = walkedOn;
        setX(getX() + r);
        setY(getY() + c);
        walkedOn = '.';
        f->nextLvl();
    } else {
        f->addaction("PC turns to face towards " + direction);
        f->notified(s);
    }
    
}


void Player::accept(Enemy *e) {
    int t = 1;
    if (e->getName() == 'L') {
        srand(time(NULL));
        t = rand() % 2;
    }
    if (!t) {
        f->addaction("PC strikes and misses. ");
    }
    if (race == "Vamp") {
        if (t) {
            if (e->getName() != 'W') {
                hp += 5;
            } else {
                hp -= 5;
            }
            e->visit(this);
        }
    } else if (race == "Troll") {
        hp += 5;
        if (hp > maxHp) {
            hp = maxHp;
        }
        if (t) {
            e->visit(this);
        }
    } else if (race == "Goblin") {
        if (t) {
            e->visit(this);
            if (e->getHp() == 0) {
                gold += 5;
            }
        }
    } else {
        if (t) {
            e->visit(this);
        }
    }
    f->notified();
}



void Player::visit(Treasure *t) {
    string type;
    int val = t->getVal();
    if (val == 1) {
        type = "small pile of gold";
    } else if (val == 2) {
        type = "normal pile of gold";
    } else if (val == 4) {
        type = "merchant hoard";
    } else {
        type = "dragon hoard";
    }
    gold += val;
    f->addaction("PC picks up a " + type + ". ");
}



void Player::addGold(int g) {
    gold += g;
}

int Player::getGold() {
    return gold;
}

int Player::getAtk() {
    return atk + tAtk;
}
int Player::getDef() {
    return def + tDef;
}










