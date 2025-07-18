#include "../header/avltree.h"

/*---------------------------------*/
// Rotation
/*---------------------------------*/

void AvlTree::rotate_left(typAvlTreeNode** node) // ����� balFactor�� AVL_LEFT_HEAVY�� ���
{
	typAvlTreeNode* left_subTree, * grandChild;

	left_subTree = (typAvlTreeNode*)this->get_leftPtr(*node);

	if (this->get_balFactor(*node) == AVL_LEFT_HEAVY &&
		this->get_balFactor(left_subTree) == AVL_LEFT_HEAVY)
	{
#ifdef forDebug
		cout << "LL rotation!" << endl;
#endif
		// ����Ʈ���� balFactor�� AVL_LEFT_HEAVY�� ��� (LLȸ��)
		this->set_leftPtr(*node, this->get_rightPtr(left_subTree));			// 1. ����� leftPtr				->		leftSubTree�� rightPtr
		this->set_rightPtr(left_subTree, *node);							// 2. leftSubTree�� rightPtr		->		����� rightPtr

		this->set_balFactor(*node, AVL_BALANCED);							// 3. ���� ���� leftSubTree�� balFactor = AVL_BALANCED
		this->set_balFactor(left_subTree, AVL_BALANCED);

		*node = left_subTree;												// 4. ����� leftSubTree�� ����	=> 		�κ�Ʈ���� root�� ���� leftSubTree
	}
	else
	{
#ifdef forDebug
		cout << "LR rotation!" << endl;
#endif
		// ����Ʈ���� balFactor�� AVL_RIGHT_HEAVY�� ��� (LRȸ��)
		grandChild = (typAvlTreeNode*)this->get_rightPtr(left_subTree);		// grandChild = leftSubTree�� rightPtr (LR ȸ��)

		this->set_rightPtr(left_subTree, this->get_leftPtr(grandChild));	// 1. leftSubTree�� rightPtr		->		grandChild�� leftChild
		this->set_leftPtr(grandChild, left_subTree);						// 2. grandChild�� leftPtr		->		leftSubTree
		this->set_leftPtr(*node, this->get_rightPtr(grandChild));			// 3. ����� leftPtr				->		grandChild�� rightChild
		this->set_rightPtr(grandChild, *node);								// 4. grandChild�� rightPtr		->		���

		switch (this->get_balFactor(grandChild))							// 5. grandChild�� balFactor�� ���� '���'�� 'leftSubTree'�� balFactor�� ����	
		{
		case AVL_LEFT_HEAVY:
			this->set_balFactor(*node, AVL_RIGHT_HEAVY);
			this->set_balFactor(left_subTree, AVL_BALANCED);
			break;

		case AVL_BALANCED:
			this->set_balFactor(*node, AVL_BALANCED);
			this->set_balFactor(left_subTree, AVL_BALANCED);
			break;

		case AVL_RIGHT_HEAVY:
			this->set_balFactor(*node, AVL_BALANCED);
			this->set_balFactor(left_subTree, AVL_LEFT_HEAVY);
			break;

		default:
			break;
		}

		this->set_balFactor(grandChild, AVL_BALANCED);
		*node = grandChild;													// 6. ����� grandChild�� ����		=> 		�κ�Ʈ���� root�� ���� grandChild
	}
	return;
}

void AvlTree::rotate_right(typAvlTreeNode** node) // ����� balFactor�� AVL_RIGHT_HEAVY�� ���
{
	typAvlTreeNode* right_subTree, * grandChild;

	right_subTree = (typAvlTreeNode*)this->get_rightPtr(*node);

	if (this->get_balFactor(*node) == AVL_RIGHT_HEAVY &&
		this->get_balFactor(right_subTree) == AVL_RIGHT_HEAVY)
	{
#ifdef forDebug
		cout << "RR rotation!" << endl;
#endif
		// ����Ʈ���� balFactor�� AVL_RIGHT_HEAVY�� ��� (RRȸ��)
		this->set_rightPtr(*node, this->get_leftPtr(right_subTree));		// 1. ����� rightPtr				->		rightSubTree�� leftPtr
		this->set_leftPtr(right_subTree, *node);							// 2. rightSubTree�� leftPtr		->		����� leftPtr		

		this->set_balFactor(*node, AVL_BALANCED);							// 3. ���� ���� rightSubTree�� balFactor = AVL_BALANCED	
		this->set_balFactor(right_subTree, AVL_BALANCED);

		*node = right_subTree;												// 4. ����� rightSubTree�� ����	=> 		�κ�Ʈ���� root�� ���� rightSubTree
	}
	else
	{
#ifdef forDebug
		cout << "RL rotation!" << endl;
#endif
		grandChild = (typAvlTreeNode*)this->get_leftPtr(right_subTree);	// ����Ʈ���� balFactor�� AVL_LEFT_HEAVY�� ��� (RLȸ��)

		this->set_leftPtr(right_subTree, this->get_rightPtr(grandChild));	// 1. rightSubTree�� leftPtr		->		grandChild�� rightPtr
		this->set_rightPtr(grandChild, right_subTree);						// 2. grandChild�� rightPtr		->		rightSubTree
		this->set_rightPtr(*node, this->get_leftPtr(grandChild));			// 3. ����� rightPtr				->		grandChild�� leftPtr
		this->set_leftPtr(grandChild, *node);								// 4. grandChild�� leftPtr		->		���

		switch (this->get_balFactor(grandChild))							// 5. grandChild�� balFactor�� ���� '���'�� 'rightSubTree'�� balFactor�� ����
		{
		case AVL_LEFT_HEAVY:
			this->set_balFactor(*node, AVL_BALANCED);
			this->set_balFactor(right_subTree, AVL_RIGHT_HEAVY);
			break;

		case AVL_BALANCED:
			this->set_balFactor(*node, AVL_BALANCED);
			this->set_balFactor(right_subTree, AVL_BALANCED);
			break;

		case AVL_RIGHT_HEAVY:
			this->set_balFactor(*node, AVL_LEFT_HEAVY);
			this->set_balFactor(right_subTree, AVL_BALANCED);
			break;

		default:
			break;
		}

		this->set_balFactor(grandChild, AVL_BALANCED);
		*node = grandChild;													// 6. ����� grandChild�� ����		=> 		�κ�Ʈ���� root�� ���� grandChild
	}
	return;
}

/*---------------------------------*/
// Destroy
/*---------------------------------*/

void AvlTree::destroy_left(typAvlTreeNode* node)
{
	typAvlTreeNode** position = nullptr;

	if (this->get_Size() == 0)
	{
		return;
	}

	if (node == nullptr)
		position = &this->AvlTreeRoot;
	else
		position = (typAvlTreeNode**)&(((typBiTreeNode*)node)->left); // ������ ��� : node�� leftPtr -> �����ͺ����� �ּ�ȹ��

	if (*position != nullptr)
	{
		this->remove_left(*position);
		this->remove_right(*position);

		if (this->destroyDataFunc != nullptr)
		{
			this->destroyDataFunc((*position)->data); // ����� ���� data ���� �Լ� ȣ��

			this->deleteNode((void**)position);
		}
		else
		{
			this->errCode = SYS_FAULT;
		}
	}
	return;
}

void AvlTree::destroy_right(typAvlTreeNode* node)
{
	typAvlTreeNode** position = nullptr;
	if (this->get_Size() == 0)
	{
		return;
	}

	if (node == nullptr)
		position = &this->AvlTreeRoot;
	else
		position = (typAvlTreeNode**)&(((typBiTreeNode*)node)->right); // ������ ��� : node�� rightPtr -> �����ͺ����� �ּ�ȹ��

	if (*position != nullptr)
	{
		this->remove_left(*position);
		this->remove_right(*position);
		if (this->destroyDataFunc != nullptr)
		{
			this->destroyDataFunc((*position)->data); // ����� ���� data ���� �Լ� ȣ��

			this->deleteNode((void**)position);
		}
		else
		{
			this->errCode = SYS_FAULT;
		}
	}
	return;
}

int AvlTree::recursive_insert(typAvlTreeNode** node, const void* data, typBalancedFlag* balanced)
{
	// Ʈ���� root�ּҸ� �޴� ������ root ���� �����ؼ� ��尡 ������ ��ġ���� �������� �̵��ϱ� ����
	typAvlTreeNode* newNode = nullptr, ** tempNode = nullptr;
	typCmpResult cmpResult = EQUAL;
	int retVal = 0;

	if (this->is_emptyNode(*node))															// 1. Ʈ���� ����ְų�, ���� ��忡 ������ ���
	{
		if (retVal = this->insert_left(*node, data) == INSERT_SUCCESS)						// 2. Ʈ���� �ڷ����
			this->availableNodeCnt++; // ���ٰ����� ��� �� ����

		return retVal;
	}
	else																					// 1-1. Ʈ���� ������� ���� ���
	{
		cmpResult = this->compareFunc(data, (*node)->data);									// 2. data�� ���� ����� data�� ��

		if (cmpResult == LESS)																//-----data < ���� ����� data �� ��� (LeftChild�� �����ʿ�)
		{
			if (this->is_emptyNode(this->get_leftPtr(*node)))								// 3. ���� ����� leftPtr�� ����ִٸ� �ش���ġ�� �ڷ����
			{
				if (this->insert_left(*node, data) != INSERT_SUCCESS)
					return INSERT_FAILED;
				else
				{
					*balanced = AVLNODE_UNBALANCED;											// 4. ���� �� Ʈ���� ����ȭ�� �ʿ��ϴٰ� �˸�
					this->availableNodeCnt++; // ���ٰ����� ��� �� ����
				}
			}
			else																			// 3-1. ���� ����� leftPtr�� ������� �ʴٸ�
			{
				tempNode = (typAvlTreeNode**)&(((typBiTreeNode*)(*node))->left);
				retVal = this->recursive_insert(tempNode, data, balanced);					// 4. ���� ����� leftPtr�� ��������� Ž���Ͽ� data ����

				if (retVal != INSERT_SUCCESS)
					return retVal;
			}

			if (*balanced == AVLNODE_UNBALANCED)											 // 5. ���� �� Ʈ���� ����ȭ�� �ʿ��� ��常 ��� ����ȭ �۾� ����
			{
				switch (this->get_balFactor(*node))
				{
				case AVL_LEFT_HEAVY:
					this->rotate_left(node);
					*balanced = AVLNODE_BALANCED;
					break;

				case AVL_BALANCED:
					this->set_balFactor(*node, AVL_LEFT_HEAVY);
					*balanced = AVLNODE_UNBALANCED;
					break;

				case AVL_RIGHT_HEAVY:
					this->set_balFactor(*node, AVL_BALANCED);
					*balanced = AVLNODE_BALANCED;
					break;

				default:
					break;
				}
			}
		} // End of cmpResult = LESS

		else if (cmpResult == GREATER) 														//-----data > ���� ����� data �� ��� (RightChild�� �����ʿ�)
		{
			if (this->is_emptyNode(this->get_rightPtr(*node)))								// 3. ���� ����� rightPtr�� ����ִٸ� �ش���ġ�� �ڷ����
			{
				if (this->insert_right(*node, data) != INSERT_SUCCESS)
					return INSERT_FAILED;
				else
				{
					*balanced = AVLNODE_UNBALANCED;											// 4. ���� �� Ʈ���� ����ȭ�� �ʿ��ϴٰ� �˸�
					this->availableNodeCnt++; // ���ٰ����� ��� �� ����
				}
			}
			else 																			// 3-1. ���� ����� rightPtr�� ������� �ʴٸ�
			{
				tempNode = (typAvlTreeNode**)&(((typBiTreeNode*)(*node))->right);
				retVal = this->recursive_insert(tempNode, data, balanced);					// 4. ���� ����� leftPtr�� ��������� Ž���Ͽ� data ����

				if (retVal != INSERT_SUCCESS)
					return retVal;
			}

			if (*balanced == AVLNODE_UNBALANCED)											 // 5. ���� �� Ʈ���� ����ȭ�� �ʿ��� ��常 ��� ����ȭ �۾� ����
			{
				switch (this->get_balFactor(*node))
				{
				case AVL_LEFT_HEAVY:
					this->set_balFactor(*node, AVL_BALANCED);
					*balanced = AVLNODE_BALANCED;
					break;

				case AVL_BALANCED:
					this->set_balFactor(*node, AVL_RIGHT_HEAVY);
					break;

				case AVL_RIGHT_HEAVY:
					rotate_right(node);
					*balanced = AVLNODE_BALANCED;
					break;

				default:
					break;
				}
			}
		} // End of cmpResult = GREATER

		else if (cmpResult == EQUAL)														//-----data == ���� ����� data �� ���
		{
			if (this->get_hiddenFlag(*node) == NODE_AVAILABLE)								// 3. �����尡 �̹� �ִٸ� �ߺ����� �������� ���� ����
			{
				return INSERT_FAILED; // �̹� �����ϴ� ���
			}
			else																			// 3-1. �����尡 ������ ����� ��������� ������ ������Ʈ �ʿ�
			{
				if (this->destroyDataFunc != nullptr)
				{
					this->destroyDataFunc((*node)->data);									// 4. ��尡 ����Ű�� ������ ����

					this->set_hiddenFlag(*node, NODE_AVAILABLE);							// 5. ����ʱ�ȭ ��������
					this->set_data(*node, (void*)data);
					*balanced = AVLNODE_BALANCED;
					this->availableNodeCnt++; // ���ٰ����� ��� �� ����
				}
				else
				{
					this->errCode = SYS_FAULT;
					return INSERT_FAILED; // ������ �ı� �Լ��� ���� ��
				}
			}
		} // End of cmpResult = EQUAL
	}

	return INSERT_SUCCESS;
}

/*---------------------------------*/
// Hide
/*---------------------------------*/

bool AvlTree::recursive_hide(typAvlTreeNode* node, const void* data)
{
	typCmpResult cmpResult = EQUAL;
	typAvlTreeNode* tempPtr = nullptr;
	bool retFlag = false;

	if (this->is_emptyNode(node))															// 1. Ʈ���� ����ְų�, ���� ��忡 ������ ���
	{
		return retFlag;
	}
	else																					// 1-1. Ʈ���� ������� ���� ���
	{
		cmpResult = this->compareFunc(data, this->get_data(node));							// 2. data�� ���� ����� data�� ��

		if (cmpResult == LESS)																//-----data < ���� ����� data �� ��� (LeftChild�� Ž���ʿ�)
		{
			tempPtr = (typAvlTreeNode*)this->get_leftPtr(node);								// 3. ���� ����� leftPtr�� ������ �Լ� ���ȣ��
			retFlag = this->recursive_hide(tempPtr, data);
		}

		else if (cmpResult == GREATER)														//-----data > ���� ����� data �� ��� (RightChild�� Ž���ʿ�)
		{
			tempPtr = (typAvlTreeNode*)this->get_rightPtr(node);							// 3. ���� ����� rightPtr�� ������ �Լ� ���ȣ��
			retFlag = this->recursive_hide(tempPtr, data);
		}

		else                                                                                //-----data == ���� ����� data �� ���
		{
			if (this->get_hiddenFlag(node) == NODE_AVAILABLE)								// 3. �����尡 �������� ���� �����
			{
				this->set_hiddenFlag(node, NODE_HIDDEN);									// 4. �����带 ����ó��
				retFlag = true;
				this->availableNodeCnt--; // ���ٰ����� ��� �� ����
			}
			else
			{
				retFlag = false; // �̹� ������ ���
			}
		}

		return retFlag;
	}
}
bool AvlTree::recursive_lookup(typAvlTreeNode* node, void** data)
{
	typCmpResult cmpResult = EQUAL;
	typAvlTreeNode* tempPtr = nullptr;
	bool retFlag = false;

	if (this->is_emptyNode(node))
	{
		return retFlag;
	}
	else
	{
		cmpResult = this->compareFunc(*data, this->get_data(node));

		if (cmpResult == LESS)
		{
			tempPtr = (typAvlTreeNode*)this->get_leftPtr(node);
			retFlag = this->recursive_lookup(tempPtr, data);
		}
		else if (cmpResult == GREATER)
		{
			tempPtr = (typAvlTreeNode*)this->get_rightPtr(node);
			retFlag = this->recursive_lookup(tempPtr, data);
		}
		else
		{
			if (this->get_hiddenFlag(node) == NODE_AVAILABLE)
			{
				*data = this->get_data(node);
				retFlag = true;
			}
			else
			{
				retFlag = false;
			}
		}
		return retFlag;
	}
}