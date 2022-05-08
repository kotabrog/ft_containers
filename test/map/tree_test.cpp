#include "_Rb_tree.hpp"
#include <iostream>
#include <string>
#include <map>

int main()
{
    ft::_Rb_tree_node<int> a;
    a._value = 0;

    ft::_Rb_tree_node<int> b;
    b._value = 1;
    a.insert_left(&b);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(b.get_root()), "test1.dot");

    ft::_Rb_tree_node<int> c;
    c._value = 2;
    a.insert_right(&c);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(c.get_root()), "test2.dot");

    ft::_Rb_tree_node<int> d;
    d._value = 3;
    b.insert_left(&d);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(d.get_root()), "test3.dot");

    ft::_Rb_tree_node<int> e;
    e._value = 4;
    c.insert_left(&e);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(e.get_root()), "test4.dot");

    ft::_Rb_tree_node<int> f;
    f._value = 5;
    d.insert_left(&f);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(f.get_root()), "test5.dot");

    ft::_Rb_tree_node<int> g;
    g._value = 6;
    f.insert_right(&g);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(g.get_root()), "test6.dot");

    ft::_Rb_tree_node<int> h;
    h._value = 7;
    g.insert_left(&h);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(h.get_root()), "test7.dot");

    ft::_Rb_tree_node<int> i;
    i._value = 8;
    f.insert_left(&i);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(i.get_root()), "test8.dot");
}
