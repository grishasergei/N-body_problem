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

typedef struct{
    double x;
    double y;
    double Fx;
    double Fy;
    double u;
    double v;
}Body;

double getDistance(Body a, Body b);

#endif /* defined(__N_body_problem__NB_Body__) */

