/*
 * rbtree.h
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#ifndef SRC_RBTREE_H_
#define SRC_RBTREE_H_

#include "common.h"

#define RED 0
#define BLACK 1

typedef struct rbnode {
	short color;
	void* key;
	void* data;
	struct rbnode* link[2];
} rbnode;

typedef struct rbtree {
	rbnode *root;
	comparator compare;
} rbtree;

rbtree* rbtree_new(comparator compare);
void* rbtree_find(rbtree* tree, void* key);
int rbtree_insert ( rbtree* tree, void* key, void* data);

#endif /* SRC_RBTREE_H_ */
