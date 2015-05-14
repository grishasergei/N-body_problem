//
//  BHTree.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 03/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__BHTree__
#define __N_body_problem__BHTree__

#include <stdio.h>
#include "NB_Body.h"
#include "stdbool.h"
#include "Quad.h"


struct BHTree{
    Body* body;
    Quad quad;
    struct BHTree *NW;
    struct BHTree *NE;
    struct BHTree *SW;
    struct BHTree *SE;
};

typedef struct BHTree BHTree;

void    BHTree_destroy(BHTree* tree);
bool    BHTree_isExternal(BHTree* tree);
void    BHTree_insertBody(BHTree* tree, Body* body);
void    BHTree_updateForce(BHTree* tree, Body* body, UniverseProperties uniprops);


#endif /* defined(__N_body_problem__BHTree__) */
