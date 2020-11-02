//
//  enemy.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-11.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include "character.hpp"

class Player;
class Enemy : public Character {
protected:
    bool hostile;
    bool canMove;
    char name;
public:
    void visit(Player*);
    void makemove();
    char getName();
    void setHostile(bool);
    virtual void accept(Player*);
    virtual ~Enemy() = default;
    
};

#endif /* enemy_hpp */
