#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree FaitureParallel", "[bt_par]" ) {
    VirtualMachine vm;
    MockFailureParallel parallel;
    SECTION( "single" ) {
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 0);
    }

    MockAction action_foo;
    parallel.inner_node.children.push_back(action_foo.inner_node);
    SECTION( "[S]" ) {
        action_foo.update_result = BH_SUCCESS;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "[F]" ) {
        action_foo.update_result = BH_FAILURE;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "[R]" ) {
        action_foo.update_result = BH_RUNNING;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    MockAction action_bar;
    parallel.inner_node.children.push_back(action_bar.inner_node);
    SECTION( "[S,S]" ) {
        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_SUCCESS;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 1);
        REQUIRE(action_bar.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 4);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 2);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 2);
        REQUIRE(action_bar.counter.child_update == 0);
    }

    SECTION( "[S,F]" ) {
        action_foo.update_result = BH_SUCCESS;
        action_bar.update_result = BH_FAILURE;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 1);
        REQUIRE(action_bar.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 4);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 2);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 2);
        REQUIRE(action_bar.counter.child_update == 0);
    }

    SECTION( "[F,S]" ) {
        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_SUCCESS;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 1);
        REQUIRE(action_bar.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 4);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 2);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 2);
        REQUIRE(action_bar.counter.child_update == 0);
    }

    SECTION( "[F,R]" ) {
        action_foo.update_result = BH_FAILURE;
        action_bar.update_result = BH_RUNNING;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 1);
        REQUIRE(action_bar.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 4);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 2);
        REQUIRE(action_bar.counter.child_update == 0);
    }

    SECTION( "[R,F]" ) {
        action_foo.update_result = BH_RUNNING;
        action_bar.update_result = BH_FAILURE;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 1);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 1);
        REQUIRE(action_bar.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 4);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
        REQUIRE(action_bar.counter.prepare == 2);
        REQUIRE(action_bar.counter.abort == 0);
        REQUIRE(action_bar.counter.self_update == 2);
        REQUIRE(action_bar.counter.child_update == 0);
    }
}
