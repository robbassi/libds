/*
 * rbtree.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 *      Author: Julienne Walker <http://www.eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx>
 */
#include <stdlib.h>
#include "rbtree.h"

rbnode* rbtree_single ( rbnode* root, int dir );
rbnode* rbtree_double ( rbnode* root, int dir );
void* rbtree_find_r(rbtree* tree, rbnode* root, void* key);
rbnode* rbtree_insert_r (rbtree* tree, rbnode* root, void* key, void* data);

rbtree* rbtree_new(comparator compare) {
	rbtree* tree = (rbtree*) malloc(sizeof(rbtree));
	tree->compare = compare;
	return tree;
}

rbnode* rbnode_new(void* key, void* data) {
	rbnode* node = (rbnode*) malloc(sizeof(rbnode));
	node->color = RED;
	node->key = key;
	node->data = data;
	node->link[0] = NULL;
	node->link[1] = NULL;
	return node;
}

void* rbtree_find(rbtree* tree, void* key) {
	if (tree->root == NULL)
		return NULL;

	int eq = tree->compare(tree->root->key, key) == 0;
	int dir = tree->compare(tree->root->key, key) > 0;

	if (eq)
		return tree->root->data;
	else
		return rbtree_find_r(tree, tree->root->link[dir], key);
}


void* rbtree_find_r(rbtree* tree, rbnode* root, void* key) {
	puts("recur");
	if (root == NULL)
		return NULL;

	int eq = tree->compare(root->key, key) == 0;
	int dir = tree->compare(root->key, key) > 0;

	if (eq)
		return root->data;
	else
		return rbtree_find_r(tree, root->link[dir], key);
}

int rbtree_insert ( rbtree* tree, void* key, void* data)
{
  tree->root = rbtree_insert_r ( tree, tree->root, key, data );
  tree->root->color = BLACK;
  return 1;
}

rbnode* rbtree_insert_r (rbtree* tree, rbnode* root, void* key, void* data)
{
  if ( root == NULL )
    root = rbnode_new ( key, data );
  else if ( data != root->data ) {
    int dir = tree->compare(root->key, data) < 0;

    root->link[dir] = rbtree_insert_r ( tree, root->link[dir], key, data );

    if ( is_red ( root->link[dir] ) ) {
      if ( is_red ( root->link[!dir] ) ) {
        /* Case 1 */
        root->color = RED;
        root->link[0]->color = BLACK;
        root->link[1]->color = BLACK;
      }
      else {
        /* Cases 2 & 3 */
        if ( is_red ( root->link[dir]->link[dir] ) )
          root = rbtree_single ( root, !dir );
        else if ( is_red ( root->link[dir]->link[!dir] ) )
          root = rbtree_double ( root, !dir );
      }
    }
  }

  return root;
}

int is_red (rbnode* root) {
	return root != NULL && root->color == RED;
}

rbnode* rbtree_single ( rbnode* root, int dir ) {
	puts("single");
	rbnode* save = root->link[!dir];

	root->link[!dir] = save->link[dir];
	save->link[dir] = root;

	root->color = RED;
	save->color = BLACK;

	return save;
 }

rbnode* rbtree_double ( rbnode* root, int dir ) {
	puts("double");
	root->link[!dir] = rbtree_single ( root->link[!dir], !dir );
	return rbtree_single ( root, dir );
}

int rbtree_rb_assert ( rbnode* root ) {
	int lh, rh;

	if ( root == NULL )
		return 1;
	else {
		rbnode* ln = root->link[0];
		rbnode* rn = root->link[1];

	/* Consecutive red links */
	if ( is_red ( root ) ) {
		if ( is_red ( ln ) || is_red ( rn ) ) {
			puts ( "Red violation" );
			return 0;
		}
	}

	lh = rbtree_rb_assert ( ln );
	rh = rbtree_rb_assert ( rn );

	/* Invalid binary search tree */
	if ( ( ln != NULL && ln->data >= root->data )
			|| ( rn != NULL && rn->data <= root->data ) ) {
		puts ( "Binary tree violation" );
		return 0;
	}

	/* Black height mismatch */
	if ( lh != 0 && rh != 0 && lh != rh ) {
		puts ( "Black violation" );
		return 0;
	}

	/* Only count black links */
	if ( lh != 0 && rh != 0 )
		return is_red ( root ) ? lh : lh + 1;
	else
		return 0;
	}
}
