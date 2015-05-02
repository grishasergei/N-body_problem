//
//  main.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "NB.Globals.h"
#include <math.h>
#include "NB_Universe.h"
#include "NB_Body.h"
#include <libiomp/omp.h>
//#include "graphics.h"
//#include <GLUT/glut.h>

UniverseProperties uniprops;
Body* bodies_list;

double uniform_rand(double a, double b){
    return rand()/(RAND_MAX + 1.0)*(b-a) + a;
}

void initialize_bodies(Body* bodies, UniverseProperties universe){
    int i;
    double r;
    double theta;
    double b = (double) universe.L_dim / 4;
    double pi2 = 2 * M_PI;
    double r_prime;
    
    #pragma omp parallel for private(r, theta, r_prime)
    for (i=0; i<universe.N; i++) {
        r = uniform_rand(0,b);
        theta = uniform_rand(0,pi2);
        bodies[i].x = (double)universe.L_dim/2 + r*cos(theta);
        bodies[i].y = (double)universe.W_dim/2 + universe.alpha * r * sin(theta);
        r_prime = sqrt((bodies[i].x - universe.L_dim/2)*(bodies[i].x - universe.L_dim/2) +
                       (bodies[i].y - universe.W_dim/2)*(bodies[i].y - universe.W_dim/2));
        bodies[i].u = -universe.V * r_prime * sin(theta);
        bodies[i].v = universe.V * r_prime * cos(theta);
    }
}

void display(void){
    drawBodies(bodies_list, uniprops.N);
}

int main(int argc, const char * argv[]) {

    
    uniprops.N = 2500;
    uniprops.delta_t = 1E-3;
    uniprops.L_dim = 1;
    uniprops.W_dim = 1;
    uniprops.V = 50;
    uniprops.alpha = 0.25;
    
    bodies_list = (Body*)calloc(uniprops.N,sizeof(Body));
    
    initialize_bodies(bodies_list, uniprops);
    
    graphicsInit(&argc, argv, display);
    glutMainLoop();
    
    free(bodies_list);
    
    
    printf("Hello, World!\n");
    return 0;
}

