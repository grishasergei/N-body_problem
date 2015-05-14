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

BHTree*  Pool_getNextTree(Pool* pool, Quad quad){
    if (pool->count>=(pool->capacity-1)) {
        pool->capacity += pool->capacity;
        pool->trees = (BHTree*)realloc(pool->trees, sizeof(BHTree)*pool->capacity);
        pool->bodies = (Body*)realloc(pool->bodies, sizeof(Body)*pool->capacity);
        int i;
        for (i=pool->count; i<pool->capacity-1; i++) {
            pool->trees[i].body = &pool->bodies[i];
        }
    }
    pool->count++;
    pool->trees[pool->count].quad = quad;
    pool->trees[pool->count].body->ID = -1;
    return &pool->trees[pool->count];
}

void    Pool_init(Pool* pool, int capacity){
    int i;
    
    pool->capacity = capacity;
    pool->count = -1;
    pool->trees = (BHTree*)calloc(capacity, sizeof(BHTree));
    pool->bodies = (Body*)calloc(capacity, sizeof(Body));
    
    for (i=0; i<capacity; i++) {
        pool->trees[i].body = &pool->bodies[i];
    }
    
}