//
//  NB_Calculations.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include "NB_Calculations.h"


void calculate_forces(Body* bodies, UniverseProperties uniprop){
    int i,j;
    double r;
    
    #pragma omp parallel for private(j,r)
    for (i=0; i<uniprop.N; i++) {
        bodies[i].Fx = 0;
        bodies[i].Fy = 0;
        for (j=0; j<uniprop.N; j++) {
            if (i==j) {
                continue;
            }
            r = getDistance(bodies[i], bodies[j]);
            bodies[i].Fx += MASS / ((NB_EPSILON + r)*(NB_EPSILON + r)*(NB_EPSILON + r)) * (bodies[i].x - bodies[j].x);
            bodies[i].Fy += MASS / ((NB_EPSILON + r)*(NB_EPSILON + r)*(NB_EPSILON + r)) * (bodies[i].y - bodies[j].y);
        }
        bodies[i].Fx *= -uniprop.gravity * MASS;
        bodies[i].Fy *= -uniprop.gravity * MASS;
    }
}

void calculate_velocity(Body* bodies, UniverseProperties uniprop){
    int i;
    double ax, ay;
    
    calculate_forces(bodies, uniprop);
    
    for (i=0; i<uniprop.N; i++) {
        ax = bodies[i].Fx / MASS;
        ay = bodies[i].Fy / MASS;
        
        bodies[i].u += uniprop.delta_t * ax;
        bodies[i].v += uniprop.delta_t * ay;
        
        bodies[i].x += uniprop.delta_t * bodies[i].u;
        bodies[i].y += uniprop.delta_t * bodies[i].v;
        /*
        if ((bodies[i].x >= 1) || (bodies[i].y >= 1)) {
            printf("X = %f Y = %f \n",bodies[i].x, bodies[i].y);
        }
         */
    }
    
}
