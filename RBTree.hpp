#include "RBTree.h"

namespace my {
    template <typename T>
    rbtree<T>::rbtree() noexcept {

    }

    template <typename T>
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
    void rbtree<T>::left_rotate(pointer node) noexcept {
        pointer parent = node->parent;

        if (parent) {
            if (parent->right == node) {
                parent->right = node->right;
            }
            else {
                parent->left = node->right;
            }

            pointer np_left = node->right->left;
            node->right->left = node;
            node->right = np_left;
        }
        else {
            root = node->right;
            pointer root_left = root->left;
            root->left = node;
            node->right = root_left;
        }
    }

    template <typename T>
    void rbtree<T>::right_rotate(pointer node) noexcept {
        parent parent = node->parent;

        if (parent) {
            if (parent->right == node) {
                parent->right = node->left;
            }
            else {
                parent->left = node->left;
            }

            pointer np_right = node->left->right;
            node->left->right = node;
            node->left = np_right;
        }
        else {
            root = node->left;
            pointer root_right = root->right;
            root->right = node;
            node->left = root_right;
        }

    }

    template <typename T>
    void rbtree<T>::fixup(pointer node) noexcept {
        pointer parent = node->parent;
        pointer grandparent = (parent) ? parent->parent : nullptr;
        pointer uncle = (grandparent) ? ((grandparent->left == parent) ? grandparent->right : grandparent->left) : nullptr;

        // Case 0: Node is root, recolour to black.
        if (node == m_root) {
            node->colour = colour::black;
        }
        // Case 1: Uncle and Parent are red, recolour to black and grandparent to red.
        else if (uncle && uncle->colour == colour::red && parent->colour == colour::red) {
            parent->colour = colour::black;
            uncle->colour = colour::black;
            grandparent->color = color::red;

            fixup(grandparent);
        }
        // Case 2: Uncle is black or null, rotation is needed.
        else if (!uncle || uncle->colour == colour::black) {
            // Case 2.1: Left-Left, N is left child of P and P is left child of G -> right_rotate(G)
            if (parent->left == node && grandparent->left == parent) {
                right_rotate(grandparent);
            }
            // Case 2.2: Right-Right, N is right child of P and P is right child of G -> left_rotate(G)
            else if (parent->right == node && grandparent->right == parent) {
                left_rotate(grandparent);
            }
            // Case 2.3: Left-Right, N is right child of P, but P is left child of G -> left_rotate(P), right_rotate(G)
            else if (parent->right == node && grandparent->left == parent) {
                left_rotate(parent);
                right_rotate(grandparent);
            }
            // Case 2.4: Right-Left, N is left child of P, but P is right child of G -> right_rotate(P), left_rotate(G)
            else if (parent->left == node && grandparent->right == parent) {
                right_rotate(parent);
                left_rotate(grandparent);
            }
        }
    }

    template <typename T>
    rbtree<T>::const_reference rbtree<T>::insert(value_type value) noexcept {
        if (!m_root) {
            m_root = new node_type{ .value = std::move(value), .colour = colour::black };
        }
        else {
            pointer current = m_root;
            pointer new_node = nullptr;

            while (current && current->value != value) {
                if (value < current->value) {
                    if (!current->left) {
                        current->left = new node_type{ .value = std::move(value) };
                        current->left->parent = current;
                        new_node = current->left;
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
                        new_node = current->right;
                        break;
                    }
                    else {
                        current = current->right;
                    }
                }
            }

            fixup(new_node);
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
