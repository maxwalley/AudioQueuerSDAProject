//
//  Array.hpp
//  CommandLineTool
//
//  Created by Maximillian Walley on 08/10/2019.
//  Copyright © 2019 Tom Mitchell. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdio.h>

#pragma once

class Array
{
public:
    Array();
    ~Array();
    void add(float itemValue);
    float get(int index);
    void remove(int index);
    int size();
    
private:
    float* data;
    int no_Items;
};

#endif /* Array_hpp */
