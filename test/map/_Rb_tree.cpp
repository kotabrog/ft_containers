#include "_Rb_tree.hpp"

namespace ft
{
_Rb_tree_node_structure::_Rb_tree_node_structure()
    : _parent(NULL), _left(NULL), _right(NULL), _color(_Rb_tree_node_structure::_RED) {}


_Rb_tree_node_structure* _Rb_tree_node_structure::get_other_brothers()
{
    if (_parent)
    {
        if (_parent->_left == this)
            return _parent->_right;
        else if (_parent->_right == this)
            return _parent->_left;
        throw std::runtime_error("Node did not find himself in his parent's child");
    }
    return NULL;
}


_Rb_tree_node_structure* _Rb_tree_node_structure::get_root()
{
    _Rb_tree_node_structure* node = this;
    while (node->_parent)
        node = node->_parent;
    return node;
}


bool _Rb_tree_node_structure::is_left_node()
{
    return _parent && _parent->_left == this;
}


bool _Rb_tree_node_structure::is_right_node()
{
    return _parent && _parent->_right == this;
}


void _Rb_tree_node_structure::_insert_brother_is_non_or_red_case(_Rb_tree_node_structure* node)
{
    _parent->_color = _RED;
    _color = _BLACK;
    node->_parent = this;
    if (_parent->is_left_node())
        _parent->_parent->insert_left(_parent);
    else if (_parent->is_right_node())
        _parent->_parent->insert_right(_parent);
}


void _Rb_tree_node_structure::_insert_left_left_case_rotation()
{
    _parent->_left = _right;
    if (_right)
        _right->_parent = _parent;
    _right = _parent;
    if (_parent->is_left_node())
        _parent->_parent->_left = this;
    else if (_parent->is_right_node())
        _parent->_parent->_right = this;
    _parent = _parent->_parent;
    _right->_parent = this;
    _color = _BLACK;
    _right->_color = _RED;
}


void _Rb_tree_node_structure::_insert_right_right_case_rotation()
{
    _parent->_right = _left;
    if (_left)
        _left->_parent = _parent;
    _left = _parent;
    if (_parent->is_left_node())
        _parent->_parent->_left = this;
    else if (_parent->is_right_node())
        _parent->_parent->_right = this;
    _parent = _parent->_parent;
    _left->_parent = this;
    _color = _BLACK;
    _left->_color = _RED;
}


void _Rb_tree_node_structure::insert_left(_Rb_tree_node_structure* node)
{
    if (node->_color == _BLACK)
        throw std::runtime_error("The color of the node to be added must be red");
    if (_color == _BLACK)
    {
        node->_parent = this;
        _left = node;
    }
    else if (_parent == NULL)
    {
        _color = _BLACK;
        node->_parent = this;
        _left = node;
    }
    else
    {
        _Rb_tree_node_structure* brother = get_other_brothers();
        if (brother && brother->_color == _RED)
        {
            brother->_color = _BLACK;
            _left = node;
            _insert_brother_is_non_or_red_case(node);
        }
        else if (is_right_node())
        {
            _left = node->_right;
            if (_left)
                _left->_parent = this;
            node->_parent = _parent;
            _parent->_right = node;
            node->_right = this;
            _parent = node;
            node->_insert_right_right_case_rotation();
        }
        else
        {
            _left = node;
            node->_parent = this;
            _insert_left_left_case_rotation();
        }
    }
}


void _Rb_tree_node_structure::insert_right(_Rb_tree_node_structure* node)
{
    if (node->_color == _BLACK)
        throw std::runtime_error("The color of the node to be added must be red");
    if (_color == _BLACK)
    {
        node->_parent = this;
        _right = node;
    }
    else if (_parent == NULL)
    {
        _color = _BLACK;
        node->_parent = this;
        _right = node;
    }
    else
    {
        _Rb_tree_node_structure* brother = get_other_brothers();
        if (brother && brother->_color == _RED)
        {
            brother->_color = _BLACK;
            _right = node;
            _insert_brother_is_non_or_red_case(node);
        }
        else if (is_left_node())
        {
            _right = node->_left;
            if (_right)
                _right->_parent = this;
            node->_parent = _parent;
            _parent->_left = node;
            node->_left = this;
            _parent = node;
            node->_insert_left_left_case_rotation();
        }
        else
        {
            _right = node;
            node->_parent = this;
            _insert_right_right_case_rotation();
        }
    }
}


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
