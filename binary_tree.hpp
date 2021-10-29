#pragma once

#include <iostream>
#include <memory>
//#include "map.hpp"
namespace ft
{
	// template <class T>
	// class	_tree
	// {
	// 	//class map;
	// 	struct Node{

	// 		T value;
	// 		bool bigger;
	// 		Node *left;
	// 		Node *right;
	// 		Node *parent;
	// 	};

	// 	private:
	// 		std::allocator<T> _alloc;
	// 		Node *_root;
	// 		Node *_current;
		
	// 	public:
	// 		_tree() { _root = nullptr; }
	// 		Node *getRoot () const { return _root; }
	// 		void insertValue(Node *curr, T newValue)
	// 		{
	// 			if (curr == nullptr)
	// 				curr = _alloc.allocate(sizeof(Node));
	// 			if (curr->value == 0)
	// 				curr->value = newValue;
	// 			else if(newValue > curr->value)
	// 			{
	// 				insertValue(curr->right, newValue);
	// 				curr->right->bigger = true;
	// 			}
	// 			else
	// 			{
	// 				insertValue(curr->left, newValue);
	// 				curr->left->bigger = false;
	// 			}
	// 		}
	// 		T returnValue(Node *curr) const { return curr->value; }

	// }; //class _tree
	// template <class T>
	// std::ostream& operator<<(std::ostream& os, const ft::_tree<T>& dt)
	// {
	// 	os << dt.returnValue(dt.getRoot()) << "\n";
	// 	return os;
	// }

template <class _Tp, class _Compare, class _Allocator> 		class __tree;
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

// Returns:  true if __x is a left child of its parent, else false
// Precondition:  __x != nullptr.
template <class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
bool
__tree_is_left_child(_NodePtr __x) _NOEXCEPT
{
    return __x == __x->__parent_->__left_;
}

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

// Determines if the red black tree rooted at __root is a proper red black tree.
//    __root == nullptr is a proper tree.  Returns true is __root is a proper
//    red black tree, else returns false.
template <class _NodePtr>
bool
__tree_invariant(_NodePtr __root)
{
    if (__root == nullptr)
        return true;
    // check __x->__parent_ consistency
    if (__root->__parent_ == nullptr)
        return false;
    if (!__tree_is_left_child(__root))
        return false;
    // root must be black
    if (!__root->__is_black_)
        return false;
    // do normal node checks
    return __tree_sub_invariant(__root) != 0;
}

// Returns:  pointer to the left-most node under __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
_NodePtr
__tree_min(_NodePtr __x) _NOEXCEPT
{
    while (__x->__left_ != nullptr)
        __x = __x->__left_;
    return __x;
}

// Returns:  pointer to the right-most node under __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
_NodePtr
__tree_max(_NodePtr __x) _NOEXCEPT
{
    while (__x->__right_ != nullptr)
        __x = __x->__right_;
    return __x;
}

// Returns:  pointer to the next in-order node after __x.
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_next(_NodePtr __x) _NOEXCEPT
{
    if (__x->__right_ != nullptr)
        return __tree_min(__x->__right_);
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_unsafe();
    return __x->__parent_unsafe();
}

template <class _EndNodePtr, class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
_EndNodePtr
__tree_next_iter(_NodePtr __x) _NOEXCEPT
{
    if (__x->__right_ != nullptr)
        return static_cast<_EndNodePtr>(__tree_min(__x->__right_));
    while (!__tree_is_left_child(__x))
        __x = __x->__parent_unsafe();
    return static_cast<_EndNodePtr>(__x->__parent_);
}

// Returns:  pointer to the previous in-order node before __x.
// Precondition:  __x != nullptr.
// Note: __x may be the end node.
template <class _NodePtr, class _EndNodePtr>
inline _LIBCPP_INLINE_VISIBILITY
_NodePtr
__tree_prev_iter(_EndNodePtr __x) _NOEXCEPT
{
    if (__x->__left_ != nullptr)
        return __tree_max(__x->__left_);
    _NodePtr __xx = static_cast<_NodePtr>(__x);
    while (__tree_is_left_child(__xx))
        __xx = __xx->__parent_unsafe();
    return __xx->__parent_unsafe();
}

// Returns:  pointer to a node which has no children
// Precondition:  __x != nullptr.
template <class _NodePtr>
_NodePtr
__tree_leaf(_NodePtr __x) _NOEXCEPT
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

// Effects:  Makes __x->__right_ the subtree root with __x as its left child
//           while preserving in-order order.
// Precondition:  __x->__right_ != nullptr
template <class _NodePtr>
void
__tree_left_rotate(_NodePtr __x) _NOEXCEPT
{
    _NodePtr __y = __x->__right_;
    __x->__right_ = __y->__left_;
    if (__x->__right_ != nullptr)
        __x->__right_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__left_ = __x;
    __x->__set_parent(__y);
}

// Effects:  Makes __x->__left_ the subtree root with __x as its right child
//           while preserving in-order order.
// Precondition:  __x->__left_ != nullptr
template <class _NodePtr>
void
__tree_right_rotate(_NodePtr __x) _NOEXCEPT
{
    _NodePtr __y = __x->__left_;
    __x->__left_ = __y->__right_;
    if (__x->__left_ != nullptr)
        __x->__left_->__set_parent(__x);
    __y->__parent_ = __x->__parent_;
    if (__tree_is_left_child(__x))
        __x->__parent_->__left_ = __y;
    else
        __x->__parent_unsafe()->__right_ = __y;
    __y->__right_ = __x;
    __x->__set_parent(__y);
}

// Effects:  Rebalances __root after attaching __x to a leaf.
// Precondition:  __root != nulptr && __x != nullptr.
//                __x has no children.
//                __x == __root or == a direct or indirect child of __root.
//                If __x were to be unlinked from __root (setting __root to
//                  nullptr if __root == __x), __tree_invariant(__root) == true.
// Postcondition: __tree_invariant(end_node->__left_) == true.  end_node->__left_
//                may be different than the value passed in as __root.
template <class _NodePtr>
void
__tree_balance_after_insert(_NodePtr __root, _NodePtr __x) _NOEXCEPT
{
    __x->__is_black_ = __x == __root;
    while (__x != __root && !__x->__parent_unsafe()->__is_black_)
    {
        // __x->__parent_ != __root because __x->__parent_->__is_black == false
        if (__tree_is_left_child(__x->__parent_unsafe()))
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_unsafe()->__right_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (!__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    __tree_left_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = false;
                __tree_right_rotate(__x);
                break;
            }
        }
        else
        {
            _NodePtr __y = __x->__parent_unsafe()->__parent_->__left_;
            if (__y != nullptr && !__y->__is_black_)
            {
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
                __x->__is_black_ = __x == __root;
                __y->__is_black_ = true;
            }
            else
            {
                if (__tree_is_left_child(__x))
                {
                    __x = __x->__parent_unsafe();
                    __tree_right_rotate(__x);
                }
                __x = __x->__parent_unsafe();
                __x->__is_black_ = true;
                __x = __x->__parent_unsafe();
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
__tree_remove(_NodePtr __root, _NodePtr __z) _NOEXCEPT
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
            __w = __y->__parent_unsafe()->__right_;
        else
            __root = __x;  // __w == nullptr
    }
    else
    {
        __y->__parent_unsafe()->__right_ = __x;
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
            __y->__parent_unsafe()->__right_ = __y;
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
                        __w->__parent_unsafe()->__is_black_ = false;
                        __tree_left_rotate(__w->__parent_unsafe());
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
                        __x = __w->__parent_unsafe();
                        // __x can no longer be null
                        if (__x == __root || !__x->__is_black_)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_unsafe()->__right_ :
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
                            __w = __w->__parent_unsafe();
                        }
                        // __w has a right red child, left child may be null
                        __w->__is_black_ = __w->__parent_unsafe()->__is_black_;
                        __w->__parent_unsafe()->__is_black_ = true;
                        __w->__right_->__is_black_ = true;
                        __tree_left_rotate(__w->__parent_unsafe());
                        break;
                    }
                }
                else
                {
                    if (!__w->__is_black_)
                    {
                        __w->__is_black_ = true;
                        __w->__parent_unsafe()->__is_black_ = false;
                        __tree_right_rotate(__w->__parent_unsafe());
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
                        __x = __w->__parent_unsafe();
                        // __x can no longer be null
                        if (!__x->__is_black_ || __x == __root)
                        {
                            __x->__is_black_ = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = __tree_is_left_child(__x) ?
                                    __x->__parent_unsafe()->__right_ :
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
                            __w = __w->__parent_unsafe();
                        }
                        // __w has a left red child, right child may be null
                        __w->__is_black_ = __w->__parent_unsafe()->__is_black_;
                        __w->__parent_unsafe()->__is_black_ = true;
                        __w->__left_->__is_black_ = true;
                        __tree_right_rotate(__w->__parent_unsafe());
                        break;
                    }
                }
            }
        }
    }
}




}//namespace