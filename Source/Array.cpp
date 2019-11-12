//
//  Array.cpp
//  CommandLineTool
//
//  Created by Maximillian Walley on 08/10/2019.
//  Copyright © 2019 Tom Mitchell. All rights reserved.
//

#include "Array.hpp"

Array::Array()
{
    data = nullptr;
    no_Items = 0;
    
}

Array::~Array()
{
    delete[] data;
}

void Array::add(float itemValue)
{
    no_Items++;
    float* temp = new float[no_Items];
    
    if(no_Items > 1)
    {
        for(int index = 0; index < no_Items-1; index++)
        {
            temp[index] = data[index];
        }
        
        delete[] data;
        data = temp;
        
    }
    else {
        data = new float[1];

    }
    data[no_Items-1] = itemValue;
    
}

float Array::get(int index)
{
    return data[index];
}

void Array::remove(int index)
{
    no_Items--;
    float* temp = new float[no_Items];
    
    for(int i = index; i < no_Items; i++)
    {
        if(i == no_Items)
        {
            data[no_Items] = NULL;
        }
        else
        {
            data[i] = data[i+1];
        }
    }
    
    for(int i = 0; i < no_Items; i++)
    {
        temp[i] = data[i];
    }
    
    delete [] data;
    data = temp;
}

int Array::size()
{
    return no_Items;
}
