/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:51 by mmosca            #+#    #+#             */
/*   Updated: 2022/07/09 19:12:00 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_AVL_HPP
#define FT_CONTAINERS_AVL_HPP

#include <memory>
#include <algorithm>
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

	template<typename U, typename V>
	class AvlNode {
	public:
		/**
		 * Member types
		 */
		typedef ft::pair<U, V> value_type;

		/**
		 * Member objects
		 */
		value_type value;
		AvlNode *parent;
		AvlNode *left;
		AvlNode *right;

		/**
		 * Constructor initialized value with value.
		 * @param value value to initialized
		 */
		AvlNode(const value_type &value) : _height(1), value(value), left(nullptr), right(nullptr) {}

		/**
		 * Returns the max value in the tree.
		 * @return the max value in the tree
		 */
		ft::AvlNode<U, V> *getMax() {
			return right ? right->getMax() : this;
		}

		/**
		 * Returns the min value in the tree.
		 * @return the min value in the tree
		 */
		ft::AvlNode<U, V> *getMin() {
			return left ? left->getMin() : this;
		}

		/**
		 * Allows you to update the height of the tree.
		 */
		void updateHeight() {
			_height = 1 + std::max(left ? left->height() : 0, right ? right->height() : 0);
		}

		/**
		 * Returns the height of the tree.
		 * @return the height of the tree
		 */
		unsigned int height() const {
			return _height;
		}

		/**
		 * Allows to know if the tree is balanced.
		 * @return the result of the subtraction of the left and right height
		 */
		long balance() const {
			return (left ? left->_height : 0) - (right ? right->_height : 0);
		}

	private:
		/**
		 * Member objects
		 */
		unsigned int _height;
	};

	template<typename U, typename V, class Node = AvlNode<U, V>, class Allocator = std::allocator<Node> >
	class avl_tree {
	public:
		/**
		 * Member types
		 */
		typedef ft::pair<U, V> value_type;
		typedef Node node_type;
		typedef Node* node_pointer;
		typedef Allocator node_allocator;
		typedef ft::avl_iterator<Node> iterator;
		typedef ft::avl_iterator<Node> const_iterator;
		typedef typename node_allocator::size_type size_type;

		/**
		 * Member objects
		 */
		node_pointer _root;
		node_allocator _alloc;
		size_t _size;

		/**
		 * Constructor with allocator in parameter.
		 * @param node_alloc allocator to set
		 */
		avl_tree(const node_allocator &node_alloc = node_allocator()) : _root(nullptr), _alloc(node_alloc), _size(0) {}

		/**
		 * Destructor.
		 */
		~avl_tree() {
			clear_tree();
		}

		void clear_tree() {
			clear_tree(_root);
			_size = 0;
			_root = nullptr;
		}

		void insert(value_type value) {
			_root = insert(value, _root);
			reset_parents();
		}

		void remove(value_type value) {
			_root = remove(value, _root);
			reset_parents();
		}

		bool isEmpty() const {
			return _root == nullptr;
		}

		size_type getSize() const {
			return _size;
		}

		size_type getMaxSize() const {
			return _alloc.max_size();
		}

		node_pointer find(value_type value) const {
			return find(value, _root);
		}

		node_pointer getRoot() const {
			return _root;
		}

		iterator begin() {
			return _root ? iterator(_root->getMin(), _root->getMin(), _root->getMax()) : iterator();
		}

		const_iterator begin() const {
			return _root ? const_iterator(_root->getMin(), _root->getMin(), _root->getMax()) : const_iterator();
		}

		iterator end() {
			return _root ? iterator(nullptr, _root->getMin(), _root->getMax()) : iterator();
		}

		const_iterator end() const {
			return _root ? const_iterator(nullptr, _root->getMin(), _root->getMax()) : const_iterator();
		}

		void swap(ft::avl_tree<U, V, Node, Allocator> &t) {
			node_type *tmpRoot = _root;
			node_type *tmpAllocator = _alloc;
			node_type *tmpSize = _size;

			_root = t._root;
			_alloc = t._alloc;
			_size = t._size;

			t._root = tmpRoot;
			t._alloc = tmpAllocator;
			t._size = tmpSize;
		}

	private:
		node_pointer find(value_type value, node_pointer node) const {
			if (node == nullptr) {
				return nullptr;
			} else if (node->value.first == value.first) {
				return node;
			} else {
				return find(value, (node->value.first < value.first) ? node->right : node->left);
			}
		}

		node_pointer insert(value_type value, node_pointer node) {
			if (node == nullptr) {
				node_pointer newNode = _alloc.allocate(1);
				_alloc.construct(newNode, node_type(value));
				_size++;
				return newNode;
			}
			if (node->value.first == value.first) {
				return node;
			}
			(node->value.first < value.first) ? node->right = insert(value, node->right) : node->left = insert(value, node->left);
			node->updateHeight();
			return applyRotation(node);
		}

		node_pointer applyRotation(node_pointer node) {
			long balance = node->balance();

			if (balance < -1) {
				if (node->right && node->right->balance() > 0) {
					node->right = rightRotation(node->right);
				}
				return leftRotation(node);
			} else if (balance > 1) {
				if (node->left && node->left->balance() < 0) {
					node->left = leftRotation(node->left);
				}
				return rightRotation(node);
			} else {
				return node;
			}
		}

		node_pointer leftRotation(node_pointer node) {
			node_pointer right = node->right;
			node_pointer center = right->left;

			right->left = node;
			node->right = center;
			node->updateHeight();
			right->updateHeight();
			return right;
		}

		node_pointer rightRotation(node_pointer node) {
			node_pointer left = node->left;
			node_pointer center = left->right;

			left->right = node;
			node->left = center;
			node->updateHeight();
			left->updateHeight();
			return left;
		}

		node_pointer remove(value_type value, node_pointer node) {
			if (node == nullptr) {
				return nullptr;
			}
			if (node->value.first == value.first) {
				node_pointer tmp;

				if (node->left != nullptr && node->right != nullptr) {
					node->value = node->left->getMax()->value;
					node->left = remove(node->value, node->left);
				} else {
					tmp = (node->left == nullptr) ? node->right : node->left;
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					_size--;
					return tmp;
				}
			} else {
				(node->value.first < value.first) ? node->right = remove(value, node->right) : node->left = remove(value, node->left);
			}
			node->updateHeight();
			return applyRotation(node);
		}

		void reset_parents() {
			if (!_root) {
				return;
			}
			_root->parent = nullptr;
			reset_parents(_root);
		}

		void reset_parents(node_pointer node) {
			if (node == nullptr) {
				return;
			}
			if (node->left) {
				node->left->parent = node;
			}
			if (node->right) {
				node->right->parent = node;
			}
			reset_parents(node->left);
			reset_parents(node->right);
		}

		void clear_tree(node_pointer node) {
			if (node == nullptr) {
				return;
			}
			clear_tree(node->left);
			clear_tree(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
	};

}

#endif //FT_CONTAINERS_AVL_HPP
