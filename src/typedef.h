#ifndef BEHAVIOR_TREE_TYPEDEF_H
#define BEHAVIOR_TREE_TYPEDEF_H

#if defined(BEHAVIOR_TREE_AS_GODOT_MODULE)
#include "core/vector.h"
#define BT_STATIC_ASSERT(x, y)
#define BT_ASSERT(x)
#else
#include <cassert>
#include <vector>
#include <algorithm>
#define BT_STATIC_ASSERT(x, y) static_assert(x, y)
#define BT_ASSERT(x) assert(x)
#endif

namespace BehaviorTree { struct Node; }

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

#if defined(BEHAVIOR_TREE_AS_GODOT_MODULE)

template<typename T> class BTVector : public Vector<T> {}

template<typename T, typename COMPARATOR>
void sort(BTVector<T>& vector) { vector.sort_custom<COMPARATOR>(); }

#else

template<typename T> class BTVector : public std::vector<T> {};

template<typename T, typename COMPARATOR>
void sort(BTVector<T>& vector) { std::sort(vector.begin(), vector.end(), COMPARATOR()); }

#endif

typedef BTVector<NodeData> BTStructure;
typedef BTVector<Node*> NodeList;


} /* BehaviorTree */ 

#endif
