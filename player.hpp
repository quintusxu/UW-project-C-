//
//  player.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "potion.hpp"
#include "enemy.hpp"
#include "treasure.hpp"
#include "character.hpp"
#include <vector>
#include <string>

class Player : public Character {
protected:
    std::string race;
    int gold = 0, tAtk = 0, tDef = 0, maxHp;
    char walkedOn = '.';
public:
    std::vector<TypeofPotion> eaten;
    bool atkMerchant = false;
    std::string getRace();
    int getAtk() override;
    int getDef() override;
    int getGold();
    void addGold(int);
    void clearTemp();
    void move(std::string);
    void visit(Treasure*);
    void visit(Enemy*);
    virtual void visit(Potion*);
    void accept(Enemy *);
    virtual ~Player() = default;
};
#endif /* player_hpp */
