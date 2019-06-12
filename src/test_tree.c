//
// Created by wuday on 09/05/19.
//

#include <stdio.h>
#include "tree.h"
#include "svg.h"
#include "eps.h"

/// test_node test function for binary trees
/// we first create the binary tree defined in the project paper, draw it,
/// and export it to SVG and to EPS
void test_node () {
  printf("> binary tree test draw_binary_tree(tf, root)\n");
  Node *root = create_node(10);
  root->left = create_node(100);
  root->left->left = create_node(4);
  root->left->right = create_node(11);
  root->right = create_node(89);
  root->right->right = create_node(54);
  root->right->right->right = create_node(166);
  root->right->right->left = create_node(155);
  Figure *tf = start_figure(400, 400);
  draw_binary_tree(tf, root);
  print_figure(tf);
  export_svg(tf, "./figures/tree.svg");
  printf("  result exported to ./figures/tree.svg\n");
  export_eps(tf, "./figures/tree.eps");
  printf("  result exported to ./figures/tree.eps\n");
  printf("  done\n");
  free_figure(tf);
}
