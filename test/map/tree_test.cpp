#include "_Rb_tree.hpp"
#include <iostream>
#include <map>

int main()
{
    ft::_Rb_tree_node_structure a;
    ft::_Rb_tree_node_structure b;
    ft::_Rb_tree_node_structure c;
    ft::_Rb_tree_node_structure d;

    a._color = ft::_Rb_tree_node_structure::_RED;
    b._color = ft::_Rb_tree_node_structure::_BLACK;
    c._color = ft::_Rb_tree_node_structure::_RED;
    d._color = ft::_Rb_tree_node_structure::_BLACK;

    a._left = &b;
    a._right = &c;
    b._right = &d;

    ft::_Rb_tree_node_structure::debug(&a);
}
