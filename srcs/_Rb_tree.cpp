#include "_Rb_tree.hpp"

namespace ft
{
_Rb_tree_node_structure::_Rb_tree_node_structure()
    : _color(_Rb_tree_node_structure::_RED), _parent(NULL), _left(NULL), _right(NULL) {}


_Rb_tree_node_structure* _Rb_tree_node_structure::get_other_brothers()
{
    return const_cast<_Rb_tree_node_structure*>(static_cast<const _Rb_tree_node_structure*>(this)->get_other_brothers());
}


_Rb_tree_node_structure::~_Rb_tree_node_structure() {}

const _Rb_tree_node_structure* _Rb_tree_node_structure::get_other_brothers() const
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


const _Rb_tree_node_structure* _Rb_tree_node_structure::get_root() const
{
    const _Rb_tree_node_structure* node = this;
    while (node->_parent)
        node = node->_parent;
    return node;
}


_Rb_tree_node_structure* _Rb_tree_node_structure::get_minimum()
{
    _Rb_tree_node_structure* node = this;
    while (node->_left)
        node = node->_left;
    return node;
}


const _Rb_tree_node_structure* _Rb_tree_node_structure::get_minimum() const
{
    const _Rb_tree_node_structure* node = this;
    while (node->_left)
        node = node->_left;
    return node;
}


_Rb_tree_node_structure* _Rb_tree_node_structure::get_maximum()
{
    _Rb_tree_node_structure* node = this;
    while (node->_right)
        node = node->_right;
    return node;
}


const _Rb_tree_node_structure* _Rb_tree_node_structure::get_maximum() const
{
    const _Rb_tree_node_structure* node = this;
    while (node->_right)
        node = node->_right;
    return node;
}


bool _Rb_tree_node_structure::is_left_node() const
{
    return _parent && _parent->_left == this;
}


bool _Rb_tree_node_structure::is_right_node() const
{
    return _parent && _parent->_right == this;
}


_Rb_tree_node_structure* _Rb_tree_node_structure::increment()
{
    _Rb_tree_node_structure* node = this;
    if (node->_right)
        return node->_right->get_minimum();
    while (node->_parent && node->is_right_node())
        node = node->_parent;
    return node->_parent;
}


const _Rb_tree_node_structure* _Rb_tree_node_structure::increment() const
{
    const _Rb_tree_node_structure* node = this;
    if (node->_right)
        return node->_right->get_minimum();
    while (node->_parent && node->is_right_node())
        node = node->_parent;
    return node->_parent;
}


_Rb_tree_node_structure* _Rb_tree_node_structure::decrement()
{
    _Rb_tree_node_structure* node = this;
    if (node->_left)
        return node->_left->get_maximum();
    while (node->_parent && node->is_left_node())
        node = node->_parent;
    return node->_parent;
}


const _Rb_tree_node_structure* _Rb_tree_node_structure::decrement() const
{
    const _Rb_tree_node_structure* node = this;
    if (node->_left)
        return node->_left->get_maximum();
    while (node->_parent && node->is_left_node())
        node = node->_parent;
    return node->_parent;
}


void _Rb_tree_node_structure::_insert_brother_is_non_or_red_case(_Rb_tree_node_structure* node)
{
    _parent->_color = _RED;
    _color = _BLACK;
    node->_parent = this;
    if (_parent->_parent == NULL)
        _parent->_color = _BLACK;
    else if (_parent->is_left_node())
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
            return ;
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


void _Rb_tree_node_structure::_connect_node(_Rb_tree_node_structure* parent, bool left)
{
    if (parent)
    {
        if (left)
            parent->_left = this;
        else
            parent->_right = this;
    }
    _parent = parent;
}


void _Rb_tree_node_structure::_adjacent_position_swap(_Rb_tree_node_structure* parent)
{
    _Rb_tree_node_structure* left = _left;
    _Rb_tree_node_structure* right = _right;
    _Rb_tree_node_structure* parent_parent = parent->_parent;
    bool parent_is_left = parent->is_left_node();
    if (this == parent->_left)
    {
        _Rb_tree_node_structure* parent_right = parent->_right;

        _connect_node(parent_parent, parent_is_left);
        parent->_connect_node(this, true);
        if (parent_right)
            parent_right->_connect_node(this, false);
        else
            _right = NULL;

        if (left)
            left->_connect_node(parent, true);
        else
            parent->_left = NULL;
        if (right)
            right->_connect_node(parent, false);
        else
            parent->_right = NULL;
    }
    else
    {
        _Rb_tree_node_structure* parent_left = parent->_left;

        _connect_node(parent_parent, parent_is_left);
        parent->_connect_node(this, false);
        if (parent_left)
            parent_left->_connect_node(this, true);
        else
            _left = NULL;

        if (left)
            left->_connect_node(parent, true);
        else
            parent->_left = NULL;
        if (right)
            right->_connect_node(parent, false);
        else
            parent->_right = NULL;
    }
}


void _Rb_tree_node_structure::_position_swap(_Rb_tree_node_structure* node)
{
    if (node->_parent == this)
        node->_adjacent_position_swap(this);
    else if (_parent == node)
        _adjacent_position_swap(node);
    else
    {
        _Rb_tree_node_structure* parent = _parent;
        bool is_left = is_left_node();
        _Rb_tree_node_structure* left = _left;
        _Rb_tree_node_structure* right = _right;
        _Rb_tree_node_structure* node_parent = node->_parent;
        bool node_is_left = node->is_left_node();
        _Rb_tree_node_structure* node_left = node->_left;
        _Rb_tree_node_structure* node_right = node->_right;

        _connect_node(node_parent, node_is_left);
        if (node_left)
            node_left->_connect_node(this, true);
        else
            _left = NULL;
        if (node_right)
            node_right->_connect_node(this, false);
        else
            _right = NULL;

        node->_connect_node(parent, is_left);
        if (left)
            left->_connect_node(node, true);
        else
            node->_left = NULL;
        if (right)
            right->_connect_node(node, false);
        else
            node->_right = NULL;
    }
}


bool _Rb_tree_node_structure::_delete_node()
{
    if (_left && _right)
    {
        _Rb_tree_node_structure* left_max_node = _left->get_maximum();
        _Rb_tree_node_structure* right_min_node = _right->get_minimum();
        if (left_max_node->_color == _RED)
        {
            _position_swap(left_max_node);
            left_max_node->_color = _color;
            _color = _RED;
        }
        else
        {
            _position_swap(right_min_node);
            if (_color != right_min_node->_color)
            {
                bool temp_color;
                temp_color = _color;
                _color = right_min_node->_color;
                right_min_node->_color = temp_color;
            }
        }
    }
    bool is_parent_left = true;
    if (_left)
    {
        _left->_parent = _parent;
        if (is_left_node())
            _parent->_left = _left;
        else if (is_right_node())
        {
            is_parent_left = false;
            _parent->_right = _left;
        }
    }
    else if (_right)
    {
        _right->_parent = _parent;
        if (is_left_node())
            _parent->_left = _right;
        else if (is_right_node())
        {
            is_parent_left = false;
            _parent->_right = _right;
        }
    }
    else
    {
        if (is_left_node())
            _parent->_left = NULL;
        else if (is_right_node())
        {
            is_parent_left = false;
            _parent->_right = NULL;
        }
    }
    return is_parent_left;
}


void _Rb_tree_node_structure::_delete_brother_black_and_brother_child_red(_Rb_tree_node_structure* brother, _Rb_tree_node_structure* red_child, bool left)
{
    _Rb_tree_node_structure* parent = brother->_parent;
    bool brother_is_left = brother->is_left_node();
    if ((brother_is_left && left) || (!brother_is_left && !left))
    {
        brother->_connect_node(parent->_parent, parent->is_left_node());
        if (brother_is_left)
        {
            if (brother->_right)
                brother->_right->_connect_node(parent, true);
            else
                parent->_left = NULL;
        }
        else
        {
            if (brother->_left)
                brother->_left->_connect_node(parent, false);
            else
                parent->_right = NULL;
        }
        parent->_connect_node(brother, !brother_is_left);
        brother->_color = parent->_color;
        parent->_color = _BLACK;
        red_child->_color = _BLACK;
        if (brother->_parent == NULL)
            brother->_color = _BLACK;
    }
    else
    {
        red_child->_connect_node(parent, brother_is_left);
        if (left)
        {
            if (red_child->_right)
                red_child->_right->_connect_node(brother, true);
            else
                brother->_left = NULL;
        }
        else
        {
            if (red_child->_left)
                red_child->_left->_connect_node(brother, false);
            else
                brother->_right = NULL;
        }
        brother->_connect_node(red_child, !left);

        red_child->_connect_node(parent->_parent, parent->is_left_node());
        if (brother_is_left)
        {
            if (red_child->_right)
                red_child->_right->_connect_node(parent, true);
            else
                parent->_left = NULL;
        }
        else
        {
            if (red_child->_left)
                red_child->_left->_connect_node(parent, false);
            else
                parent->_right = NULL;
        }
        parent->_connect_node(red_child, !brother_is_left);
        red_child->_color = parent->_color;
        parent->_color = _BLACK;
        if (red_child->_parent == NULL)
            red_child->_color = _BLACK;
    }
}


void _Rb_tree_node_structure::_delete_brother_black_and_brother_child_black(_Rb_tree_node_structure* brother)
{
    _Rb_tree_node_structure* parent = brother->_parent;
    bool parent_color = parent->_color;
    parent->_color = _BLACK;
    brother->_color = _RED;
    if (parent_color == _BLACK)
        parent->_delete_node_adjustment(parent->get_other_brothers());
}


void _Rb_tree_node_structure::_delete_brother_red(_Rb_tree_node_structure* brother)
{
    _Rb_tree_node_structure* parent = brother->_parent;
    bool brother_is_left = brother->is_left_node();
    brother->_connect_node(parent->_parent, parent->is_left_node());
    if (brother_is_left)
    {
        if (brother->_right)
            brother->_right->_connect_node(parent, true);
        else
            parent->_left = NULL;
    }
    else
    {
        if (brother->_left)
            brother->_left->_connect_node(parent, false);
        else
            parent->_right = NULL;
    }
    parent->_connect_node(brother, !brother_is_left);
    parent->_color = _RED;
    brother->_color = _BLACK;
    _delete_node_adjustment(brother_is_left ? parent->_left : parent->_right);
}


void _Rb_tree_node_structure::_delete_node_adjustment(_Rb_tree_node_structure* brother)
{
    if (_parent && _color == _BLACK)
    {
        if (brother)
        {
            if (brother->_color == _BLACK)
            {
                if (brother->_left && brother->_left->_color == _RED)
                    _delete_brother_black_and_brother_child_red(brother, brother->_left, true);
                else if (brother->_right && brother->_right->_color == _RED)
                    _delete_brother_black_and_brother_child_red(brother, brother->_right, false);
                else
                    _delete_brother_black_and_brother_child_black(brother);
            }
            else
                _delete_brother_red(brother);
        }
    }
}


void _Rb_tree_node_structure::_delete_node_adjustment_first(bool is_parent_left)
{
    if (_parent == NULL)
    {
        if (_left)
            _left->_color = _BLACK;
        else if (_right)
            _right->_color = _BLACK;
    }
    else
        _delete_node_adjustment(is_parent_left ? _parent->_right : _parent->_left);
}


void _Rb_tree_node_structure::delete_node()
{
    bool is_parent_left = _delete_node();
    _delete_node_adjustment_first(is_parent_left);
}


void* _Rb_tree_node_structure::get_value_ptr()
{
    return NULL;
}


const void* _Rb_tree_node_structure::get_value_ptr() const
{
    return NULL;
}


void _Rb_tree_node_structure::_debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs, const _Rb_tree_node_structure* prohibited_node)
{
    if (node == prohibited_node)
        return ;
    int my_num = node_num;
    if (node->_color == _Rb_tree_node_structure::_RED)
        ofs << "    " << my_num << " [\n        color = \"#ff0000\"\n    ];" << std::endl;
    else
        ofs << "    " << my_num << " [\n        color = \"#000000\"\n    ];" << std::endl;
    if (node->_left && node->_left != prohibited_node)
    {
        node_num += 1;
        ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
        _debug_node(node->_left, node_num, ofs, prohibited_node);
    }
    else
        ofs << "    left" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> left" << my_num << ";" << std::endl;
    if (node->_right && node->_right != prohibited_node)
    {
        node_num += 1;
        ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
        _debug_node(node->_right, node_num, ofs, prohibited_node);
    }
    else
        ofs << "    right" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> right" << my_num << ";" << std::endl;
}


void _Rb_tree_node_structure::debug(const _Rb_tree_node_structure* root, const std::string file_name, const _Rb_tree_node_structure* prohibited_node)
{
    std::ofstream ofs(file_name.c_str());
    if (!ofs)
        return ;
    ofs << "digraph test {" << std::endl;
    int node_num = 0;
    _debug_node(root, node_num, ofs, prohibited_node);
    ofs << "}" << std::endl;
    ofs.close();
}


void _Rb_tree_node_structure::_check_rb_tree_rule_node(const _Rb_tree_node_structure* node, int black_node_num, const _Rb_tree_node_structure* prohibited_node)
{
    if (node->_parent && node->_parent->_color == _RED && node->_color == _RED)
        throw std::runtime_error("Under the red node must be black");
    if (node->_color == _BLACK)
        black_node_num -= 1;
    if (node->_left && node->_left != prohibited_node)
    {
        if (node->_left->_parent != node)
            throw std::runtime_error("Child-parent bonding does not match.");
        _check_rb_tree_rule_node(node->_left, black_node_num, prohibited_node);
    }
    if (node->_right && node->_right != prohibited_node)
    {
        if (node->_right->_parent != node)
            throw std::runtime_error("Child-parent bonding does not match.");
        _check_rb_tree_rule_node(node->_right, black_node_num, prohibited_node);
    }
    if (!(node->_left && node->_right) && black_node_num != 0)
        throw std::runtime_error("The number of black node from root to leaf must be constant");
}


void _Rb_tree_node_structure::check_rb_tree_rule(const _Rb_tree_node_structure* root, const _Rb_tree_node_structure* prohibited_node)
{
    if (root == NULL || root == prohibited_node)
        return ;
    if (root->_color != _BLACK)
        throw std::runtime_error("Root must be black.");
    if (root->_parent != NULL)
        throw std::runtime_error("Root parents should not be there.");
    int black_node_num = 0;
    const _Rb_tree_node_structure* node = root;
    while (node && node != prohibited_node)
    {
        if (node->_color == _BLACK)
            black_node_num += 1;
        node = node->_left;
    }
    _check_rb_tree_rule_node(root, black_node_num, prohibited_node);
}

} // namespace ft
