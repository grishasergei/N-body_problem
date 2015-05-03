//
//  Quad.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 03/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include "Quad.h"

bool quad_contains(Quad quad, double x, double y){
    bool result = false;
    if ((x<=quad.xmid + quad.length/2) && (x>=quad.xmid - quad.length/2) && (y<=quad.ymid + quad.length/2) &&(y>=quad.ymid - quad.length/2))  {
        result = true;
    }
    return result;
}

Quad quad_subdivide_NW(Quad quad){
    Quad q;
    q.xmid = quad.xmid - quad.length/4;
    q.ymid = quad.ymid + quad.length/4;
    q.length = quad.length/2;
    return q;
}

Quad quad_subdivide_NE(Quad quad){
    Quad q;
    q.xmid = quad.xmid + quad.length/4;
    q.ymid = quad.ymid + quad.length/4;
    q.length = quad.length/2;
    return q;
}

Quad quad_subdivide_SW(Quad quad){
    Quad q;
    q.xmid = quad.xmid - quad.length/4;
    q.ymid = quad.ymid - quad.length/4;
    q.length = quad.length/2;
    return q;
}

Quad quad_subdivide_SE(Quad quad){
    Quad q;
    q.xmid = quad.xmid + quad.length/4;
    q.ymid = quad.ymid - quad.length/4;
    q.length = quad.length/2;
    return q;
}