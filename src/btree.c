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
���ܣ�������ӽڵ㣬�����Ϊ�գ��򴴽�һ����
����ֵ������ڵ�󷵻ص������� 
******************************************************************************/
struct btree_head * btree_insert(struct btree_head *root, struct btree_head *node)
{
	struct btree_head *parent = root;
	if(root==null)
		return node;

	/*�ҵ������*/
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
	
	/*ִ�в������*/
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
���ܣ����ݹؼ��ֲ��ҽڵ� 
����ֵ�����ҵ��Ľڵ�ָ��
���Σ����ڵ�ָ��
��Σ����������ڵ㣬�����ҽڵ�ؼ��� 
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
		//�ҵ��˽ڵ㣬���Ǹ� 
		if(root != null && p != root)
			*pparent = p;
		else
		//δ�ҵ��������ҵ��˸� 
			*pparent = null;
	} 
	return root;
}

/*****************************************************************************
���ܣ��������Ƴ��ڵ� 
����ֵ���Ƴ��ڵ��������ĸ��ڵ� 
��Σ����������ڵ㣬��ɾ�ڵ�ؼ��� 
******************************************************************************/
struct btree_head *btree_remove(struct btree_head *root, int key)
{
	struct btree_head *parent;
	struct btree_head *prev = null;
	struct btree_head *node;
	
	node = btree_search(root,&parent,key);
	/*����ɾ�ڵ��Ƿ����*/
	if(node == null)
	{
		perror("node doesnot exists.");
		return root;
	}
	
	/*��ɾ���û�к��ӣ�ֱ��ɾ��*/
	if(node->lchild == null && node->rchild == null)
	{
		if(parent == null)
		    /*ɾ����*/
			return null;
		else if(parent->lchild==node)
			parent->lchild = null;
		else if(parent->rchild==node)
			parent->rchild = null;
	}
	/*��ɾ���ֻ����������ֱ�ӽ��������������ڵ�����Լ�*/
	else if(node->lchild == null && node->rchild != null)
	{
		if(parent==null)
 			/*ֱ�ӷ��ظ���������*/
			return node->rchild;		
		else if(parent->lchild==node)
			parent->lchild = node->rchild;
		else if(parent->rchild==node)
			parent->rchild = node->rchild;
	}
	/*��ɾ���ֻ����������ֱ�ӽ��������������ڵ�����Լ�*/
	else if(node->lchild != null && node->rchild == null)
	{
		if(parent==null)
 			/*ֱ�ӷ��ظ���������*/
			return node->lchild;
		else if(parent->lchild==node)
			parent->lchild = node->lchild;
		else if(parent->rchild==node)
			parent->rchild = node->lchild;
	}
	/*��ɾ����������������ӣ���ʱ������ɾ����ǰ���ڵ�����Լ��ҽ���������*/
	else if(node->lchild != null && node->rchild != null)
	{
		struct btree_head *parentprev;
		
		/*���Ҵ�ɾ����ǰ��*/
		parentprev = node;
		prev = node->lchild;
		while(prev !=null && prev->rchild!=null)
		{
			parentprev = prev;
			prev = prev->rchild;
		}
		
		/*ǰ���ڵ��Ǵ�ɾ��������*/
		if(parentprev->lchild == prev)
		{
			parentprev->lchild = null;
		}
		else
		{
			/*ǰ���ڵ�ĸ��ڵ�ӹ�ǰ���ڵ������*/
			parentprev->rchild = prev->lchild;
			/*ǰ���ڵ�ӹܴ�ɾ��������*/
			prev->lchild = node->lchild;
		}

		/*ǰ���ڵ�ӹܴ�ɾ�����Һ���*/
		prev->rchild = node->rchild;
		node->rchild = null;
		
		/*�������ɾ�����ڵ㣬����Ҫ�޸Ĵ�ɾ���ĸ��ڵ��ָ��*/
		if(parent!=null)
		{
			if(parent->lchild==node)
				parent->lchild = prev;
			else if(parent->rchild==node)
				parent->rchild = prev;
		}
		else
		/*ɾ���˸��ڵ㣬ǰ���ڵ�����Ϊ���ڵ�*/
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


