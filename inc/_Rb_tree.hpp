#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <string>
#include <fstream>

#include "alloc_traits.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

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

    static void _debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs, const _Rb_tree_node_structure* prohibited_node);
    static void _check_rb_tree_rule_node(const _Rb_tree_node_structure* node, int black_node_num, const _Rb_tree_node_structure* prohibited_node = NULL);

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

    static void debug(const _Rb_tree_node_structure* root, const std::string file_name = "test.dot", const _Rb_tree_node_structure* prohibited_node = NULL);
    static void check_rb_tree_rule(const _Rb_tree_node_structure* root, const _Rb_tree_node_structure* prohibited_node = NULL);
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

    static void debug_node(const _Rb_tree_node_structure* node, int& node_num, std::ofstream& ofs, const _Rb_tree_node_structure* prohibited_node)
    {
        int my_num = node_num;
        if (node == prohibited_node)
            return ;
        if (node->_color == _Rb_tree_node_structure::_RED)
            ofs << "    " << my_num << " [\n        label = \"" << *static_cast<const Val*>(node->get_value_ptr()) << "\",\n        color = \"#ff0000\"\n    ];" << std::endl;
        else
            ofs << "    " << my_num << " [\n        label = \"" << *static_cast<const Val*>(node->get_value_ptr()) << "\",\n        color = \"#000000\"\n    ];" << std::endl;
        if (node->_left || node->_left != prohibited_node)
        {
            node_num += 1;
            ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
            debug_node(node->_left, node_num, ofs, prohibited_node);
        }
        else
            ofs << "    left" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> left" << my_num << ";" << std::endl;
        if (node->_right || node->_left != prohibited_node)
        {
            node_num += 1;
            ofs << "    " << my_num << " -> " << node_num << ";" <<std::endl;
            debug_node(node->_right, node_num, ofs, prohibited_node);
        }
        else
            ofs << "    right" << my_num << " [\n        label = \"NULL\",\n        color = \"#ffffff\"\n    ];\n"  <<"    " << my_num << " -> right" << my_num << ";" << std::endl;
    }

    static void debug(const _Rb_tree_node* head, const std::string file_name = "test.dot", const _Rb_tree_node_structure* prohibited_node = NULL)
    {
        std::ofstream ofs(file_name.c_str());
        if (!ofs)
            return ;
        ofs << "digraph test {" << std::endl;
        int node_num = 0;
        debug_node(head, node_num, ofs, prohibited_node);
        ofs << "}" << std::endl;
        ofs.close();
    }
};


template<typename Val>
class _Rb_tree_iterator
{
public:
    typedef Val value_type;
    typedef Val& reference;
    typedef Val* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

private:
    typedef _Rb_tree_iterator<Val> _Self;
    typedef _Rb_tree_node_structure* _Base_ptr;
    typedef _Rb_tree_node<Val>* _Link_type;


public:
    _Base_ptr _node;

    _Rb_tree_iterator() : _node(NULL) {}
    explicit _Rb_tree_iterator(_Base_ptr node) : _node(node) {}

    reference operator*() const
    {
        return *static_cast<pointer>(static_cast<_Link_type>(_node)->get_value_ptr());
    }

    pointer operator->() const
    {
        return static_cast<pointer>(static_cast<_Link_type>(_node)->get_value_ptr());
    }

    _Self& operator++()
    {
        _node = _node->increment();
        return *this;
    }

    _Self operator++(int)
    {
        _Self temp = *this;
        _node = _node->increment();
        return temp;
    }

    _Self& operator--()
    {
        _node = _node->decrement();
        return *this;
    }

    _Self operator--(int)
    {
        _Self temp = *this;
        _node = _node->decrement();
        return temp;
    }

    bool operator==(const _Self& other) const
    {
        return _node == other._node;
    }

    bool operator!=(const _Self& other) const
    {
        return !(*this == other);
    }
};


template<typename Val>
class _Rb_tree_const_iterator
{
public:
    typedef Val value_type;
    typedef const Val& reference;
    typedef const Val* pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

private:
    typedef _Rb_tree_iterator<Val> iterator;

    typedef _Rb_tree_const_iterator<Val> _Self;
    typedef const _Rb_tree_node_structure* _Base_ptr;
    typedef const _Rb_tree_node<Val>* _Link_type;

public:
    _Base_ptr _node;

    _Rb_tree_const_iterator() : _node(NULL) {}
    explicit _Rb_tree_const_iterator(_Base_ptr node) : _node(node) {}
    _Rb_tree_const_iterator(const iterator& it) : _node(it._node) {}

    reference operator*() const
    {
        return *static_cast<pointer>(static_cast<_Link_type>(_node)->get_value_ptr());
    }

    pointer operator->() const
    {
        return static_cast<pointer>(static_cast<_Link_type>(_node)->get_value_ptr());
    }

    _Self& operator++()
    {
        _node = _node->increment();
        return *this;
    }

    _Self operator++(int)
    {
        _Self temp = *this;
        _node = _node->increment();
        return temp;
    }

    _Self& operator--()
    {
        _node = _node->decrement();
        return *this;
    }

    _Self operator--(int)
    {
        _Self temp = *this;
        _node = _node->decrement();
        return temp;
    }

    bool operator==(const _Self& other) const
    {
        return _node == other._node;
    }

    bool operator!=(const _Self& other) const
    {
        return !(*this == other);
    }
};

template<typename T>
bool operator==(const _Rb_tree_iterator<T>& lhs,
                const _Rb_tree_const_iterator<T>& rhs)
{
    return lhs._node == rhs._node;
}

template<typename T>
bool operator!=(const _Rb_tree_iterator<T>& lhs,
                const _Rb_tree_const_iterator<T>& rhs)
{
    return !(lhs == rhs);
}


class _ValueCopy
{
public:
    template<typename T>
    void operator()(T& dest, T& src)
    {
        dest = src;
    }
};


template<typename Val, typename Compare = std::less<Val>, typename Alloc = std::allocator<Val>, typename ValueCopy = _ValueCopy >
class _Rb_tree
{
public:
    typedef _Rb_tree_iterator<Val> iterator;
    typedef _Rb_tree_const_iterator<Val> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef Val value_type;
    typedef Val* value_type_ptr;
    typedef _Rb_tree_node<Val> node_value_type;
    typedef _Rb_tree_node<Val>* node_value_ptr;
    typedef const _Rb_tree_node<Val>* node_value_const_ptr;
    typedef _Rb_tree_node_structure node_type;
    typedef _Rb_tree_node_structure* node_ptr;
    typedef const _Rb_tree_node_structure* node_const_ptr;
    typedef alloc_traits<Alloc> allocator;
    typedef std::size_t size_type;

    Alloc _alloc;
    Compare _comp;
    node_ptr _head;
    node_ptr _begin;
    node_ptr _end;
    size_type _node_count;

private:
    void _end_remove()
    {
        if (_end->_parent)
            _end->_parent->_right = NULL;
        else
        {
            _head = NULL;
            _begin = NULL;
        }
    }

    void _end_put()
    {
        if (_end->_parent)
            _end->_parent->_right = _end;
        else
        {
            _head = _end;
            _begin = _end;
        }
    }

    typename Alloc::template rebind<node_value_type>::other::size_type
    _alloc_max_size() const
    {
        return allocator::template max_size<node_value_type>(_alloc);
    }

    template <typename Pointer>
    void _destroy(Pointer p) const
    {
        allocator::destroy(_alloc, p);
    }

    template<typename Size>
    node_ptr _allocate(Size n) const
    {
        return allocator::template allocate<node_value_ptr, Size>(_alloc, n);
    }

    void _construct(node_ptr p, const Val& value) const
    {
        allocator::construct(_alloc, static_cast<node_value_ptr>(p), value);
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
            _node_destroy_and_deallocate(node->_left);
        if (node->_right)
            _node_destroy_and_deallocate(node->_right);
        _destroy_and_deallocate(node);
    }

    void _all_destroy_and_deallocate()
    {
        _end_remove();
        _node_destroy_and_deallocate(_head);
        if (_end != NULL)
            _destroy_and_deallocate(_end);
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

    void _init_end_and_begin()
    {
        try
        {
            _end = _init_node(Val());
        }
        catch(const std::exception& e)
        {
            _node_destroy_and_deallocate(_head);
            _head = NULL;
            throw;
        }
        _end->_left = NULL;
        _end->_right = NULL;
        if (_head == NULL)
        {
            _end->_parent = NULL;
            _begin = NULL;
        }
        else
        {
            _end->_parent = _head->get_maximum();
            _begin = _head->get_minimum();
        }
        _end_put();
    }

    void _copy_loop(node_const_ptr head, node_ptr dest_head, node_const_ptr prohibited_node)
    {
        if (head == NULL)
            return ;
        if (head->_left && head->_left != prohibited_node)
        {
            dest_head->_left = _init_node(*static_cast<const Val*>(head->_left->get_value_ptr()));
            dest_head->_left->_color = head->_left->_color;
            dest_head->_left->_parent = dest_head;
            _copy_loop(head->_left, dest_head->_left, prohibited_node);
        }
        if (head->_right && head->_right != prohibited_node)
        {
            dest_head->_right = _init_node(*static_cast<const Val*>(head->_right->get_value_ptr()));
            dest_head->_right->_color = head->_right->_color;
            dest_head->_right->_parent = dest_head;
            _copy_loop(head->_right, dest_head->_right, prohibited_node);
        }
    }

    void _copy(node_const_ptr head, node_ptr* dest_head, node_const_ptr prohibited_node)
    {
        if (head == NULL || head == prohibited_node)
        {
            *dest_head = NULL;
            return ;
        }
        const Val* value = static_cast<const Val*>(head->get_value_ptr());
        *dest_head = _init_node(*value);
        (*dest_head)->_color = head->_color;
        try
        {
            _copy_loop(head, *dest_head, prohibited_node);
        }
        catch(const std::exception& e)
        {
            _node_destroy_and_deallocate((*dest_head));
            *dest_head = NULL;
            throw;
        }
    }

    template<class It>
    void _copy(It start, It last)
    {
        for (; start != last; ++start)
        {
            insert_node(*start);
        }
    }

    void _insert_to_empty_tree(node_ptr add_node)
    {
        _head = add_node;
        _head->_color = node_type::_BLACK;
        _end->_parent = _head;
        _begin = _head;
        _node_count += 1;
    }

    node_ptr _insert_node(node_ptr add_node)
    {
        if (_head == NULL)
        {
            _insert_to_empty_tree(add_node);
            return _head;
        }
        node_ptr node = _head;
        Val* add_value = static_cast<Val*>(add_node->get_value_ptr());
        while (true)
        {
            Val* node_value = static_cast<Val*>(node->get_value_ptr());
            if (compare_value(*node_value, *add_value))
            {
                if (node->_right == NULL)
                {
                    node->insert_right(add_node);
                    _head = _head->get_root();
                    if (node == _end->_parent)
                        _end->_parent = add_node;
                    _node_count += 1;
                    return add_node;
                }
                node = node->_right;
            }
            else if (compare_value(*add_value, *node_value))
            {
                if (node->_left == NULL)
                {
                    node->insert_left(add_node);
                    _head = _head->get_root();
                    if (node == _begin)
                        _begin = add_node;
                    _node_count += 1;
                    return add_node;
                }
                node = node->_left;
            }
            else
            {
                _destroy_and_deallocate(add_node);
                return node;
            }
        }
    }

    node_ptr _insert_node(iterator hint, node_ptr add_node)
    {
        if (_head == NULL)
        {
            _insert_to_empty_tree(add_node);
            return _head;
        }
        node_ptr node = hint._node;
        if (node == _end)
            node = _head;
        Val* add_value = static_cast<Val*>(add_node->get_value_ptr());
        while (true)
        {
            Val* node_value = static_cast<Val*>(node->get_value_ptr());
            if (compare_value(*node_value, *add_value))
            {
                if (node->_right == NULL)
                {
                    node_ptr next_node = node->increment();
                    if (next_node == NULL
                            || compare_value(*add_value, *static_cast<Val*>(next_node->get_value_ptr())))
                    {
                        node->insert_right(add_node);
                        _head = _head->get_root();
                        if (node == _end->_parent)
                            _end->_parent = add_node;
                        _node_count += 1;
                        return add_node;
                    }
                    node = next_node;
                }
                else
                    node = node->_right;
            }
            else if (compare_value(*add_value, *node_value))
            {
                if (node->_left == NULL)
                {
                    node_ptr pred_node = node->decrement();
                    if (pred_node == NULL
                            || compare_value(*static_cast<Val*>(pred_node->get_value_ptr()), *add_value))
                    {
                        node->insert_left(add_node);
                        _head = _head->get_root();
                        if (node == _begin)
                            _begin = add_node;
                        _node_count += 1;
                        return add_node;
                    }
                    node = pred_node;
                }
                else
                    node = node->_left;
            }
            else
            {
                _destroy_and_deallocate(add_node);
                return node;
            }
        }
    }

    template <class Key, typename keyCompare>
    node_ptr _search_node(const Key& key, int mode = 0)
    {
        const keyCompare& comp = _comp.get_key_compare();
        if (_head == NULL)
            return NULL;
        node_ptr node = _head;
        while (true)
        {
            Val* node_value = static_cast<Val*>(node->get_value_ptr());
            if (comp(node_value->first, key))
            {
                if (node->_right == NULL)
                    return NULL;
                node = node->_right;
            }
            else if (comp(key, node_value->first))
            {
                if (node->_left == NULL)
                {
                    if (mode == 0)
                        return NULL;
                    else
                        return node;
                }
                node = node->_left;
            }
            else
            {
                if (mode != 2)
                    return node;
                else
                    return node->increment();
            }
        }
    }

    template <class Key, typename keyCompare>
    node_const_ptr _search_node(const Key& key, int mode = 0) const
    {
        const keyCompare& comp = _comp.get_key_compare();
        if (_head == NULL || _head == _end)
            return NULL;
        node_ptr node = _head;
        while (true)
        {
            Val* node_value = static_cast<Val*>(node->get_value_ptr());
            if (comp(node_value->first, key))
            {
                if (node->_right == NULL || node->_right == _end)
                    return NULL;
                node = node->_right;
            }
            else if (comp(key, node_value->first))
            {
                if (node->_left == NULL || node->_left == _end)
                {
                    if (mode == 0)
                        return NULL;
                    else
                        return node;
                }
                node = node->_left;
            }
            else
            {
                if (mode != 2)
                    return node;
                else
                    return node->increment();
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
            Val* node_value = static_cast<Val*>(node->get_value_ptr());
            if (compare_value(*node_value, value))
            {
                if (node->_right == NULL)
                    return NULL;
                node = node->_right;
            }
            else if (compare_value(value, *node_value))
            {
                if (node->_left == NULL)
                    return NULL;
                node = node->_left;
            }
            else
                return node;
        }
    }

    bool _delete_node(node_ptr node)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node == _begin)
            _begin = node->increment();
        if (node == _end->_parent)
            _end->_parent = node->decrement();
        node->delete_node();
        _node_count -= 1;
        if (_node_count == 0)
            _head = NULL;
        else if (node == _head)
        {
            if (_head->_left)
                _head = _head->_left->get_root();
            else if (_head->_right)
                _head = _head->_right->get_root();
            else if (_head->_parent)
                _head = _head->_parent->get_root();
        }
        else
            _head = _head->get_root();
        _destroy_and_deallocate(node);
        return true;
    }

public:
    _Rb_tree(): _alloc(), _comp(), _head(NULL), _begin(NULL), _end(NULL), _node_count(0)
    {
        _init_end_and_begin();
    }

    explicit _Rb_tree(const Alloc& alloc)
        : _alloc(alloc), _comp(), _head(NULL), _begin(NULL), _end(NULL), _node_count(0)
    {
        _init_end_and_begin();
    }

    explicit _Rb_tree(const Compare& comp, const Alloc& alloc = Alloc())
        : _alloc(alloc), _comp(comp), _head(NULL), _begin(NULL), _end(NULL), _node_count(0)
    {
        _init_end_and_begin();
    }

    template<class It>
    _Rb_tree(It start, It last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
        : _alloc(alloc), _comp(comp), _head(NULL), _begin(NULL), _end(NULL), _node_count(0)
    {
        _init_end_and_begin();
        _copy(start, last);
    }

    _Rb_tree(const _Rb_tree& other)
        : _alloc(other._alloc), _comp(other._comp), _head(NULL), _begin(NULL), _end(NULL), _node_count(other._node_count)
    {
        _copy(other._head, &_head, other._end);
        _init_end_and_begin();
    }

    _Rb_tree& operator=(const _Rb_tree& other)
    {
        if (this != &other)
        {
            node_ptr head_node = NULL;
            _copy(other._head, &head_node, other._end);
            _all_destroy_and_deallocate();
            _head = head_node;
            _init_end_and_begin();
        }
        return *this;
    }

    virtual ~_Rb_tree()
    {
        _all_destroy_and_deallocate();
    }

    size_type size() const
    {
        return _node_count;
    }

    bool empty() const
    {
        return _node_count == 0;
    }

    size_type max_size() const
    {
        return _alloc_max_size();
    }

    void clear()
    {
        _all_destroy_and_deallocate();
        _head = NULL;
        _node_count = 0;
        _init_end_and_begin();
    }

    bool compare_value(const Val& lhs, const Val& rhs) const
    {
        return _comp(lhs, rhs);
    }

    template<typename T>
    pair<iterator, bool> insert_node(const T& value)
    {
        node_ptr node = _init_node(value);
        _end_remove();
        size_type num = _node_count;
        node = _insert_node(node);
        _end_put();
        return pair<iterator, bool>(iterator(node), num != _node_count);
    }

    template<typename T>
    iterator insert_node(iterator hint, const T& value)
    {
        node_ptr node = _init_node(value);
        _end_remove();
        node = _insert_node(hint, node);
        _end_put();
        return iterator(node);
    }

    template< class It >
    void insert_iter(It start, It last)
    {
        for (; start != last; ++start)
            insert_node(*start);
    }

    template <class Key, class KeyCompare>
    bool delete_node(const Key& value)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(value);
        bool delete_or_not = _delete_node(node);
        _end_put();
        return delete_or_not;
    }

    bool delete_node(iterator pos)
    {
        _end_remove();
        bool delete_or_not = _delete_node(pos._node);
        _end_put();
        return delete_or_not;
    }

    void delete_node(iterator start, iterator last)
    {
        _end_remove();
        iterator dummy_last(NULL);
        while (true)
        {
            if ((start == last) || (start == dummy_last && iterator(_end) == last))
                break;
            _delete_node((start++)._node);
        }
        _end_put();
    }

    template <class Key, class V, class KeyCompare>
    V& search_node(const Key& key)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(key);
        _end_put();
        if (node == NULL)
            throw std::out_of_range("_Rb_tree::search_node");
        return static_cast<Val*>(node->get_value_ptr())->second;
    }

    template <class Key, class V, class KeyCompare>
    const V& search_node(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key);
        if (node == NULL)
            throw std::out_of_range("_Rb_tree::search_node");
        return static_cast<const Val*>(node->get_value_ptr())->second;
    }

    iterator search_node(const Val& value)
    {
        _end_remove();
        node_ptr node = _search_node(value);
        _end_put();
        if (node == NULL)
            throw std::out_of_range("_Rb_tree::search_node");
        return iterator(node);
    }

    template <class Key, class KeyCompare>
    iterator find(const Key& key)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(key);
        _end_put();
        if (node == NULL)
            return iterator(_end);
        return iterator(node);
    }

    template <class Key, class KeyCompare>
    const_iterator find(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key);
        if (node == NULL)
            return const_iterator(_end);
        return const_iterator(node);
    }

    template <class Key, class KeyCompare>
    pair<iterator, iterator> equal_range(const Key& key)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(key, 1);
        _end_put();
        if (node == NULL)
            return pair<iterator, iterator>(iterator(_end), iterator(_end));
        else if (_comp.get_key_compare()(key, iterator(node)->first))
            return pair<iterator, iterator>(iterator(node), iterator(node));
        else
            return pair<iterator, iterator>(iterator(node), iterator(node->increment()));
    }

    template <class Key, class KeyCompare>
    pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key, 1);
        if (node == NULL || node == _end)
            return pair<const_iterator, const_iterator>(const_iterator(_end), const_iterator(_end));
                else if (_comp.get_key_compare()(key, const_iterator(node)->first))
            return pair<const_iterator, const_iterator>(const_iterator(node), const_iterator(node));
        else
            return pair<const_iterator, const_iterator>(const_iterator(node), const_iterator(node->increment()));
    }

    template <class Key, class KeyCompare>
    iterator lower_bound(const Key& key)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(key, 1);
        _end_put();
        if (node == NULL)
            return iterator(_end);
        else
            return iterator(node);
    }

    template <class Key, class KeyCompare>
    const_iterator lower_bound(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key, 1);
        if (node == NULL || node == _end)
            return const_iterator(_end);
        else
            return const_iterator(node);
    }

    template <class Key, class KeyCompare>
    iterator upper_bound(const Key& key)
    {
        _end_remove();
        node_ptr node = _search_node<Key, KeyCompare>(key, 2);
        _end_put();
        if (node == NULL)
            return iterator(_end);
        else
            return iterator(node);
    }

    template <class Key, class KeyCompare>
    const_iterator upper_bound(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key, 2);
        if (node == NULL || node == _end)
            return const_iterator(_end);
        else
            return const_iterator(node);
    }

    template <class Key, class KeyCompare>
    size_type count(const Key& key) const
    {
        node_const_ptr node = _search_node<Key, KeyCompare>(key);
        return node != NULL;
    }

    void swap(_Rb_tree& other)
    {
        node_ptr temp = _head;
        _head = other._head;
        other._head = temp;

        temp = _end;
        _end = other._end;
        other._end = temp;

        temp = _begin;
        _begin = other._begin;
        other._begin = temp;

        size_type temp_size = _node_count;
        _node_count = other._node_count;
        other._node_count = temp_size;

        std::swap(_comp, other._comp);
        std::swap(_alloc, other._alloc);
    }

    node_value_ptr get_min_node()
    {
        return const_cast<node_value_ptr>(static_cast<const _Rb_tree*>(this)->get_min_node());
    }

    node_value_const_ptr get_min_node() const
    {
        if (_head == _end)
            return NULL;
        return static_cast<node_value_const_ptr>(_head->get_minimum());
    }

    node_value_ptr get_max_node()
    {
        return const_cast<node_value_ptr>(static_cast<const _Rb_tree*>(this)->get_max_node());
    }

    node_value_const_ptr get_max_node() const
    {
        if (_head == _end)
            return NULL;
        return static_cast<node_value_const_ptr>(_end->_parent);
    }

    void check_rb_tree_rule() const
    {
        if (_head == NULL || _head == _end)
            return ;
        node_type::check_rb_tree_rule(_head, _end);
        node_const_ptr node = _head->get_minimum();
        if (node != _begin)
            throw std::runtime_error("_begin is wrong.");
        const Val* value = static_cast<const Val*>(node->get_value_ptr());
        int num = 1;
        node = node->increment();
        while (node != _end)
        {
            if (!compare_value(*value, *static_cast<const Val*>(node->get_value_ptr())))
                throw std::runtime_error("Root must be black.");
            value = static_cast<const Val*>(node->get_value_ptr());
            node = node->increment();
            num += 1;
        }
        if (num != _node_count)
            throw std::runtime_error("node count is wrong.");
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
    while (lhs_node != lhs._end && rhs_node != lhs._end)
    {
        if (*static_cast<const Val*>(lhs_node->get_value_ptr()) != *static_cast<const Val*>(rhs_node->get_value_ptr()))
            return false;
        lhs_node = lhs_node->increment();
        rhs_node = rhs_node->increment();
    }
    return lhs_node == lhs._end && rhs_node == rhs._end;
}

template<typename Val, typename Compare, typename Alloc>
bool operator!=(const _Rb_tree<Val, Compare, Alloc>& lhs,
                const _Rb_tree<Val, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

} // namespace ft

#endif
