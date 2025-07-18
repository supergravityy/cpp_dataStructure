#include "../header/avltree.h"

/*---------------------------------*/
// Rotation
/*---------------------------------*/

void AvlTree::rotate_left(typAvlTreeNode** node) // 대상의 balFactor가 AVL_LEFT_HEAVY인 경우
{
	typAvlTreeNode* left_subTree, * grandChild;

	left_subTree = (typAvlTreeNode*)this->get_leftPtr(*node);

	if (this->get_balFactor(*node) == AVL_LEFT_HEAVY &&
		this->get_balFactor(left_subTree) == AVL_LEFT_HEAVY)
	{
#ifdef forDebug
		cout << "LL rotation!" << endl;
#endif
		// 서브트리의 balFactor가 AVL_LEFT_HEAVY인 경우 (LL회전)
		this->set_leftPtr(*node, this->get_rightPtr(left_subTree));			// 1. 대상의 leftPtr				->		leftSubTree의 rightPtr
		this->set_rightPtr(left_subTree, *node);							// 2. leftSubTree의 rightPtr		->		대상의 rightPtr

		this->set_balFactor(*node, AVL_BALANCED);							// 3. 대상과 이전 leftSubTree의 balFactor = AVL_BALANCED
		this->set_balFactor(left_subTree, AVL_BALANCED);

		*node = left_subTree;												// 4. 대상을 leftSubTree로 변경	=> 		부분트리의 root가 이제 leftSubTree
	}
	else
	{
#ifdef forDebug
		cout << "LR rotation!" << endl;
#endif
		// 서브트리의 balFactor가 AVL_RIGHT_HEAVY인 경우 (LR회전)
		grandChild = (typAvlTreeNode*)this->get_rightPtr(left_subTree);		// grandChild = leftSubTree의 rightPtr (LR 회전)

		this->set_rightPtr(left_subTree, this->get_leftPtr(grandChild));	// 1. leftSubTree의 rightPtr		->		grandChild의 leftChild
		this->set_leftPtr(grandChild, left_subTree);						// 2. grandChild의 leftPtr		->		leftSubTree
		this->set_leftPtr(*node, this->get_rightPtr(grandChild));			// 3. 대상의 leftPtr				->		grandChild의 rightChild
		this->set_rightPtr(grandChild, *node);								// 4. grandChild의 rightPtr		->		대상

		switch (this->get_balFactor(grandChild))							// 5. grandChild의 balFactor에 따라 '대상'과 'leftSubTree'의 balFactor를 결정	
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
		*node = grandChild;													// 6. 대상을 grandChild로 변경		=> 		부분트리의 root가 이제 grandChild
	}
	return;
}

void AvlTree::rotate_right(typAvlTreeNode** node) // 대상의 balFactor가 AVL_RIGHT_HEAVY인 경우
{
	typAvlTreeNode* right_subTree, * grandChild;

	right_subTree = (typAvlTreeNode*)this->get_rightPtr(*node);

	if (this->get_balFactor(*node) == AVL_RIGHT_HEAVY &&
		this->get_balFactor(right_subTree) == AVL_RIGHT_HEAVY)
	{
#ifdef forDebug
		cout << "RR rotation!" << endl;
#endif
		// 서브트리의 balFactor가 AVL_RIGHT_HEAVY인 경우 (RR회전)
		this->set_rightPtr(*node, this->get_leftPtr(right_subTree));		// 1. 대상의 rightPtr				->		rightSubTree의 leftPtr
		this->set_leftPtr(right_subTree, *node);							// 2. rightSubTree의 leftPtr		->		대상의 leftPtr		

		this->set_balFactor(*node, AVL_BALANCED);							// 3. 대상과 이전 rightSubTree의 balFactor = AVL_BALANCED	
		this->set_balFactor(right_subTree, AVL_BALANCED);

		*node = right_subTree;												// 4. 대상을 rightSubTree로 변경	=> 		부분트리의 root가 이제 rightSubTree
	}
	else
	{
#ifdef forDebug
		cout << "RL rotation!" << endl;
#endif
		grandChild = (typAvlTreeNode*)this->get_leftPtr(right_subTree);	// 서브트리의 balFactor가 AVL_LEFT_HEAVY인 경우 (RL회전)

		this->set_leftPtr(right_subTree, this->get_rightPtr(grandChild));	// 1. rightSubTree의 leftPtr		->		grandChild의 rightPtr
		this->set_rightPtr(grandChild, right_subTree);						// 2. grandChild의 rightPtr		->		rightSubTree
		this->set_rightPtr(*node, this->get_leftPtr(grandChild));			// 3. 대상의 rightPtr				->		grandChild의 leftPtr
		this->set_leftPtr(grandChild, *node);								// 4. grandChild의 leftPtr		->		대상

		switch (this->get_balFactor(grandChild))							// 5. grandChild의 balFactor에 따라 '대상'과 'rightSubTree'의 balFactor를 결정
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
		*node = grandChild;													// 6. 대상을 grandChild로 변경		=> 		부분트리의 root가 이제 grandChild
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
		position = (typAvlTreeNode**)&(((typBiTreeNode*)node)->left); // 삭제할 대상 : node의 leftPtr -> 포인터변수의 주소획득

	if (*position != nullptr)
	{
		this->remove_left(*position);
		this->remove_right(*position);

		if (this->destroyDataFunc != nullptr)
		{
			this->destroyDataFunc((*position)->data); // 사용자 정의 data 해제 함수 호출

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
		position = (typAvlTreeNode**)&(((typBiTreeNode*)node)->right); // 삭제할 대상 : node의 rightPtr -> 포인터변수의 주소획득

	if (*position != nullptr)
	{
		this->remove_left(*position);
		this->remove_right(*position);
		if (this->destroyDataFunc != nullptr)
		{
			this->destroyDataFunc((*position)->data); // 사용자 정의 data 해제 함수 호출

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
	// 트리의 root주소를 받는 이유는 root 부터 시작해서 노드가 정해진 위치까지 말단으로 이동하기 위함
	typAvlTreeNode* newNode = nullptr, ** tempNode = nullptr;
	typCmpResult cmpResult = EQUAL;
	int retVal = 0;

	if (this->is_emptyNode(*node))															// 1. 트리가 비어있거나, 말단 노드에 도달한 경우
	{
		if (retVal = this->insert_left(*node, data) == INSERT_SUCCESS)						// 2. 트리에 자료삽입
			this->availableNodeCnt++; // 접근가능한 노드 수 증가

		return retVal;
	}
	else																					// 1-1. 트리가 비어있지 않은 경우
	{
		cmpResult = this->compareFunc(data, (*node)->data);									// 2. data와 현재 노드의 data를 비교

		if (cmpResult == LESS)																//-----data < 현재 노드의 data 인 경우 (LeftChild로 삽입필요)
		{
			if (this->is_emptyNode(this->get_leftPtr(*node)))								// 3. 현재 노드의 leftPtr이 비어있다면 해당위치에 자료삽입
			{
				if (this->insert_left(*node, data) != INSERT_SUCCESS)
					return INSERT_FAILED;
				else
				{
					*balanced = AVLNODE_UNBALANCED;											// 4. 삽입 후 트리의 평형화가 필요하다고 알림
					this->availableNodeCnt++; // 접근가능한 노드 수 증가
				}
			}
			else																			// 3-1. 현재 노드의 leftPtr이 비어있지 않다면
			{
				tempNode = (typAvlTreeNode**)&(((typBiTreeNode*)(*node))->left);
				retVal = this->recursive_insert(tempNode, data, balanced);					// 4. 현재 노드의 leftPtr을 재귀적으로 탐색하여 data 삽입

				if (retVal != INSERT_SUCCESS)
					return retVal;
			}

			if (*balanced == AVLNODE_UNBALANCED)											 // 5. 삽입 후 트리의 평형화가 필요한 노드만 골라 평형화 작업 수행
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

		else if (cmpResult == GREATER) 														//-----data > 현재 노드의 data 인 경우 (RightChild로 삽입필요)
		{
			if (this->is_emptyNode(this->get_rightPtr(*node)))								// 3. 현재 노드의 rightPtr이 비어있다면 해당위치에 자료삽입
			{
				if (this->insert_right(*node, data) != INSERT_SUCCESS)
					return INSERT_FAILED;
				else
				{
					*balanced = AVLNODE_UNBALANCED;											// 4. 삽입 후 트리의 평형화가 필요하다고 알림
					this->availableNodeCnt++; // 접근가능한 노드 수 증가
				}
			}
			else 																			// 3-1. 현재 노드의 rightPtr이 비어있지 않다면
			{
				tempNode = (typAvlTreeNode**)&(((typBiTreeNode*)(*node))->right);
				retVal = this->recursive_insert(tempNode, data, balanced);					// 4. 현재 노드의 leftPtr을 재귀적으로 탐색하여 data 삽입

				if (retVal != INSERT_SUCCESS)
					return retVal;
			}

			if (*balanced == AVLNODE_UNBALANCED)											 // 5. 삽입 후 트리의 평형화가 필요한 노드만 골라 평형화 작업 수행
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

		else if (cmpResult == EQUAL)														//-----data == 현재 노드의 data 인 경우
		{
			if (this->get_hiddenFlag(*node) == NODE_AVAILABLE)								// 3. 현재노드가 이미 있다면 중복방지 차원에서 삽입 생략
			{
				return INSERT_FAILED; // 이미 존재하는 노드
			}
			else																			// 3-1. 현재노드가 숨겨진 노드라면 기존노드의 데이터 업데이트 필요
			{
				if (this->destroyDataFunc != nullptr)
				{
					this->destroyDataFunc((*node)->data);									// 4. 노드가 가리키는 데이터 삭제

					this->set_hiddenFlag(*node, NODE_AVAILABLE);							// 5. 노드초기화 과정진행
					this->set_data(*node, (void*)data);
					*balanced = AVLNODE_BALANCED;
					this->availableNodeCnt++; // 접근가능한 노드 수 증가
				}
				else
				{
					this->errCode = SYS_FAULT;
					return INSERT_FAILED; // 데이터 파괴 함수가 없을 때
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

	if (this->is_emptyNode(node))															// 1. 트리가 비어있거나, 말단 노드에 도달한 경우
	{
		return retFlag;
	}
	else																					// 1-1. 트리가 비어있지 않은 경우
	{
		cmpResult = this->compareFunc(data, this->get_data(node));							// 2. data와 현재 노드의 data를 비교

		if (cmpResult == LESS)																//-----data < 현재 노드의 data 인 경우 (LeftChild로 탐색필요)
		{
			tempPtr = (typAvlTreeNode*)this->get_leftPtr(node);								// 3. 현재 노드의 leftPtr을 가져와 함수 재귀호출
			retFlag = this->recursive_hide(tempPtr, data);
		}

		else if (cmpResult == GREATER)														//-----data > 현재 노드의 data 인 경우 (RightChild로 탐색필요)
		{
			tempPtr = (typAvlTreeNode*)this->get_rightPtr(node);							// 3. 현재 노드의 rightPtr을 가져와 함수 재귀호출
			retFlag = this->recursive_hide(tempPtr, data);
		}

		else                                                                                //-----data == 현재 노드의 data 인 경우
		{
			if (this->get_hiddenFlag(node) == NODE_AVAILABLE)								// 3. 현재노드가 숨겨지지 않은 노드라면
			{
				this->set_hiddenFlag(node, NODE_HIDDEN);									// 4. 현재노드를 숨김처리
				retFlag = true;
				this->availableNodeCnt--; // 접근가능한 노드 수 감소
			}
			else
			{
				retFlag = false; // 이미 숨겨진 노드
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