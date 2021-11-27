#pragma once

#include <iostream>


	/******************************* ALGORITMO DELL'ALBERO *******************************/

namespace ft
{

	template <class NodePtr>
	bool
	is_left_child(NodePtr x)
	{
		if (x->parent == nullptr || x == x->parent->left || (x->parent->left == nullptr && x != x->parent->right && x->parent->right != nullptr) )
			return true;
		return false;
	}

	template <class NodePtr>
	NodePtr tree_min(NodePtr x)
	{
		while (x->left != nullptr)
			x = x->left;
		return x;
	}

	template <class NodePtr>
	NodePtr tree_max(NodePtr x)
	{
		while (x->right != nullptr)
			x = x->right;
		return x;
	}

	template <class NodePtr>
	NodePtr next_iter(NodePtr x)
	{
		if (x->right != nullptr)
			return tree_min(x->right);
		while (!is_left_child(x))
			x = x->parent;
		return static_cast< NodePtr>(x->parent);
	}

	template <class NodePtr>
	NodePtr prev_iter(NodePtr x)
	{
		if (x->left != nullptr)
			return tree_max(x->left);
		while (x->parent != nullptr && is_left_child(x))
			x = x->parent;
		if (x->parent == nullptr)
			return x;
		return x->parent;
	}

	template <class NodePtr>
	void
	left_rotate(NodePtr x)
	{
		NodePtr y = x->right;   //crea un nodo y a cui assegna x->right
		x->right = y->left;	//x->right diventa il left child di y
		if (x->right != nullptr)
			x->right->parent = x;
		y->parent = x->parent;
		if (is_left_child(x))
		{
			if (x->parent != nullptr)
				x->parent->left = y;
		}
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	template <class NodePtr>
	void
	right_rotate(NodePtr x)
	{
		NodePtr y = x->left;
		x->left = y->right;
		if (x->left != nullptr)
			x->left->parent = x;
		y->parent = x->parent;
		if (is_left_child(x))
		{
			if (x->parent != nullptr)
				x->parent->left = y;
		}
		else
			x->parent->right = y;
		y->right = x;
		x->parent = y;
	}

	template <class NodePtr>
	void
	balance_after_insert(NodePtr root, NodePtr x)
	{
		x->is_black = x == root; // x é nero se x é la root, altrimenti é rosso (soddisfa la condizione per cui la root é nera, altrimenti inseriamo a prescindere un nodo rosso)
		while (x != root && !x->parent->is_black)// questo é il caso in cui invece non abbiamo inserito la root, e quindi é tutto da bilanciare perché anche il genitore é rosso (non soddisfa la proprietá per cui i rossi devono avere figli neri)
		{
			// e il genitore non é manco root perché se la root é nera, quindi siamo in un subtree
			if (is_left_child(x->parent)) // se il genitore é un figlio sinistro
			{
				NodePtr y = x->parent->parent->right; // assegno a y lo zio destro di x
				if (y != nullptr && !y->is_black)	//se lo zio destro esiste e é rosso
				{
					x = x->parent;
					x->is_black = true;	// il genitore diventa nero
					x = x->parent;
					x->is_black = x == root; //il nonno diventa nero se é la root, altrimenti diventa rosso
					y->is_black = true;		//anche lo zio diventa nero
				}
				else //se lo zio non esiste e/o é nero
				{
					if (!is_left_child(x)) //se x é figlio di destra
					{
						x = x->parent;
						left_rotate(x); // rotea e il genitore diventa il figlio di sinistra di x
					}
					x = x->parent;
					x->is_black = true; // il genitore diventa nero
					x = x->parent;
					x->is_black = false; //il nonno diventa rosso
					right_rotate(x); // il nonno diventa il nuovo fratello in pratica
					break;
				}
			}
			else
			{
				NodePtr y = x->parent->parent->left;
				if (y != nullptr && !y->is_black)
				{
					x = x->parent;
					x->is_black = true;
					x = x->parent;
					x->is_black = x == root;
					y->is_black = true;
				}
				else
				{
					if (is_left_child(x))
					{
						x = x->parent;
						right_rotate(x);
					}
					x = x->parent;
					x->is_black = true;
					x = x->parent;
					x->is_black = false;
					left_rotate(x);
					break;
				}
			}
		}
	}

	template <class NodePtr>
	void
	tree_remove(NodePtr root, NodePtr z)
	{
		//Z sará rimosso dall'albero. Y sará o Z, o se Z ha due figli, sará quello piú grande,
		//Y avrá quindi massimo un figlio.
		NodePtr y = (z->left == nullptr ||  z->right == nullptr || (z->right->is_end)) ? 			//se il nodo che stiamo togliendo non ha figli, y = nodo, altrimenti y = nodo piú grande
						z : next_iter(z);
		// x é forse il figlio null di y
		NodePtr x = y->left != nullptr ? y->left : y->right;				//se y ha figlio di sinistra, x diventa quello, se no diventa quello di destra
		if (x != nullptr && x->is_end)
			x = nullptr;
		// w sará forse lo zio null di _x, che diventerá fratello di _x
		NodePtr w = nullptr;
		// _x prenderá il genitore di y, e trova w
		if (x != nullptr)
			x->parent = y->parent;
		if (is_left_child(y)) // se y é figlio di sinistra
		{
			if (root != y)
				y->parent->left = x; //x diventa figlio di sinistra del genitore di y
			if (y != root)		//se y non é root
				w = y->parent->right;	//w diventa il fratello di y
			else
				root = x;  // w == nullptr
		}
		else	//se y é figlio di sinistra
		{
			y->parent->right = x;
			// y can't be root if it is a right child
			w = y->parent->left;
		}
		bool removed_black = y->is_black;
		// If we didn't remove z, do so now by splicing in y for z,
		//    but copy z's color.  This does not impact x or w.
		if (y != z)
		{
			// z->left != nulptr but z->right might == x == nullptr
			y->parent = z->parent;
			if (is_left_child(z))
			{
				if (root == z)
					root = y;
				else
					y->parent->left = y;
			}
			else
				y->parent->right = y;
			y->left = z->left;
			y->left->parent = y;
			y->right = z->right;
			if (y->right != nullptr)
				y->right->parent = y;
			y->is_black = z->is_black;
		}
		// There is no need to rebalance if we removed a red, or if we removed
		//     the last node.
		if (removed_black && root != nullptr)
		{
			// Rebalance:
			// x has an implicit black color (transferred from the removed y)
			//    associated with it, no matter what its color is.
			// If x is root (in which case it can't be null), it is supposed
			//    to be black anyway, and if it is doubly black, then the double
			//    can just be ignored.
			// If x is red (in which case it can't be null), then it can absorb
			//    the implicit black just by setting its color to black.
			// Since y was black and only had one child (which x points to), x
			//   is either red with no children, else null, otherwise y would have
			//   different black heights under left and right pointers.
			// if (x == root || x != nullptr && !x->is_black)
			if (x != nullptr)
				x->is_black = true;
			else
			{
				//  Else x isn't root, and is "doubly black", even though it may
				//     be null.  w can not be null here, else the parent would
				//     see a black height >= 2 on the x side and a black height
				//     of 1 on the w side (w must be a non-null black or a red
				//     with a non-null black child).
				while (true)
				{
					if (!is_left_child(w))  // if x is left child
					{
						if (!w->is_black)
						{
							w->is_black = true;
							w->parent->is_black = false;
							left_rotate(w->parent);
							// x is still valid
							// reset root only if necessary
							if (root == w->left)
								root = w;
							// reset sibling, and it still can't be null
							w = w->left->right;
						}
						// w->is_black is now true, w may have null children
						if ((w->left  == nullptr || w->left->is_black) && (w->right == nullptr || w->right->is_black))
						{
							w->is_black = false;
							x = w->parent;
							// x can no longer be null
							if (x == root || !x->is_black)
							{
								x->is_black = true;
								break;
							}
							// reset sibling, and it still can't be null
							w = is_left_child(x) ?
										x->parent->right :
										x->parent->left;
							// continue;
						}
						else  // w has a red child
						{
							if (w->right == nullptr || w->right->is_black)
							{
								// w left child is non-null and red
								w->left->is_black = true;
								w->is_black = false;
								right_rotate(w);
								// w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								w = w->parent;
							}
							// w has a right red child, left child may be null
							w->is_black = w->parent->is_black;
							w->parent->is_black = true;
							w->right->is_black = true;
							left_rotate(w->parent);
							break;
						}
					}
					else
					{
						if (!w->is_black)
						{
							w->is_black = true;
							w->parent->is_black = false;
							right_rotate(w->parent);
							// x is still valid
							// reset root only if necessary
							if (root == w->right)
								root = w;
							// reset sibling, and it still can't be null
							w = w->right->left;
						}
						// w->is_black is now true, w may have null children
						if ((w->left  == nullptr || w->left->is_black) &&
							(w->right == nullptr || w->right->is_black))
						{
							w->is_black = false;
							x = w->parent;
							// x can no longer be null
							if (!x->is_black || x == root)
							{
								x->is_black = true;
								break;
							}
							// reset sibling, and it still can't be null
							w = is_left_child(x) ?
										x->parent->right :
										x->parent->left;
							// continue;
						}
						else  // w has a red child
						{
							if (w->left == nullptr || w->left->is_black)
							{
								// w right child is non-null and red
								w->right->is_black = true;
								w->is_black = false;
								left_rotate(w);
								// w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								w = w->parent;
							}
							// w has a left red child, right child may be null
							w->is_black = w->parent->is_black;
							w->parent->is_black = true;
							w->left->is_black = true;
							right_rotate(w->parent);
							break;
						}
					}
				}
			}
		}
	}

}//namespace
