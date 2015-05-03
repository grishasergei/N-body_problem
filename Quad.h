//
//  Quad.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 03/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__Quad__
#define __N_body_problem__Quad__

#include <stdio.h>
#include "stdbool.h"

typedef struct{
    double xmid, ymid;
    double length;
} Quad;

bool quad_contains(Quad quad, double x, double y);
Quad quad_subdivide_NW(Quad quad);
Quad quad_subdivide_NE(Quad quad);
Quad quad_subdivide_SW(Quad quad);
Quad quad_subdivide_SE(Quad quad);



#endif /* defined(__N_body_problem__Quad__) */
