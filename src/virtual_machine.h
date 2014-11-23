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
    typedef unsigned short IndexType;
    struct NodeData
    {
        union {
        IndexType begin;
        IndexType index;
        };
        IndexType end;
    };

    std::vector<NodeData> data_list;
    std::vector<Node*> node_list;

private:
    IndexType index_marker;
    IndexType count_last_running_behaviors;
    std::stack<NodeData> running_behaviors;
    std::deque<IndexType> last_running_behaviors;

public:
    VirtualMachine():index_marker(0), count_last_running_behaviors(0) {}
    void tick(void* context);
    void reset();

private:
    void cancel_skipped_behaviors(void* context);
    void cancel_behavior(IndexType index, void* context);
    void pop_last_running_behavior();
    void pop_finished_behaviors();
    void prepare_behavior(IndexType index);

    inline bool is_running(IndexType index) const { return index == last_running_behaviors.front(); }
};


} /* BehaviorTree */ 

#endif
