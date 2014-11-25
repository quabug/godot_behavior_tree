#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree Action", "[bt_act]" ) {
    VirtualMachine vm;
    MockAction action;

    SECTION( "S" ) {
        to_vm(vm, action.inner_node);
        action.update_result = BH_SUCCESS;
        vm.tick(nullptr);
        REQUIRE(action.counter.prepare == 1);
        REQUIRE(action.counter.abort == 0);
        REQUIRE(action.counter.self_update == 1);
        REQUIRE(action.counter.child_update == 0);
    }

    SECTION( "F" ) {
        to_vm(vm, action.inner_node);
        action.update_result = BH_FAILURE;
        vm.tick(nullptr);
        REQUIRE(action.counter.prepare == 1);
        REQUIRE(action.counter.abort == 0);
        REQUIRE(action.counter.self_update == 1);
        REQUIRE(action.counter.child_update == 0);
    }

    SECTION( "R" ) {
        to_vm(vm, action.inner_node);
        action.update_result = BH_RUNNING;
        vm.tick(nullptr);
        REQUIRE(action.counter.prepare == 1);
        REQUIRE(action.counter.abort == 0);
        REQUIRE(action.counter.self_update == 1);
        REQUIRE(action.counter.child_update == 0);
    }
}

