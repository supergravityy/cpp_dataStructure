#include "../header/bitree.h"

int BiTree::insert_leftChild(void* node, const void* data)
{
	return this->insert_left(node, data);
}

int BiTree::insert_rightChild(void* node, const void* data)
{
	return this->insert_right(node, data);
}

bool BiTree::remove_leftChild(void* node)
{
	return this->remove_left(node);
}

bool BiTree::remove_rightChild(void* node)
{
	return this->remove_right(node);
}

bool BiTree::mergeTree(void* leftTree, void* rightTree, void* data)
{
	return this->merge(leftTree, rightTree, data);
}

int BiTree::insert_left(void* node, const void* data)
{
	typBiTreeNode* newNode = nullptr, 
		* targetNode = (typBiTreeNode*)node,
		** position = nullptr;	// -> 포인터변수의 주소를 받아, 포인터변수에 값(주소)을 대입함

	if (targetNode == nullptr)							// 1. 대상 노드가 null 이면, root 업데이트
	{
		if (this->treeSize == 0)						// 2. 혹시라도 실수로 대상노드를 nullptr로 보냈는지 확인
			position = &this->BiTreeRoot;				// 3. 인스턴스의 root 변수를 업데이트 할 것임 (대상확보)
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else												// 1-1. 대상 노드가 실제 존재하는 노드
	{
		if (!this->is_emptyNode(targetNode->left))		// 2. 대상노드의 leftChild가 null인지 확인
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = &targetNode->left;				// 3. 노드의 왼쪽자식 포인터 변수를 업데이트 할 것임 (대상확보)
	}

	this->makeNode((void**)&newNode);
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);			// 4. 새 노드 생성
		*position = newNode;							// 5. 확보된 대상의 주소에 새로 할당한 노드 주소대입
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

int BiTree::insert_right(void* node, const void* data)
{
	typBiTreeNode* newNode = nullptr, * targetNode = (typBiTreeNode*)node,
		** position = nullptr;

	if (targetNode == nullptr)
	{
		if (this->treeSize == 0)
			position = &this->BiTreeRoot;
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else
	{
		if (!this->is_emptyNode(targetNode->right))
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = &targetNode->right;
	}

	this->makeNode((void**)&newNode);
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);
		*position = newNode;
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

bool BiTree::remove_left(void* node)
{
	typBiTreeNode** target = nullptr, * targetNode = (typBiTreeNode*)node;
	bool result = false;

	if (this->treeSize == 0)					// 1. 빈 트리인지 확인
		return result;
	else										// 1-1. 빈 트리가 아닐 경우
	{
		if (this->is_emptyNode(targetNode))		// 2. 대상노드가 빈 노드인지 확인 -> 삭제기준노드는 이제 root 
			target = &this->BiTreeRoot;
		else
			target = &targetNode->left;			// 2-1. 삭제 기준노드는 이제, 인자로 받은 노드의 leftChild
	}

	if (!this->is_emptyNode(*target))
	{
		this->remove_left(*target);				// 3. 재귀적으로 하위 트리를 전부 삭제함
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

		result = true;
	}
	return result;
}

bool BiTree::remove_right(void* node)
{
	typBiTreeNode** target = nullptr, * targetNode = (typBiTreeNode*)node;
	bool result = false;

	if (this->treeSize == 0)
		return result;
	else
	{
		if (targetNode == nullptr)
			target = &this->BiTreeRoot;
		else
			target = &targetNode->right;
	}

	if (!this->is_emptyNode(*target))
	{
		this->remove_left(*target);
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

		result = true;
	}
	return result;
}

bool BiTree::merge(void* leftTree, void* rightTree, void* data)
{
	BiTree* left = (BiTree*)leftTree, * right = (BiTree*)rightTree;
	typBiTreeNode* tempNode = nullptr;

	// 1. root 삽입
	if (this->insert_left(nullptr, data) != 0)
	{
		this->init(this->compareFunc, this->printTreeFunc, this->destroyDataFunc, this->traverseFunc);
		return false;
	}

	// 2. 새 트리의 루트의 자식노드로 두 트리를 삽입
	else
	{
		tempNode = this->get_BiTreeRoot();
		this->set_leftPtr(tempNode, left->get_BiTreeRoot());
		this->set_rightPtr(tempNode, right->get_BiTreeRoot());

		// 3. 세 트리의 크기 업데이트
		this->treeSize += left->get_Size() + right->get_Size();

		// 4. 인자로 받은 두 트리의 멤버정보를 손상시켜 사용을 막음
		left->BiTreeRoot = nullptr;
		left->treeSize = 0;
		right->BiTreeRoot = nullptr;
		right->treeSize = 0;

		return true;
	}
}

void* BiTree::lookup(void** saveData)
{
	if (this->traverseFunc == nullptr)
	{
		this->errCode = SYS_FAULT;
		return nullptr;
	}
	else
		return this->traverseFunc(this->get_BiTreeRoot(), saveData);
}

