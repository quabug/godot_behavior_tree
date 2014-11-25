#ifndef BEHAVIOR_TREE_TEST_UTILS_H
#define BEHAVIOR_TREE_TEST_UTILS_H

#include "virtual_machine.h"
#include "composite.h"

using namespace BehaviorTree;

struct ConstructNode
{
    std::vector<ConstructNode> children;
    Node* node;

    ConstructNode(Node* node_=nullptr):node(node_) {}
};

void to_vm(VirtualMachine& vm, ConstructNode& node);

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
    E_State self_update_result;
    E_State child_update_result;

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
        self_update_result = T::self_update(vm, context, state);
        return self_update_result;
    }

    virtual E_State child_update(VirtualMachine& vm, void* context, E_State child_state) override {
        ++counter.child_update;
        child_update_result = T::child_update(vm, context, child_state);
        return child_update_result;
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

struct MockDecorator : public MockNode<Decorator>
{
    int update_counter;
    MockDecorator() : update_counter(0) {}
    virtual E_State update(void*, E_State child_state) {
        ++update_counter;
        return child_state;
    }
};

struct MockSelector : public MockNode<Selector> {};
struct MockSequence : public MockNode<Sequence> {};
struct MockFailureParallel : public MockNode<Parallel<BH_FAILURE> > {};

#endif
