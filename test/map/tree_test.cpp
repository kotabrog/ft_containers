#include "_Rb_tree.hpp"
#include <iostream>
#include <string>
#include <map>

int main()
{
    /*
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
    */
    /*
    ft::_Rb_tree_node<int> a;
    ft::_Rb_tree_node<int> b;
    ft::_Rb_tree_node<int> c;
    ft::_Rb_tree_node<int> d;

    a._color = ft::_Rb_tree_node<int>::_RED;
    b._color = ft::_Rb_tree_node<int>::_BLACK;
    c._color = ft::_Rb_tree_node<int>::_RED;
    d._color = ft::_Rb_tree_node<int>::_BLACK;

    a._value = 0;
    b._value = 1;
    c._value = 2;
    d._value = 3;

    a._left = &b;
    a._right = &c;
    b._right = &d;

    ft::_Rb_tree_node<int>::debug(&a);
    */
    ft::_Rb_tree_node<std::string> a;
    ft::_Rb_tree_node<std::string> b;
    ft::_Rb_tree_node<std::string> c;
    ft::_Rb_tree_node<std::string> d;

    a._color = ft::_Rb_tree_node<std::string>::_RED;
    b._color = ft::_Rb_tree_node<std::string>::_BLACK;
    c._color = ft::_Rb_tree_node<std::string>::_RED;
    d._color = ft::_Rb_tree_node<std::string>::_BLACK;

    a._value = "aaaaa";
    b._value = "bbbbb";
    c._value = "ccccc";
    d._value = "ddddd";

    a._left = &b;
    a._right = &c;
    b._right = &d;

    ft::_Rb_tree_node<std::string>::debug(&a);
}
