//
//  character.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef character_hpp
#define character_hpp
#include "item.hpp"


class Character : public Item {
protected:
    int hp, atk, def;
public:
    int getHp();
    virtual int getAtk();
    virtual int getDef();
    void changeHp(int);
    virtual ~Character() = default;
};

#endif /* character_hpp */
