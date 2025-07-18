#include "../header/avltree.h"

/*------------------------------------------*/
// Public (for User)
/*------------------------------------------*/

void AvlTree::printAll()
{
	if (this->printTreeFunc == nullptr)
		this->errCode = SYS_FAULT;
	else
		this->printTreeFunc(this->get_AvlTreeRoot());
}

int AvlTree::get_Count()
{
	return this->availableNodeCnt;
}

int AvlTree::get_maxHeight()
{
	int temp = cal_maxHeight(this->get_AvlTreeRoot());

	return temp;
}

/*------------------------------------------*/
// Protected (for Dev)
/*------------------------------------------*/

void AvlTree::initNode(void* node, void* data)
{
	this->set_data(node, data);
	this->set_leftPtr(node, nullptr);
	this->set_rightPtr(node, nullptr);
	this->set_balFactor((typAvlTreeNode*)node, AVL_BALANCED);
	this->set_hiddenFlag((typAvlTreeNode*)node, NODE_AVAILABLE);
}
bool AvlTree::makeNode(void** node)
{
	typAvlTreeNode* temp = new typAvlTreeNode;
	if (temp == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return false;
	}
	else
	{
		*node = temp;
		return true;
	}
}

bool AvlTree::deleteNode(void** node)
{
	if (node == nullptr || *node == nullptr)
		return false;

	delete* node;
	*node = nullptr;
	this->treeSize--;

	return true;
}
void AvlTree::destroyTree()
{
	this->destroy_left(nullptr); // ��� ��� ����

	return;
}
int AvlTree::cal_maxHeight(void* node)
{
	int tempLeftHeight = 0, tempRightHeight = 0;

	if (node == nullptr)
	{
		this->errCode = SYS_FAULT;
		return 0;
	}
	else
	{
		tempLeftHeight = this->cal_maxHeight(this->get_leftPtr(node));
		tempRightHeight = this->cal_maxHeight(this->get_rightPtr(node));

		return 1 + std::max(tempLeftHeight, tempRightHeight);
	}
}

/*------------------------------------------*/
// Overriding (for Dev)
/*------------------------------------------*/

int AvlTree::insert_left(void* node, const void* data)
{
	typAvlTreeNode* newNode = nullptr, * targetNode = (typAvlTreeNode*)node,
		** position = nullptr;
	if (targetNode == nullptr)													// 1. ���� ��ġ�� �θ� ��尡 ����ִٸ�
	{
		if (this->get_Size() == 0)
			position = &this->AvlTreeRoot;										// 2. Ʈ���� ����ִٸ� -> ���� ��ġ�� Ʈ���� Root
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else																		// 1-1. ���� ��ġ�� �θ� ��尡 ������� �ʴٸ�
	{
		if (!this->is_emptyNode(targetNode->left))								// 2. �ش� ����� leftChild�� ���ٸ� -> ���� ��ġ�� ����� leftPtr
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = (typAvlTreeNode**)&targetNode->left;
	}
	this->makeNode((void**)&newNode);											// 3. ���ο� ��� ����
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);									// 4. ���ο� ��� �ʱ�ȭ
		*position = newNode;													// 5. �θ� ����� leftPtr => ���ο� ��� �ּ� ������
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

int AvlTree::insert_right(void* node, const void* data)
{
	typAvlTreeNode* newNode = nullptr, * targetNode = (typAvlTreeNode*)node,
		** position = nullptr;
	if (targetNode == nullptr)													// 1. ���� ��ġ�� �θ� ��尡 ����ִٸ�
	{
		if (this->get_Size() == 0)
			position = &this->AvlTreeRoot;										// 2. Ʈ���� ����ִٸ� -> ���� ��ġ�� Ʈ���� Root
		else
		{
			this->errCode = SYS_FAULT;
			return INSERT_FAILED;
		}
	}
	else 																		// 1-1. ���� ��ġ�� �θ� ��尡 ������� �ʴٸ�
	{
		if (!this->is_emptyNode(targetNode->right))								// 2. �ش� ����� rightChild�� ���ٸ� -> ���� ��ġ�� ����� rightPtr
		{
			this->errCode = SYS_FAULT;
			return INSERT_CHILD_EXISTS;
		}
		else
			position = (typAvlTreeNode**)&targetNode->right;
	}
	this->makeNode((void**)&newNode);											// 3. ���ο� ��� ����
	if (newNode == nullptr)
	{
		this->errCode = MEMORY_ERR;
		return INSERT_MEMORY_ERR;
	}
	else
	{
		this->initNode(newNode, (void*)data);									// 4. ���ο� ��� �ʱ�ȭ
		*position = newNode;													// 5. �θ� ����� rightPtr => ���ο� ��� �ּ� ������
		this->treeSize++;
		return INSERT_SUCCESS;
	}
}

bool AvlTree::remove_left(void* node)
{
	typAvlTreeNode** target = nullptr, * targetNode = (typAvlTreeNode*)node;
	bool result = false;

	if (this->treeSize == 0)
		return result;
	else																		// 1. Ʈ���� ������� ���� ���
	{
		if (this->is_emptyNode(targetNode))										// 2. targetNode�� ����ִٸ� -> target�� Ʈ���� Root�� ����Ŵ			
			target = &this->AvlTreeRoot;
		else
			target = (typAvlTreeNode**)&targetNode->left;						// 2.1 targetNode�� ������� �ʴٸ� -> target�� targetNode�� leftPtr�� ����Ŵ
	}

	if (!this->is_emptyNode(targetNode))										// 3. targetNode�� ������� �ʴٸ�
	{
		this->remove_left(*target);												// 4. targetNode�� children ������ ��������� ����
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

		result = true;
	}
	return result;
}

bool AvlTree::remove_right(void* node)
{
	typAvlTreeNode** target = nullptr, * targetNode = (typAvlTreeNode*)node;
	bool result = false;
	if (this->treeSize == 0)
		return result;
	else																		// 1. Ʈ���� ������� ���� ���
	{
		if (this->is_emptyNode(targetNode))										// 2. targetNode�� ����ִٸ� -> target�� Ʈ���� Root�� ����Ŵ	
			target = &this->AvlTreeRoot;
		else
			target = (typAvlTreeNode**)&targetNode->right;						// 2.1 targetNode�� ������� �ʴٸ� -> target�� targetNode�� leftPtr�� ����Ŵ
	}
	if (!this->is_emptyNode(targetNode))										// 3. targetNode�� ������� �ʴٸ�
	{
		this->remove_left(*target);												// 4. targetNode�� children ������ ��������� ����
		this->remove_right(*target);
		this->deleteNode((void**)target);
		this->treeSize--;

		result = true;
	}
	return result;
}