//
//  floor.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/13.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "floor.hpp"
#include "basicenemy.hpp"
#include "dragonhoard.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void Floor::notified() {
    for(unsigned i = 0; i < enemies.size(); i++) {
        enemies.at(i)->makemove();
    }
}


void Floor::notified(std::string d) {
    int r = p->getX();
    int c = p->getY();
    display.at(r)[c] = '@';
    int x = 0, y = 0;
    if (d == "ea") {
        y = 1;
    } else if (d == "se") {
        x = 1;
        y = 1;
    } else if (d == "so") {
        x = 1;
    } else if (d == "sw") {
        x = 1;
        y = -1;
    } else if (d == "we") {
        y = -1;
    } else if (d == "nw") {
        x = -1;
        y = -1;
    } else if (d == "no") {
        x = -1;
    } else if (d == "ne") {
        x = -1;
        y = 1;
    }
    if (display.at(r + x)[c + y] == 'G') {
        action += " and sees a pile of gold. ";
    } else if (display.at(r + x)[c + y] == 'P') {
        for (unsigned i = 0; i < potions.size(); i++) {
            if (potions.at(i)->getX() == r + x && potions.at(i)->getY() == c + y) {
                if (potions.at(i)->isRevealed()) {
                    string type;
                    TypeofPotion t = potions.at(i)->getType();
                    if (t == TypeofPotion::RH) {
                        type = "RH";
                    } else if (t == TypeofPotion::BA) {
                        type = "BA";
                    } else if (t == TypeofPotion::BD) {
                        type = "BD";
                    } else if (t == TypeofPotion::PH) {
                        type = "PH";
                    } else if (t == TypeofPotion::WA) {
                        type = "WA";
                    } else {
                        type = "WD";
                    }
                    action += (" and sees a potion of type " + type + ". ");
                } else {
                    action += (" and sees an unknown potion. ");
                }
            }
        }
    } else {
        action += ". ";
    }
    for(unsigned i = 0; i < enemies.size(); i++) {
        enemies.at(i)->makemove();
    }
}

void Floor::togglePause() {
    pause = !pause;
}

void Floor::notified(Enemy *e) {
    int r = e->getX();
    int c = e->getY();
    char name = e->getName();
    if (display.at(r)[c] == '.') {
        display.at(r)[c] = name;
    }
    if (e->getHp() != 0) {
        return;
    }
    display.at(r)[c] = '.';
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
    action += " PC kills " + n + ". ";
    if (name == 'H') {
        int r1, c1 = 0;;
        Treasure *t1 = new Treasure(2);
        t1->setX(e->getX());
        t1->setY(e->getY());
        display.at(t1->getX())[t1->getY()] = 'G';
        Treasure *t2 = new Treasure(2);
        srand(time(NULL));
        while (1) {
            int t = rand() % 9;
            if (t == 0 && display.at(e->getX() - 1)[e->getY()] == '.') {
                r1 = e->getX() - 1;
                c1 = e->getY();
                break;
            } else if (t == 1 && display.at(e->getX() - 1)[e->getY() - 1] == '.') {
                r1 = e->getX() - 1;
                c1 = e->getY() - 1;
                break;
            } else if (t == 2 && display.at(e->getX())[e->getY() - 1] == '.') {
                r1 = e->getX();
                c1 = e->getY() - 1;
                break;
            } else if (t == 3 && display.at(e->getX() + 1)[e->getY() - 1] == '.') {
                r1 = e->getX() + 1;
                c1 = e->getY() - 1;
                break;
            } else if (t == 4 && display.at(e->getX() + 1)[e->getY()] == '.') {
                r1 = e->getX() + 1;
                c1 = e->getY();
                break;
            } else if (t == 5 && display.at(e->getX() + 1)[e->getY() + 1] == '.') {
                r1 = e->getX() + 1;
                c1 = e->getY() + 1;
                break;
            } else if (t == 6 && display.at(e->getX())[e->getY() + 1] == '.') {
                r1 = e->getX();
                c1 = e->getY() + 1;
                break;
            } else if (t == 7 && display.at(e->getX() - 1)[e->getY() + 1] == '.') {
                r1 = e->getX() - 1;
                c1 = e->getY() + 1;
                break;
            } else if (t == 8 && display.at(r)[c] == '.') {
                r1 = r;
                c1 = c;
                break;
            }
        }
        t2->setX(r1);
        t2->setY(c1);
        display.at(r1)[c1] = 'G';
        treasures.emplace_back(t1);
        treasures.emplace_back(t2);
    } else if (name == 'M') {
        Treasure *t = new Treasure(4);
        t->setX(e->getX());
        t->setY(e->getY());
        treasures.emplace_back(t);
        display.at(t->getX())[t->getY()] = 'G';
    } else if (name == 'D') {
        static_cast<Dragon*>(e)->getTreasure()->setDrag(nullptr);
    } else {
        int t = rand() % 2;
        if(t) {
            p->addGold(2);
        } else {
            p->addGold(1);
        }
    }
    for (unsigned i = 0; i < enemies.size(); i++) {
        if (enemies.at(i)->getX() == r && enemies.at(i)->getY() == c) {
            enemies.erase(enemies.begin() + i);
        }
    }
    delete e;
}

void Floor::notified(Potion *po) {
    int r = po->getX();
    int c = po->getY();
    if(po->isRevealed()) {
        display.at(r)[c] = '.';
        for (unsigned i = 0; i < potions.size(); i++) {
            if (potions.at(i)->getX() == r && potions.at(i)->getY() == c) {
                potions.erase(potions.begin() + i);
            }
        }
        delete po;
    }
}

void Floor::notified(Treasure *t) {
    int r = t->getX();
    int c = t->getY();
    for (unsigned i = 0; i < treasures.size(); i++) {
        if(treasures.at(i)->getX() == r && treasures.at(i)->getY() == c) {
            treasures.erase(treasures.begin() + i);
        }
    }
    delete t;
    display.at(r)[c] = '.';
}

struct Point {
    int row, col;
};

Point GivePoint(vector<string> display) {
    Point p;
    while (1) {
        int t = rand() % 5;
        int r , c;
        if (t == 0) {
            r = rand() % 4 + 3;
            c = rand() % 26 + 3;
        } else if (t == 1) {
            r = rand() % 7 + 15;
            c = rand() % 21 + 4;
        } else if (t == 2) {
            r = rand() % 3 + 10;
            c = rand() % 12 + 38;
        } else if (t == 3) {
            int w = rand() % 50;
            if (w < 11) {
                r = rand() % 3 + 16;
                c = rand() % 11 + 65;
            } else {
                r = rand() % 3 + 19;
                c = rand() % 39 + 36;
            }
        } else if (t == 4) {
            int w = rand() % 201;
            if (w < 46) {
                r =  w / 23 + 3;
                c =  w % 23 + 39;
            } else if (w < 77) {
                r = 5;
                c =  (w - 46) + 39;
            } else if (w < 111) {
                r = 6;
                c = w - 77 + 39;
            } else {
                r = (w - 111) / 15 + 7;
                c = (w - 111) % 15 + 60;
            }
        }
        if (display.at(r)[c] == '.') {
            p = {r, c};
            break;
        }
        
    }
    return p;
}



void Floor::init(Player *pl) {
    p = pl;
    //p->clearTemp();
    p->setFloor(this);
    display.clear();
    for (unsigned i = 0; i < enemies.size(); i++) {
        delete enemies.at(i);
    }
    for (unsigned i = 0; i < treasures.size(); i++) {
        delete treasures.at(i);
    }
    for (unsigned i = 0; i < potions.size(); i++) {
        delete potions.at(i);
    }
    enemies.clear();
    treasures.clear();
    potions.clear();
    string s0 =  "|-----------------------------------------------------------------------------|";
    string s1 =  "|                                                                             |";
    string s2 =  "| |--------------------------|        |-----------------------|               |";
    string s3 =  "| |..........................|        |.......................|               |";
    string s4 =  "| |..........................+########+.......................|-------|       |";
    string s5 =  "| |..........................|   #    |...............................|--|    |";
    string s6 =  "| |..........................|   #    |..................................|--| |";
    string s7 =  "| |----------+---------------|   #    |----+----------------|...............| |";
    string s8 =  "|            #                 #############                |...............| |";
    string s9 =  "|            #                 #     |-----+------|         |...............| |";
    string s10 = "|            #                 #     |............|         |...............| |";
    string s11 = "|            ###################     |............|   ######+...............| |";
    string s12 = "|            #                 #     |............|   #     |...............| |";
    string s13 = "|            #                 #     |-----+------|   #     |--------+------| |";
    string s14 = "|  |---------+-----------|     #           #          #              #        |";
    string s15 = "|  |.....................|     #           #          #         |----+------| |";
    string s16 = "|  |.....................|     ########################         |...........| |";
    string s17 = "|  |.....................|     #           #                    |...........| |";
    string s18 = "|  |.....................|     #    |------+--------------------|...........| |";
    string s19 = "|  |.....................|     #    |.......................................| |";
    string s20 = "|  |.....................+##########+.......................................| |";
    string s21 = "|  |.....................|          |.......................................| |";
    string s22 = "|  |---------------------|          |---------------------------------------| |";
    string s23 = "|                                                                             |";
    string s24 = "|-----------------------------------------------------------------------------|";
    display.emplace_back(s0);
    display.emplace_back(s1);
    display.emplace_back(s2);
    display.emplace_back(s3);
    display.emplace_back(s4);
    display.emplace_back(s5);
    display.emplace_back(s6);
    display.emplace_back(s7);
    display.emplace_back(s8);
    display.emplace_back(s9);
    display.emplace_back(s10);
    display.emplace_back(s11);
    display.emplace_back(s12);
    display.emplace_back(s13);
    display.emplace_back(s14);
    display.emplace_back(s15);
    display.emplace_back(s16);
    display.emplace_back(s17);
    display.emplace_back(s18);
    display.emplace_back(s19);
    display.emplace_back(s20);
    display.emplace_back(s21);
    display.emplace_back(s22);
    display.emplace_back(s23);
    display.emplace_back(s24);
    
    srand(time(NULL));
    
    int t = rand() % 5;
    if (t == 0) {//create player
        int r = rand() % 4 + 3;
        int c = rand() % 26 + 3;
        p->setX(r);
        p->setY(c);
        display.at(r)[c] = '@';
    } else if (t == 1) {
        int r = rand() % 7 + 15;
        int c = rand() % 21 + 4;
        p->setX(r);
        p->setY(c);
        display.at(r)[c] = '@';
    } else if (t == 2) {
        int r = rand() % 3 + 10;
        int c = rand() % 12 + 38;
        p->setX(r);
        p->setY(c);
        display.at(r)[c] = '@';
    } else if (t == 3) {
        int w = rand() % 50;
        int r, c;
        if (w < 11) {
            r = rand() % 3 + 16;
            c = rand() % 11 + 65;
        } else {
            r = rand() % 3 + 19;
            c = rand() % 39 + 36;
        }
        p->setX(r);
        p->setY(c);
        display.at(r)[c] = '@';
    } else if (t == 4) {
        int w = rand() % 201;
        int r, c;
        if (w < 46) {
            r =  w / 23 + 3;
            c =  w % 23 + 39;
        } else if (w < 77) {
            r = 5;
            c =  (w - 46) + 39;
        } else if (w < 111) {
            r = 6;
            c = w - 77 + 39;
        } else {
            r = (w - 111) / 15 + 7;
            c = (w - 111) % 15 + 61;
        }
        p->setX(r);
        p->setY(c);
        display.at(r)[c] = '@';
    }
    
    //create stair
    int stair=rand()%5;//choose stair in which floor
    while (stair==t) {
        stair=rand()%5;
    }
    if (stair == 0) {//create stair
        int row = rand() % 4 + 3;
        int col = rand() % 26 + 3;
        display.at(row)[col] = '\\';
    } else if (stair == 1) {
        int row = rand() % 7 + 15;
        int col = rand() % 21 + 4;
        display.at(row)[col] = '\\';
    } else if (stair == 2) {
        int row = rand() % 3 + 10;
        int col = rand() % 12 + 38;
        display.at(row)[col] = '\\';
    } else if (stair == 3) {
        int ww = rand() % 50;
        int row, col;
        if (ww < 11) {
            row = rand() % 3 + 16;
            col = rand() % 11 + 65;
        } else {
            row = rand() % 3 + 19;
            col = rand() % 39 + 36;
        }
        display.at(row)[col] = '\\';
    } else if (stair == 4) {
        int ww = rand() % 201;
        int row, col;
        if (ww < 46) {
            row =  ww / 23 + 3;
            col =  ww % 23 + 39;
        } else if (ww < 77) {
            row = 5;
            col =  (ww - 46) + 39;
        } else if (ww < 111) {
            row = 6;
            col = ww - 77 + 39;
        } else {
            row = (ww - 111) / 15 + 7;
            col = (ww - 111) % 15 + 60;
        }
        display.at(row)[col] = '\\';
    }
    
    //Create Potion
    for (int i = 0; i < 10; i++) {
        Point p = GivePoint(display);
        int r = p.row;
        int c = p.col;
        display[r][c]= 'P';
        int t = rand() % 6;
        Potion *e = new Potion;
        if (t == 0) {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::RH);
        } else if (t == 1) {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::BA);
        } else if (t == 2) {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::BD);
        } else if (t == 3) {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::PH);
        } else if (t == 4) {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::WA);
        } else {
            e->setX(r);
            e->setY(c);
            e->setType(TypeofPotion::WD);
        }
        e->setFloor(this);
        for(unsigned i = 0; i < pl->eaten.size(); i++) {
            if (e->getType() == pl->eaten.at(i)) {
                e->setRevealed();
            }
        }
        potions.emplace_back(e);
    }
    
    //Create gold
    for (int i = 0; i < 10; i++) {
        Point p = GivePoint(display);
        int r=p.row;
        int c=p.col;
        display[r][c]= 'G';
        int t = rand() % 8;
        if (t < 2) {
            Treasure *t = new Treasure(1);
            t->setX(r);
            t->setY(c);
            t->setFloor(this);
            treasures.emplace_back(t);
        } else if (t < 7) {
            Treasure *t = new Treasure(2);
            t->setX(r);
            t->setY(c);
            t->setFloor(this);
            treasures.emplace_back(t);
        } else {
            DragonHoard *t = new DragonHoard;
            t->setX(r);
            t->setY(c);
            display[r][c] = 'G';
            Dragon *d = new Dragon;
            while(1) {
                int w = rand() % 8;
                if (w == 0 && display.at(t->getX() - 1)[t->getY()] == '.' ) {
                    d->setX(t->getX() - 1);
                    d->setY(t->getY());
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 1 && display.at(t->getX() - 1)[t->getY() + 1] == '.') {
                    d->setX(t->getX() - 1);
                    d->setY(t->getY() + 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 2 && display.at(t->getX())[t->getY() + 1] == '.') {
                    d->setX(t->getX());
                    d->setY(t->getY() + 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 3 && display.at(t->getX() + 1)[t->getY() + 1] == '.') {
                    d->setX(t->getX() + 1);
                    d->setY(t->getY() + 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 4 && display.at(t->getX() + 1)[t->getY()] == '.') {
                    d->setX(t->getX() + 1);
                    d->setY(t->getY());
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 5 && display.at(t->getX() + 1)[t->getY() - 1] == '.') {
                    d->setX(t->getX() + 1);
                    d->setY(t->getY() - 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 6 && display.at(t->getX())[t->getY() - 1] == '.') {
                    d->setX(t->getX());
                    d->setY(t->getY() - 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                } else if (w == 7 && display.at(t->getX() - 1)[t->getY() - 1] == '.'){
                    d->setX(t->getX() - 1);
                    d->setY(t->getY() - 1);
                    display[d->getX()][d->getY()] = 'D';
                    break;
                }
                    
            }
            t->setFloor(this);
            d->setFloor(this);
            static_cast<DragonHoard*>(t)->setDrag(static_cast<Dragon*>(d));
            static_cast<Dragon*>(d)->setTreasure(static_cast<DragonHoard*>(t));
            treasures.emplace_back(t);
            enemies.emplace_back(d);
        }
    }
    
    //Create Enemy
    for (int i = 0; i < 20; i++) {
        Point p=GivePoint(display);
        int r=p.row;
        int c=p.col;
        int t = rand() % 18;
        if (t<4) {
            display[r][c]= 'H';
            Human *e = new Human;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            enemies.emplace_back(e);
        } else if (t<7) {
            display[r][c]= 'W';
            Dwarf *e = new Dwarf;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            enemies.emplace_back(e);
        } else if (t<12) {
            display[r][c]= 'L';
            Halfling *e = new Halfling;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            enemies.emplace_back(e);
        } else if (t<14) {
            display[r][c]= 'E';
            Elf *e = new Elf;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            enemies.emplace_back(e);
        } else if (t<16) {
            display[r][c]= 'O';
            Orcs *e = new Orcs;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            enemies.emplace_back(e);
        } else {
            display[r][c]= 'M';
            Merchant *e = new Merchant;
            e->setX(r);
            e->setY(c);
            e->setFloor(this);
            if (pl->atkMerchant) {
                e->setHostile(true);
            }
            enemies.emplace_back(e);
        }
    }
    
    //create Mascot
    if (inclBonus) {
        Point p = GivePoint(display);
        int r = p.row;
        int c = p.col;
        display[r][c] = 'A';
        Mascot *e = new Mascot;
        e->setX(r);
        e->setY(c);
        e->setFloor(this);
        enemies.emplace_back(e);
    }
    action = "Player character has spawned.";
}

void Floor::addaction(std::string s) {
    action += s;
}

void Floor::nextLvl() {
    if (floorNum == 5) {
        isFinished = true;
    } else {
        floorNum++;
        p->clearTemp();
        if (cmdOpt) {
            init2(p);
            return;
        }
        init(p);
    }
}

std::ostream &operator<< (std::ostream &out, const Floor &f)  {
    for (unsigned i = 0; i < f.display.size(); i++) {
        out << f.display.at(i) << endl;
    }
    cout << "Race: " << f.p->getRace() << " Gold: " << f.p->getGold();
    string spaces (51 - to_string(f.p->getGold()).length(), ' ');
    cout << spaces;
    cout << "Floor " << f.floorNum << endl;
    cout << "HP: " << f.p->getHp() << endl;
    cout << "Atk: " << f.p->getAtk() << endl;
    cout << "Def: " << f.p->getDef() << endl;
    cout << "Action: " << f.action << endl;
    return out;
}

void Floor::restart(Player *pl) {
    floorNum = 1;
    if (cmdOpt) {
        init2(pl);
        return;
    }
    init(pl);
}

void Floor::clearAction() {
    action = "";
}

Floor::~Floor() {
    for (unsigned i = 0; i < enemies.size(); i++) {
        delete enemies.at(i);
    }
    for (unsigned i = 0; i < treasures.size(); i++) {
        delete treasures.at(i);
    }
    for (unsigned i = 0; i < potions.size(); i++) {
        delete potions.at(i);
    }
    enemies.clear();
    treasures.clear();
    potions.clear();
}


bool Floor::isPaused() {
    return pause;
}



void Floor::init2(Player *pl) {
    p = pl;
    //p->clearTemp();
    p->setFloor(this);
    for (unsigned i = 0; i < enemies.size(); i++) {
        delete enemies.at(i);
    }
    for (unsigned i = 0; i < treasures.size(); i++) {
        delete treasures.at(i);
    }
    for (unsigned i = 0; i < potions.size(); i++) {
        delete potions.at(i);
    }
    enemies.clear();
    treasures.clear();
    potions.clear();
    display.clear();
    for (int i = (floorNum - 1) * 25; i < floorNum * 25; i++) {
        display.emplace_back(defaultDisplay.at(i));
    }
    for (unsigned i = 0; i < display.size(); i++) {
        for (int j = 0;  j < display.at(i).length(); j++) {
            if (display.at(i)[j] == '0') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::RH);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '1') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::BA);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '2') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::BD);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '3') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::PH);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '4') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::WA);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '5') {
                Potion *po = new Potion;
                po->setType(TypeofPotion::WD);
                po->setX(i);
                po->setY(j);
                po->setFloor(this);
                display.at(i)[j] = 'P';
                for(unsigned i = 0; i < pl->eaten.size(); i++) {
                    if (po->getType() == pl->eaten.at(i)) {
                        po->setRevealed();
                    }
                }
                potions.emplace_back(po);
            } else if (display.at(i)[j] == '6') {
                Treasure *t = new Treasure(2);
                t->setX(i);
                t->setY(j);
                t->setFloor(this);
                display.at(i)[j] = 'G';
                treasures.emplace_back(t);
            } else if (display.at(i)[j] == '7') {
                Treasure *t = new Treasure(1);
                t->setX(i);
                t->setY(j);
                t->setFloor(this);
                display.at(i)[j] = 'G';
                treasures.emplace_back(t);
            } else if (display.at(i)[j] == '8') {
                Treasure *t = new Treasure(4);
                t->setX(i);
                t->setY(j);
                t->setFloor(this);
                display.at(i)[j] = 'G';
                treasures.emplace_back(t);
            } else if (display.at(i)[j] == '9') {
                DragonHoard *t = new DragonHoard;
                t->setX(i);
                t->setY(j);
                t->setFloor(this);
                display.at(i)[j] = 'G';
                Dragon *d = new Dragon;
                d->setTreasure(t);
                d->setFloor(this);
                t->setDrag(d);
                treasures.emplace_back(t);
                if (display.at(i + 1)[j] == 'D') {
                    d->setY(i + 1);
                    d->setY(j);
                } else if (display.at(i + 1)[j - 1] == 'D') {
                    d->setY(i + 1);
                    d->setY(j - 1);
                } else if (display.at(i + 1)[j + 1] == 'D') {
                    d->setY(i + 1);
                    d->setY(j + 1);
                } else if (display.at(i)[j - 1] == 'D') {
                    d->setY(i);
                    d->setY(j - 1);
                } else if (display.at(i)[j + 1] == 'D') {
                    d->setY(i);
                    d->setY(j + 1);
                } else if (display.at(i - 1)[j - 1] == 'D') {
                    d->setY(i - 1);
                    d->setY(j - 1);
                } else if (display.at(i - 1)[j] == 'D') {
                    d->setY(i - 1);
                    d->setY(j);
                } else if (display.at(i - 1)[j + 1] == 'D') {
                    d->setY(i - 1);
                    d->setY(j + 1);
                }
                enemies.emplace_back(d);
            } else if (display.at(i)[j] == 'M') {
                Merchant *e = new Merchant;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                if (pl->atkMerchant) {
                    e->setHostile(true);
                }
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == 'O') {
                Orcs *e = new Orcs;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == 'L') {
                Halfling *e = new Halfling;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == 'H') {
                Human *e = new Human;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == 'W') {
                Dwarf *e = new Dwarf;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == 'E') {
                Elf *e = new Elf;
                e->setX(i);
                e->setY(j);
                e->setFloor(this);
                enemies.emplace_back(e);
            } else if (display.at(i)[j] == '@') {
                p->setX(i);
                p->setY(j);
            }
        }
    }
    action = "Player character has spawned.";
}

