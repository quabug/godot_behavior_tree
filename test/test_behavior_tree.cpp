#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree Parallel", "[bt_par]" ) {
    VirtualMachine vm;
    SECTION( "single parallel" ) {
        MockParallel parallel;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 0);
    }
}
