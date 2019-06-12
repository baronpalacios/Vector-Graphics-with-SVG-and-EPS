//
// Created by wuday on 30/04/19.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "figures.h"
#include "svg.h"


#define SIZE 25.00

unsigned int pow2(unsigned int n) {
  return 1u << n;
}

/// create_node creates a binary tree node without subtrees
/// \param data the node info
/// \return the node creates
Node *create_node(int data) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/// get_depth computes the depth of a tree
/// \param node
/// \param depth the depth of the node
/// \return the depth of the tree
unsigned int get_depth(Node *node, unsigned int depth) {
  unsigned int ld, rd;
  if (node == NULL) {
    return depth - 1;
  }
  ld = get_depth(node->left, depth + 1);
  rd = get_depth(node->right, depth + 1);
  return (ld < rd) ? rd : ld;
}

///
/// \param fig the figure
/// \param root the root of the tree
/// \param tx the x coordinate of the node center
/// \param ty the y coordinate of the node center
/// \param col the vertical position of the node
/// \param line the horizontal position of the node
void draw_node_info(Figure *fig, Node *root, double tx, double ty,
                    int col, int line) {
  Point2D *center = malloc(sizeof(Point2D));
  center->x = col * SIZE + tx;
  center->y = -line * 3 * SIZE + ty;
  set_color(fig, 0xFF0000);
  set_fill(fig, 0xFFFFFF);
  draw_circle(fig, center, 10.0);
  char *text = malloc(sizeof(char) * 20);
  sprintf(text, "%d", root->data);
  set_fill(fig, 0x0000FF);
  draw_text(fig, center, text);
  set_color(fig, 0x000000);
}

/// draw_binary_tree_node draws a node of a binary tree
/// a bit quick and dirty: we first draw the edges from the node center to the
/// center of the subnodes (without clipping), and then paint a white filled
/// circle, and finally we write the node info
/// \param fig the figure
/// \param root the relative root of the tree
/// \param tx the x coordinate of the node center
/// \param ty the y coordinate of the node center
/// \param width the distance between the columns
/// \param col the vertical position of the node
/// \param line the horizontal position of the node
void draw_binary_tree_node(Figure *fig, Node *root, double tx, double ty,
                           int width, int col, int line) {
  if (root->left) {
    draw_line(fig, col * SIZE + tx, -line * 3 * SIZE + ty,
              (col - width / 2.0) * SIZE + tx, -(line + 1) * 3 * SIZE + ty);
    draw_binary_tree_node(fig, root->left, tx, ty, width / 2, col - width / 2,
                          line + 1);
  }
  if (root->right) {
    draw_line(fig, col * SIZE + tx, -line * 3 * SIZE + ty,
              (col + width / 2.0) * SIZE + tx, -(line + 1) * 3 * SIZE + ty);
    draw_binary_tree_node(fig, root->right, tx, ty, width / 2, col + width / 2,
                          line + 1);
  }
  draw_node_info(fig, root, tx, ty, col, line);
}

/// draw_binary_tree draws a binary tree
/// \param fig the figure
/// \param root the root of the tree
void draw_binary_tree(Figure *fig, Node *root) {
  fig->f = 0xFFFFFF;
  draw_binary_tree_node(fig, root, 0.00, (fig->h / 2) - 20.00,
                        pow2(get_depth(root, 0)), 0, 0);
}

