#pragma once

#include <iostream>
#include <memory>
#include <__tree>
//#include "map.hpp"
namespace ft
{

template<class Pointer, class Key, class T>
class Node
{
	public:
		typedef Pointer pointer;
		pointer __left_;
		pointer __right_;
		pointer __parent_;
		bool	__is_black;
		Key		_key;
		T		_data;

}; //FINIRE QUESTA CLASSE E QUELLA DOPO

template <class _Tp, class _Compare, class Allocator>
class __tree
{
public:
	class Node;
    typedef _Tp                                     value_type;
    typedef _Compare                                value_compare;
    typedef Allocator                               allocator_type;

private:
    //typedef allocator_traits<allocator_type>         __alloc_traits;
    // typedef typename __make_tree_node_types<value_type,
    //     typename allocator_type::void_pointer>::type
    //                                                 _NodeTypes;
    // typedef typename _NodeTypes::key_type           key_type;
public:
    // typedef typename _NodeTypes::__node_value_type      __node_value_type;
    // typedef typename _NodeTypes::__container_value_type __container_value_type;

    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

public:
    // typedef typename _NodeTypes::__void_pointer        __void_pointer;

    // typedef typename _NodeTypes::__node_type           __node;
    // typedef typename _NodeTypes::__node_pointer        __node_pointer;

    // typedef typename _NodeTypes::__node_base_type      __node_base;
    // typedef typename _NodeTypes::__node_base_pointer   __node_base_pointer;

    // typedef typename _NodeTypes::__end_node_type       __end_node_t;
    // typedef typename _NodeTypes::__end_node_pointer    __end_node_ptr;

    // typedef typename _NodeTypes::__parent_pointer      __parent_pointer;
    // typedef typename _NodeTypes::__iter_pointer        __iter_pointer;

    // typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type 	__node_allocator;
    // typedef allocator_type<__node_allocator>         __node_traits;

private:
    // check for sane allocator pointer rebinding semantics. Rebinding the
    // allocator for a new pointer type should be exactly the same as rebinding
    // the pointer using 'pointer_traits'.
    // static_assert((is_same<__node_pointer, typename __node_traits::pointer>::value),
    //               "Allocator does not rebind pointers in a sane manner.");
    // typedef typename __rebind_alloc_helper<__node_traits, __node_base>::type
    //     __node_base_allocator;
    // typedef allocator_traits<__node_base_allocator> __node_base_traits;
    // static_assert((is_same<__node_base_pointer, typename __node_base_traits::pointer>::value),
    //              "Allocator does not rebind pointers in a sane manner.");

private:
    Node                __begin_node;
	Node				__end_node;
	Allocator			__alloc;
	size_type			__size;
	value_compare		__value_compare;

public:
    pointer __end_node() { return __end_node; }
    pointer __end_node() const { return __end_node; }
    Allocator& __node_alloc() {return __alloc; }
    const Allocator& __node_alloc() const {return __alloc;}
          pointer& __begin_node() {return __begin_node;}
    const pointer& __begin_node() const {return __begin_node;}
          size_type& size() { return __size; }
    const size_type& size() const { return __size; }
          value_compare& value_comp() { return __value_compare; }
    const value_compare& value_comp() const { return __value_compare; }


/*     DA QUA IN POI DA FARE 
    pointer __root() const { return __end_node()->__left_;}

    pointer* __root_ptr() const {
        return _VSTD::addressof(__end_node()->__left_);
    }

    typedef __tree_iterator<value_type, __node_pointer, difference_type>             iterator;
    typedef __tree_const_iterator<value_type, __node_pointer, difference_type> const_iterator;

    explicit __tree(const value_compare& __comp)
       _(
            is_nothrow_default_constructible<__node_allocator>::value &&
            is_nothrow_copy_constructible<value_compare>::value);
    explicit __tree(const allocator_type& __a);
    __tree(const value_compare& __comp, const allocator_type& __a);
    __tree(const __tree& __t);
    __tree& operator=(const __tree& __t);
    template <class _InputIterator>
        void __assign_unique(_InputIterator __first, _InputIterator __last);
    template <class _InputIterator>
        void __assign_multi(_InputIterator __first, _InputIterator __last);

    ~__tree();

          iterator begin()  {return       iterator(__begin_node());}
    const_iterator begin() const {return const_iterator(__begin_node());}
          iterator end() {return       iterator(__end_node());}
    const_iterator end() const {return const_iterator(__end_node());}

    size_type max_size() const
        {return std::min<size_type>(
                __node_traits::max_size(__node_alloc()),
                numeric_limits<difference_type >::max());}

    void clear();

    void swap(__tree& __t)
#if _LIBCPP_STD_VER <= 11
       _(
            __is_nothrow_swappable<value_compare>::value
            && (!__node_traits::propagate_on_container_swap::value ||
                 __is_nothrow_swappable<__node_allocator>::value)
            );
#else
       _(__is_nothrow_swappable<value_compare>::value);
#endif


#else
    template <class _Key, class _Args>
    pair<iterator, bool> __emplace_unique_key_args(_Key const&, _Args& __args);
    template <class _Key, class _Args>
    iterator __emplace_hint_unique_key_args(const_iterator, _Key const&, _Args&);
#endif

    pair<iterator, bool> __insert_unique(const __container_value_type& __v) {
        return __emplace_unique_key_args(_NodeTypes::__get_key(__v), __v);
    }

    iterator __insert_unique(const_iterator __p, const __container_value_type& __v) {
        return __emplace_hint_unique_key_args(__p, _NodeTypes::__get_key(__v), __v);
    }

#ifdef _LIBCPP_CXX03_LANG
    iterator __insert_multi(const __container_value_type& __v);
    iterator __insert_multi(const_iterator __p, const __container_value_type& __v);

#endif // !_LIBCPP_CXX03_LANG

    pair<iterator, bool> __node_insert_unique(__node_pointer __nd);
    iterator             __node_insert_unique(const_iterator __p,
                                              __node_pointer __nd);

    iterator __node_insert_multi(__node_pointer __nd);
    iterator __node_insert_multi(const_iterator __p, __node_pointer __nd);

 iterator
    __remove_node_pointer(__node_pointer);



    iterator erase(const_iterator __p);
    iterator erase(const_iterator __f, const_iterator __l);
    template <class _Key>
        size_type __erase_unique(const _Key& __k);
    template <class _Key>
        size_type __erase_multi(const _Key& __k);

    void __insert_node_at(__parent_pointer     __parent,
                          __node_base_pointer& __child,
                          __node_base_pointer __new_node);

    template <class _Key>
        iterator find(const _Key& __v);
    template <class _Key>
        const_iterator find(const _Key& __v) const;

    template <class _Key>
        size_type __count_unique(const _Key& __k) const;
    template <class _Key>
        size_type __count_multi(const _Key& __k) const;

    template <class _Key>

        iterator lower_bound(const _Key& __v)
            {return __lower_bound(__v, __root(), __end_node());}
    template <class _Key>
        iterator __lower_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>

        const_iterator lower_bound(const _Key& __v) const
            {return __lower_bound(__v, __root(), __end_node());}
    template <class _Key>
        const_iterator __lower_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>

        iterator upper_bound(const _Key& __v)
            {return __upper_bound(__v, __root(), __end_node());}
    template <class _Key>
        iterator __upper_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>

        const_iterator upper_bound(const _Key& __v) const
            {return __upper_bound(__v, __root(), __end_node());}
    template <class _Key>
        const_iterator __upper_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>
        pair<iterator, iterator>
        __equal_range_unique(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator>
        __equal_range_unique(const _Key& __k) const;

    template <class _Key>
        pair<iterator, iterator>
        __equal_range_multi(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator>
        __equal_range_multi(const _Key& __k) const;

    typedef __tree_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

    __node_holder remove(const_iterator __p);
private:
    __node_base_pointer&
        __find_leaf_low(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf_high(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf(const_iterator __hint,
                    __parent_pointer& __parent, const key_type& __v);
    // FIXME: Make this function const qualified. Unfortunetly doing so
    // breaks existing code which uses non-const callable comparators.
    template <class _Key>
    __node_base_pointer&
        __find_equal(__parent_pointer& __parent, const _Key& __v);
    template <class _Key> __node_base_pointer&
    __find_equal(__parent_pointer& __parent, const _Key& __v) const {
      return const_cast<__tree*>(this)->__find_equal(__parent, __v);
    }
    template <class _Key>
    __node_base_pointer&
        __find_equal(const_iterator __hint, __parent_pointer& __parent,
                     __node_base_pointer& __dummy,
                     const _Key& __v);

#ifndef _LIBCPP_CXX03_LANG
    template <class ..._Args>
    __node_holder __construct_node(_Args&& ...__args);
#else
    __node_holder __construct_node(const __container_value_type& __v);
#endif

    void destroy(__node_pointer __nd);

    void __copy_assign_alloc(const __tree& __t)
        {__copy_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_copy_assignment::value>());}

    void __copy_assign_alloc(const __tree& __t, true_type)
        {
        if (__node_alloc() != __t.__node_alloc())
            clear();
        __node_alloc() = __t.__node_alloc();
        }
    void __copy_assign_alloc(const __tree&, false_type) {}

    void __move_assign(__tree& __t, false_type);
    void __move_assign(__tree& __t, true_type)
       _(is_nothrow_move_assignable<value_compare>::value &&
                   is_nothrow_move_assignable<__node_allocator>::value);

    void __move_assign_alloc(__tree& __t)
       _(
            !__node_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<__node_allocator>::value)
        {__move_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_move_assignment::value>());}

    void __move_assign_alloc(__tree& __t, true_type)
       _(is_nothrow_move_assignable<__node_allocator>::value)
        {__node_alloc() = _VSTD::move(__t.__node_alloc());}
    void __move_assign_alloc(__tree&, false_type) {}

    __node_pointer __detach();
    static __node_pointer __detach(__node_pointer);

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
};



*/





template <class _Tp, class _NodePtr, class _DiffType>		class __tree_iterator;
template <class _Tp, class _ConstNodePtr, class _DiffType>	class __tree_const_iterator;

template <class _Pointer> 				class __tree_end_node;
template <class _VoidPtr> 				class __tree_node_base;
template <class _Tp, class _VoidPtr> 	class __tree_node;

template <class _Key, class _Value>
struct __value_type;

template <class _Allocator> 	class __map_node_destructor;
template <class _TreeIterator> 	class  __map_iterator;
template <class _TreeIterator> 	class __map_const_iterator;

/*

_NodePtr algorithms


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
inline _LIBCPP_INLINE_VISIBILITY
bool
__tree_is_left_child(_NodePtr __x)
{
    return __x == __x->__parent_->__left_;
}





/************* POI VEDIAMO SE SERVE **************/




// Determines if the subtree rooted at __x is a proper red black subtree.  If
//    __x is a proper subtree, returns the black height (null counts as 1).  If
//    __x is an improper subtree, returns 0.

/*
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
} */



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
inline _LIBCPP_INLINE_VISIBILITY
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
inline _LIBCPP_INLINE_VISIBILITY
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

/* ********************** FORSE NON CI INTERESSA *********************
template <class _EndNodePtr, class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
_EndNodePtr
__tree_next_iter(_NodePtr __x)
{
    if (__x->__right_ != nullptr)
        return static_cast<_EndNodePtr>(__tree_min(__x->__right_));
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_;
    return static_cast<_EndNodePtr>(__x->__parent_);
}*/


// Ritorna: puntatore al nodo piú piccolo prima di _x
// Condizione di partenza : _x != nullptr.
// Nota: _x potrebbe essere _root->parent
template <class _NodePtr, class _EndNodePtr>
inline _LIBCPP_INLINE_VISIBILITY
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

/************************************** CI SERVIRÁ MAI? *****************************/
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




}//namespace