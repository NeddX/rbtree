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
            enum colour : std::uint8_t {
                red,
                black
            } colour = colour::red;
            node* left = nullptr;
            node* right = nullptr;
        };

    private:
        using value_type = T;
        using size_type = std::size_t;
        using referece = value_type&;
        using const_reference = const value_type&;
        using node_type = node;
        using pointer = node_type*;
        using const_pointer = const node_type*;

    private:
        node* m_root;

    private:
        rbtree() noexcept;
        rbtree(const std::initializer_list<T> list) noexcept;
        // TODO: cpy, mv ctors
        ~rbtree() noexcept;

    private:
        inline void drop(const bool destructing = false) noexcept;

    private:
        void left_rotate(node* ptr) noexcept;
        void right_rotate(node* ptr) noexcept;

    public:
        // TODO: rvalue ref ver
        // TODO: ret iter
        const_reference insert(value_type value) noexcept;
        const_pointer search(const value_type& value) const noexcept;
        void erase() noexcept;
    };
} // namespace my

#ifndef MY_RED_BLACK_TREE_IMPL
#define MY_RED_BLACK_TREE_IMPL
#include "RBTree.hpp"
#endif // MY_RED_BLACK_TREE_IMPL

#endif // MY_RED_BLACK_TREE_H
