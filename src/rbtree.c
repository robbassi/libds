/*
 * rbtree.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 *      Author: Julienne Walker <http://www.eternallyconfuzzled.com/tuts/datastructures/rbtree_tut_rbtree.aspx>
 */
#include <stdlib.h>
#include "rbtree.h"

rbnode* rbtree_single(rbnode* root, int dir);
rbnode* rbtree_double(rbnode* root, int dir);
void* rbtree_find_r(rbtree* tree, rbnode* root, void* key);
//rbnode* rbtree_insert_r(rbtree* tree, rbnode* root, void* key, void* data);

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
	int dir = tree->compare(tree->root->key, key) < 0;

	if (eq)
		return tree->root->data;
	else
		return rbtree_find_r(tree, tree->root->link[dir], key);
}

void* rbtree_find_r(rbtree* tree, rbnode* root, void* key) {
	if (root == NULL)
		return NULL;

	int eq = tree->compare(root->key, key) == 0;
	int dir = tree->compare(root->key, key) < 0;

	if (eq)
		return root->data;
	else
		return rbtree_find_r(tree, root->link[dir], key);
}

void rbtree_insert(rbtree*tree, void* key, void* data) {
	if (tree->root == NULL) {
		/* Empty tree case */
		tree->root = rbnode_new(key, data);
		if (tree->root == NULL)
			return;
	} else {
		rbnode head = { BLACK }; /* False tree root */

		rbnode *g, *t; /* Grandparent & parent */
		rbnode *p, *q; /* Iterator & parent */
		int dir = 0, last;

		/* Set up helpers */
		t = &head;
		g = p = NULL;
		q = t->link[1] = tree->root;

		/* Search down the tree */
		for (;;) {
			if (q == NULL) {
				/* Insert new node at the bottom */
				p->link[dir] = q = rbnode_new(key, data);
				if (q == NULL)
					return;
			} else if (is_red(q->link[0]) && is_red(q->link[1])) {
				/* Color flip */
				q->color = RED;
				q->link[0]->color = BLACK;
				q->link[1]->color = BLACK;
			}

			/* Fix red violation */
			if (is_red(q) && is_red(p)) {
				int dir2 = t->link[1] == g;

				if (q == p->link[last])
					t->link[dir2] = rbtree_single(g, !last);
				else
					t->link[dir2] = rbtree_double(g, !last);
			}

			/* Stop if found */
			if (tree->compare(q->key, key) == 0)
				break;

			last = dir;
			dir = tree->compare(q->key, key) < 0;

			/* Update helpers */
			if (g != NULL)
				t = g;
			g = p, p = q;
			q = q->link[dir];
		}

		/* Update root */
		tree->root = head.link[1];
	}

	/* Make root black */
	tree->root->color = BLACK;
}

int rbtree_remove(rbtree *tree, void* key) {
	if (tree->root != NULL) {
		rbnode head = { 0 }; /* False tree root */
		rbnode *q, *p, *g; /* Helpers */
		rbnode *f = NULL; /* Found item */
		int dir = 1;

		/* Set up helpers */
		q = &head;
		g = p = NULL;
		q->link[1] = tree->root;

		/* Search and push a red down */
		while (q->link[dir] != NULL) {
			int last = dir;

			/* Update helpers */
			g = p, p = q;
			q = q->link[dir];
			dir = tree->compare(q->key, key) < 0;

			/* Save found node */
			if (tree->compare(q->key, key) == 0)
				f = q;

			/* Push the red node down */
			if (!is_red(q) && !is_red(q->link[dir])) {
				if (is_red(q->link[!dir]))
					p = p->link[last] = rbtree_single(q, dir);
				else if (!is_red(q->link[!dir])) {
					rbnode *s = p->link[!last];

					if (s != NULL) {
						if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
							/* Color flip */
							p->color = BLACK;
							s->color = RED;
							q->color = RED;
						} else {
							int dir2 = g->link[1] == p;

							if (is_red(s->link[last]))
								g->link[dir2] = rbtree_double(p, last);
							else if (is_red(s->link[!last]))
								g->link[dir2] = rbtree_single(p, last);

							/* Ensure correct coloring */
							q->color = g->link[dir2]->color = RED;
							g->link[dir2]->link[0]->color = BLACK;
							g->link[dir2]->link[1]->color = BLACK;
						}
					}
				}
			}
		}

		/* Replace and remove if found */
		if (f != NULL) {
			f->key = q->key;
			f->data = q->data;
			p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
			free(q);
		}

		/* Update root and make it black */
		tree->root = head.link[1];
		if (tree->root != NULL)
			tree->root->color = BLACK;
	}

	return 1;
}

int is_red(rbnode* root) {
	return root != NULL && root->color == RED;
}

rbnode* rbtree_single ( rbnode* root, int dir ) {
	rbnode* save = root->link[!dir];

	root->link[!dir] = save->link[dir];
	save->link[dir] = root;

	root->color = RED;
	save->color = BLACK;

	return save;
}

rbnode* rbtree_double ( rbnode* root, int dir ) {
	root->link[!dir] = rbtree_single ( root->link[!dir], !dir );
	return rbtree_single ( root, dir );
}

int rbtree_rb_assert(rbnode* root) {
	int lh, rh;

	if (root == NULL)
		return 1;
	else {
		rbnode* ln = root->link[0];
		rbnode* rn = root->link[1];

		/* Consecutive red links */
		if (is_red(root)) {
			if (is_red(ln) || is_red(rn)) {
				puts("Red violation");
				return 0;
			}
		}

		lh = rbtree_rb_assert(ln);
		rh = rbtree_rb_assert(rn);

		/* Invalid binary search tree */
		if ((ln != NULL && ln->data >= root->data)
				|| (rn != NULL && rn->data <= root->data)) {
			puts("Binary tree violation");
			return 0;
		}

		/* Black height mismatch */
		if (lh != 0 && rh != 0 && lh != rh) {
			puts("Black violation");
			return 0;
		}

		/* Only count black links */
		if (lh != 0 && rh != 0)
			return is_red(root) ? lh : lh + 1;
		else
			return 0;
	}
}
