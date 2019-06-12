//
// Created by wuday on 30/04/19.
//

#ifndef NODE_H
#define NODE_H

#include "figures.h"

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int data);

void draw_binary_tree(Figure *fig, Node *tree);

#endif // NODE_H
