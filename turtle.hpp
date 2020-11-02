//
//  turtle.hpp
//  cc3k
//
//  Created by Aurora Jin on 2018-07-21.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef turtle_hpp
#define turtle_hpp

#include "player.hpp"

class Turtle: public Player {
public:
    Turtle();
    virtual ~Turtle();
    void visit(Potion *) override;
};

#endif /* turtle_hpp */
