//
//  NB_Calculations.h
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 02/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#ifndef __N_body_problem__NB_Calculations__
#define __N_body_problem__NB_Calculations__

#include <stdio.h>
#include "NB_Body.h"
#include "NB_Universe.h"
#include "NB.Globals.h"

void update_positions(Body *bodies, UniverseProperties uniprop);
void initialize_bodies(Body* bodies, UniverseProperties universe);

#endif /* defined(__N_body_problem__NB_Calculations__) */
