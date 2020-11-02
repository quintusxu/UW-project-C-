//
//  drow.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-12.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef drow_hpp
#define drow_hpp

#include "player.hpp"

class Drow : public Player {
public:
    void visit(Potion*) override;
    Drow();
    virtual ~Drow();
};
#endif /* drow_hpp */
