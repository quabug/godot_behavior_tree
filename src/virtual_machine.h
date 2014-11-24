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
public:
    std::vector<NodeData> data_list;
    std::vector<NodeData> running_behaviors;
    std::vector<IndexType> this_tick_running;
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
        assert(!running_behaviors.empty());
        index_marker = running_behaviors.back().end;
    }

private:
    void cancel_skipped_behaviors(void* context);
    void cancel_behavior(IndexType index, void* context);
    void record_running_index(IndexType index);
    void pop_last_running_behavior();
    void prepare_behavior(IndexType index);
    void run_composites(E_State state, void* context);
    E_State run_action(Node* node, void* context);

    inline bool is_running(IndexType index) const { 
        return !last_tick_running.empty() &&
            index == last_tick_running.back();
    }
};


} /* BehaviorTree */ 

#endif
