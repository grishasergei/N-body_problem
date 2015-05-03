//
//  NB_Body.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__NB_Body__
#define __N_body_problem__NB_Body__

#include <stdio.h>
#include "stdbool.h"
#include "Quad.h"
#include "NB_Universe.h"

typedef struct{
    int ID;
    double x;
    double y;
    double Fx;
    double Fy;
    double u;
    double v;
    double mass;
}Body;

double  getDistance(Body a, Body b);
bool    body_inQuad(Body body, Quad quad);
void    Body_addAtoB(Body a, Body* b);
void    body_addForce(Body* a, Body b, UniverseProperties uniprops);

#endif /* defined(__N_body_problem__NB_Body__) */

