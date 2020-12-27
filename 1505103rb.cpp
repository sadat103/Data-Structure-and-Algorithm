#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#define inf 100000000
#define red 1
#define black 0

using namespace std;

struct treeNode
{
	int dt,clr;
	treeNode *lft, *rht, *prnt;

	treeNode(int mdt)
	{
		dt =mdt;
		clr = red;
		lft = rht = prnt = NULL;
	}
};

class redBlackTree
{
	treeNode *tmp, *prnt, *uncl, *grandprnt;
	treeNode *n1, *n2, *n3, *n4, *gt,*a, *b, *c;

public:
	treeNode *root;
	redBlackTree()
	{
		root = NULL;
	}



	treeNode *rhtRotate(treeNode *t)
	{
		b = t;
		a = b->prnt; gt = a->prnt;
		c = b->lft; n3 = b->rht;

		swap(a->clr, b->clr);

		b->prnt = gt;
		//a is the rht child
		if (gt != NULL &&  a->dt > gt->dt)
			gt->rht = b;

		//a is the lft child
		else if (gt != NULL &&  a->dt < gt->dt)
			gt->lft = b;

		a->lft = n3;
		b->rht = a; a->prnt=b;

		if (n3 != NULL)
			n3->prnt = a;

		if (b->prnt == NULL)
			root = b;

		return b;
	}




	treeNode *lftRotate(treeNode *t)
	{
		b = t;
		a = b->prnt; gt = a->prnt;
		c = b->rht; n2 = b->lft;

		swap(a->clr, b->clr);

		b->prnt = gt;
		//a is the rht child
		if (gt != NULL &&  a->dt > gt->dt)
			gt->rht = b;

		//a is the lft child
		else if (gt != NULL &&  a->dt < gt->dt)
			gt->lft = b;

		a->rht = n2;
		b->lft = a; a->prnt = b;

		if (n2 != NULL)
			n2->prnt = a;

		//see if root needs to be updated
		if (b->prnt == NULL)
			root = b;

		return b;
	}

     void inOrTrvrsl(treeNode *t)
	{
		if (t == NULL)
			return;

		inOrTrvrsl(t->lft);
		printf("%d ", t->dt);
		inOrTrvrsl(t->rht);
	}


	void rbInsertFixup(treeNode *t)
	{
		if (root == t)
		{
			t->clr = black;
			return;
		}

		while (t->prnt != NULL && t->prnt->clr==red)
		{
			prnt = t->prnt;
			grandprnt = prnt->prnt;

			if (grandprnt->lft == prnt)
			{
				uncl = grandprnt->rht;

				//prnt and uncl both are red

				if (uncl != NULL && uncl->clr==red)
				{
					prnt->clr = black;
					uncl->clr = black;
					grandprnt->clr = red;

					t = grandprnt;
				}

				//uncl is either empty or black
				//needs rotation and re-clring
				else
				{
					if (prnt->rht == t)
					{

						t = lftRotate(t);
						t = rhtRotate(t);
					}

					else
					{

						t = rhtRotate(t->prnt);
					}
				}
			}

			else
			{
				uncl = grandprnt->lft;

				if (uncl != NULL && uncl->clr == red)
				{
					prnt->clr = black;
					uncl->clr = black;
					grandprnt->clr = red;
					t = grandprnt;
				}


				else
				{
					if (prnt->lft == t)
					{


						t = rhtRotate(t);
						t = lftRotate(t);
					}

					else
					{


						t = lftRotate(t->prnt);
					}
				}
			}

			if (t->prnt == NULL)
			{
				root = t; break;
			}
		}

		root->clr = black;
	}

	void insert(int dt)
	{
		/*if (lookUp(dt))
		{
			printf("%d already exists in the tree !!!\n", dt);
			return;
		}*/

		struct treeNode *newtreeNode = new treeNode(dt);
		if (root == NULL)
        {
			root = newtreeNode;
        }

		else
		{
			tmp = root;
			while (tmp)
			{
				if (dt >= tmp->dt && tmp->rht == NULL)
				{
					newtreeNode->prnt = tmp;
					tmp->rht = newtreeNode;
					break;
				}

				else if (dt < tmp->dt && tmp->lft == NULL)
				{
					newtreeNode->prnt = tmp;
					tmp->lft = newtreeNode;
					break;
				}

				else if (dt >= tmp->dt && tmp->rht)
                {
                     tmp = tmp->rht;
                }

				else if (dt < tmp->dt && tmp->lft)
                {
                    tmp = tmp->lft;
			    }

				else
					exit(EXIT_FAILURE);
			}
		}

		//rbInsertFixup
		rbInsertFixup(newtreeNode);
	}
	//-----------------------------------------------------------------------insert in the tree


	//-----------------------------------------------------------------------search a key in the tree
	treeNode* lookUp(int k)
	{
		struct treeNode *tmp;
		tmp = root;

		while (tmp != NULL)
		{
			if (tmp->dt == k)
				return tmp;

			else if (tmp->dt > k)
				tmp = tmp->lft;

			else
				tmp = tmp->rht;
		}

		return tmp;
	}
	//-----------------------------------------------------------------------search a key in the tree


	//-----------------------------------------------------------------------get sibling
	treeNode *sibling(treeNode *x)
	{
		prnt = x->prnt;

		if (prnt != NULL)
		{
			if (prnt->lft==x)
				return prnt->rht;
			else
				return prnt->lft;
		}
	}
	//-----------------------------------------------------------------------get sibling


	//-----------------------------------------------------------------------case: red
	void caseRed(treeNode *x)
	{
		prnt = x->prnt;
		n1 = x->lft; n2 = x->rht;

		//x is rht child
		if (x==x->prnt->rht)
		{
			if (x->lft != NULL)
				prnt->rht = x->lft, x->lft->prnt = prnt;

			else if (x->rht != NULL)
				prnt->rht = x->rht, x->rht->prnt = prnt;

			else
				prnt->rht = NULL;
		}

		//x is lft child
		else
		{
			if (x->lft != NULL)
				prnt->lft = x->lft, x->lft->prnt = prnt;

			else if (x->rht != NULL)
				prnt->lft = x->rht, x->rht->prnt = prnt;

			else
				prnt->lft = NULL;
		}

		delete x;
	}
	//-----------------------------------------------------------------------case: red


	//-----------------------------------------------------------------------delete case: 1
	void deleteCase1(treeNode *x)
	{
		if (x->prnt == NULL)
			x->clr = black;
		else
			deleteCase2(x);
	}
	//-----------------------------------------------------------------------delete case: 1


	//-----------------------------------------------------------------------delete case: 2
	void deleteCase2(treeNode *x)
	{
		n1 = sibling(x);

		if (n1 != NULL && n1->clr == red)
		{
			if (x == x->prnt->lft)
				lftRotate(n1);
			else
				rhtRotate(n1);
		}

		deleteCase3(x);
	}
	//-----------------------------------------------------------------------delete case: 2


	//-----------------------------------------------------------------------delete case: 3
	void deleteCase3(treeNode *x)
	{
		n3 = sibling(x);

		bool f1=0, f2=0;
		if (n3->lft == NULL)
			f1 = 1;
		else if (n3->lft != NULL && n3->lft->clr == black)
			f1 = 1;

		if (n3->rht == NULL)
			f2 = 1;
		else if (n3->rht != NULL && n3->rht->clr == black)
			f2 = 1;

		if (x->prnt->clr == black && n3->clr == black && f1 && f2)
		{
			n3->clr = red;
			deleteCase1(x->prnt);
		}


	}

	void deletetreeNode(treeNode *x)
	{
		treeNode *p;

		if(x->lft!=NULL && x->rht!=NULL)
		{
			//delete the succesor
			tmp=getMax(x->lft);
			x->dt = tmp->dt;

			deletetreeNode(tmp);
		}

		else
		{
			if (x->clr == red)
				caseRed(x);

			else if (x->rht != NULL && x->rht->clr == red && x->clr == black)
			{
				//change clr of x.rht into black and stick it with x.prnt, delete x
				x->rht->clr = black;
				prnt = x->prnt;

				//root
				if (prnt == NULL)
					root = x->rht;

				else
				{
					if (x==x->prnt->lft)
						prnt->lft = x->rht;

					else
						prnt->rht = x->rht;
				}

				x->rht->prnt = prnt;
				delete x;
			}

			else if (x->lft != NULL && x->lft->clr == red && x->clr == black)
			{

				x->lft->clr = black;
				prnt = x->prnt;

				//root
				if (prnt == NULL)
					root = x->lft;

				else
				{
					if (x->dt < prnt->dt)
						prnt->lft = x->lft;

					else
						prnt->rht = x->lft;
				}

				x->lft->prnt = prnt;
				delete x;
			}

			//tryout the six cases
			else
			{
				deleteCase1(x);

				//replace with child;
				if (x->rht != NULL)
				{
					n3 = x->rht;
					n3->clr = x->clr;
					n3->prnt = x->prnt;

					if (x->prnt && x == x->prnt->rht)
						x->prnt->rht = n3;
					else if (x->prnt && x == x->prnt->lft)
						x->prnt->lft = n3;
				}

				else if (x->lft != NULL)
				{
					n3 = x->lft; n3->clr = x->clr;
					n3->prnt = x->prnt;

					if (x->prnt && x == x->prnt->rht)
						x->prnt->rht = n3;
					else if (x->prnt && x == x->prnt->lft)
						x->prnt->lft = n3;
				}

				else
				{
					if (x->prnt && x == x->prnt->rht)
						x->prnt->rht = NULL;
					else if (x->prnt && x == x->prnt->lft)
						x->prnt->lft = NULL;
				}

				if (root == x)
					root = NULL;

				delete x;
			}
		}
	}

	void deleteItem(int x)
	{
		treeNode *rm = lookUp(x);

		if (rm == NULL)
			printf("not found\n");

		else
			deletetreeNode(rm);
	}

	treeNode* getMin(treeNode *x)
	{
		if (root == NULL)
			return NULL;

		tmp = x;

		while (tmp->lft!= NULL)
		{
			tmp = tmp->lft;
		}

		return tmp;
	}




	treeNode* getMax(treeNode *x)
	{
		if (root == NULL)
			return NULL;

		tmp = x;

		while (tmp->rht != NULL)
		{
			tmp = tmp->rht;
		}

		return tmp;
	}



	void print()
	{
		inOrTrvrsl(root);
		printf("\n");
	}

	int height(treeNode *x)
	{
		if (x == NULL)
			return 0;

		return max(height(x->lft) +1, height(x->rht)+1);
	}

	int getHeight()
	{
		return height(root);
	}

};

int main()
{

	int i, j, k;
	int n, m, t;

	redBlackTree x;

	while (1)
	{

		printf("1. insert  2.search  3. minimum  4. maximum  5. print   \n");
		printf("6. height   7. exit\n");
		scanf("%d", &t);

		if (t == 1)
		{
			scanf("%d", &n);
			x.insert(n);
		}



		else if (t == 2)
		{
			scanf("%d", &n);

			if (x.lookUp(n) == NULL)
				printf("%d is not in the tree :(\n", n);
			else
				printf("found \n");
		}

		else if (t == 3)
		{
			if (x.getMin(x.root) == NULL)
				printf(" empty !!!\n");
			else
				printf("%d  minimum\n", x.getMin(x.root)->dt);
		}

		else if (t == 4)
		{

			if (x.getMax(x.root) == NULL)
				printf(" empty !!!\n");
			else
				printf("%d  maximum\n", x.getMax(x.root)->dt);
		}

		else if (t == 5)
			x.print();



		else if (t == 6)
			printf("height is %d\n", x.getHeight());



		else
			break;
	}

	return 0;
}
