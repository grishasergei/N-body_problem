/*
 * File: graphics.h
 * ----------------
 * Contains definitions for the graphics functions.
 *
 * CME212 Assignment 5
 * Oliver Fringer
 * Stanford University
 *
 */
#ifndef _graphics_h
#define _graphics_h

#include "NB_Body.h"
#include "NB_Universe.h"

void graphicsInit(int* argc, char** argv, void* display);

void reshape(int width, int height);

void idle(void);

void display(void); 

void drawPoints(double* x, double* y, int N);

void drawBodies(Body* bodies, int N);


#endif
