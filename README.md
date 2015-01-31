# Behavior Tree for Godot Engine
## References
[Understanding Behavior Trees](http://aigamedev.com/open/article/bt-overview/) by Alex J. Champandard

[Behavior trees for AI: How they work](http://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) by Chris Simpson

[An Introduction to Behavior Trees](http://guineashots.com/2014/07/25/an-introduction-to-behavior-trees-part-1/) by Renato Pereira

[Behavior tree series](http://web.archive.org/web/20140723035304/http://www.altdev.co/2011/02/24/introduction-to-behavior-trees/) by Bjoern Knafla
(this series of behavior tree is really helpful, but unfortunately the original post cannot be accessed since altdev.co was dead)

## Compiling as Godot module

Link or copy *src* directory to *$(GODOT_ROOT)/modules/behaviortree*, then [compile engine](https://github.com/okamstudio/godot/wiki/advanced#compiling--running).

## Usage

After success compile godot engine with this module, you can find those new types of node in editor:
**BTRootNode**, **BTParallelNode**, **BTSelectorNode**, **BTSequenceNode**, **BTDecoratorNode**, **BTActionNode**.

**BTActionNode**, **BTDecoratorNode** and **BTRootNode** can be extend by script for creating your own AI.

**BTParallelNode**, **BTSelectorNode** and **BTSequenceNode** are composite node which cannot be extend by script.

Beware that node extend by script cannot control access flow. If you need extra composite or a special decorator which can control access flow, you must write that composite or decorator in c++.

### BTRootNode

Inherit: **BTDecorator**

Constraint: Must be placed at top of behavior tree.
- `void tick(Object context, int running_data_index)`
travel entire behavior tree.

- `void step(Object context, int running_data_index)`
just one step forward

### BTDecoratorNode

Inherit: **BTNode**

Constraint: Only one child allowed.

- `void _bt_continue(int index, Object context)` continue running if this node was running last tick
- `void _bt_prepare(int index, Object context)` prepare for running if this node was not running last tick
- `E_State _bt_pre_update(int index, Object context)` before run child
- `E_State _bt_post_update(int index, Object context, E_State child_state)` after run child
- `void _bt_abort(int index, Object context)` abort this running node

### BTParallelNode

Inherit: **BTCompositeNode**

Execute children nodes without interruption.

### BTSelectorNode

Inherit: **BTCompositeNode**

Always execute child from left/top to right/down. Report *BH_SUCESS* or *BH_RUNNING* to parent when a child node reported a *BH_SUCCESS* or *BH_RUNNING*, report *BH_FAILURE* to parent when all its children reported a *BH_FAILURE*.

### BTSequenceNode

Inherit: **BTCompositeNode**

Execute child from left/top to right/down, or restart execute at last running child. Report *BH_FAILURE* or *BH_RUNNING* to parent when a child node reported a *BH_FAILURE* or *BH_RUNNING*, report *BH_SUCCESS* to parent when all its children reported a *BH_SUCCESS*.

### BTActionNode

Inherit: **BTNode**

Constraint: Cannot have any child.
- `void _bt_continue(int index, Object context)` continue running if this node was running last tick
- `void _bt_prepare(int index, Object context)` prepare for running if this node was not running last tick
- `E_State _bt_update(int index, Object context)` execute action
- `void _bt_abort(int index, Object context)` abort this running node

## TODO
1. Extend godot editor for behavior tree.
  - Cannot add child into BTActionNode.
  - Cannot add more than one child into BTDecoratorNode and BTRootNode.
  - Constrain BTRootNode at the top of tree.
2. Add random pick composite.
3. Add error handler decorator.
4. Add more parallel nodes with different report police.
5. More composite and decorator?
6. A specific editor view for behavior tree in godot editor.
