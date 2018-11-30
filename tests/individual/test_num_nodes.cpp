#include <cmath>
#include <random>
#include <memory>
#include <string>
#include "utils.h"
#include "../../gp/evolution.h"
#include "../../gp/individual.h"
#include "../../third-party/Catch2/single_include/catch2/catch.hpp"


TEST_CASE("Num nodes test.", "[unit]") {
    RPNTree tree(make_test_tree());
    REQUIRE(tree.num_nodes() == 9);
}


TEST_CASE("Full with incremental depths.", "[unit]") {
    std::mt19937 engine(0);

    indv_ptr indv;

    // Generate trees from depth 2 to 12, node count should always be 2^depth
    for (int depth = 2; depth < 12; depth++) {
        for (int trials = 0; trials < 10; trials++) {
            indv = Evolution::full(depth, engine);
            REQUIRE(indv->get_tree()->num_nodes() == std::pow(2, depth) - 1);
        }
    }
}
