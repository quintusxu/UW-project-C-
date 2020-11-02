//
//  treasure.hpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#ifndef treasure_hpp
#define treasure_hpp

#include "item.hpp"

class Player;

class Treasure : public Item {
protected:
    int value;
public:
    void accept(Player*);
    int getVal();
    Treasure(int val);
    ~Treasure();
};



#endif /* treasure_hpp */
