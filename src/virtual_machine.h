#include <vector>
#include <stack>
#include <functional>
#include <cassert>

#include "node.h"

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

namespace BehaviorTree
{

class VirtualMachine
{
    struct RunningNode
    {
        Node* node;
        NodeData data;
    };

public:
    std::vector<NodeData> data_list;
    std::vector<Node*> node_list;

    // NOTE: should I remove those data below from this class scope 
    //       for making virtual machine eaiser to achieve thread-safty?
private:
    std::vector<RunningNode> running_nodes;
    std::vector<IndexType> this_tick_running;
    // TODO: last_tick_running should be moved from this class scope to agent scope,
    //       then this virtual mathine can be reused by any agent.
    std::vector<IndexType> last_tick_running;
    IndexType index_marker;

public:
    VirtualMachine():index_marker(0) {}
    void tick(void* context);
    void reset();

    inline void increase_index() { ++index_marker; }
    inline void move_index_to_running() {
        assert(!last_tick_running.empty());
        index_marker = last_tick_running.back();
    }
    inline void move_index_to_composite_end() {
        assert(!running_nodes.empty());
        index_marker = running_nodes.back().data.end;
    }
    inline NodeData get_running_node() const {
        assert(!running_nodes.empty());
        return running_nodes.back().data;
    }

private:
    void cancel_skipped_behaviors(void* context);
    void cancel_behavior(IndexType index, void* context);
    void pop_last_running_behavior();
    void prepare_behavior(IndexType index);
    void run_composites(E_State state, void* context);
    E_State run_action(Node* node, void* context);
    void sort_last_running_nodes();

    inline bool is_running(IndexType index) const { 
        return !last_tick_running.empty() &&
            index == last_tick_running.back();
    }
};


} /* BehaviorTree */ 

#endif
