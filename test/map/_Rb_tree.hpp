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

    // static _Rb_tree_node_structure* increment(_Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* increment(const _Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* decrement(_Rb_tree_node_structure* node);
    // static _Rb_tree_node_structure* decrement(const _Rb_tree_node_structure* node);

    virtual void* get_value_ptr();
    virtual const void* get_value_ptr() const;

    static void debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs);
    static void debug(const _Rb_tree_node_structure* head, const std::string file_name = "test.dot");
};

template<typename Val>
class _Rb_tree_node : public _Rb_tree_node_structure
{
public:
    Val _value;

    _Rb_tree_node() : _Rb_tree_node_structure() {}

    virtual void* get_value_ptr() {return &_value;}
    virtual const void* get_value_ptr() const {return &_value;}

    static void debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs)
    {
        int my_num = node_num;
        if (node->_color == _Rb_tree_node_structure::_RED)
            ofs << "    " << my_num << " [\n        label = \"" << *static_cast<const Val*>(node->get_value_ptr()) << "\",\n        color = \"#ff0000\"\n    ];" << std::endl;
        else
            ofs << "    " << my_num << " [\n        label = \"" << *static_cast<const Val*>(node->get_value_ptr()) << "\",\n        color = \"#000000\"\n    ];" << std::endl;
        if (node->_left)
        {
            node_num += 1;
            ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
            debug_node(node->_left, node_num, ofs);
        }
        else
            ofs << "    left" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> left" << my_num << ";" << std::endl;
        if (node->_right)
        {
            node_num += 1;
            ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
            debug_node(node->_right, node_num, ofs);
        }
        else
            ofs << "    right" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> right" << my_num << ";" << std::endl;
    }

    static void debug(const _Rb_tree_node* head, const std::string file_name = "test.dot")
    {
        std::ofstream ofs(file_name.c_str());
        if (!ofs)
            return ;
        ofs << "digraph test {" << std::endl;
        int node_num = 0;
        debug_node(head, node_num, ofs);
        ofs << "}" << std::endl;
        ofs.close();
    }

};

} // namespace ft

#endif
