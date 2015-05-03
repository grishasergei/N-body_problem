//
//  main.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libiomp/omp.h>

#include "NB.Globals.h"
#include "NB_Universe.h"
#include "NB_Body.h"
#include "NB_Calculations.h"
#include "BHTree.h"
#include "Quad.h"

#include "graphics.h"

UniverseProperties uniprops;
Body* bodies_list;
double T;

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
    
    #pragma omp parallel for private(r, theta, r_prime)
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

void display(void){
    int i;
    Quad quad;
    quad.length = 1;
    quad.xmid = 0.5;
    quad.ymid = 0.5;

    drawBodies(bodies_list, uniprops.N);
    
    BHTree* tree = BHTree_create(quad);
    for (i=0; i<uniprops.N; i++) {
        BHTree_insertBody(tree, bodies_list[i]);
        printf("ID: %d inserted \n",bodies_list[i].ID);
    }
    for (i=0; i<uniprops.N; i++) {
        BHTree_updateForce(*tree, &bodies_list[i], uniprops);
    }
    update_positions(bodies_list, uniprops);
    //calculate_velocity(bodies_list, uniprops);
}

int main(int argc, const char * argv[]) {
    
    T = 0;
    
    uniprops.N = 5000;
    uniprops.delta_t = 1E-3;
    uniprops.L_dim = 1;
    uniprops.W_dim = 1;
    uniprops.V = 50;
    uniprops.alpha = 0.25;
    uniprops.gravity = 100 / uniprops.N;
    
    bodies_list = (Body*)calloc(uniprops.N,sizeof(Body));
    
    initialize_bodies(bodies_list, uniprops);
    
    graphicsInit(&argc, argv, display);
    glutMainLoop();
    
    free(bodies_list);
    
    
    printf("Hello, World!\n");
    return 0;
}

