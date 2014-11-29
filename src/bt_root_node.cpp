#include "bt_root_node.h"
#include "bt_utils.h"


BTRootNode::BTRootNode()
{
    BehaviorTree::NodeData node_data;
    node_data.begin = 0;
    node_data.end = 1;
    set_bt_node_data(node_data);
    bt_structure_data.push_back(node_data);
    bt_node_list.push_back(&behavior_node);
}

void BTRootNode::_notification(int p_notification) {
    
    switch(p_notification) {

        case NOTIFICATION_PROCESS: {

            Variant context;
            if (get_script_instance()) {

                Variant time=get_process_delta_time();
                const Variant*ptr[1]={&time};
                Variant::CallError err;
                context = get_script_instance()->call("_pre_tick",ptr,1,err);
            }
            tick(bt_structure_data, bt_node_list, bt_running_data, &context);
        } break;
    }
}

void BTRootNode::_bind_methods() {
	BIND_VMETHOD( MethodInfo("_pre_tick",PropertyInfo(Variant::REAL,"delta")) );
}

void BTRootNode::add_child_node(BTNode &child, Vector<BehaviorTree::IndexType>& node_hierarchy) {
    node_hierarchy.push_back(0);
    BehaviorTree::VMStructureData temp_vm_structure_data;
    // add new child at the end of its parent.
    int child_index = bt_structure_data[node_hierarchy[0]].end;
    create_bt_structure(temp_vm_structure_data, child, child_index);
    BehaviorTree::IndexType children_count = temp_vm_structure_data.node_list.size();

    int old_size = bt_structure_data.size();
    int new_size = old_size + children_count;
    
    bt_structure_data.resize(new_size);
    bt_node_list.resize(new_size);

    for (int i = old_size-1; i >= child_index; --i) {
        BehaviorTree::NodeData& node_data = bt_structure_data[i];
        node_data.begin += children_count;
        node_data.end += children_count;
        bt_structure_data[i+children_count] = node_data;
        bt_node_list[i+children_count] = bt_node_list[i];
    }

    for (int i = 0; i < children_count; ++i) {
        ERR_EXPLAIN("Index of child is not correct.");
        ERR_FAIL_COND(child_index+i != temp_vm_structure_data.data_list[i].index);
        bt_structure_data[child_index+i] = temp_vm_structure_data.data_list[i];
        bt_node_list[child_index+i] = temp_vm_structure_data.node_list[i];
    }

    int parents_count = node_hierarchy.size();
    for (int i = 0; i < parents_count; ++i) {
        bt_structure_data[node_hierarchy[i]].end += children_count;
    }
}

void BTRootNode::remove_child_node(BTNode& child, Vector<BehaviorTree::IndexType>& node_hierarchy) {
    node_hierarchy.push_back(0);
    BehaviorTree::NodeData child_node_data = child.get_bt_node_data();
    BehaviorTree::IndexType children_count = child_node_data.end - child_node_data.begin;

    int old_size = bt_structure_data.size();
    int new_size = old_size - children_count;
    
    for (int i = child_node_data.end; i < old_size; ++i) {
        BehaviorTree::NodeData& node_data = bt_structure_data[i];
        node_data.begin -= children_count;
        node_data.end -= children_count;
        bt_structure_data[i-children_count] = node_data;
        bt_node_list[i-children_count] = bt_node_list[i];
    }

    bt_structure_data.resize(new_size);
    bt_node_list.resize(new_size);

    int parents_count = node_hierarchy.size();
    for (int i = 0; i < parents_count; ++i) {
        bt_structure_data[node_hierarchy[i]].end -= children_count;
    }
}
