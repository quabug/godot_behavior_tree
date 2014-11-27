#ifndef BEHAVIOR_TREE_VIRTUAL_MACHINE_H
#define BEHAVIOR_TREE_VIRTUAL_MACHINE_H

#include "node.h"

namespace BehaviorTree
{

// running data
struct VMRunningData
{
    struct RunningNode
    {
        Node* node;
        NodeData data;
    };
    BTVector<RunningNode> running_nodes;
    BTVector<IndexType> this_tick_running;
    BTVector<IndexType> last_tick_running;
    IndexType index_marker;

};

// helper functions related to VMRunningData
void increase_index(VMRunningData& running_data);
void move_index_to_running(VMRunningData& running_data);
void move_index_to_composite_end(VMRunningData& running_data);
NodeData get_running_node(VMRunningData& running_data);


// structure data
struct VMStructureData
{
    BTStructure data_list;
    NodeList node_list;
};

// helper functions related to VMRunningData
void tick(VMStructureData& structure_data, VMRunningData& running_data, void* context);
void tick(const BTStructure& bt_structure, NodeList& node_list, VMRunningData& running_data, void* context);

} /* BehaviorTree */ 

#endif
