//
//  dragonhoard.hpp
//  project
//
//  Created by Chenkun Xu on 2018/7/16.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#ifndef dragonhoard_hpp
#define dragonhoard_hpp

#include "treasure.hpp"
#include "basicenemy.hpp"

class Dragon;

class DragonHoard : public Treasure {
    Dragon *drag;
public:
    virtual ~DragonHoard();
    void setDrag(Dragon*);
    bool getDragDead();
    DragonHoard();
};

#endif /* dragonhoard_hpp */
