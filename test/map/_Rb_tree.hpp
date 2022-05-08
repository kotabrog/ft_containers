#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <string>
#include <fstream>

namespace ft
{
class _Rb_tree_node_structure
{
public:
    static const bool _RED = false;
    static const bool _BLACK = true;

    bool _color;
    _Rb_tree_node_structure* _parent;
    _Rb_tree_node_structure* _left;
    _Rb_tree_node_structure* _right;

    _Rb_tree_node_structure();
    static void debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs);
    static void debug(const _Rb_tree_node_structure* head, const std::string file_name = "test.dot");
    // static _Rb_tree_node_structure* increment(_Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* increment(const _Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* decrement(_Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* decrement(const _Rb_tree_node_structure* node);
};

} // namespace ft

#endif
