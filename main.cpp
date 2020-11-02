//
//  main.cpp
//  cc3k
//
//  Created by Aurora Jin on 2018-07-18.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "floor.hpp"
#include "enemy.hpp"
#include "shade.hpp"
#include "drow.hpp"
#include "vampire.hpp"
#include "troll.hpp"
#include "potion.hpp"
#include "goblin.hpp"
#include "turtle.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    Floor f;
    string cmd;
    Player *p;
    if (argc == 2) {
        f.cmdOpt = true;
        ifstream map(argv[1]);
        string s;
        while (getline(map, s)) {
            f.defaultDisplay.emplace_back(s);
        }
        cout << "Please select one of:" << endl;
        cout << "Shade(s)" << endl;
        cout << "Drow(d)" << endl;
        cout << "Vampire(v)" << endl;
        cout << "Troll(t)" << endl;
        cout << "Goblin(g)" << endl;
        cin >> cmd;
        if (cmd == "d") {
            p =  new Drow;
        } else if (cmd == "v") {
            p = new Vampire;
        } else if (cmd == "t") {
            p =  new Troll;
        } else if (cmd == "g") {
            p = new Goblin;
        } else {
            p =  new Shade;
        }
        f.init2(p);
    } else {
        cout << "Would you like to include bonus options? Yes(y) or No." << endl;
        cin >> cmd;
        cout << "Please select one of:" << endl;
        cout << "Shade(s)" << endl;
        cout << "Drow(d)" << endl;
        cout << "Vampire(v)" << endl;
        cout << "Troll(t)" << endl;
        cout << "Goblin(g)" << endl;
        if (cmd == "y") {
            f.inclBonus = true;
            cout << "Turtle(o)" << endl;
        } else {
            f.inclBonus = false;
        }
        cin >> cmd;
        if (cmd == "d") {
            p =  new Drow;
        } else if (cmd == "v") {
            p = new Vampire;
        } else if (cmd == "t") {
            p =  new Troll;
        } else if (cmd == "g") {
            p = new Goblin;
        } else if (cmd == "o" && f.inclBonus) {
            p = new Turtle;
        } else {
            p =  new Shade;
        }
        f.init(p);
    }
    cout << f;
    while(true) {
        cin >> cmd;
        if (cmd == "no") {
            p->move("no");
        } else if (cmd == "ne") {
            p->move("ne");
        } else if (cmd == "ea") {
            p->move("ea");
        } else if (cmd == "se") {
            p->move("se");
        } else if (cmd == "so") {
            p->move("so");
        } else if (cmd == "sw") {
            p->move("sw");
        } else if (cmd == "we") {
            p->move("we");
        } else if (cmd == "nw") {
            p->move("nw");
        } else if (cmd == "u") {
            cin >> cmd;
            int r = 0, c = 0;
            if (cmd == "no") {
                r = -1;
                c = 0;
            } else if (cmd == "ne") {
                r = -1;
                c = 1;
            } else if (cmd == "ea") {
                r = 0;
                c = 1;
            } else if (cmd == "se") {
                r = 1;
                c = 1;
            } else if (cmd == "so") {
                r = 1;
                c = 0;
            } else if (cmd == "sw") {
                r = 1;
                c = -1;
            } else if (cmd == "we") {
                r = 0;
                c = -1;
            } else if (cmd == "nw") {
                r = -1;
                c = -1;
            }
            for (unsigned i = 0; i < f.potions.size(); i++) {
                if ((f.potions.at(i)->getX() ==  p->getX() + r) && (f.potions.at(i)->getY() == p->getY() + c)) {
                    f.potions.at(i)->accept(p);
                }
            }
        } else if (cmd == "a") {
            cin >> cmd;
            int r, c;
            if (cmd == "no") {
                r = -1;
                c = 0;
            } else if (cmd == "ne") {
                r = -1;
                c = 1;
            } else if (cmd == "ea") {
                r = 0;
                c = 1;
            } else if (cmd == "se") {
                r = 1;
                c = 1;
            } else if (cmd == "so") {
                r = 1;
                c = 0;
            } else if (cmd == "sw") {
                r = 1;
                c = -1;
            } else if (cmd == "we") {
                r = 0;
                c = -1;
            } else {
                r = -1;
                c = -1;
            }
            for (unsigned i = 0; i < f.enemies.size(); i++) {
                if ((f.enemies.at(i)->getX() ==  p->getX() + r) && (f.enemies.at(i)->getY() == p->getY() + c)) {
                    p->accept(f.enemies.at(i));
                }
            }
        } else if (cmd == "f") {
            f.togglePause();
        } else if (cmd == "r") {
            delete p;
            if (argc == 2) {
                cout << "Please select one of:" << endl;
                cout << "Shade(s)" << endl;
                cout << "Drow(d)" << endl;
                cout << "Vampire(v)" << endl;
                cout << "Troll(t)" << endl;
                cout << "Goblin(g)" << endl;
                cin >> cmd;
                if (cmd == "d") {
                    p =  new Drow;
                } else if (cmd == "v") {
                    p = new Vampire;
                } else if (cmd == "t") {
                    p =  new Troll;
                } else if (cmd == "g") {
                    p = new Goblin;
                } else {
                    p =  new Shade;
                }
            } else {
                cout << "Would you like to include bonus options? Yes(y) or No." << endl;
                cin >> cmd;
                cout << "Please select one of:" << endl;
                cout << "Shade(s)" << endl;
                cout << "Drow(d)" << endl;
                cout << "Vampire(v)" << endl;
                cout << "Troll(t)" << endl;
                cout << "Goblin(g)" << endl;
                if (cmd == "y") {
                    f.inclBonus = true;
                    cout << "Turtle(o)" << endl;
                } else {
                    f.inclBonus = false;
                }
                cin >> cmd;
                if (cmd == "d") {
                    p =  new Drow;
                } else if (cmd == "v") {
                    p = new Vampire;
                } else if (cmd == "t") {
                    p =  new Troll;
                } else if (cmd == "g") {
                    p = new Goblin;
                } else if (cmd == "o" && f.inclBonus) {
                    p = new Turtle;
                } else {
                    p =  new Shade;
                }
            }
            f.restart(p);
        } else if (cmd == "q") {
            delete p;
            return 0;
        }
        cout << f;
        f.clearAction();
        if ((p->getHp() == 0 && !f.isFinished) || f.isFinished) {
            if (!f.isFinished) {
                cout << "Game Over!" << endl;
            } else {
                cout << "Congratulations! You win!" << endl;
            }
            cout << "Score: " << p->getGold() << endl;
            delete p;
            cout << "Would you like to restart(r) or quit?" << endl;
            while(1) {
                cin >> cmd;
                if (cmd == "r") {
                    if (argc == 2) {
                        cout << "Please select one of:" << endl;
                        cout << "Shade(s)" << endl;
                        cout << "Drow(d)" << endl;
                        cout << "Vampire(v)" << endl;
                        cout << "Troll(t)" << endl;
                        cout << "Goblin(g)" << endl;
                        cin >> cmd;
                        if (cmd == "d") {
                            p =  new Drow;
                        } else if (cmd == "v") {
                            p = new Vampire;
                        } else if (cmd == "t") {
                            p =  new Troll;
                        } else if (cmd == "g") {
                            p = new Goblin;
                        } else {
                            p =  new Shade;
                        }
                    } else {
                        cout << "Would you like to include bonus options? Yes(y) or No." << endl;
                        cin >> cmd;
                        cout << "Please select one of:" << endl;
                        cout << "Shade(s)" << endl;
                        cout << "Drow(d)" << endl;
                        cout << "Vampire(v)" << endl;
                        cout << "Troll(t)" << endl;
                        cout << "Goblin(g)" << endl;
                        if (cmd == "y") {
                            f.inclBonus = true;
                            cout << "Turtle(o)" << endl;
                        } else {
                            f.inclBonus = false;
                        }
                        cin >> cmd;
                        if (cmd == "d") {
                            p =  new Drow;
                        } else if (cmd == "v") {
                            p = new Vampire;
                        } else if (cmd == "t") {
                            p =  new Troll;
                        } else if (cmd == "g") {
                            p = new Goblin;
                        } else if (cmd == "o" && f.inclBonus) {
                            p = new Turtle;
                        } else {
                            p =  new Shade;
                        }
                    }
                    f.restart(p);
                    cout << f;
                    break;
                } else if (cmd == "q") {
                    return 0;
                }
            }
        }
        
    }
}
