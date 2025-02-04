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
        auto recv = [&](node_type* ptr) {
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
    rbtree<T>::const_reference rbtree<T>::insert(value_type value) noexcept {
        if (!m_root) {
            m_root = new node_type{ .val = std::move(value) };
        }
        else {
            auto* current = m_root;

            while (current && current->value != value) {
                
            }
        }
    }

    template <typename T>
    rbtree<T>::reference rbtree<T>::search(const value_type& value) noexcept {

    }

    template <typename T>
    void rbtree<T>::erase() noexcept {

    }
} // namespace my
