#include "catch.hpp"
#include "virtual_machine.h"
#include "composite.h"
#include "utils.h"

struct Counter
{
    int self_update;
    int child_update;
    int abort;
    int prepare;

    Counter():self_update(0), child_update(0), abort(0), prepare(0) {}
};

template<typename T>
struct MockNode : public T
{
    Counter counter;
    ConstructNode inner_node;

    MockNode() { inner_node.node = this; }

    void reset() { counter = Counter(); }

    virtual void prepare(VirtualMachine& vm, void* context) override {
        ++counter.prepare;
        T::prepare(vm, context);
    }

    virtual void abort(VirtualMachine& vm, void* context) override {
        ++counter.abort;
        T::abort(vm, context);
    }

    virtual E_State self_update(VirtualMachine& vm, void* context, E_State state) override {
        ++counter.self_update;
        return T::self_update(vm, context, state);
    }

    virtual E_State child_update(VirtualMachine& vm, void* context, E_State child_state) override {
        ++counter.child_update;
        return T::child_update(vm, context, child_state);
    }
};

struct MockAction : public MockNode<Action>
{
    E_State update_result;
    MockAction() : update_result(BH_SUCCESS) {}
    MockAction(E_State result) : update_result(result) {}

    virtual E_State update(void*) override {
        return update_result;
    }
};

struct MockSelector : public MockNode<Selector> {};
struct MockSequence : public MockNode<Sequence> {};
struct MockParallel : public MockNode<Parallel>
{
    E_State update_result;
    MockParallel() : update_result(BH_SUCCESS) {}
    MockParallel(E_State result) : update_result(result) {}

    virtual E_State update(VirtualMachine& , void*, E_State ) override {
        return update_result;
    }
};


TEST_CASE( "Behavior Tree Action", "[bt_act]" ) {
    VirtualMachine vm;
    MockAction action;

    SECTION( "single action without running" ) {
        to_vm(vm, action.inner_node);
        action.update_result = BH_SUCCESS;
        vm.tick(nullptr);
        REQUIRE(action.counter.prepare == 1);
        REQUIRE(action.counter.abort == 0);
        REQUIRE(action.counter.self_update == 1);
        REQUIRE(action.counter.child_update == 0);
    }

    SECTION( "single action with running" ) {
        to_vm(vm, action.inner_node);
        action.update_result = BH_RUNNING;
        vm.tick(nullptr);
        REQUIRE(action.counter.prepare == 1);
        REQUIRE(action.counter.abort == 0);
        REQUIRE(action.counter.self_update == 1);
        REQUIRE(action.counter.child_update == 0);
    }
}

TEST_CASE( "Behavior Tree Sequence", "[bt_seq]" ) {
    VirtualMachine vm;
    MockSequence sequence;
    SECTION( "single seq" ) {
        to_vm(vm, sequence.inner_node);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 1);
        REQUIRE(sequence.counter.child_update == 0);
    }

    MockAction action_foo;
    sequence.inner_node.children.push_back(action_foo.inner_node);
    SECTION( "single sequence with one successful action" ) {
        action_foo.update_result = BH_SUCCESS;
        to_vm(vm, sequence.inner_node);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 1);
        REQUIRE(sequence.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 2);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 2);
        REQUIRE(sequence.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "single sequence with one failed action" ) {
        action_foo.update_result = BH_FAIL;
        to_vm(vm, sequence.inner_node);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 1);
        REQUIRE(sequence.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 2);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 2);
        REQUIRE(sequence.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 2);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }

    SECTION( "single sequence with one running action" ) {
        action_foo.update_result = BH_RUNNING;
        to_vm(vm, sequence.inner_node);
        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 1);
        REQUIRE(sequence.counter.child_update == 1);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 1);
        REQUIRE(action_foo.counter.child_update == 0);

        vm.tick(nullptr);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 2);
        REQUIRE(sequence.counter.child_update == 2);
        REQUIRE(action_foo.counter.prepare == 1);
        REQUIRE(action_foo.counter.abort == 0);
        REQUIRE(action_foo.counter.self_update == 2);
        REQUIRE(action_foo.counter.child_update == 0);
    }
}

TEST_CASE( "Behavior Tree Selector", "[bt_sel]" ) {
    VirtualMachine vm;
    SECTION( "single selector" ) {
        MockSelector selector;
        to_vm(vm, selector.inner_node);
        vm.tick(nullptr);
        REQUIRE(selector.counter.prepare == 1);
        REQUIRE(selector.counter.abort == 0);
        REQUIRE(selector.counter.self_update == 1);
        REQUIRE(selector.counter.child_update == 0);
    }
}

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
