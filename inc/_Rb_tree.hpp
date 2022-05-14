#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <string>
#include <fstream>

#include "alloc_traits.hpp"

namespace ft
{
class _Rb_tree_node_structure
{
private:
    void _insert_brother_is_non_or_red_case(_Rb_tree_node_structure* node);
    void _insert_left_left_case_rotation();
    void _insert_right_right_case_rotation();
    void _connect_node(_Rb_tree_node_structure* parent, bool left);
    void _adjacent_position_swap(_Rb_tree_node_structure* parent);
    void _position_swap(_Rb_tree_node_structure* node);
    bool _delete_node();
    void _delete_brother_black_and_brother_child_red(_Rb_tree_node_structure* brother,
                                                     _Rb_tree_node_structure* red_child,
                                                     bool left);
    void _delete_brother_black_and_brother_child_black(_Rb_tree_node_structure* brother);
    void _delete_brother_red(_Rb_tree_node_structure* brother);
    void _delete_node_adjustment(_Rb_tree_node_structure* brother);
    void _delete_node_adjustment_first(bool is_parent_left);

    static void _debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs);
    static void _check_rb_tree_rule_node(const _Rb_tree_node_structure* node, int black_node_num);

public:
    static const bool _RED = false;
    static const bool _BLACK = true;

    bool _color;
    _Rb_tree_node_structure* _parent;
    _Rb_tree_node_structure* _left;
    _Rb_tree_node_structure* _right;

    _Rb_tree_node_structure();
    virtual ~_Rb_tree_node_structure();

    _Rb_tree_node_structure* get_other_brothers();
    const _Rb_tree_node_structure* get_other_brothers() const;
    _Rb_tree_node_structure* get_root();
    const _Rb_tree_node_structure* get_root() const;
    _Rb_tree_node_structure* get_minimum();
    const _Rb_tree_node_structure* get_minimum() const;
    _Rb_tree_node_structure* get_maximum();
    const _Rb_tree_node_structure* get_maximum() const;
    bool is_left_node() const;
    bool is_right_node() const;

    _Rb_tree_node_structure* increment();
    const _Rb_tree_node_structure* increment() const;
    _Rb_tree_node_structure* decrement();
    const _Rb_tree_node_structure* decrement() const;

    void insert_left(_Rb_tree_node_structure* node);
    void insert_right(_Rb_tree_node_structure* node);

    void delete_node();

    virtual void* get_value_ptr();
    virtual const void* get_value_ptr() const;

    static void debug(const _Rb_tree_node_structure* root, const std::string file_name = "test.dot");
    static void check_rb_tree_rule(const _Rb_tree_node_structure* root);
};

template<typename Val>
class _Rb_tree_node : public _Rb_tree_node_structure
{
public:
    Val _value;

    _Rb_tree_node() : _Rb_tree_node_structure(), _value() {}
    _Rb_tree_node(const Val& value) 
        : _Rb_tree_node_structure(), _value(value) {}

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

template<typename Val, typename Compare = std::less<Val>, typename Alloc = std::allocator<Val> >
class _Rb_tree
{
public:
    typedef _Rb_tree_node<Val> node_type;
    typedef _Rb_tree_node<Val>* node_ptr;
    typedef alloc_traits<Alloc> allocator;
    typedef std::size_t size_type;

    Alloc _alloc;
    Compare _comp;
    node_ptr _head;
    size_type _node_count;

private:
    typename Alloc::template rebind<node_type>::other::size_type
    _alloc_max_size() const
    {
        return allocator::template max_size<node_type>(_alloc);
    }

    template <typename Pointer>
    void _destroy(Pointer p) const
    {
        allocator::destroy(_alloc, p);
    }

    template<typename Size>
    node_ptr _allocate(Size n) const
    {
        return allocator::template allocate<node_ptr, Size>(_alloc, n);
    }

    template <typename Pointer, typename V>
    void _construct(Pointer p, const V& value) const
    {
        allocator::construct(_alloc, p, value);
    }

    template <typename Pointer, typename Size>
    void _deallocate(Pointer p, Size n) const
    {
        allocator::deallocate(_alloc, p, n);
    }

    template <typename Pointer>
    void _destroy_and_deallocate(Pointer p) const
    {
        _destroy(p);
        _deallocate(p, 1);
    }

    void _node_destroy_and_deallocate(node_ptr node)
    {
        if (node == NULL)
            return ;
        if (node->_left)
            _node_destroy_and_deallocate(static_cast<node_ptr>(node->_left));
        if (node->_right)
            _node_destroy_and_deallocate(static_cast<node_ptr>(node->_right));
        _destroy_and_deallocate(node);
    }

    void _all_destroy_and_deallocate()
    {
        _node_destroy_and_deallocate(_head);
    }

    template<typename T>
    node_ptr _init_node(const T& value) const
    {
        node_ptr node;
        node = _allocate(1);
        try
        {
            _construct(node, value);
        }
        catch(const std::exception& e)
        {
            _deallocate(node, 1);
            throw;
        }
        return node;
    }

    // node_ptr _init_node(const node_ptr p) const
    // {
    //     node_ptr node;
    //     node = _allocate(1);
    //     try
    //     {
    //         _construct(node, *p);
    //     }
    //     catch(const std::exception& e)
    //     {
    //         _deallocate(node, 1);
    //         throw;
    //     }
    //     return node;
    // }

    void _copy_loop(const node_ptr head, node_ptr dest_head)
    {
        if (head == NULL)
            return ;
        // if (head->_left)
        //     _copy_loop(static_cast<const node_ptr>(head->_left), &static_cast<node_ptr*>((*dest_head)->_left));
        // if (head->_right)
        //     _copy_loop(static_cast<const node_ptr>(head->_right), &static_cast<node_ptr*>((*dest_head)->_right));
        if (head->_left)
        {
            dest_head->_left = _init_node(*static_cast<Val*>(head->_left->get_value_ptr()));
            dest_head->_left->_color = head->_left->_color;
            dest_head->_left->_parent = dest_head;
            _copy_loop(static_cast<const node_ptr>(head->_left), static_cast<node_ptr>(dest_head->_left));
        }
        if (head->_right)
        {
            dest_head->_right = _init_node(*static_cast<Val*>(head->_right->get_value_ptr()));
            dest_head->_right->_color = head->_right->_color;
            dest_head->_right->_parent = dest_head;
            _copy_loop(static_cast<const node_ptr>(head->_right), static_cast<node_ptr>(dest_head->_right));
        }
    }

    void _copy(const node_ptr head, node_ptr* dest_head)
    {
        if (head == NULL)
        {
            *dest_head = NULL;
            return ;
        }
        *dest_head = _init_node(head->_value);
        (*dest_head)->_color = head->_color;
        try
        {
            _copy_loop(head, *dest_head);
        }
        catch(const std::exception& e)
        {
            _node_destroy_and_deallocate((*dest_head));
            *dest_head = NULL;
            throw;
        }
    }

    bool _insert_node(node_ptr add_node)
    {
        if (_head == NULL)
        {
            _head = add_node;
            _head->_color = _Rb_tree_node_structure::_BLACK;
            return true;
        }
        node_ptr node = _head;
        while (true)
        {
            if (compare_value(node->_value, add_node->_value))
            {
                if (node->_right == NULL)
                {
                    node->insert_right(add_node);
                    _head = static_cast<node_ptr>(_head->get_root());
                    return true;
                }
                node = static_cast<node_ptr>(node->_right);
            }
            else if (compare_value(add_node->_value, node->_value))
            {
                if (node->_left == NULL)
                {
                    node->insert_left(add_node);
                    _head = static_cast<node_ptr>(_head->get_root());
                    return true;
                }
                node = static_cast<node_ptr>(node->_left);
            }
            else
            {
                node->_value = add_node->_value;
                _destroy_and_deallocate(add_node);
                return false;
            }
        }
    }

    node_ptr _search_node(const Val& value)
    {
        if (_head == NULL)
            return NULL;
        node_ptr node = _head;
        while (true)
        {
            if (compare_value(node->_value, value))
            {
                if (node->_right == NULL)
                    return NULL;
                node = static_cast<node_ptr>(node->_right);
            }
            else if (compare_value(value, node->_value))
            {
                if (node->_left == NULL)
                    return NULL;
                node = static_cast<node_ptr>(node->_left);
            }
            else
                return node;
        }
    }

public:
    _Rb_tree(): _alloc(), _comp(), _head(NULL), _node_count(0) {}

    explicit _Rb_tree(const Alloc& alloc)
        : _alloc(alloc), _comp(), _head(NULL), _node_count(0) {}

    _Rb_tree(const _Rb_tree& other)
        : _alloc(other._alloc), _comp(), _head(NULL), _node_count(other._node_count)
    {
        _copy(other._head, &_head);
    }

    ~_Rb_tree()
    {
        _all_destroy_and_deallocate();
    }

    size_type size() const
    {
        return _node_count;
    }

    bool compare_value(const Val& lhs, const Val& rhs) const
    {
        return _comp(lhs, rhs);
    }

    template<typename T>
    void insert_node(const T& value)
    {
        node_ptr node = _init_node(value);
        if (_insert_node(node))
            _node_count += 1;
    }

    // void insert_node(const node_ptr p)
    // {
    //     node_ptr node = _init_node(p);
    //     _insert_node(node);
    // }

    template<typename T>
    bool delete_node(const T& value)
    {
        node_ptr node = _search_node(value);
        if (node == NULL)
            return false;
        node->delete_node();
        _node_count -= 1;
        if (_node_count == 0)
            _head = NULL;
        else if (node == _head)
        {
            if (_head->_left)
                _head = static_cast<node_ptr>(_head->_left->get_root());
            else if (_head->_right)
                _head = static_cast<node_ptr>(_head->_right->get_root());
            else if (_head->_parent)
                _head = static_cast<node_ptr>(_head->_parent->get_root());
            else
                throw std::runtime_error("_head is isolated.");
        }
        else
            _head = static_cast<node_ptr>(_head->get_root());
        _destroy_and_deallocate(node);
        return true;
    }

    node_ptr get_min_node()
    {
        return const_cast<node_ptr>(static_cast<const _Rb_tree*>(this)->get_min_node());
    }

    const node_ptr get_min_node() const
    {
        if (_head == NULL)
            return NULL;
        return static_cast<const node_ptr>(_head->get_minimum());
    }

    node_ptr get_max_node()
    {
        return const_cast<node_ptr>(static_cast<const _Rb_tree*>(this)->get_max_node());
    }

    const node_ptr get_max_node() const
    {
        if (_head == NULL)
            return NULL;
        return static_cast<const node_ptr>(_head->get_maximum());
    }

    void check_rb_tree_rule() const
    {
        if (_head == NULL)
            return ;
        _Rb_tree_node_structure::check_rb_tree_rule(_head);
        const _Rb_tree_node_structure* node = _head->get_minimum();
        const Val* value = static_cast<const Val*>(node->get_value_ptr());
        node = node->increment();
        while (node)
        {
            if (!compare_value(*value, *static_cast<const Val*>(node->get_value_ptr())))
                throw std::runtime_error("Root must be black.");
            value = static_cast<const Val*>(node->get_value_ptr());
            node = node->increment();
        }
    }
};


template<typename Val, typename Compare, typename Alloc>
bool operator==(const _Rb_tree<Val, Compare, Alloc>& lhs,
                const _Rb_tree<Val, Compare, Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    const _Rb_tree_node_structure* lhs_node = lhs.get_min_node();
    const _Rb_tree_node_structure* rhs_node = rhs.get_min_node();
    while (lhs_node && rhs_node)
    {
        if (*static_cast<const Val*>(lhs_node->get_value_ptr()) != *static_cast<const Val*>(rhs_node->get_value_ptr()))
            return false;
        lhs_node = lhs_node->increment();
        rhs_node = rhs_node->increment();
    }
    return lhs_node == NULL && rhs_node == NULL;
}

template<typename Val, typename Compare, typename Alloc>
bool operator!=(const _Rb_tree<Val, Compare, Alloc>& lhs,
                const _Rb_tree<Val, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

} // namespace ft

#endif
