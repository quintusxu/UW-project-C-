//
//  basicenemy.hpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#ifndef basicenemy_hpp
#define basicenemy_hpp
#include "enemy.hpp"

class DragonHoard;

class BasicEnemy: public Enemy {
public:
    virtual ~BasicEnemy()=default;
};

class Human: public BasicEnemy {
public:
    Human();
    virtual ~Human();
};

class Merchant: public BasicEnemy {
public:
    Merchant();
    virtual ~Merchant();
};

class Dragon: public BasicEnemy {
public:
    DragonHoard *t;
    Dragon();
    virtual ~Dragon();
    DragonHoard* getTreasure();
    void setTreasure(DragonHoard *);
};
#endif /* basicenemy_hpp */
