//
//  Pool.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 14/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__Pool__
#define __N_body_problem__Pool__

#include <stdio.h>
#include "BHTree.h"
#include "NB_Body.h"

typedef struct{
    int count;
    int capacity;
    BHTree* trees;
    Body* bodies;
} Pool;

BHTree*  Pool_getNextTree(Pool* pool, Quad quad);
void    Pool_init(Pool* pool, int capacity);

#endif /* defined(__N_body_problem__Pool__) */
