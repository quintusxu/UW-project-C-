//
//  floor.hpp
//  project
//
//  Created by Chenkun Xu on 2018/7/13.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#ifndef floor_hpp
#define floor_hpp
#include <string>
#include <vector>
#include "player.hpp"
#include "treasure.hpp"
#include "potion.hpp"
#include "halfling.hpp"
#include "basicenemy.hpp"
#include "mascot.hpp"
#include "dwarf.hpp"
#include "orcs.hpp"
#include "elf.hpp"

class Enemy;
class Potion;
class Treasure;

class Floor {
    std::string race;
    std::string action="";
    bool pause = false;
    int floorNum = 1;
public:
    std::vector<std::string> display;
    std::vector<std::string> defaultDisplay;
    std::vector<Potion*> potions;
    std::vector<Enemy*> enemies;
    std::vector<Treasure*> treasures;
    bool inclBonus = false;
    bool cmdOpt = false;
    ~Floor();
    bool isPaused();
    Player *p;
    bool isFinished = false;
    void nextLvl();
    void setRace(std::string);
    void togglePause();
    void notified(); //actions other than movements. notify enemies to move.
    void notified(std::string); //notify movements
    void notified(Enemy*);
    void notified(Potion*);
    void notified(Treasure*);
    void init(Player*);
    void init2(Player*);
    void addaction(std::string);
    void restart(Player*);
    void clearAction();
    friend std::ostream &operator<< (std::ostream &out, const Floor &f);    
};
#endif /* floor_hpp */
