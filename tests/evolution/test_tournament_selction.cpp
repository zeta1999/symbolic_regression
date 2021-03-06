#include <random>
#include "../evolution/utils.h"
#include "../../gp/population.h"
#include "../../gp/individual.h"
#include "../../third-party/Catch2/single_include/catch2/catch.hpp"

using std::mt19937;

TEST_CASE("Test tourn", "[unit]") {
    size_t len = 3;
    int min_depth = 2;
    int max_depth = 6;
    mt19937 engine(0);
    Population pop(len);
    pop.initialize(engine, min_depth, max_depth);
    pop[0]->set_fitness(0.25);

    auto indv = Evolution::tournament_selection(&pop, engine, 3);
    REQUIRE(indv->get_fitness() == 0.25);
}
