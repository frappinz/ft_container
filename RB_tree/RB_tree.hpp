#pragma once

#include <iostream>
#include <memory>
#include "tree_algorithm.hpp"
#include "../utils.hpp"
#include "tree_iterator.hpp"


namespace ft
{


	template <class _Tp, class Iterator, class Const, class _Compare, class _Allocator> class __tree;
	template <class _Tp> class tree_iterator;
	template <class _Tp> class const_tree_iterator;
	template <typename T> struct Node;
		
							/******************************** STRUTTURA NODI ********************************/
	
	template <class T>
	struct Node 
	{
		struct Node<T> *left, *right;
		struct Node<T> *parent;
		bool is_black;
		bool is_end;
		T pair;
		Node() : left(nullptr), right(nullptr), parent(nullptr), is_black(false), is_end(false) {}
		Node(T value) : left(nullptr), right(nullptr), parent(nullptr), is_black(false), is_end(false), pair(value) {}
		~Node(){}
	};

							/******************************** CLASSE TREE ********************************/

	template <class _Tp, class Iterator, class Const, class _Compare, class Allocator = std::allocator<Node<_Tp> > > //pair, compare, allocator<node<pair
	class __tree
	{
	public:
		typedef struct Node<_Tp>								_Node;
		typedef _Node*											nodeptr;
		typedef _Tp                                     		value_type;
		typedef _Compare                                 		value_compare;
		typedef Iterator										iterator;
		typedef Const											const_iterator;
		typedef Allocator                               		allocator_type;
		typedef typename allocator_type::pointer        		pointer;
		typedef typename allocator_type::const_pointer   		const_pointer;
		typedef typename allocator_type::size_type       		size_type;
		typedef typename allocator_type::difference_type 		difference_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;

	private:
		nodeptr				root;
		nodeptr         	_begin_node;
		nodeptr				_end_node;
		Allocator			_alloc;
		size_type			_size;
		value_compare		_value_compare;

	public:


		__tree() : _size(0)
		{
			root = nullptr;
			_begin_node = nullptr;
			_end_node = _alloc.allocate(1);
			_end_node->is_end = true;
			_begin_node = _end_node;
		}

		explicit __tree(const value_compare& __comp) : _size(0), _value_compare(__comp)
		{
			root = nullptr;
			_begin_node = nullptr;
			_end_node = _alloc.allocate(1);
			_end_node->is_end = true;
			_begin_node = _end_node;
		}

		explicit __tree(const allocator_type& __a) : _alloc(__a), _size(0)
		{
			root = nullptr;
			_begin_node = nullptr;
			_end_node = _alloc.allocate(1);
			_end_node->is_end = true;
			_begin_node = _end_node;
		}

		__tree(const value_compare& __comp, const allocator_type& __a) : _alloc(__a), _size(0), _value_compare(__comp)
		{
			root = nullptr;
			_begin_node = nullptr;
			_end_node = _alloc.allocate(1);
			_end_node->is_end = true;
			_begin_node = _end_node;
		}

		__tree(const __tree& __t)  
		{
			if (this != &__t)
			{
				_value_compare = __t.value_comp();
				if (_alloc != __t._alloc)
					clear();
				else
					_alloc = __t._alloc;

				_end_node = _alloc.allocate(1);
				for(iterator i = __t.begin(); i != __t.end(); i++)
					insert(*i);
			}
		}

		__tree& operator=(const __tree& __t)
		{	
			if (this != &__t)
			{
				_value_compare = __t.value_comp();
				if (_alloc != __t._alloc)
					clear();
				else
					_alloc = __t._alloc;
				_end_node = __t._end_node;
				_begin_node = __t._begin_node;
				_size = __t._size;
			}
			return *this;
		}
		~__tree() 
		{
			if (_size)
				erase_range(begin(), end());
			_alloc.deallocate(_end_node, 1);
		}

		/********************************    GETTER    ********************************/

		nodeptr 	get_end_node() 	const 		{ return _end_node; }
		nodeptr 	get_begin_node() const 		{ return _begin_node; }

				Allocator& 	get_alloc()			{ return _alloc; }
		const	Allocator& 	get_alloc() const 	{ return _alloc; }
		size_type	 		max_size() const 	{ return _alloc.max_size();	}

				size_type& size() 					{ return _size; }
		const	size_type& size() const 			{ return _size; }
				value_compare& value_comp() 		{ return _value_compare; }
		const	value_compare& value_comp() const 	{ return _value_compare; }

		nodeptr get_root() const 				{ return root; }
		void	set_root(nodeptr x) 			{ root = x; }
		void	find_new_root(nodeptr x) 
		{
			while (x->parent != nullptr)
				x = x->parent;
			root = x;
		}

		void	find_new_end(nodeptr root)
		{
			nodeptr x = root;
			while (x->right && !x->right->is_end)
				x = x->right;
			x->right = _end_node;
			_end_node->parent = x;
			_end_node->left = nullptr;
			_end_node->right = nullptr;
			_end_node->is_end = true;
		}
		/********************************      ITERATOR     ********************************/

			iterator 	begin() const 	{ return       iterator(_begin_node); }
		const_iterator 	cbegin() const 	{ return const_iterator(_begin_node); }
			iterator 	end() const 	{ return      iterator(_end_node); }
		const_iterator 	cend() const 	{ return const_iterator(_end_node); }



		/********************************   	MODIFIERS     ********************************/


		template <class U>
		_Node *newnode (U& value) 
		{
			_Node *a = _alloc.allocate(1);
			_Node n(value);
			_alloc.construct(a, n);
			return a;
		}

		void clear()
		{
			erase_range(begin(), end());
			_size = 0;
			_begin_node = _end_node;
		}

		void swap(__tree& __t)
		{
			std::swap(_begin_node, __t._begin_node);
			std::swap(_end_node, __t._end_node);
			std::swap(_alloc, __t._alloc);
			std::swap(_size, __t._size);
			std::swap(_value_compare, __t._value_compare);
		}
		void erase_position(iterator __p)
		{
			pointer __np = __p.base();
			iterator __r = __remove_node_nodeptr(__np);
			_alloc.deallocate(__p.base(), 1);
			if (_size > 0)
				find_new_end(root);
		}

		void erase_range(iterator __f, iterator __l)
		{
			iterator tmp;
			while(__f != __l)
			{
				tmp = __f;
				if(__f++ != __l)
					erase_position(tmp);
			}

		}

		template <class _Key>
		size_type erase_key(const _Key& __k)
		{
			iterator r = find(__k);
			if (r == end())
				return (0);
			erase_position(r);
			return 1;
		}

		ft::pair<iterator, bool> insert(const value_type& value )
		{
			nodeptr _root = get_root();
			nodeptr x = nullptr;
			nodeptr nuovo = nullptr;
			bool inserted = false;
			if (_root != nullptr && _size != 0) //se root esiste
			{
				x = _root;//puntiamo x a root
				while (true)
				{
					if (value_comp()(value, x->pair)) //se la key é minore della root
					{
						if (x->left != nullptr) //se esiste un figlio di sinistra
							x = x->left;//ci spostiamo
						else{
							nuovo = newnode(value);
							nuovo->parent = x;
							x->left = nuovo;
							inserted = true;
							break ;
						}
					}
					else if (value_comp()(x->pair, value))
					{
						if (x->right != nullptr && x->right != _end_node)
							x = x->right;
						else
						{
							nuovo = newnode(value);
							nuovo->parent = x;
							x->right = nuovo;
							if (value_comp()(_end_node->parent->pair , value))
							{
								nuovo->right = _end_node;
								_end_node->parent = nuovo;
								_end_node->left = nullptr;
							}
							nuovo->left = nullptr;
							inserted = true;
							break ;
						}
					}
					else//se troviamo un'uguaglianza
					{
						nuovo = x;
						break ;
					}
				}
			}
			else
			{
				root = newnode(value);
				nodeptr r = root;
				_size++;
				root->right = _end_node;
				root->is_black = true;
				_end_node->left = nullptr;
				_end_node->right = nullptr;
				_begin_node = root;
				_end_node->parent = root;
				return ft::pair<iterator,bool>((iterator)r, true);
			}
			if (_begin_node->left != nullptr)
				_begin_node = _begin_node->left;
			if (inserted == true)
			{
				balance_after_insert(get_root(), nuovo);
				find_new_root(nuovo);
				_size++;
			}
			nodeptr r = nuovo;
			return ft::pair<iterator,bool>((iterator)r, inserted);
		}

		iterator insert( iterator hint, const value_type& value )
		{
			ft::pair<iterator, bool> miao;
			(void) hint;
			miao = insert(value);
			return (miao.first);
		}

		iterator __remove_node_nodeptr(pointer __ptr)
		{
			iterator __r(__ptr);
			++__r;
			if (get_begin_node() == __ptr)
				_begin_node = __r.base();
			find_new_root(__ptr);
			--_size;
			tree_remove(root, static_cast<nodeptr>(__ptr));
			find_new_root(_begin_node);
			return __r;
		}

			/********************************    MAP OPERATIONS   ********************************/

		template <class key_type>
		iterator 		find(const key_type& k)
		{
			iterator p = lower_bound(k);
			if (p != end() && !value_comp()(k, *p))
				return p;
			return end();
		}

		template <class key_type>
		const_iterator 	find(const key_type& k) const
		{
			const_iterator p = lower_bound(k);
			if (p != end() && !value_comp()(k, *p))
				return p;
			return end();
		}

		template <class key_type>
		size_type      	count(const key_type& k) const
		{
			nodeptr rt = get_root();
			while (rt != nullptr)
			{
				if (value_comp()(k, rt->pair))
				{
					rt = static_cast<nodeptr>(rt->left);
				}
				else if (value_comp()(rt->pair, k))
					rt = static_cast<nodeptr>(rt->right);
				else
					return 1;
			}
			return 0;
		}

		template <class key_type>
		iterator 		__lower_bound(const key_type& k, nodeptr start, nodeptr result)
		{
			while (start != nullptr && start != _end_node)
			{
				if (!value_comp()(start->pair, k))
				{
					result = start;
					start = start->left;
				}
				else
				{
					start = start->right;
				}
			}
			return iterator(result);
		}

		template <class key_type>
		const_iterator 	__lower_bound(const key_type& k, nodeptr start, nodeptr result) const
		{
			while (start != nullptr)
			{
				if (!value_comp()(start->pair, k))
				{
					result = start;
					start = start->left;
				}
				else
				{
					start = start->right;
				}
			}
			return const_iterator(result);
		}

		template <class key_type>
		iterator 		lower_bound(const key_type& k)
		{
			nodeptr result = get_end_node();
			return (iterator)__lower_bound(k, root, result);
		}

		template <class key_type>
		const_iterator 		lower_bound(const key_type& k) const
		{
			nodeptr result = get_end_node();
			return (const_iterator)__lower_bound(k, root, result);
		}
		

		template <class key_type>
		const_iterator	__upper_bound(const key_type& __v, nodeptr start, nodeptr result) const
		{
			while (start != nullptr)
			{
				if (value_comp()(__v, start->pair))
				{
					result = static_cast<nodeptr>(start);
					start = static_cast<nodeptr>(start->left);
				}
				else
					start = static_cast<nodeptr>(start->right);
			}
			return const_iterator(result);
		}

		template <class key_type>
		iterator	__upper_bound(const key_type& __v, nodeptr start, nodeptr result)
		{
			while (start != nullptr)
			{
				if (value_comp()(__v, start->pair))
				{
					result = static_cast<nodeptr>(start);
					start = static_cast<nodeptr>(start->left);
				}
				else
					start = static_cast<nodeptr>(start->right);
			}
			return iterator(result);
		}

		template <class key_type>
		iterator 		upper_bound(const key_type& k)
		{
			nodeptr root = get_root();
			nodeptr result = get_end_node();
			while (root != nullptr)
			{
				if (value_comp()(k, root->pair))
				{
					result = root;
					root = root->left;
				}
				else
					root =root->right;
			}
			return iterator(result);
		}

		template <class key_type>
		const_iterator 	upper_bound(const key_type& k) const
		{
			nodeptr root = get_root();
			nodeptr result = get_end_node();
			while (root != nullptr)
			{
				if (value_comp()(k, root->pair))
				{
					result = root;
					root = root->left;
				}
				else
					root =root->right;
			}
			return const_iterator(result);
		}

		template <class key_type>
		ft::pair<iterator,iterator> equal_range(const key_type& k)
		{
			typedef ft::pair<iterator, iterator> _Pp;
			nodeptr result = get_end_node();
			nodeptr root = get_root();
			while (root != nullptr)
			{
				if (value_comp()(k, root->pair))
				{
					result = root;
					root = root->left;
				}
				else if (value_comp()(root->pair, k))
					root = root->right;
				else
					return _Pp(__lower_bound(k, root->left, root), __upper_bound(k, root->right, result));
			}
			return _Pp(iterator(result), iterator(result));
		}

		template <class key_type>
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
		{
			typedef ft::pair<const_iterator, const_iterator> _Pp;
			nodeptr result = get_end_node();
			nodeptr root = get_root();
			while (root != nullptr)
			{
				if (value_comp()(k, root->pair))
				{
					result = root;
					root = root->left;
				}
				else if (value_comp()(root->pair, k))
					root = root->right;
				else
					return _Pp(__lower_bound(k, root->left, root), __upper_bound(k, root->right, result));
			}
			return _Pp(const_iterator(result), const_iterator(result));
		}


		void _print_tree()
		{
			iterator i = begin();
			while (i != end())
			{
				if (i.base() != root)
				{
					if (i.base()->is_black)
						std::cout << "\033[0;31m" << i.base()->pair << "\033[0;37m -> parent = " << i.base()->parent->pair << std::endl;
					else
						std::cout << i.base()->pair << " -> parent = " << i.base()->parent->pair << std::endl;
				}
				else
					std::cout << "ROOT : " << i.base()->pair << std::endl;
				i++;
			}
			std::cout << "\n\n\n";
		}	

	}; //classe tree

}//namespace