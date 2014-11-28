#include "register_types.h"
#include "object_type_db.h"

#include "bt_root_node.h"
#include "bt_behavior_node.h"

void register_behaviortree_types() {
    ObjectTypeDB::register_type<BTRootNode>();
    ObjectTypeDB::register_type<BTActionNode>();
    ObjectTypeDB::register_type<BTDecoratorNode>();
}

void unregister_behaviortree_types() {
}

