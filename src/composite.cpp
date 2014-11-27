#include "composite.h"

namespace BehaviorTree
{

void Selector::init(VMRunningData& running_data, IndexType , E_State ) {
    increase_index(running_data);
}

E_State Selector::child_update(VMRunningData& running_data, IndexType , void*, E_State child_state) {
    BT_ASSERT(child_state != BH_READY);
    if (child_state == BH_SUCCESS || child_state == BH_RUNNING) {
        move_index_to_composite_end(running_data);
    }
    return child_state;
}

void Sequence::init(VMRunningData& running_data, IndexType , E_State init_state) {
    BT_ASSERT(init_state == BH_READY || init_state == BH_RUNNING);
    if (init_state == BH_RUNNING) {
        move_index_to_running(running_data);
    } else {
        increase_index(running_data);
    }
}

E_State Sequence::child_update(VMRunningData& running_data, IndexType , void*, E_State child_state) {
    BT_ASSERT(child_state != BH_READY);
    if (child_state == BH_FAILURE || child_state == BH_RUNNING) {
        move_index_to_composite_end(running_data);
    }
    return child_state;
}

} /* BehaviorTree */ 
