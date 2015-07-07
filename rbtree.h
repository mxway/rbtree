#include <iostream>
#include <queue>
using namespace std;
static int _rb_black_node = 0;
static int _rb_red_node   = 1;
template<typename T>
struct RBNode
{
	RBNode():left(NULL),right(NULL),parent(NULL),val(T()),color(_rb_red_node){}
	RBNode(const T &v1):left(NULL),right(NULL),parent(NULL),val(v1),color(_rb_red_node){}
	RBNode	*left;
	RBNode	*right;
	RBNode	*parent;
	int		color;
	T		val;
};

template<typename T>
class RBTree
{
public:
	RBTree():root(NULL){}
	~RBTree()
	{
		if(root)
		{
			Destroy(root);
		}
	}
	void	print();
	void	Search(const T &v1, RBNode<T> *&node);
	bool	InsertUnique(const T &v1);
	void	DeleteValue(const T &v1);
	void	DeleteReblance(RBNode<T> *node);
	void	Destroy(RBNode<T> *p);
	void	InsertReBalance(RBNode<T> *node);
	RBNode<T>*	_rbtree_rotate_left(RBNode<T> *node);
	RBNode<T>*  _rbtree_rotate_right(RBNode<T> *node);
private:
	RBNode<T>	*root;
};

/*
*
* ��ӡ������Ľڵ���Ϣ
*
*/
template<typename T>
void RBTree<T>::print()
{
	RBNode<T> *p;
	queue<RBNode<T> *> Q;
	Q.push(root);
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		cout<<"�ڵ�: "<<p->val<<" ";
		if(p->left)
		{
			cout<<"left:"<<p->left->val<<"->color:"<<p->left->color<<" ";
			Q.push(p->left);
		}
		if(p->right)
		{
			cout<<"right:"<<p->right->val<<"->color:"<<p->right->color<<" ";
			Q.push(p->right);
		}
		cout<<endl<<endl;
	}
}

/*
*
* ����v1�ں�����г��ֵ�λ�ã����v1�ں��������node�ڵ�Ϊ
* ֵΪv1���ں�����еĽڵ㡣
* ����node�ڵ�Ϊ�����v1���뵽������еĸ��ڵ�
*
*/
template<typename T>
void RBTree<T>::Search(const T &v1,RBNode<T> *&node)
{
	RBNode<T> *p = root;
	node = NULL;
	while(p)
	{
		if(p->val == v1)
		{
			node = p;
			break;
		}
		else if(p->val < v1)
		{
			node = p;
			p = p->right;
		}
		else
		{
			node = p;
			p = p->left;
		}
	}
}

template<typename T>
bool RBTree<T>::InsertUnique(const T &v1)
{
	RBNode<T> *parent = NULL;
	RBNode<T> *newNode = new RBNode<T>(v1);
	Search(v1, parent);
	if(parent == NULL)
	{//�����Ϊ�գ���ǰ����Ľڵ�Ϊ���ڵ㡣����󽫸���ɫ��Ϊ��
		root = newNode;
		root->color = _rb_black_node;
		return true;
	}
	if(parent->val == v1)//v1�Ѿ����ں�����С����ٲ���
		return false;
	
	if(v1 < parent->val)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}
	newNode->parent = parent;
	InsertReBalance(newNode);
	return true;
}

/*
*
* ����ڵ����е�����
* ʹ���нڵ���������������
*
*/
template<typename T>
void RBTree<T>::InsertReBalance(RBNode<T> *node)
{
	RBNode<T> *parent = node->parent;
	RBNode<T> *grandParent = NULL;
	while(parent && parent->color==_rb_red_node)
	{
		grandParent = parent->parent;
		if(parent == grandParent->left)
		{//���ڵ�Ϊ�游�ڵ�������
			RBNode<T> *uncle = grandParent->right;
			if(uncle && uncle->color == _rb_red_node)
			{//����1 ���ڵ�����ڵ㶼Ϊ��
				//��������������ڣ��游��ڡ��游��Ϊ�µĵ�ǰ�ڵ����½����㷨
				parent->color = _rb_black_node;
				uncle->color  = _rb_black_node;
				grandParent->color = _rb_red_node;
				node = grandParent;
				parent = grandParent->parent;
			}
			else
			{
				if(node == parent->right)
				{//����2����Ϊ�ڣ���ǰ�ڵ�Ϊ�丸�ڵ�����ӽڵ�
					//����������Ը��ڵ�Ϊ����������
					//������ת��Ϊ����3
					node = _rbtree_rotate_left(parent);
					parent = node->parent;
					grandParent = parent->parent;
				}
				//����3��Ϊ�죬��ǰ�ڵ�Ϊ���ڵ�����ӽڵ�
				//������������ڵ��ڣ��游�ڵ��죬��
				//�游�ڵ�Ϊ���ڵ��������
				parent->color = _rb_black_node;
				grandParent->color = _rb_red_node;
				_rbtree_rotate_right(grandParent);
			}
		}
		else
		{//���ڵ�Ϊ�游�ڵ�����ӽڵ㣬�����������ͬ
			RBNode<T> *uncle = grandParent->left;
			if(uncle && uncle->color == _rb_red_node)
			{
				uncle->color = _rb_black_node;
				parent->color = _rb_black_node;
				grandParent->color = _rb_red_node;
				node = grandParent;
				parent = node->parent;
			}
			else
			{
				if(node == parent->left)
				{
					node = _rbtree_rotate_right(parent);
					parent = node->parent;
					grandParent = parent->parent;
				}
				parent->color = _rb_black_node;
				grandParent->color = _rb_red_node;
				_rbtree_rotate_left(grandParent);
			}
		}
	}
	root->color = _rb_black_node;
}

/*
*
* ����
*
*/
template<typename T>
RBNode<T> *RBTree<T>::_rbtree_rotate_left(RBNode<T> *x)
{
	RBNode<T> *y = x->right;
	if(y == NULL)
	{
		return x;
	}
	//x���ҽڵ�Ϊy����ڵ�
	x->right = y->left;
	if(y->left)//���y����ڵ���ڣ��丸�ڵ�Ϊy
		y->left->parent = x;
	if(root == x)
	{//xΪroot����ת��yΪ�µ�root���ڵ�
		root = y;
	}
	else
	{
		if(x == x->parent->left)
		{//���xΪ�丸�ڵ�����ӽڵ㡣
			//x�ĸ��ڵ�������ӽڵ�Ϊy
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		//y�ĸ��ڵ�Ϊx�ĸ��ڵ�
		y->parent = x->parent;
	}
	//y�����ӽڵ�Ϊx
	y->left = x;
	//x�ĸ��ڵ�Ϊy
	x->parent = y;
	return x;
}

/*
*
* ����
* �������߼���������������
*
*/
template<typename T>
RBNode<T>* RBTree<T>::_rbtree_rotate_right(RBNode<T> *x)
{
	RBNode<T> *y = x->left;
	if(y == NULL)
	{
		return x;
	}
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	if(root == x)
	{
		root = y;
	}
	else
	{
		if(x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->parent = x->parent;
	}
	y->right = x;
	x->parent = y;
	return x;
}

/*
*
* �������ú����
*
*/
template<typename T>
void RBTree<T>::Destroy(RBNode<T> *p)
{
	if(p->left)
	{
		Destroy(p->left);
	}
	if(p->right)
	{
		Destroy(p->right);
	}
	delete p;
}

/***
*
*
*
***/
template<typename T>
void RBTree<T>::DeleteValue(const T &v1)
{
	RBNode<T>		*p = NULL;
	RBNode<T>		*nextNode = NULL;
	Search(v1,p);
	if(p==NULL)
	{
		cout<<"ɾ����ֵ������"<<endl;
		return;
	}
	if(p->left && p->right)
	{
		RBNode<T> *tempNode = p->right;
		while(tempNode)
		{//�������еĺ�̽ڵ�
			nextNode = tempNode;
			tempNode = tempNode->left;
		}
		p->val = nextNode->val;
		p = nextNode;
	}
	if(p->left)
	{
		//ֱ���ú�̽ڵ��ֵ�滻
		RBNode<T> *temp = p->left;
		p->val = temp->val;
		p->left = NULL;
		delete temp;
	}
	else if(p->right)
	{
		//ֱ���ú�̽ڵ��ֵ�滻
		RBNode<T> *temp = p->right;
		p->val = temp->val;
		p->right = NULL;
		delete temp;
	}
	else
	{
		//���������������ڣ���Ҫ����ɾ�������㷨
		DeleteReblance(p);
		if(p==root)
		{
			root = NULL;
		}
		else if(p==p->parent->left)
		{//���ڵ��ָ������Ҫ�޸�
			p->parent->left = NULL;
		}
		else if(p==p->parent->right)
		{//���ڵ��ָ������Ҫ�޸�
			p->parent->right = NULL;
		}
		delete p;
	}
}

//ɾ���ڵ��ĵ���
template<typename T>
void RBTree<T>::DeleteReblance(RBNode<T> *node)
{
	RBNode<T> *parent = NULL;
	RBNode<T> *other = NULL;
	while(node->color==_rb_black_node && node->parent)
	{
		parent = node->parent;
		if(node == parent->left)
		{
			other = parent->right;
			if(other->color==_rb_red_node)
			{//����1�ֵܽڵ�Ϊ��
				parent->color = _rb_red_node;
				other->color = _rb_black_node;
				_rbtree_rotate_left(parent);
				other = parent->right;
			}
			if( (other->left==NULL || other->left->color==_rb_black_node)
				&& (other->right==NULL || other->left->color==_rb_black_node))
			{//����2�ֵ�Ϊ�ڣ����ֵܵ���������ҲΪ��
				other->color=_rb_red_node;
				node = parent;
				continue;
			}
			if( other->right==NULL || other->right->color==_rb_black_node)
			{//����3�ֵܽڵ���Һ���Ϊ�ڣ���Ϊ��
				other->left->color=_rb_black_node;//��ʱ����һ����������ɫΪ�죬���������Ͳ�������������
				other->color = _rb_red_node;
				_rbtree_rotate_right(other);
				other = parent->right;
			}
			//����4�ֵܽڵ���Һ���Ϊ��
			other->right->color=_rb_black_node;
			other->color = parent->color;
			parent->color = _rb_black_node;
			_rbtree_rotate_left(parent);
			break;
		}
		else
		{
			other = parent->left;
			if(other->color==_rb_red_node)
			{//����1�ֵܽڵ�Ϊ��
				parent->color = _rb_red_node;
				other->color = _rb_black_node;
				_rbtree_rotate_right(parent);
				other = parent->left;
			}
			if( (other->left==NULL || other->left->color==_rb_black_node)
				&& (other->right==NULL || other->left->color==_rb_black_node))
			{//����2�ֵ�Ϊ�ڣ����ֵܵ���������ҲΪ��
				other->color=_rb_red_node;
				node = parent;
				continue;
			}
			if( other->left==NULL || other->left->color==_rb_black_node)
			{//����3�ֵܽڵ���Һ���Ϊ�ڣ���Ϊ��
				other->right->color=_rb_black_node;//��ʱ����һ����������ɫΪ�죬���������Ͳ�������������
				other->color = _rb_red_node;
				_rbtree_rotate_left(other);
				other = parent->left;
			}
			//����4�ֵܽڵ���Һ���Ϊ��
			other->left->color=_rb_black_node;
			other->color = parent->color;
			parent->color = _rb_black_node;
			_rbtree_rotate_right(parent);
			break;
		}
	}
	node->color = _rb_black_node;
}