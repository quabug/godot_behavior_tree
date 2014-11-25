#ifndef BEHAVIOR_TREE_TYPEDEF_H
#define BEHAVIOR_TREE_TYPEDEF_H

namespace BehaviorTree
{
    
enum E_State { BH_READY, BH_SUCCESS, BH_FAILURE, BH_RUNNING };

typedef unsigned short IndexType;
struct NodeData
{
    union {
    IndexType begin;
    IndexType index;
    };
    IndexType end;
};

#if defined(USE_GODOT_CONTAINER)
#elif defined(USE_STL_CONTAINER)
#endif

} /* BehaviorTree */ 

#endif
