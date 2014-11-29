#include "virtual_machine.h"

namespace BehaviorTree
{
namespace {

// helper functions related to VMRunningData
void tick_begin(VMRunningData& running_data);
void tick_end(VMRunningData& running_data);
void sort_last_running_nodes(VMRunningData& running_data);
bool is_current_node_running(VMRunningData& running_data);
void pop_last_running_behavior(VMRunningData& running_data);
void add_running_node(VMRunningData& running_data, Node* node, NodeData node_data);

// helper functions related to VMStructureData
void cancel_skipped_behaviors(NodeList& node_list, VMRunningData& data, void* context);
void cancel_behavior(NodeList& node_list, VMRunningData& data, void* context);
void run_composites(VMRunningData& data, E_State state, void* context);
E_State run_action(VMRunningData& data, Node* node, void* context);

}

void tick(VMStructureData& structure_data, VMRunningData& running_data, void* context) {
    tick(structure_data.data_list, structure_data.node_list, running_data, context);
}

void tick(const BTStructure& bt_structure, NodeList& node_list, VMRunningData& running_data, void* context) {
    BT_ASSERT(bt_structure.size() == node_list.size());
    tick_begin(running_data);
    size_t num_nodes = bt_structure.size();
    BT_ASSERT(bt_structure.size() == node_list.size());
    while (running_data.index_marker < num_nodes) {
        step_forward(bt_structure, node_list, running_data, context);
    }
    tick_end(running_data);
}

void step_forward(const BTStructure& bt_structure, NodeList& node_list, VMRunningData& running_data, void* context) {
    NodeData node_data = bt_structure[running_data.index_marker];
    Node* node = node_list[running_data.index_marker];
    E_State state = run_action(running_data, node, context);
    BT_ASSERT(running_data.index_marker <= node_data.end);
    if (running_data.index_marker < node_data.end) {
        // this node should be a composite or a decorator
        BT_ASSERT(state == BH_RUNNING);
        add_running_node(running_data, node, node_data);
    } else {
        if (state == BH_RUNNING) {
            running_data.this_tick_running.push_back(node_data.index);
        }
        run_composites(running_data, state, context);
    }
    cancel_skipped_behaviors(node_list, running_data, context);
}

namespace
{

void run_composites(VMRunningData& running_data, E_State state, void* context) {
    while (!running_data.running_nodes.empty()) {
        VMRunningData::RunningNode running_node = running_data.running_nodes.back();
        state = running_node.node->child_update(running_data, running_node.data.index, context, state);
        BT_ASSERT(running_data.index_marker <= running_node.data.end);
        if (running_data.index_marker == running_node.data.end) {
            running_data.running_nodes.pop_back();
            if (state == BH_RUNNING) {
                running_data.this_tick_running.push_back(running_node.data.index);
            }
            continue;
        } else {
            break;
        }
    }
}

E_State run_action(VMRunningData& running_data, Node* node, void* context) {
    E_State state = BH_READY;
    if (is_current_node_running(running_data)) {
        pop_last_running_behavior(running_data);
        state = BH_RUNNING;
    } else {
        node->prepare(running_data, running_data.index_marker, context);
        state = BH_READY;
    }
    return node->self_update(running_data, running_data.index_marker, context, state);
}

void cancel_skipped_behaviors(NodeList& node_list, VMRunningData& running_data, void* context) {
    while (!running_data.last_tick_running.empty() && running_data.last_tick_running.back() < running_data.index_marker) {
        cancel_behavior(node_list, running_data, context);
        pop_last_running_behavior(running_data);
    }
}

void cancel_behavior(NodeList& node_list, VMRunningData& running_data, void* context) {
    IndexType index = running_data.last_tick_running.back();
    Node* node = node_list[index];
    node->abort(running_data, index, context);
}

// function related to VMRunningData
void tick_begin(VMRunningData& running_data) {
    running_data.this_tick_running.resize(0);
    running_data.running_nodes.resize(0);
    running_data.index_marker = 0;
    sort_last_running_nodes(running_data);
}

void tick_end(VMRunningData& running_data) {
    running_data.this_tick_running.swap(running_data.last_tick_running);
    running_data.this_tick_running.clear();
}

struct IndexGreatThanComp
{
    bool operator()(IndexType lhs, IndexType rhs) const { return lhs > rhs; }
};

void sort_last_running_nodes(VMRunningData& running_data) {
    sort<IndexGreatThanComp>(running_data.last_tick_running);
}

bool is_current_node_running(VMRunningData& running_data) { 
    return !running_data.last_tick_running.empty() &&
        running_data.index_marker == running_data.last_tick_running.back();
}

void pop_last_running_behavior(VMRunningData& running_data) {
    running_data.last_tick_running.pop_back();
}

void add_running_node(VMRunningData& running_data, Node* node, NodeData node_data) {
    VMRunningData::RunningNode running = { node, node_data };
    running_data.running_nodes.push_back(running);
}
    
}

void increase_index(VMRunningData& running_data) { ++running_data.index_marker; }

void move_index_to_running(VMRunningData& running_data) {
    BT_ASSERT(!running_data.last_tick_running.empty());
    running_data.index_marker = running_data.last_tick_running.back();
}

void move_index_to_composite_end(VMRunningData& running_data) {
    BT_ASSERT(!running_data.running_nodes.empty());
    running_data.index_marker = running_data.running_nodes.back().data.end;
}

NodeData get_running_node(VMRunningData& running_data) {
    BT_ASSERT(!running_data.running_nodes.empty());
    return running_data.running_nodes.back().data;
}



} /* BehaviorTree */ 
