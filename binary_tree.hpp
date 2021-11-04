#pragma once

#include <iostream>
#include <memory>
#include <__tree>
#include "iterator.hpp"
//#include "map_iterator.hpp"
#include <map>
namespace ft
{


	template <class _Tp, class _Compare, class _Allocator> class __tree;
	template <class _Tp, class Iterator, class _DiffType> class tree_iterator;
		
		
	/**********************  STRUTTURA NODI **********************/
	template<class Pointer, class Key, class T>
	struct Node
	{
		typedef Pointer pointer;
		pointer __left_;
		pointer __right_;
		pointer __parent_;
		bool	__is_black;
		Key		_key;
		T		_data;

	}; //nodo



	/******************************* ALGORITMO DELL'ALBERO *******************************/

	/*_NodePtr algorithms


	Gli algoritmi che prendono _NodePtr sono algoritmi dell'albero rosso-nero.
	Questi algoritmi che prendono un parametro chiamato __root dovrebbero considerare che
	__root punta a un albero rosso-nero corretto.

	Ciascuno di questi algoritmi assume che _root->parent punta a una struttura non-null
	che ha un membro _left, che punta a _root. Nessun altro membro é letto o scritto
	a _root->parent. 
	(in parole povere, il genitore della root ha un solo membro left che punta alla root stessa)

	Nei prossimi commenti _root->parent sará riferito a end_node. 
	end_node->left quindi é un valore accessibile esternamente che sta per _root, 
	e puó essere cambiato inserendo e rimuovendo nodi.

	Tutti i nodi (ad eccezione di end_node), persino il nodo riferito a _root,
	hanno un parente che punti a qualcosa di non-null

	*/

// Ritorna VERO se _x é left child (piú piccolo del genitore)
// Precondition:  __x != nullptr.
template <class _NodePtr>
bool
__tree_is_left_child(_NodePtr __x)
{
    return __x == __x->__parent_->__left_;
}





/************* POI VEDIAMO SE SERVE **************/




// Determines if the subtree rooted at __x is a proper red black subtree.  If
//    __x is a proper subtree, returns the black height (null counts as 1).  If
//    __x is an improper subtree, returns 0.


template <class _NodePtr>
unsigned
__tree_sub_invariant(_NodePtr __x)
{
    if (__x == nullptr)
        return 1;
    // parent consistency checked by caller
    // check __x->__left_ consistency
    if (__x->__left_ != nullptr && __x->__left_->__parent_ != __x)
        return 0;
    // check __x->__right_ consistency
    if (__x->__right_ != nullptr && __x->__right_->__parent_ != __x)
        return 0;
    // check __x->__left_ != __x->__right_ unless both are nullptr
    if (__x->__left_ == __x->__right_ && __x->__left_ != nullptr)
        return 0;
    // If this is red, neither child can be red
    if (!__x->__is_black_)
    {
        if (__x->__left_ && !__x->__left_->__is_black_)
            return 0;
        if (__x->__right_ && !__x->__right_->__is_black_)
            return 0;
    }
    unsigned __h = __tree_sub_invariant(__x->__left_);
    if (__h == 0)
        return 0;  // invalid left subtree
    if (__h != __tree_sub_invariant(__x->__right_))
        return 0;  // invalid or different height right subtree
    return __h + __x->__is_black_;  // return black height of this node
}



// Determina se l'albero é corretto : 
// root == nullptr é corretto. Ritorna vero se root é un albero corretto, se no falso
template <class _NodePtr>
bool
__tree_invariant(_NodePtr __root)
{
    if (__root == nullptr)
        return true;
    // check __x->__parent_ consistency
    if (__root->__parent_ == nullptr) //il genitore della root deve esistere
        return false;
    if (!__tree_is_left_child(__root)) //root deve essere il figlio di sinistra 
        return false;
    // root must be black
    if (!__root->__is_black_) //root deve essere nera
        return false;
    // do normal node checks
    return __tree_sub_invariant(__root) != 0;
}


// Ritorna: puntatore al nodo piú a sinistra sotto _x
// Condizione di partenza : _x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_min(_NodePtr __x)
{
    while (__x->__left_ != nullptr)
        __x = __x->__left_;
    return __x;
}

// Ritorna: puntatore al nodo piú a destra sotto _x
// Condizione di partenza : _x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_max(_NodePtr __x)
{
    while (__x->__right_ != nullptr)
        __x = __x->__right_;
    return __x;
}


// Ritorna: puntatore al prossimo nodo in ordine di grandezza dopo _x.
// Condizione di partenza : _x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_next(_NodePtr __x)
{
    if (__x->__right_ != nullptr)
        return __tree_min(__x->__right_);
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_;
    return __x->__parent_;
}

/* ********************** FORSE NON CI INTERESSA *********************/
template <class _NodePtr>
_NodePtr __tree_next_iter(_NodePtr __x)
{
    if (__x->__right_ != nullptr)
        return static_cast<_NodePtr>(__tree_min(__x->__right_));
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_;
    return static_cast< _NodePtr>(__x->__parent_);
}


// Ritorna: puntatore al nodo piú piccolo prima di _x
// Condizione di partenza : _x != nullptr.
// Nota: _x potrebbe essere _root->parent
template <class _NodePtr, class _EndNodePtr>
_NodePtr
__tree_prev_iter(_EndNodePtr __x)
{
    if (__x->__left_ != nullptr)
        return __tree_max(__x->__left_);
    _NodePtr __xx = static_cast<_NodePtr>(__x);
    while (__tree_is_left_child(__xx))
        __xx = __xx->__parent_;
    return __xx->__parent_;
}

// Ritorna: puntatore a una foglia
// Condizione di partenza : _x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_leaf(_NodePtr __x)
{
    while (true)
    {
        if (__x->__left_ != nullptr)
        {
            __x = __x->__left_;
            continue;
        }
        if (__x->__right_ != nullptr)
        {
            __x = __x->__right_;
            continue;
        }
        break;
    }
    return __x;
}


// Effetti: rende _x->right la root del subtree con _x come left child, preservando l'ordine
// Condizione di partenza: x->right != nullptr
template <class _NodePtr>
void
__tree_left_rotate(_NodePtr __x)
{
    _NodePtr __y = __x->__right_;   //crea un nodo y a cui assegna x->right
    __x->__right_ = __y->__left_;	//x->right diventa il left child di y
    if (__x->__right_ != nullptr)
        __x->__right_->__parent_ = __x;
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_->__right_ = __y;
    __y->__left_ = __x;
    __x->__parent_ = __y;
}

// Effetti: rende _x->left la root del subtree con _x come right child, preservando l'ordine
// Condizione di partenza: x->left != nullptr
template <class _NodePtr>
void
__tree_right_rotate(_NodePtr __x)
{
    _NodePtr __y = __x->__left_;
    __x->__left_ = __y->__right_;
    if (__x->__left_ != nullptr)
        __x->__left_->__parent_ = __x;
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_->__right_ = __y;
    __y->__right_ = __x;
    __x->__parent = __y;
}



// Effetti: Ribilancia la root dopo aver attaccato _x a una foglia.
// Condizione di partenza: root != nullptr && _x != nullptr
							// _x non ha figli
							//_x é la root o un figlio diretto o indiretto della root
//                If __x were to be unlinked from __root (setting __root to
//                  nullptr if __root == __x), __tree_invariant(__root) == true.
// Postcondition: __tree_invariant(end_node->__left_) == true.  end_node->__left_
//                may be different than the value passed in as __root.
template <class _NodePtr>
void
__tree_balance_after_insert(_NodePtr __root, _NodePtr __x)
{
    __x->__is_black_ = __x == __root; // x é nero se x é la root, altrimenti é rosso (soddisfa la condizione per cui la root é nera, altrimenti inseriamo a prescindere un nodo rosso)
    while (__x != __root && !__x->__parent_->__is_black_)// questo é il caso in cui invece non abbiamo inserito la root, e quindi é tutto da bilanciare perché anche il genitore é rosso (non soddisfa la proprietá per cui i rossi devono avere figli neri)
    {
		// e il genitore non é manco root perché se la root é nera, quindi siamo in un subtree
        if (__tree_is_left_child(__x->__parent_)) // se il genitore é un figlio sinistro
        {
            _NodePtr __y = __x->__parent_->__parent_->__right_; // assegno a y lo zio destro di x
            if (__y != nullptr && !__y->__is_black_)	//se lo zio destro esiste e é rosso
            {
                __x = __x->__parent_;
                __x->__is_black_ = true;	// il genitore diventa nero
                __x = __x->__parent_;
                __x->__is_black_ = __x == __root; //il nonno diventa nero se é la root, altrimenti diventa rosso
                __y->__is_black_ = true;		//anche lo zio diventa nero
            }
            else //se lo zio non esiste e/o é nero
            {
                if (!__tree_is_left_child(__x)) //se x é figlio di destra
                {
                    __x = __x->__parent_;
                    __tree_left_rotate(__x); // rotea e il genitore diventa il figlio di sinistra di x
                }
                __x = __x->__parent_;
                __x->__is_black_ = true; // il genitore diventa nero
                __x = __x->__parent_;
                __x->__is_black_ = false; //il nonno diventa rosso
                __tree_right_rotate(__x); // il nonno diventa il nuovo fratello in pratica
                break;
            }
        }
        else
        {
            _NodePtr __y = __x->__parent_->__parent_->__left_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_;
                __x->__is_black_ = true;
                __x = __x->__parent_;
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (__tree_is_left_child(__x))
                {
                    __x = __x->__parent_;
                    __tree_right_rotate(__x);
                }
                __x = __x->__parent_;
                __x->__is_black_ = true;
                __x = __x->__parent_;
                __x->__is_black_ = false;
                __tree_left_rotate(__x);
                break;
            }
        }
    }
}

// Precondition:  __root != nullptr && __z != nullptr.
//                __tree_invariant(__root) == true.
//                __z == __root or == a direct or indirect child of __root.
// Effects:  unlinks __z from the tree rooted at __root, rebalancing as needed.
// Postcondition: __tree_invariant(end_node->__left_) == true && end_node->__left_
//                nor any of its children refer to __z.  end_node->__left_
//                may be different than the value passed in as __root.


template <class _NodePtr>
void
__tree_remove(_NodePtr __root, _NodePtr __z)
{
    // __z will be removed from the tree.  Client still needs to destruct/deallocate it
    // __y is either __z, or if __z has two children, __tree_next(__z).
    // __y will have at most one child.
    // __y will be the initial hole in the tree (make the hole at a leaf)
    _NodePtr __y = (__z->__left_ == nullptr || __z->__right_ == nullptr) ?
                    __z : __tree_next(__z);
    // __x is __y's possibly null single child
    _NodePtr __x = __y->__left_ != nullptr ? __y->__left_ : __y->__right_;
    // __w is __x's possibly null uncle (will become __x's sibling)
    _NodePtr __w = nullptr;
    // link __x to __y's parent, and find __w
    if (__x != nullptr)
        __x->__parent_ = __y->__parent_;
    if (__tree_is_left_child(__y))
    {
        __y->__parent_->__left_ = __x;
        if (__y != __root)
            __w = __y->__parent_->__right_;
        else
            __root = __x;  // __w == nullptr
    }
    else
    {
        __y->__parent_->__right_ = __x;
        // __y can't be root if it is a right child
        __w = __y->__parent_->__left_;
    }
    bool __removed_black = __y->__is_black_;
    // If we didn't remove __z, do so now by splicing in __y for __z,
    //    but copy __z's color.  This does not impact __x or __w.
    if (__y != __z)
    {
        // __z->__left_ != nulptr but __z->__right_ might == __x == nullptr
        __y->__parent_ = __z->__parent_;
        if (__tree_is_left_child(__z))
            __y->__parent_->__left_ = __y;
        else
            __y->__parent_->__right_ = __y;
        __y->__left_ = __z->__left_;
        __y->__left_->__set_parent(__y);
        __y->__right_ = __z->__right_;
        if (__y->__right_ != nullptr)
            __y->__right_->__set_parent(__y);
        __y->__is_black_ = __z->__is_black_;
        if (__root == __z)
            __root = __y;
    }
    // There is no need to rebalance if we removed a red, or if we removed
    //     the last node.
    if (__removed_black && __root != nullptr)
    {
        // Rebalance:
        // __x has an implicit black color (transferred from the removed __y)
        //    associated with it, no matter what its color is.
        // If __x is __root (in which case it can't be null), it is supposed
        //    to be black anyway, and if it is doubly black, then the double
        //    can just be ignored.
        // If __x is red (in which case it can't be null), then it can absorb
        //    the implicit black just by setting its color to black.
        // Since __y was black and only had one child (which __x points to), __x
        //   is either red with no children, else null, otherwise __y would have
        //   different black heights under left and right pointers.
        // if (__x == __root || __x != nullptr && !__x->__is_black_)
        if (__x != nullptr)
            __x->__is_black_ = true;
        else
        {
            //  Else __x isn't root, and is "doubly black", even though it may
            //     be null.  __w can not be null here, else the parent would
            //     see a black height >= 2 on the __x side and a black height
            //     of 1 on the __w side (__w must be a non-null black or a red
            //     with a non-null black child).
            while (true)
            {
                if (!__tree_is_left_child(__w))  // if x is left child
                {
                    if (!__w->__is_black_)
                    {
                        __w->__is_black_ = true;
                        __w->__parent_->__is_black_ = false;
                        __tree_left_rotate(__w->__parent_);
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->__left_)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->__left_->__right_;
                    }
                    // __w->__is_black_ is now true, __w may have null children
                    if ((__w->__left_  == nullptr || __w->__left_->__is_black_) &&
                        (__w->__right_ == nullptr || __w->__right_->__is_black_))
                    {
                        __w->__is_black_ = false;
                        __x = __w->__parent_;
                        // __x can no longer be null
                        if (__x == __root || !__x->__is_black_)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_->__right_ :
                                    __x->__parent_->__left_;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->__right_ == nullptr || __w->__right_->__is_black_)
                        {
                            // __w left child is non-null and red
                            __w->__left_->__is_black_ = true;
                            __w->__is_black_ = false;
                            __tree_right_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->__parent_;
                        }
                        // __w has a right red child, left child may be null
                        __w->__is_black_ = __w->__parent_->__is_black_;
                        __w->__parent_->__is_black_ = true;
                        __w->__right_->__is_black_ = true;
                        __tree_left_rotate(__w->__parent_);
                        break;
                    }
                }
                else
                {
                    if (!__w->__is_black_)
                    {
                        __w->__is_black_ = true;
                        __w->__parent_->__is_black_ = false;
                        __tree_right_rotate(__w->__parent_);
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->__right_)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->__right_->__left_;
                    }
                    // __w->__is_black_ is now true, __w may have null children
                    if ((__w->__left_  == nullptr || __w->__left_->__is_black_) &&
                        (__w->__right_ == nullptr || __w->__right_->__is_black_))
                    {
                        __w->__is_black_ = false;
                        __x = __w->__parent_;
                        // __x can no longer be null
                        if (!__x->__is_black_ || __x == __root)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_->__right_ :
                                    __x->__parent_->__left_;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->__left_ == nullptr || __w->__left_->__is_black_)
                        {
                            // __w right child is non-null and red
                            __w->__right_->__is_black_ = true;
                            __w->__is_black_ = false;
                            __tree_left_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->__parent_;
                        }
                        // __w has a left red child, right child may be null
                        __w->__is_black_ = __w->__parent_->__is_black_;
                        __w->__parent_->__is_black_ = true;
                        __w->__left_->__is_black_ = true;
                        __tree_right_rotate(__w->__parent_);
                        break;
                    }
                }
            }
        }
    }
}


/******************************** CLASSE TREE ********************************/


template <class _Tp, class _Compare, class Allocator = std::allocator<_Tp> >
class __tree
{
public:
	//friend class map;
    typedef _Tp                                     	value_type;
    typedef _Compare                                	value_compare;
    typedef Allocator                               	allocator_type;
    typedef typename allocator_type::pointer         	pointer;
    typedef typename allocator_type::const_pointer   	const_pointer;
    typedef typename allocator_type::size_type       	size_type;
    typedef typename allocator_type::difference_type 	difference_type;
    typedef tree_iterator<value_type, pointer, difference_type>            	iterator;
    typedef tree_iterator<value_type, const_pointer, difference_type> 		const_iterator;
	typedef struct Node <pointer, _Tp, _Compare>		_Node;



private:
    iterator            begin_node; // nei costruttori punta all'end node
	_Node				end_node; //deve essere genitore di root
	Allocator			__alloc;
	size_type			__size;
	value_compare		__value_compare;

public:
    _Node __end_node() { return end_node; }
   // Iterator __end_node() const { return __end_node; }
    Allocator& __node_alloc() {return __alloc; }
    const Allocator& __node_alloc() const {return __alloc;}
          iterator __begin_node() {return begin_node;}
    const pointer& __begin_node() const {return begin_node;}
          size_type& size() { return __size; }
    const size_type& size() const { return __size; }
          value_compare& value_comp() { return __value_compare; }
    const value_compare& value_comp() const { return __value_compare; }
    pointer __root() const { return end_node.__left_; }
	__tree() : __size(0) {}
    explicit __tree(const value_compare& __comp) : __size(0), __value_compare(__comp)
	{
		begin_node = end_node;
	}
    explicit __tree(const allocator_type& __a) : __alloc(__a), __size(0)
	{
		begin_node = end_node;
	}
    __tree(const value_compare& __comp, const allocator_type& __a) : __alloc(__a), __size(0), __value_compare(__comp)
	{
    	begin_node = end_node;
	}
    __tree(const __tree& __t) {} // da fare
    __tree& operator=(const __tree& __t){
		if (this != &__t)
		{
			__value_compare = __t.value_compare();
			if (__alloc != __t.__alloc)
				clear();
			else
				__alloc = __t.__alloc;
			end_node = __t.end_node;
			begin_node = __t.begin_node;
			__size = __t.__size;
		}
	} // da fare
    ~__tree() { __alloc.destroy(__root()); }

          iterator begin()  {return       iterator(__begin_node());}
    const_iterator begin() const {return const_iterator(__begin_node());}
          iterator end() {return       iterator(__end_node());}
    const_iterator end() const {return const_iterator(__end_node());}

    size_type max_size() const { return __alloc.max_size(); }

    void clear()
	{
		__alloc.destroy(__root());
		__size = 0;
		begin_node = end_node;
		end_node->__left_ = nullptr;
		
	}

    void swap(__tree& __t)
	{;
    	std::swap(begin_node, __t.begin_node);
    	std::swap(end_node, __t.end_node);
    	std::swap(__alloc, __t.__alloc);
    	std::swap(__size, __t.__size);
		std::swap(__value_compare, __t.__value_compare);
    	if (size() == 0)
			__begin_node() = __end_node();
		else
			__end_node()->__left_->__parent_ = static_cast<pointer>(__end_node());
		if (__t.size() == 0)
			__t.__begin_node() = __t.__end_node();
		else
			__t.__end_node()->__left_->__parent_ = static_cast<pointer>(__t.__end_node());
	}
    iterator erase(const_iterator __p)
	{
		pointer __np = __p.__get_np();
		iterator __r = __remove_node_pointer(__np);
		Allocator& __na = __node_alloc();
		__alloc.destroy(__na, __get_ptr(const_cast<pointer>(*__p)));
		__alloc.deallocate(__na, __np, 1);
		return __r;
	}

    iterator erase(const_iterator __f, const_iterator __l)
	{
		while (__f != __l)
			__f = erase(__f);
		return iterator(__l.__ptr_);
	}

	std::pair<iterator, bool> insert( const value_type& value ) //std::pair 
	{
		// //mymap.insert ( std::pair<char,int>('a',100) );
		// iterator _beg;
		// //value->key;
		// //value
		// pointer _parent;
		// pointer _child = __fin

		

	}
	iterator insert( iterator hint, const value_type& value )
	{
		// __parent_pointer __parent;
		// __node_base_pointer& __child = __find_leaf(__p, __parent, _NodeTypes::__get_key(__v));
		// __node_holder __h = __construct_node(__v);
		// __insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
		// return iterator(__h.release());
	}
    //iterator find(const _Key& __v);


	template <class key_type>
	iterator 		find(const key_type& k); 
	template <class key_type>
	const_iterator 	find(const key_type& k) const;

	template <class key_type>
	size_type      	count(const key_type& k) const;

	template <class key_type>
	iterator 		lower_bound(const key_type& k);
	template <class key_type>
	const_iterator 	lower_bound(const key_type& k) const;
	template <class key_type>
	iterator 		upper_bound(const key_type& k);
	template <class key_type>
	const_iterator 	upper_bound(const key_type& k) const;

	template <class key_type>
	std::pair<iterator,iterator>             equal_range(const key_type& k);
	template <class key_type>
	std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;

    // template <class, class, class, class> friend class map;
    // template <class, class, class, class> friend class multimap;
	//template <class _Tp, class _Compare, class _Allocator>
	iterator __remove_node_pointer(pointer __ptr)
	{
		iterator __r(__ptr);
		++__r;
		if (__begin_node() == __ptr)
			__begin_node() = __r.__ptr_;
		--size();
		__tree_remove(__end_node()->__left_,
					static_cast<pointer>(__ptr));
		return __r;
	}
};





	/******************************* CLASSE TREE_ITERATOR *******************************/

	template <class _Tp, class Iterator, class _DiffType>
	class tree_iterator 
	{
		//class _tree;
		typedef Iterator                                       	pointer;
		pointer __ptr_;

	public:
		struct Node;
		class _tree;
		//typedef bidirectional_iterator_tag                     iterator_category;
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
	
		tree_iterator() : __ptr_() {}
		reference operator*() const { return static_cast<reference>(*__ptr_); }  
		pointer operator->() const { return __ptr_; }

		tree_iterator& operator++() 
		{ 
			__ptr_ = static_cast<pointer>(ft::__tree_next_iter(__ptr_));
			return *this;
		}
		tree_iterator operator++(int)
			{tree_iterator __t(*this); ++(*this); return __t;}

		tree_iterator& operator--() {
		__ptr_ = static_cast<pointer>(__tree_prev_iter<pointer>(
			static_cast<pointer>(__ptr_)));
		return *this;
		}
		tree_iterator operator--(int)
			{tree_iterator __t(*this); --(*this); return __t;}

		friend
		bool operator==(const tree_iterator& __x, const tree_iterator& __y)
			{return __x.__ptr_ == __y.__ptr_;}
		friend
		bool operator!=(const tree_iterator& __x, const tree_iterator& __y)
			{return !(__x == __y);}

	private:
		explicit tree_iterator(pointer __p) : __ptr_(__p) {}
		pointer __get_np() const { return static_cast<pointer>(__ptr_); }
	}; //tree_iterator
}//namespace