#include <stdio.h>

#ifndef null
#define null ((void *)0)
#endif

struct btree_head
{
	int key;
	struct btree_head *lchild;
	struct btree_head *rchild;
};

/*****************************************************************************
功能：向树添加节点，如果树为空，则创建一棵树
返回值：插入节点后返回的新树根 
******************************************************************************/
struct btree_head * btree_insert(struct btree_head *root, struct btree_head *node)
{
	struct btree_head *parent = root;
	if(root==null)
		return node;

	/*找到插入点*/
	while(parent)
	{
		if(parent->key > node->key && parent->lchild!=null)
		{
			parent = parent->lchild;
		}
		else if(parent->key < node->key && parent->rchild!=null)
		{
			parent = parent->rchild;
		}
		else
			break;
	}
	
	/*执行插入操作*/
	if(parent->key > node->key)
	{
		parent->lchild = node;
	}
	else if(parent->key < node->key)
	{
		parent->rchild = node;
	}
	else
		perror("duplicate key");
		
	return root;
}

/*****************************************************************************
功能：根据关键字查找节点 
返回值：查找到的节点指针
出参：父节点指针
入参：二叉树根节点，待查找节点关键字 
******************************************************************************/
struct btree_head *btree_search(struct btree_head *root, struct btree_head **pparent, int key)
{
	struct btree_head *p = root; 
	while(root && root->key != key)
	{
		p = root;
		if(root->key < key)
			root = root->rchild;
		else if(root->key > key)
			root = root->lchild;
		else
			break;
	}
	if(pparent!=null)
	{
		//找到了节点，不是根 
		if(root != null && p != root)
			*pparent = p;
		else
		//未找到，或者找到了根 
			*pparent = null;
	} 
	return root;
}

/*****************************************************************************
功能：从树中移除节点 
返回值：移除节点后的新树的根节点 
入参：二叉树根节点，待删节点关键字 
******************************************************************************/
struct btree_head *btree_remove(struct btree_head *root, int key)
{
	struct btree_head *parent;
	struct btree_head *prev = null;
	struct btree_head *node;
	
	node = btree_search(root,&parent,key);
	/*检查待删节点是否存在*/
	if(node == null)
	{
		perror("node doesnot exists.");
		return root;
	}
	
	/*待删结点没有孩子，直接删除*/
	if(node->lchild == null && node->rchild == null)
	{
		if(parent == null)
		    /*删除根*/
			return null;
		else if(parent->lchild==node)
			parent->lchild = null;
		else if(parent->rchild==node)
			parent->rchild = null;
	}
	/*待删结点只有右子树，直接将右子树交给父节点代替自己*/
	else if(node->lchild == null && node->rchild != null)
	{
		if(parent==null)
 			/*直接返回根的右子树*/
			return node->rchild;		
		else if(parent->lchild==node)
			parent->lchild = node->rchild;
		else if(parent->rchild==node)
			parent->rchild = node->rchild;
	}
	/*待删结点只有左子树，直接将左子树交给父节点代替自己*/
	else if(node->lchild != null && node->rchild == null)
	{
		if(parent==null)
 			/*直接返回根的左子树*/
			return node->lchild;
		else if(parent->lchild==node)
			parent->lchild = node->lchild;
		else if(parent->rchild==node)
			parent->rchild = node->lchild;
	}
	/*待删结点有左右两个孩子，此时，将待删结点的前驱节点代替自己挂接两个孩子*/
	else if(node->lchild != null && node->rchild != null)
	{
		struct btree_head *parentprev;
		
		/*查找待删结点的前驱*/
		parentprev = node;
		prev = node->lchild;
		while(prev !=null && prev->rchild!=null)
		{
			parentprev = prev;
			prev = prev->rchild;
		}
		
		/*前驱节点是待删结点的左孩子*/
		if(parentprev->lchild == prev)
		{
			parentprev->lchild = null;
		}
		else
		{
			/*前驱节点的父节点接管前驱节点的左孩子*/
			parentprev->rchild = prev->lchild;
			/*前驱节点接管待删结点的左孩子*/
			prev->lchild = node->lchild;
		}

		/*前驱节点接管待删结点的右孩子*/
		prev->rchild = node->rchild;
		node->rchild = null;
		
		/*如果不是删除根节点，还需要修改待删结点的父节点的指针*/
		if(parent!=null)
		{
			if(parent->lchild==node)
				parent->lchild = prev;
			else if(parent->rchild==node)
				parent->rchild = prev;
		}
		else
		/*删除了根节点，前驱节点升级为根节点*/
			root = prev;
	}
	return root;
}

void btree_rmnod(struct btree_head *node)
{
	free(node);
}

struct btree_head *btree_mknod(int key)
{
	struct btree_head *pnode = (struct btree_head *)malloc(sizeof(struct btree_head));
	if(pnode!=null)
	{
		pnode->key = key;
		pnode->lchild = null;
		pnode->rchild = null;
	}
	return pnode;
}

void btree_destroy(struct btree_head *root)
{
	if(root->lchild!=null)
		btree_destroy(root->lchild);
	if(root->rchild!=null)
		btree_destroy(root->rchild);
	btree_rmnod(root);
} 

void btree_print(struct btree_head *root, int level)
{
	int orglevel = level;
	while(level--)
		printf(" ");
	printf("@%p,l=%#p,r=%#p,key=%d\n",root,root->lchild,root->rchild,root->key);
	if(root->lchild!=null)
		btree_print(root->lchild,orglevel+1);
	if(root->rchild!=null)
		btree_print(root->rchild,orglevel+1);
}

void test(void)
{
	struct btree_head *node;
	struct btree_head *root;
	root = btree_mknod(21);
	root = btree_insert(null,root);

	node = btree_mknod(8);
	btree_insert(root,node);

	node = btree_mknod(20);
	btree_insert(root,node);

	node = btree_mknod(22);
	btree_insert(root,node);

	node = btree_mknod(15);
	btree_insert(root,node);

	node = btree_mknod(6);
	btree_insert(root,node);
	
	node = btree_mknod(9);
	btree_insert(root,node);
	
	btree_print(root,0);
	printf("\n");
	root = btree_remove(root,15);
	btree_print(root,0);

	printf("\n");
	root = btree_remove(root,21);
	btree_print(root,0);
	
	printf("\n");
	root = btree_remove(root,20);
	btree_print(root,0);
	
	printf("\n");
 	node = btree_mknod(3);
 	btree_insert(root,node);
	btree_print(root,0);

	printf("\n");
	root = btree_remove(root,3);
	btree_print(root,0);
	
	btree_destroy(root);
}

int main()
{
	test();
	return 0;
}


