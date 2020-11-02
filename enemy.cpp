//
//  enemy.cpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-11.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include "enemy.hpp"
#include "dragonhoard.hpp"
#include "treasure.hpp"
#include "player.hpp"
#include "floor.hpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

void Enemy::accept(Player *p) {
    if(!hostile) {
        return;
    }
    //srand(time(NULL));
    if (name == 'E' && p->getRace() != "Drow") {
        if(rand() % 2) {
            p->visit(this);
        }
    }
    int t = rand() % 2;
    if (t) {
        if (name == 'O' && p->getRace() == "Goblin") {
            int dmg = ceil(float(100) / (100 + p->getDef()) * atk / 2);
            p->changeHp(-dmg);
        }
        p->visit(this);
    } else {
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
        string s = n + " swings and misses. ";
        f->addaction(s);
    }
}

void Enemy::setHostile(bool h) {
    hostile = h;
}


void Enemy::visit(Player *p) {
    int damage= ceil(float(100)/(100+def) * p->getAtk());
    if (name == 'A') {
        damage = 0;
        Treasure *t= new Treasure(1);
        t->setX(getX());
        t->setY(getY());
        f->display.at(getX())[getY()] = 'G';
        f->treasures.emplace_back(t);
    }
    
    int t = hp - damage;
    if (t <= 0) {
        hp = 0;
    } else {
        hp = t;
    }
    if (name == 'M' && !hostile) {
        p->atkMerchant = true;
        for (unsigned i = 0; i < f->enemies.size(); i++) {
            if (f->enemies.at(i)->getName() == 'M') {
                f->enemies.at(i)->setHostile(true);
            }
        }
    }
    
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
    } else if (name == 'A') {
        n = "A";
        f->clearAction();
        string s = "The Mascot has dropped a pile of gold on the ground. ";
        f->addaction(s);
        f->notified(this);
        return;
    }
    f->clearAction();
    string s = "PC deals " + to_string(damage) + " damage to " + n + " (" + to_string(hp) + " HP). ";
    f->addaction(s);
    f->notified(this);
}




void Enemy::makemove() {
    int px = f->p->getX();
    int py = f->p->getY();
    if (name == 'D') {
        int tx = static_cast<Dragon*>(this)->getTreasure()->getX();
        int ty = static_cast<Dragon*>(this)->getTreasure()->getY();
        if ((px == tx + 1 && py == ty) || (px == tx - 1 && py == ty) ||
            (px == tx && py == ty + 1) || (px == tx && py == ty - 1) ||
            (px == tx + 1 && py == ty + 1) || (px == tx + 1 && py == ty - 1) ||
            (px == tx - 1 && py == ty + 1) || (px == tx - 1 && py == ty - 1)) {
            accept(f->p);
            return;
        }
    }
    if ((px == getX() + 1 && py == getY()) || (px == getX() - 1 && py == getY()) ||
        (px == getX() && py == getY() + 1) || (px == getX() && py == getY() - 1) ||
        (px == getX() + 1 && py == getY() + 1) || (px == getX() + 1 && py == getY() - 1) ||
        (px == getX() - 1 && py == getY() + 1) || (px == getX() - 1 && py == getY() - 1)) {
        if (hostile) {
            accept(f->p);
            return;
        }
    }
    if (!canMove || f->isPaused()) {
        return;
    }
    //srand(time(NULL));
    while (1) {
        int t = rand() % 8;
        
        if (f->display.at(getX())[getY()] == name) {
            f->display.at(getX())[getY()] = '.';
        }
        if (t == 0 && f->display.at(getX() - 1)[getY()] == '.') {
            setX(getX() - 1);
            break;
        } else if (t == 1 && f->display.at(getX() - 1)[getY() - 1] == '.') {
            setX(getX() - 1);
            setY(getY() - 1);
            break;
        } else if (t == 2 && f->display.at(getX())[getY() - 1] == '.') {
            setY(getY() - 1);
            break;
        } else if (t == 3 && f->display.at(getX() + 1)[getY() - 1] == '.') {
            setX(getX() + 1);
            setY(getY() - 1);
            break;
        } else if (t == 4 && f->display.at(getX() + 1)[getY()] == '.') {
            setX(getX() + 1);
            break;
        } else if (t == 5 && f->display.at(getX() + 1)[getY() + 1] == '.') {
            setX(getX() + 1);
            setY(getY() + 1);
            break;
        } else if (t == 6 && f->display.at(getX())[getY() + 1] == '.') {
            setY(getY() + 1);
            break;
        } else if (t == 7 && f->display.at(getX() - 1)[getY() + 1] == '.') {
            setX(getX() - 1);
            setY(getY() + 1);
            break;
        }
    }
    f->notified(this);
    if ((px == getX() + 1 && py == getY()) || (px==getX() - 1 && py == getY()) ||
        (px == getX() && py == getY() + 1) || (px == getX() && py == getY() - 1) ||
        (px == getX() + 1 && py == getY() + 1) || (px == getX() + 1 && py == getY() - 1) ||
        (px == getX() - 1 && py == getY() + 1) || (px == getX() - 1 && py == getY() - 1)) {
        accept(f->p);
        return;
    }
}


char Enemy::getName() {
    return name;
}

























