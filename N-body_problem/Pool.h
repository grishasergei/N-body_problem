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
} PoolTree;

typedef struct{
    int count;
    int capacity;
    Body* bodies;
} PoolBody;

BHTree*  PoolTree_getNextTree(PoolTree* pool, PoolBody* poolBody, Quad quad);
void    PoolTree_init(PoolTree* pool, int capacity);

Body*   PoolBody_getNext(PoolBody* pool);
void    PoolBody_init(PoolBody* pool, int capacity);

//void    PoolBody_setCapacity(PoolBody* pool, int capacity);



#endif /* defined(__N_body_problem__Pool__) */
