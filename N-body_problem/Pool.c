//
//  Pool.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 14/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include "Pool.h"
#include <string.h>
#include "stdlib.h"
#include "NB.Globals.h"

BHTree*  PoolTree_getNextTree(PoolTree* pool, PoolBody* poolBody, Quad quad){
    if (pool->count>=(pool->capacity-1)) {
        pool->capacity += pool->capacity;
        pool->trees = (BHTree*)realloc(pool->trees, sizeof(BHTree)*pool->capacity);
    }
    pool->count++;
    pool->trees[pool->count].quad = quad;
    pool->trees[pool->count].body = PoolBody_getNext(poolBody);
    return &pool->trees[pool->count];
}

void    PoolTree_init(PoolTree* pool, int capacity){
    pool->capacity = capacity;
    pool->count = -1;
    pool->trees = (BHTree*)calloc(capacity, sizeof(BHTree));
}

Body*   PoolBody_getNext(PoolBody* pool){
    if (pool->count>=(pool->capacity-1)) {
        pool->capacity += pool->capacity;
        pool->bodies = (Body*)realloc(pool->bodies, sizeof(Body)*pool->capacity);
        bodies_list = pool->bodies;
    }
    pool->count++;
    memset(&pool->bodies[pool->count], 0, sizeof(Body));
    pool->bodies[pool->count].ID = -1;
    return &pool->bodies[pool->count];
}

void    PoolBody_init(PoolBody* pool, int capacity){
    pool->capacity = capacity;
    pool->count = -1;
    pool->bodies = (Body*)calloc(capacity, sizeof(Body));
}
/*
void    PoolBody_setCapacity(PoolBody* pool, int capacity){
    pool->capacity = capacity;
    pool->bodies = (Body*)realloc(pool->bodies, sizeof(Body)*pool->capacity);
    if (pool->count >= (pool->capacity-1)) {
        pool->count = pool->capacity-1;
    }
    
}*/