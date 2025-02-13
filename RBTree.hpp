#include "RBTree.h"

namespace my {
    template <typename T>
    rbtree<T>::rbtree() noexcept {

    }

    rbtree<T>::rbtree(const std::initializer_list<T> list) noexcept {
        for (const auto& e : list) 
            insert(e);
    }


    template <typename T>
    rbtree<T>::~rbtree() noexcept {
        drop(true);
    }

    template <typename T>
    inline void rbtree<T>::drop(const bool destructing) noexcept {
        const auto recv = [&](pointer ptr) {
            if (ptr->left)
                recv(ptr->left);
            if (ptr->right)
                recv(ptr->right);

            delete ptr;
        };

        recv(m_root);
        m_root = nullptr;
    }

    template <typename T>
    void rbtree<T>::left_rotate(node* ptr) noexcept {

    }

    template <typename T>
    void rbtree<T>::right_rotate(node* ptr) noexcept {

    }

    template <typename T>
    void rbtree<T>::fixup(node* parent) noexcept {
        node* grandparent = parent->parent;
        node* uncle = (grandparent) ? ((grandparent->left == parent) ? grandparent->right : grandparent->left) : nullptr;

        // Case 0: Uncle and Parent are red, recolour to black and grandparent to red.
        if (uncle && uncle->colour == colour::red) {
            parent->colour = colour::black;
            uncle->colour = colour::black;
            grandparent->color = color::red;

            fixup(grandparent)
        }
    }

    template <typename T>
    rbtree<T>::const_reference rbtree<T>::insert(value_type value) noexcept {
        if (!m_root) {
            m_root = new node_type{ .value = std::move(value), .colour = colour::black };
        }
        else {
            auto* current = m_root;

            while (current && current->value != value) {
                if (value < current->value) {
                    if (!current->left) {
                        current->left = new node_type{ .value = std::move(value) };
                        current->left->parent = current;
                        break;
                    }
                    else {
                        current = current->left;
                    }
                }
                else {
                    if (!current->right) {
                        current->right = new node_type{ .value = value };
                        current->right->parent = current;
                        break;
                    }
                    else {
                        current = current->right;
                    }
                }
            }

            fixup(current);
        }
    }

    template <typename T>
    rbtree<T>::const_pointer rbtree<T>::search(const value_type& value) const noexcept {
        // DFS 
        const auto recv = [&](const_pointer ptr) -> const_pointer {
            if (ptr->value == value) {
                return ptr;
            }
            else { 
                if (ptr->left)
                    return recv(ptr->left);
                if (ptr->right)
                    return recv(ptr->right);
            }

            return nullptr;
        };


        return recv(m_root);
    }

    template <typename T>
    void rbtree<T>::erase() noexcept {

    }
} // namespace my
