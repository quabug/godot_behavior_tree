#include "register_types.h"
#include "object_type_db.h"

#include "bt_string_names.h"
#include "bt_root_node.h"
#include "bt_action_node.h"
#include "bt_composite_node.h"
#include "bt_decorator_node.h"

void register_behaviortree_types() {
    BTStringNames::create();

    ObjectTypeDB::register_type<BTRootNode>();
    ObjectTypeDB::register_type<BTActionNode>();
    ObjectTypeDB::register_type<BTDecoratorNode>();
    ObjectTypeDB::register_type<BTSequenceNode>();
    ObjectTypeDB::register_type<BTSelectorNode>();
    ObjectTypeDB::register_type<BTParallelNode>();
}

void unregister_behaviortree_types() {
    BTStringNames::free();
}

