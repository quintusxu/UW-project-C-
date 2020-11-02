//
//  item.hpp
//  a4q5
//
//  Created by Aurora Jin on 2018-07-10.
//  Copyright © 2018 Aurora Jin. All rights reserved.
//

#ifndef item_hpp
#define item_hpp

class Floor;

class Item {
    int x, y;
protected:
    Floor *f;
public:
    void setFloor(Floor *);
    int getX();
    int getY();
    void setX(int);
    void setY(int);
    virtual ~Item() = default;
};

#endif /* item_hpp */
