
extends Node

class Context:
	var count = 0
	var update_result

func _ready():
	var bt_root = get_node("BTRootNode")
	var context_foo = Context.new()
	context_foo.update_result = BTRootNode.BH_RUNNING
	var context_bar = Context.new()
	context_bar.update_result = BTRootNode.BH_SUCCESS
	var running_data_bar = bt_root.create_running_data()
	
	bt_root.tick(context_foo) # use default running data
	bt_root.tick(context_bar, running_data_bar)
	assert(context_foo.count == 1)
	assert(context_bar.count == 2)

	print(context_foo.count)
	print(context_bar.count)

