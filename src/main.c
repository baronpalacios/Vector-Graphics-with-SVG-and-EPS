//
// Created by wuday on 29/04/19.
//

#include "test_figures.h"
#include "test_tree.h"
#include "test_fractals.h"

/// main executes all tests
/// \return 0
int main() {
  figures_test();
  test_node();
  test_fractals();
  return 0;
}