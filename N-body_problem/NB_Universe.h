//
//  NB_Universe.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__NB_Universe__
#define __N_body_problem__NB_Universe__

#include <stdio.h>

typedef struct{
    int N;
    double gravity;
    int L_dim;
    int W_dim;
    int V;
    double delta_t;
    double alpha;
} UniverseProperties;

#endif /* defined(__N_body_problem__NB_Universe__) */

