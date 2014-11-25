#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree FaitureDecorator", "[bt_dec]" ) {
    VirtualMachine vm;
    MockDecorator decorator;
    SECTION( "+" ) {
        to_vm(vm, decorator.inner_node);
        vm.tick(nullptr);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 0);
    }

    MockAction action_foo;
    decorator.inner_node.children.push_back(action_foo.inner_node);
    SECTION( "+S" ) {
        action_foo.update_result = BH_SUCCESS;
        to_vm(vm, decorator.inner_node);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_SUCCESS);
        REQUIRE(decorator.update_counter == 1);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_SUCCESS);
        REQUIRE(decorator.update_counter == 2);
        REQUIRE(decorator.counter.prepare == 2);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 2);
        REQUIRE(decorator.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "+F" ) {
        action_foo.update_result = BH_FAILURE;
        to_vm(vm, decorator.inner_node);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_FAILURE);
        REQUIRE(decorator.update_counter == 1);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_FAILURE);
        REQUIRE(decorator.update_counter == 2);
        REQUIRE(decorator.counter.prepare == 2);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 2);
        REQUIRE(decorator.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "+R" ) {
        action_foo.update_result = BH_RUNNING;
        to_vm(vm, decorator.inner_node);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_RUNNING);
        REQUIRE(decorator.update_counter == 1);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(decorator.child_update_result == BH_RUNNING);
        REQUIRE(decorator.update_counter == 2);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 2);
        REQUIRE(decorator.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }
}
