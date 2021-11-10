#pragma once

#include <iostream>


namespace ft
{


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
		hanno un parente che punti a qualcosaz di non-null

		*/

	// Ritorna VERO se _x é left child (piú piccolo del genitore)
	// Precondition:  __x != nullptr.
	template <class _NodePtr>
	bool
	is_left_child(_NodePtr __x)
	{
		return __x == __x->parent->left;
	}

	// Determines if the subtree rooted at __x is a proper red black subtree.  If
	//    __x is a proper subtree, returns the black height (null counts as 1).  If
	//    __x is an improper subtree, returns 0.


	template <class _NodePtr>
	unsigned __tree_sub_invariant(_NodePtr __x)
	{
		if (__x == nullptr)
			return 1;
		// parent consistency checked by caller
		// check __x->left consistency
		if (__x->left != nullptr && __x->left->parent != __x)
			return 0;
		// check __x->right consistency
		if (__x->right != nullptr && __x->right->parent != __x)
			return 0;
		// check __x->left != __x->right unless both are nullptr
		if (__x->left == __x->right && __x->left != nullptr)
			return 0;
		// If this is red, neither child can be red
		if (!__x->is_black)
		{
			if (__x->left && !__x->left->is_black)
				return 0;
			if (__x->right && !__x->right->is_black)
				return 0;
		}
		unsigned __h = __tree_sub_invariant(__x->left);
		if (__h == 0)
			return 0;  // invalid left subtree
		if (__h != __tree_sub_invariant(__x->right))
			return 0;  // invalid or different height right subtree
		return __h + __x->is_black;  // return black height of this node
	}



	// Determina se l'albero é corretto : 
	// root == nullptr é corretto. Ritorna vero se root é un albero corretto, se no falso
	template <class _NodePtr>
	bool __tree_invariant(_NodePtr __root)
	{
		if (__root == nullptr)
			return true;
		// check __x->parent consistency
		if (__root->parent == nullptr) //il genitore della root deve esistere
			return false;
		if (!is_left_child(__root)) //root deve essere il figlio di sinistra 
			return false;
		// root must be black
		if (!__root->is_black) //root deve essere nera
			return false;
		// do normal node checks
		return __tree_sub_invariant(__root) != 0;
	}


	// Ritorna: puntatore al nodo piú a sinistra sotto _x
	// Condizione di partenza : _x != nullptr.
	template <class _NodePtr>
	_NodePtr tree_min(_NodePtr __x)
	{
		while (__x->left != nullptr)
			__x = __x->left;
		return __x;
	}

	// Ritorna: puntatore al nodo piú a destra sotto _x
	// Condizione di partenza : _x != nullptr.
	template <class _NodePtr>
	_NodePtr __tree_max(_NodePtr __x)
	{
		while (__x->right != nullptr)
			__x = __x->right;
		return __x;
	}


	// Ritorna: puntatore al prossimo nodo in ordine di grandezza dopo _x.
	// Condizione di partenza : _x != nullptr.
	template <class _NodePtr>
	_NodePtr __tree_next(_NodePtr __x)
	{
		if (__x->right != nullptr)
			return tree_min(__x->right);
		while (!is_left_child(__x))
			__x = __x->parent;
		return __x->parent;
	}

	template <class _NodePtr>
	_NodePtr next_iter(_NodePtr __x)
	{
		if (__x->right != nullptr)
			return static_cast<_NodePtr>(tree_min(__x->right));
		while (!is_left_child(__x))
			__x = __x->parent;
		return static_cast< _NodePtr>(__x->parent);
	}


	// Ritorna: puntatore al nodo piú piccolo prima di _x
	// Condizione di partenza : _x != nullptr.
	// Nota: _x potrebbe essere _root->parent
	template <class _NodePtr, class _EndNodePtr>
	_NodePtr prev_iter(_EndNodePtr __x)
	{
		if (__x->left != nullptr)
			return __tree_max(__x->left);
		_NodePtr __xx = static_cast<_NodePtr>(__x);
		while (is_left_child(__xx))
			__xx = __xx->parent;
		return __xx->parent;
	}

	// Ritorna: puntatore a una foglia
	// Condizione di partenza : _x != nullptr.
	template <class _NodePtr>
	_NodePtr __tree_leaf(_NodePtr __x)
	{
		while (true)
		{
			if (__x->left != nullptr)
			{
				__x = __x->left;
				continue;
			}
			if (__x->right != nullptr)
			{
				__x = __x->right;
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
	left_rotate(_NodePtr __x)
	{
		_NodePtr __y = __x->right;   //crea un nodo y a cui assegna x->right
		__x->right = __y->left;	//x->right diventa il left child di y
		if (__x->right != nullptr)
			__x->right->parent = __x;
		__y->parent = __x->parent;
		if (is_left_child(__x))
			__x->parent->left = __y;
		else
			__x->parent->right = __y;
		__y->left = __x;
		__x->parent = __y;
	}

	// Effetti: rende _x->left la root del subtree con _x come right child, preservando l'ordine
	// Condizione di partenza: x->left != nullptr
	template <class _NodePtr>
	void
	right_rotate(_NodePtr __x)
	{
		_NodePtr __y = __x->left;
		__x->left = __y->right;
		if (__x->left != nullptr)
			__x->left->parent = __x;
		__y->parent = __x->parent;
		if (is_left_child(__x))
			__x->parent->left = __y;
		else
			__x->parent->right = __y;
		__y->right = __x;
		__x->parent = __y;
	}





	// Effetti: Ribilancia la root dopo aver attaccato _x a una foglia.
	// Condizione di partenza: root != nullptr && _x != nullptr
								// _x non ha figli
								//_x é la root o un figlio diretto o indiretto della root
	//                If __x were to be unlinked from __root (setting __root to
	//                  nullptr if __root == __x), __tree_invariant(__root) == true.
	// Postcondition: __tree_invariant(end_node->left) == true.  end_node->left
	//                may be different than the value passed in as __root.
	template <class _NodePtr>
	void
	balance_after_insert(_NodePtr __root, _NodePtr __x)
	{
		__x->is_black = __x == __root; // x é nero se x é la root, altrimenti é rosso (soddisfa la condizione per cui la root é nera, altrimenti inseriamo a prescindere un nodo rosso)
		while (__x != __root && !__x->parent->is_black)// questo é il caso in cui invece non abbiamo inserito la root, e quindi é tutto da bilanciare perché anche il genitore é rosso (non soddisfa la proprietá per cui i rossi devono avere figli neri)
		{
			//std::cout << "Root quando inserisco { " << __x->key.first << " } é -> " << __root->key.first << std::endl;
			// e il genitore non é manco root perché se la root é nera, quindi siamo in un subtree
			if (is_left_child(__x->parent)) // se il genitore é un figlio sinistro
			{
				_NodePtr __y = __x->parent->parent->right; // assegno a y lo zio destro di x
				if (__y != nullptr && !__y->is_black)	//se lo zio destro esiste e é rosso
				{
					__x = __x->parent;
					__x->is_black = true;	// il genitore diventa nero
					__x = __x->parent;
					__x->is_black = __x == __root; //il nonno diventa nero se é la root, altrimenti diventa rosso
					__y->is_black = true;		//anche lo zio diventa nero
				}
				else //se lo zio non esiste e/o é nero
				{
					if (!is_left_child(__x)) //se x é figlio di destra
					{
						__x = __x->parent;
						left_rotate(__x); // rotea e il genitore diventa il figlio di sinistra di x
					}
					__x = __x->parent;
					__x->is_black = true; // il genitore diventa nero
					__x = __x->parent;
					__x->is_black = false; //il nonno diventa rosso
					right_rotate(__x); // il nonno diventa il nuovo fratello in pratica
					break;
				}
			}
			else
			{
				_NodePtr __y = __x->parent->parent->left;
				if (__y != nullptr && !__y->is_black)
				{
					__x = __x->parent;
					__x->is_black = true;
					__x = __x->parent;
					__x->is_black = __x == __root;
					__y->is_black = true;
				}
				else
				{
					if (is_left_child(__x))
					{
						__x = __x->parent;
						right_rotate(__x);
					}
					__x = __x->parent;
					__x->is_black = true;
					__x = __x->parent;
					__x->is_black = false;
					left_rotate(__x);
					break;
				}
			}
		}
	}

	// Precondition:  __root != nullptr && __z != nullptr.
	//                __tree_invariant(__root) == true.
	//                __z == __root or == a direct or indirect child of __root.
	// Effects:  unlinks __z from the tree rooted at __root, rebalancing as needed.
	// Postcondition: __tree_invariant(end_node->left) == true && end_node->left
	//                nor any of its children refer to __z.  end_node->left
	//                may be different than the value passed in as __root.


	template <class _NodePtr>
	void
	__tree_remove(_NodePtr __root, _NodePtr __z)
	{
		// __z will be removed from the tree.  Client still needs to destruct/deallocate it
		// __y is either __z, or if __z has two children, __tree_next(__z).
		// __y will have at most one child.
		// __y will be the initial hole in the tree (make the hole at a leaf)
		_NodePtr __y = (__z->left == nullptr || __z->right == nullptr) ?
						__z : __tree_next(__z);
		// __x is __y's possibly null single child
		_NodePtr __x = __y->left != nullptr ? __y->left : __y->right;
		// __w is __x's possibly null uncle (will become __x's sibling)
		_NodePtr __w = nullptr;
		// link __x to __y's parent, and find __w
		if (__x != nullptr)
			__x->parent = __y->parent;
		if (is_left_child(__y))
		{
			__y->parent->left = __x;
			if (__y != __root)
				__w = __y->parent->right;
			else
				__root = __x;  // __w == nullptr
		}
		else
		{
			__y->parent->right = __x;
			// __y can't be root if it is a right child
			__w = __y->parent->left;
		}
		bool __removed_black = __y->is_black;
		// If we didn't remove __z, do so now by splicing in __y for __z,
		//    but copy __z's color.  This does not impact __x or __w.
		if (__y != __z)
		{
			// __z->left != nulptr but __z->right might == __x == nullptr
			__y->parent = __z->parent;
			if (is_left_child(__z))
				__y->parent->left = __y;
			else
				__y->parent->right = __y;
			__y->left = __z->left;
			__y->left->__set_parent(__y);
			__y->right = __z->right;
			if (__y->right != nullptr)
				__y->right->__set_parent(__y);
			__y->is_black = __z->is_black;
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
			// if (__x == __root || __x != nullptr && !__x->is_black)
			if (__x != nullptr)
				__x->is_black = true;
			else
			{
				//  Else __x isn't root, and is "doubly black", even though it may
				//     be null.  __w can not be null here, else the parent would
				//     see a black height >= 2 on the __x side and a black height
				//     of 1 on the __w side (__w must be a non-null black or a red
				//     with a non-null black child).
				while (true)
				{
					if (!is_left_child(__w))  // if x is left child
					{
						if (!__w->is_black)
						{
							__w->is_black = true;
							__w->parent->is_black = false;
							left_rotate(__w->parent);
							// __x is still valid
							// reset __root only if necessary
							if (__root == __w->left)
								__root = __w;
							// reset sibling, and it still can't be null
							__w = __w->left->right;
						}
						// __w->is_black is now true, __w may have null children
						if ((__w->left  == nullptr || __w->left->is_black) &&
							(__w->right == nullptr || __w->right->is_black))
						{
							__w->is_black = false;
							__x = __w->parent;
							// __x can no longer be null
							if (__x == __root || !__x->is_black)
							{
								__x->is_black = true;
								break;
							}
							// reset sibling, and it still can't be null
							__w = is_left_child(__x) ?
										__x->parent->right :
										__x->parent->left;
							// continue;
						}
						else  // __w has a red child
						{
							if (__w->right == nullptr || __w->right->is_black)
							{
								// __w left child is non-null and red
								__w->left->is_black = true;
								__w->is_black = false;
								right_rotate(__w);
								// __w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								__w = __w->parent;
							}
							// __w has a right red child, left child may be null
							__w->is_black = __w->parent->is_black;
							__w->parent->is_black = true;
							__w->right->is_black = true;
							left_rotate(__w->parent);
							break;
						}
					}
					else
					{
						if (!__w->is_black)
						{
							__w->is_black = true;
							__w->parent->is_black = false;
							right_rotate(__w->parent);
							// __x is still valid
							// reset __root only if necessary
							if (__root == __w->right)
								__root = __w;
							// reset sibling, and it still can't be null
							__w = __w->right->left;
						}
						// __w->is_black is now true, __w may have null children
						if ((__w->left  == nullptr || __w->left->is_black) &&
							(__w->right == nullptr || __w->right->is_black))
						{
							__w->is_black = false;
							__x = __w->parent;
							// __x can no longer be null
							if (!__x->is_black || __x == __root)
							{
								__x->is_black = true;
								break;
							}
							// reset sibling, and it still can't be null
							__w = is_left_child(__x) ?
										__x->parent->right :
										__x->parent->left;
							// continue;
						}
						else  // __w has a red child
						{
							if (__w->left == nullptr || __w->left->is_black)
							{
								// __w right child is non-null and red
								__w->right->is_black = true;
								__w->is_black = false;
								left_rotate(__w);
								// __w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								__w = __w->parent;
							}
							// __w has a left red child, right child may be null
							__w->is_black = __w->parent->is_black;
							__w->parent->is_black = true;
							__w->left->is_black = true;
							right_rotate(__w->parent);
							break;
						}
					}
				}
			}
		}
	}

}//namespace
