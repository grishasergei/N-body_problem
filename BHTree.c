
//
//  BHTree.c
//  N-body_problem
//
//  Created by Sergii Gryshkevych on 03/05/15.
//  Copyright (c) 2015 Sergii Gryshkevych. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "NB.Globals.h"
#include "BHTree.h"

void BHTree_destroy(BHTree* tree){
    if (tree == NULL) {
        return;
    }
    if (tree->NW != NULL) {
        BHTree_destroy(tree->NW);
    }
    if (tree->NE != NULL) {
        BHTree_destroy(tree->NE);
    }
    if (tree->SW != NULL) {
        BHTree_destroy(tree->SW);
    }
    if (tree->SE != NULL) {
        BHTree_destroy(tree->SE);
    }
    if (tree->body != NULL) {
        free(tree->body);
        tree->body = NULL;
    }
    free(tree);
    tree = NULL;
}

bool BHTree_isExternal(BHTree* tree){
    bool result = false;
    if ((tree->NE==NULL) && (tree->NW==NULL) && (tree->SE==NULL) && (tree->SW==NULL)) {
        result = true;
    }
    return result;
}

void BHTree_insertBody(BHTree* tree, Body* body){
    Quad q;
    
    if (tree->body->ID==-1) {
        memcpy(tree->body, body, sizeof(Body));
        //tree->body = body;
    } else if (BHTree_isExternal(tree)==false){
        Body_addAtoB(*body, tree->body);
        //try NW
        q = quad_subdivide_NW(tree->quad);
        if (body_inQuad(*body, q)==true) {
            if (tree->NW==NULL) {
                tree->NW = PoolTree_getNextTree(&poolTree, &poolBody, q);
            }
            BHTree_insertBody(tree->NW, body);
        } else {
            //try NE
            q = quad_subdivide_NE(tree->quad);
            if (body_inQuad(*body, q)==true) {
                if (tree->NE==NULL) {
                    tree->NE = PoolTree_getNextTree(&poolTree, &poolBody, q);
                }
                BHTree_insertBody(tree->NE, body);
            } else {
                //try SW
                q = quad_subdivide_SW(tree->quad);
                if (body_inQuad(*body, q)==true) {
                    if (tree->SW==NULL) {
                        tree->SW = PoolTree_getNextTree(&poolTree, &poolBody, q);
                    }
                    BHTree_insertBody(tree->SW, body);
                } else {
                    //try SE
                    q = quad_subdivide_SE(tree->quad);
                    if (body_inQuad(*body, q)==true) {
                        if (tree->SE==NULL) {
                            tree->SE = PoolTree_getNextTree(&poolTree, &poolBody, q);
                        }
                        BHTree_insertBody(tree->SE, body);
                    }
                }
            }
        }
    } else if (BHTree_isExternal(tree)==true){
        Body *b = (Body*)calloc(1, sizeof(Body));
        memcpy(b, tree->body, sizeof(Body));
        //try NW
        q = quad_subdivide_NW(tree->quad);
        if (body_inQuad(*b, q)==true) {
            if (tree->NW==NULL) {
                tree->NW = PoolTree_getNextTree(&poolTree, &poolBody, q);
            }
            BHTree_insertBody(tree->NW, b);
        } else {
            //try NE
            q = quad_subdivide_NE(tree->quad);
            if (body_inQuad(*b, q)==true) {
                if (tree->NE==NULL) {
                    tree->NE = PoolTree_getNextTree(&poolTree, &poolBody, q);
                }
                BHTree_insertBody(tree->NE, b);
            } else {
                //try SW
                q = quad_subdivide_SW(tree->quad);
                if (body_inQuad(*b, q)==true) {
                    if (tree->SW==NULL) {
                        tree->SW = PoolTree_getNextTree(&poolTree, &poolBody, q);
                    }
                    BHTree_insertBody(tree->SW, b);
                } else {
                    //try SE
                    q = quad_subdivide_SE(tree->quad);
                    if (body_inQuad(*b, q)==true) {
                        if (tree->SE==NULL) {
                            tree->SE = PoolTree_getNextTree(&poolTree, &poolBody, q);
                        }
                        BHTree_insertBody(tree->SE, b);
                    }
                }
            }
        }
        free(b);
        b = NULL;
        BHTree_insertBody(tree, body);
    }
    
}

void    BHTree_updateForce(BHTree* tree, Body* body, UniverseProperties uniprops){
    if (BHTree_isExternal(tree)==true) {
        body_addForce(body, tree->body, uniprops);
    } else if (tree->quad.length / getDistance(*body, *tree->body) < THRESHOLD_THETA){
        body_addForce(body, tree->body, uniprops);
    } else {
        if (tree->NW != NULL) {
            BHTree_updateForce(tree->NW, body,uniprops);
        }
        if (tree->NE != NULL) {
            BHTree_updateForce(tree->NE, body,uniprops);
        }
        if (tree->SW != NULL) {
            BHTree_updateForce(tree->SW, body,uniprops);
        }
        if (tree->SE != NULL) {
            BHTree_updateForce(tree->SE, body,uniprops);
        }
    }
}









