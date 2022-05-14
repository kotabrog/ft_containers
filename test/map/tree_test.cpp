#include "_Rb_tree.hpp"
#include <iostream>
#include <string>
// #include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

void Rb_tree_node_structure_insert_and_delete_check()
{
    std::cout << "start insert" << std::endl;
    ft::_Rb_tree_node<int> a;
    a._color = ft::_Rb_tree_node_structure::_BLACK;
    a._value = 0;
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> b;
    b._value = 1;
    a.insert_left(&b);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(b.get_root()), "test1.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> c;
    c._value = 2;
    a.insert_right(&c);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(c.get_root()), "test2.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> d;
    d._value = 3;
    b.insert_left(&d);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(d.get_root()), "test3.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> e;
    e._value = 4;
    c.insert_left(&e);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(e.get_root()), "test4.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> f;
    f._value = 5;
    d.insert_left(&f);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(f.get_root()), "test5.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> g;
    g._value = 6;
    f.insert_right(&g);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(g.get_root()), "test6.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> h;
    h._value = 7;
    g.insert_left(&h);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(h.get_root()), "test7.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    ft::_Rb_tree_node<int> i;
    i._value = 8;
    f.insert_left(&i);
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(i.get_root()), "test8.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());

    std::cout << "start delete" << std::endl;
    h.delete_node();
    ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(i.get_root()), "test9.dot");
    ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());
    std::cout << "Rb_tree_node_structure_insert_and_delete_check: ok" << std::endl;
}

void random_make_tree_test(int num, bool save_flag = false)
{
    std::srand(std::time(NULL));
    ft::_Rb_tree_node<int> a;
    a._color = ft::_Rb_tree_node_structure::_BLACK;
    a._value = 0;
    std::cout << "start" << std::endl;
    for (int i = 1; i < num; ++i)
    {
        ft::_Rb_tree_node<int>* temp_node = static_cast<ft::_Rb_tree_node<int>*>(a.get_root());
        ft::_Rb_tree_node<int>* add_node = new ft::_Rb_tree_node<int>();
        add_node->_value = i;
        int stop_count = 0;
        bool is_left = true;
        while (++stop_count < 1000)
        {
            if (std::rand() % 2)
            {
                if (temp_node->_left == NULL)
                {
                    temp_node->insert_left(add_node);
                    is_left = true;
                    break;
                }
                temp_node = static_cast<ft::_Rb_tree_node<int>*>(temp_node->_left);
            }
            else
            {
                if (temp_node->_right == NULL)
                {
                    temp_node->insert_right(add_node);
                    is_left = false;
                    break;
                }
                temp_node = static_cast<ft::_Rb_tree_node<int>*>(temp_node->_right);
            }
        }
        if (stop_count == 1000)
        {
            std::cout << "error " << i << std::endl;
            return ;
        }
        std::cout << "\r" << "check " << i;
        try
        {
            ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cout << (is_left ? "left" : "right") << " added" << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
        if (save_flag)
            ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(a.get_root()), "test.dot");
    }
    std::cout << std::endl;
    std::cout << "random_make_tree_test: ok" << std::endl;
}


void random_make_tree_delete_test(int num, bool save_flag = false)
{
    std::srand(std::time(NULL));
    ft::_Rb_tree_node<int> a;
    a._color = ft::_Rb_tree_node_structure::_BLACK;
    a._value = 0;
    std::cout << "make start" << std::endl;
    for (int i = 1; i < num; ++i)
    {
        ft::_Rb_tree_node<int>* temp_node = static_cast<ft::_Rb_tree_node<int>*>(a.get_root());
        ft::_Rb_tree_node<int>* add_node = new ft::_Rb_tree_node<int>();
        add_node->_value = i;
        int stop_count = 0;
        while (++stop_count < 1000)
        {
            if (std::rand() % 2)
            {
                if (temp_node->_left == NULL)
                {
                    temp_node->insert_left(add_node);
                    break;
                }
                temp_node = static_cast<ft::_Rb_tree_node<int>*>(temp_node->_left);
            }
            else
            {
                if (temp_node->_right == NULL)
                {
                    temp_node->insert_right(add_node);
                    break;
                }
                temp_node = static_cast<ft::_Rb_tree_node<int>*>(temp_node->_right);
            }
        }
        if (stop_count == 1000)
        {
            std::cout << "error " << i << std::endl;
            return ;
        }
        std::cout << "\r" << "check " << i;
        try
        {
            ft::_Rb_tree_node_structure::check_rb_tree_rule(a.get_root());
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
    }
    if (save_flag)
        ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(a.get_root()), "test.dot");
    std::cout << std::endl;

    ft::_Rb_tree_node_structure* min_node = a.get_root()->get_minimum();
    std::cout << "delete start" << std::endl;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        ft::_Rb_tree_node_structure* temp = min_node->get_root()->get_minimum();
        int index = std::rand() % (num - i);
        for (int j = 0; j < index; ++j)
            temp = temp->increment();
        if (index == 0)
            min_node = min_node->increment();
        temp->delete_node();
        try
        {
            if (i != num - 1)
                ft::_Rb_tree_node_structure::check_rb_tree_rule(min_node->get_root());
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cout << "delete out: " << i << ", index: " << index << std::endl;
            std::cerr << e.what() << '\n';
            // return ;
            throw;
        }
        if (i != num - 1 && save_flag)
            ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(min_node->get_root()), "test.dot");
    }
    std::cout << std::endl;
    std::cout << "random_make_tree_delete_test: ok" << std::endl;
}


void random_value_insert_and_copy_test(int num, bool save_flag = false)
{
    std::srand(std::time(NULL));
    ft::_Rb_tree<int> tree;
    std::cout << "insert start" << std::endl;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        tree.insert_node(std::rand());
        try
        {
            tree.check_rb_tree_rule();
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
        if (save_flag)
            ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(tree._head), "test.dot");
    }
    std::cout << std::endl;

    std::cout << "copy start" << std::endl;
    ft::_Rb_tree<int> tree_copy(tree);
    try
    {
        tree_copy.check_rb_tree_rule();
    }
    catch(const std::exception& e)
    {
        std::cout << std::endl;
        std::cerr << e.what() << '\n';
        return ;
    }
    if (tree != tree_copy)
    {
        std::cout << "Copying results in a change in value or configuration" << std::endl;
        return ;
    }
    std::cout << "random_value_insert_and_copy_test: ok" << std::endl;
}


void decrement_check(int num)
{
    std::srand(std::time(NULL));
    ft::_Rb_tree<int> tree;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        tree.insert_node(std::rand());
        try
        {
            tree.check_rb_tree_rule();
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
    }
    ft::_Rb_tree_node_structure* node = tree._head->get_maximum();
    int value = *(int*)(node->get_value_ptr());
    node = node->decrement();
    while (node)
    {
        if (!tree._comp(*(int*)(node->get_value_ptr()), value))
        {
            std::cout << "out" << std::endl;
            return ;
        }
        value = *(int*)(node->get_value_ptr());
        node = node->decrement();
    }
    std::cout << std::endl;
    std::cout << "decrement_check: ok" << std::endl;
}


void random_value_delete_test(int num, bool save_flag = false)
{
    std::srand(std::time(NULL));
    ft::_Rb_tree<int> tree;
    std::cout << "make start" << std::endl;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        tree.insert_node(std::rand());
        try
        {
            tree.check_rb_tree_rule();
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
    }
    if (save_flag)
        ft::_Rb_tree_node<int>::debug(static_cast<ft::_Rb_tree_node<int>*>(tree._head), "test.dot");
    std::cout << std::endl;
    ft::_Rb_tree_node_structure* min_node = tree.get_min_node();
    std::cout << "delete start" << std::endl;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        ft::_Rb_tree_node_structure* temp = min_node->get_root()->get_minimum();
        int index = std::rand() % (num - i);
        for (int j = 0; j < index; ++j)
        {
            if (temp == NULL)
                break;
            temp = temp->increment();
        }
        if (temp == NULL)
            break;
        if (index == 0)
            min_node = min_node->increment();
        tree.delete_node(*(static_cast<int*>(temp->get_value_ptr())));
        try
        {
            tree.check_rb_tree_rule();
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
    }
    std::cout << std::endl;
    std::cout << "random_value_delete_test: ok" << std::endl;
}


void node_count_check(int num)
{
    ft::_Rb_tree<int> tree;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "\r" << "check " << i;
        tree.insert_node(i);
        try
        {
            tree.check_rb_tree_rule();
        }
        catch(const std::exception& e)
        {
            std::cout << std::endl;
            std::cerr << e.what() << '\n';
            return ;
        }
    }
    std::cout << std::endl;
    if (tree._node_count != num)
        std::cout << "node_count_check: no" << std::endl;
    else
        std::cout << "node_count_check: ok" << std::endl;
}


void const_check()
{
    const ft::_Rb_tree_node_structure const_node1;
    const ft::_Rb_tree_node_structure* temp = const_node1.get_root();
    std::cout << const_node1._color << std::endl;
    const ft::_Rb_tree<int> tree;
    tree.check_rb_tree_rule();
    std::cout << "const_check: ok" << std::endl;
}

int main()
{
    // no free test
    Rb_tree_node_structure_insert_and_delete_check();
    random_make_tree_test(1000, false);
    random_make_tree_delete_test(10000, false);
    // free test
    random_value_insert_and_copy_test(1000, false);
    decrement_check(100);
    random_value_delete_test(1000, false);
    node_count_check(1000);
    const_check();
}
