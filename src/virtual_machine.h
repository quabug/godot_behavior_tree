#include <vector>
#include <stack>
#include <functional>
#include <cassert>

#include "node.h"

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

namespace BehaviorTree
{

struct RunningNode
{
    Node* node;
    NodeData data;
};

struct VirtualMachineData
{
    std::vector<RunningNode> running_nodes;
    std::vector<IndexType> this_tick_running;
    std::vector<IndexType> last_tick_running;
    IndexType index_marker;

    inline void tick_begin() { 
        sort_last_running_nodes();
        index_marker = 0;
    }
    inline void tick_end() {
        this_tick_running.swap(last_tick_running);
        this_tick_running.clear();
    }

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
    inline bool is_running(IndexType index) const { 
        return !last_tick_running.empty() &&
            index == last_tick_running.back();
    }
    inline bool is_current_node_running() const { 
        return !last_tick_running.empty() &&
            index_marker == last_tick_running.back();
    }
    inline void pop_last_running_behavior() {
        last_tick_running.pop_back();
    }
    inline void add_running_node(Node* node, NodeData node_data) {
        RunningNode running = { node, node_data };
        running_nodes.push_back(running);
    }
    void sort_last_running_nodes();
};

class VirtualMachine
{
public:
    std::vector<NodeData> data_list;
    std::vector<Node*> node_list;

public:
    VirtualMachine() {}
    void tick(VirtualMachineData& data, void* context);

private:
    void cancel_skipped_behaviors(VirtualMachineData& data, void* context);
    void cancel_behavior(VirtualMachineData& data, void* context);
    void pop_last_running_behavior();
    void prepare_behavior(IndexType index);
    void run_composites(VirtualMachineData& data, E_State state, void* context);
    E_State run_action(VirtualMachineData& data, Node* node, void* context);
    void sort_last_running_nodes();
};


} /* BehaviorTree */ 

#endif
