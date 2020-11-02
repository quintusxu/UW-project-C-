//
//  potion.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef potion_hpp
#define potion_hpp
#include "item.hpp"
#include <string>

class Player;

enum class TypeofPotion {RH, BA, BD, PH, WA, WD};

class Potion : public Item {
    TypeofPotion type;
    bool revealed = false;
public:
    void accept(Player*);
    Potion();
    bool isRevealed();
    void setRevealed();
    void setType(TypeofPotion);
    TypeofPotion getType();
    virtual ~Potion();
};

#endif /* potion_hpp */
