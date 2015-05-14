//
//  main.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//
#include "BHTree.h"
#include "NB_Body.h"
#include "Quad.h"
#include "NB.Globals.h"
#include "NB_Universe.h"
#include "NB_Calculations.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <libiomp/omp.h>
#include "graphics.h"

UniverseProperties uniprops;
Body* bodies_list;
double T;
int count;
int N_ITERATIONS = 1000;
double time_to_create_bh_tree, time_to_calc_forces, time_to_update_positions;
double avg_time_to_create_bh_tree, avg_time_to_calc_forces, avg_time_to_update_positions;

void display(void){
    struct timeval t1, t2;
    int i;
    Quad quad;
    quad.length = 1;
    quad.xmid = 0.5;
    quad.ymid = 0.5;
    
    //printf("Iteration: %d\n", count);
    count++;
    
    drawBodies(bodies_list, uniprops.N);
    
    /*
     Create BH tree
     */
    gettimeofday(&t1,NULL);

    Pool_init(&pool, 10000);
    
    BHTree* tree = Pool_getNextTree(&pool, quad);
    
    
    for (i=0; i<uniprops.N; i++) {
        BHTree_insertBody(tree, &bodies_list[i]);
    }
    gettimeofday(&t2,NULL);
    time_to_create_bh_tree += t2.tv_sec - t1.tv_sec + (double)(t2.tv_usec - t1.tv_usec)/1000000;
    //printf("The time taken is.. %f\n",(double)(t2-t1)/CLOCKS_PER_SEC);

    /*
     Calculate forces
     */
    gettimeofday(&t1,NULL);
    //#pragma omp for
    for (i=0; i<uniprops.N; i++) {
        bodies_list[i].Fx = 0;
        bodies_list[i].Fy = 0;
        BHTree_updateForce(tree, &bodies_list[i], uniprops);
    }
    gettimeofday(&t2,NULL);
    time_to_calc_forces += t2.tv_sec - t1.tv_sec + (double)(t2.tv_usec - t1.tv_usec)/1000000;
    
    //BHTree_destroy(tree);
    
    free(pool.bodies);
    free(pool.trees);
    
    /*
     Update positions
     */
    gettimeofday(&t1,NULL);
    update_positions(bodies_list, uniprops);
    gettimeofday(&t2,NULL);
    time_to_update_positions += t2.tv_sec - t1.tv_sec + (double)(t2.tv_usec - t1.tv_usec)/1000000;

    //if (count>N_ITERATIONS-1) {
    /*
        avg_time_to_calc_forces = time_to_calc_forces / count;
        avg_time_to_create_bh_tree = time_to_create_bh_tree / count;
        avg_time_to_update_positions = time_to_update_positions / count;
        printf("Average time:\n");
        printf("Create BH tree: %f\n", avg_time_to_create_bh_tree);
        printf("Calculate forces: %f\n", avg_time_to_calc_forces);
        printf("Update positions: %f\n", avg_time_to_update_positions);
     */
        //exit(0);
    //}
    if (count>N_ITERATIONS-1) {
        exit(0);
    }
}

int main(int argc, const char * argv[]) {
    
    T = 0;
    
    uniprops.N = 10000;
    uniprops.delta_t = 1E-3;
    uniprops.L_dim = 1;
    uniprops.W_dim = 1;
    uniprops.V = 50;
    uniprops.alpha = 0.25;
    uniprops.gravity = 100 / uniprops.N;
    
    count = 0;
    time_to_calc_forces = 0;
    time_to_create_bh_tree = 0;
    time_to_update_positions = 0;
    
    bodies_list = (Body*)calloc(uniprops.N,sizeof(Body));
    
    initialize_bodies(bodies_list, uniprops);
    
    graphicsInit(&argc, argv, display);
    glutMainLoop();

    free(bodies_list);
    
    return 0;
}

