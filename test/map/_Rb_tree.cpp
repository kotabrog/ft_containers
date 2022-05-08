#include "_Rb_tree.hpp"

namespace ft
{
_Rb_tree_node_structure::_Rb_tree_node_structure()
    : _parent(NULL), _left(NULL), _right(NULL), _color(_Rb_tree_node_structure::_RED) {}


void* _Rb_tree_node_structure::get_value_ptr()
{
    return NULL;
}


const void* _Rb_tree_node_structure::get_value_ptr() const
{
    return NULL;
}


void _Rb_tree_node_structure::debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs)
{
    int my_num = node_num;
    if (node->_color == _Rb_tree_node_structure::_RED)
        ofs << "    " << my_num << " [\n        color = \"#ff0000\"\n    ];" << std::endl;
    else
        ofs << "    " << my_num << " [\n        color = \"#000000\"\n    ];" << std::endl;
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


void _Rb_tree_node_structure::debug(const _Rb_tree_node_structure* head, const std::string file_name)
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

} // namespace ft
