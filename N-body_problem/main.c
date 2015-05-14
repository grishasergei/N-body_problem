//
//  main.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
int count;
int N_ITERATIONS = 1000;
double time_to_create_bh_tree, time_to_calc_forces, time_to_update_positions;

void display(void){
    struct timeval t1, t2;
    int i;
    Quad quad;
    quad.length = 1;
    quad.xmid = 0.5;
    quad.ymid = 0.5;
    
    printf("Iteration: %d\n", count);
    count++;
    
    drawBodies(bodies_list, uniprops.N);
    
    /*
     Create BH tree
     */
    gettimeofday(&t1,NULL);
    BHTree* tree = BHTree_create(quad);
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
    
    BHTree_destroy(tree);
    
    /*
     Update positions
     */
    gettimeofday(&t1,NULL);
    update_positions(bodies_list, uniprops);
    gettimeofday(&t2,NULL);
    time_to_update_positions += t2.tv_sec - t1.tv_sec + (double)(t2.tv_usec - t1.tv_usec)/1000000;

    if (count>N_ITERATIONS-1) {
        time_to_calc_forces /= N_ITERATIONS;
        time_to_create_bh_tree /= N_ITERATIONS;
        time_to_update_positions /= N_ITERATIONS;
        printf("Average time:\n");
        printf("Create BH tree: %f\n", time_to_create_bh_tree);
        printf("Calculate forces: %f\n", time_to_calc_forces);
        printf("Update positions: %f\n", time_to_update_positions);
        exit(0);
    }

}

double calcall(void){
    int i;
    Quad quad;
    quad.length = 1;
    quad.xmid = 0.5;
    quad.ymid = 0.5;
    
    clock_t t1 = clock();
    
    BHTree* tree = BHTree_create(quad);
    
    for (i=0; i<uniprops.N; i++) {
        //printf("ID: %d inserting \n",bodies_list[i].ID);
        BHTree_insertBody(tree, &bodies_list[i]);
    }
    
    for (i=0; i<uniprops.N; i++) {
        bodies_list[i].Fx = 0;
        bodies_list[i].Fy = 0;
        BHTree_updateForce(tree, &bodies_list[i], uniprops);
    }
    
    BHTree_destroy(tree);
    
    clock_t t2 = clock();
    return (double)(t2-t1)/CLOCKS_PER_SEC;
    
}

int main(int argc, const char * argv[]) {
    int i, n_iterations;
    double avgT;
    
    n_iterations = 2000;
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
    /*
    avgT = 0;
    for (i=0; i<n_iterations; i++) {
        printf("%d\n",i);
        avgT += calcall();
    }
    avgT = avgT / n_iterations;
    printf("Average execution time per iteration: %f seconds\n",avgT);
    */
    free(bodies_list);
    
    return 0;
}

