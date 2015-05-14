//
//  NB_Calculations.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include "NB_Calculations.h"
#include <math.h>
#include <libiomp/omp.h>

void update_positions(Body *bodies, UniverseProperties uniprop){
    int i;
    double ax, ay;
    
    //#pragma omp parallel for private(ax, ay)
    for (i=0; i<uniprop.N; i++) {
        ax = bodies[i].Fx / MASS;
        ay = bodies[i].Fy / MASS;
        
        bodies[i].u += uniprop.delta_t * ax;
        bodies[i].v += uniprop.delta_t * ay;
        
        bodies[i].x += uniprop.delta_t * bodies[i].u;
        bodies[i].y += uniprop.delta_t * bodies[i].v;
    }
}

double uniform_rand(double a, double b){
    return rand()/(RAND_MAX + 1.0)*(b-a) + a;
}

void initialize_bodies(Body* bodies, UniverseProperties universe){
    int i;
    double r;
    double theta;
    double b = universe.L_dim / 4;
    double pi2 = 2 * M_PI;
    double r_prime;
    
    #pragma omp for private(r, theta, r_prime)
    for (i=0; i<universe.N; i++) {
        r = uniform_rand(0,b);
        theta = uniform_rand(0,pi2);
        bodies[i].x = universe.L_dim/2 + r*cos(theta);
        bodies[i].y = universe.W_dim/2 + universe.alpha * r * sin(theta);
        if ((bodies[i].x >=1) || (bodies[i].y >= 1)) {
            printf("X = %f Y = %f \n",bodies[i].x, bodies[i].y);
        }
        
        r_prime = sqrt((bodies[i].x - universe.L_dim/2)*(bodies[i].x - universe.L_dim/2) +
                       (bodies[i].y - universe.W_dim/2)*(bodies[i].y - universe.W_dim/2));
        bodies[i].u = -universe.V * r_prime * sin(theta);
        bodies[i].v = universe.V * r_prime * cos(theta);
        bodies[i].ID = i;
        bodies[i].mass = 1;
    }
    
    
}

