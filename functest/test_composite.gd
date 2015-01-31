
extends BTRootNode

var count = 0

var composites = [BTParallelNode.new(), BTSequenceNode.new(), BTSelectorNode.new(), preload("CustomParallel.gd").new()]

export(int, "parallel", "sequence", "selector", "custom_parallel") var composite_type

const state = ["BH_ERROR", "BH_SUCCESS", "BH_FAILURE", "BH_RUNNING"]
var node_list = []
var Action = preload("action.gd")
var actions = [Action.new(), Action.new(), Action.new()]

var update_results = [ # each tick array
	[BH_SUCCESS, BH_SUCCESS, BH_SUCCESS], # each actions
	[BH_FAILURE, BH_FAILURE, BH_FAILURE],
	[BH_SUCCESS, BH_RUNNING, BH_SUCCESS],
	[BH_FAILURE, BH_RUNNING, BH_FAILURE],
	[BH_SUCCESS, BH_FAILURE, BH_FAILURE]
]

func _ready():
	print("root ready")
	set_process(true)
	add_child(composites[composite_type])
	for act in actions:
		composites[composite_type].add_child(act)

func _process(delta):
	print(" ")
	print("root process")
	var actions_result = update_results[count]
	for i in range(actions.size()):
		actions[i].update_result = actions_result[i]
	tick(self)

func _bt_continue(index, context):
	print("[",index,"]"," [continue] [root] ")

func _bt_prepare(index, context):
	print("[",index,"]"," [prepare] [root] ")

func _bt_pre_update(index, context):
	print("[",index,"]"," [pre update] [root] ")
	context.count += 1
	if context.count == 5:
		set_process(false)
	return BH_SUCCESS

func _bt_post_update(index, context, child_state):
	print("[",index,"]"," [post update] [root] [", state[child_state], "] ")
	return child_state

func _bt_abort(index, context):
	print("[",index,"]"," [abort] [root]")
