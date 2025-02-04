#ifndef MY_RED_BLACK_TREE_H
#define MY_RED_BLACK_TREE_H

#include <iostream>
#include <algorithm>
#include <functional>

namespace sdx {
    template <typename T>
    class rbtree {
    private:
        struct node {
            value_type value;
            enum colour {
                red,
                black
            } colour;
            node* left;
            node* right;
        };

    private:
        using value_type = T;
        using size_type = std::size_t;
        using referece = value_type&;
        using const_reference = const value_type&;
        using node_type = node;
        using pointer = node_type*;

    private:
        node* m_root;

    private:
        rbtree() noexcept;
        rbtree(const std::initializer_list<T> list) noexcept;
        // TODO: cpy, mv ctors
        ~rbtree() noexcept;

    private:
        inline void drop(const bool destructing = false) noexcept;

    public:
        // TODO: rvalue ref ver
        // TODO: ret iter
        const_reference insert(value_type value) noexcept;
        reference search(const value_type& value) noexcept;
        void erase() noexcept;
    };
} // namespace my

#ifndef MY_RED_BLACK_TREE_IMPL
#define MY_RED_BLACK_TREE_IMPL
#include "RBTree.hpp"
#endif // MY_RED_BLACK_TREE_IMPL

#endif // MY_RED_BLACK_TREE_H
