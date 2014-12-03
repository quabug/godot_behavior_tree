# Behavior Tree for Godot Engine
## References
[Understanding Behavior Trees](http://aigamedev.com/open/article/bt-overview/) by Alex J. Champandard

[Behavior trees for AI: How they work](http://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) by Chris Simpson

[An Introduction to Behavior Trees](http://guineashots.com/2014/07/25/an-introduction-to-behavior-trees-part-1/) by Renato Pereira

[Behavior tree series](http://web.archive.org/web/20140723035304/http://www.altdev.co/2011/02/24/introduction-to-behavior-trees/) by Bjoern Knafla
(this series of behavior tree is really helpful, but unfortunately the original post cannot be accessed since altdev.co was dead)

## Compiling as Godot module
Link(recommend) or copy *src* directory to *$(GODOT_ROOT)/modules/behaviortree*, then [compile engine](https://github.com/okamstudio/godot/wiki/advanced#compiling--running).

## Usage
In editor you can find those new types of node:
BTRootNode, BTParallelNode, BTSelectorNode, BTSequenceNode, BTDecoratorNode, BTActionNode.

BTActionNode, BTDecoratorNode and BTRootNode can be extend by script for creating your own AI.
BTParallelNode, BTSelectorNode and BTSequenceNode are composite node which cannot be extend by script.
Beware that node extend by script cannot control access flow, which means if you need extra composite or a special decorator which can control access flow, you must write that composite or decorator in c++.
