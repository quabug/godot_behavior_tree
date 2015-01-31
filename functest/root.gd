
extends BTRootNode

var count = 0

const state = ["BH_ERROR", "BH_SUCCESS", "BH_FAILURE", "BH_RUNNING"]
var node_list = []

func _ready():
	print("root ready")
	set_process(true)

func _process(delta):
	print(" ")
	print("root process")
	tick(self)

func _bt_continue(index, context):
	print("[",index,"]"," [continue] [root] ")

func _bt_prepare(index, context):
	print("[",index,"]"," [prepare] [root] ")

func _bt_pre_update(index, context):
	print("[",index,"]"," [pre update] [root] ")
	context.count += 1
	if context.count == 2:
		set_process(false)
	return BH_SUCCESS

func _bt_post_update(index, context, child_state):
	print("[",index,"]"," [post update] [root] [", state[child_state], "] ")
	return child_state

func _bt_abort(index, context):
	print("[",index,"]"," [abort] [root]")
