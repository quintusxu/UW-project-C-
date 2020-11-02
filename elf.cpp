//
//  elf.cpp
//  project
//
//  Created by Chenkun Xu on 2018/7/12.
//  Copyright © 2018年 Chenkun Xu. All rights reserved.
//

#include "elf.hpp"
#include <cstdlib>
#include <ctime>

Elf::Elf() {
    hp=140;
    atk=30;
    def=10;
    name = 'E';
    hostile=true;
    canMove=true;
}

Elf::~Elf() {}
