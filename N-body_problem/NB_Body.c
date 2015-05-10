//
//  NB_Body.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include "NB_Body.h"
#include "NB.Globals.h"
#include <math.h>

double getDistance(Body a, Body b){
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
}

bool body_inQuad(Body body, Quad quad){
    return quad_contains(quad, body.x, body.y);
}

void Body_addAtoB(Body a, Body *b){
    double m = a.mass + b->mass;
    b->x = (a.x*a.mass + b->x*b->mass) / m;
    b->y = (a.y*a.mass + b->y*b->mass) / m;
    b->mass = m;
}

void body_addForce(Body* a, Body *b, UniverseProperties uniprops){
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double dist = sqrt(dx*dx +dy*dy);

    double F = uniprops.gravity * a->mass * b->mass / ((dist + NB_EPSILON)*(dist + NB_EPSILON));
    a->Fx += F * dx / (dist + NB_EPSILON);
    a->Fy += F * dy / (dist + NB_EPSILON);
}

bool    Body_areEqual(Body* a, Body* b){
    return (a->ID == b->ID) && (a->mass == b->mass) && (a->x == b->x) && (a->y == b->y);
}