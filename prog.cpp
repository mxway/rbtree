#include "rbtree.h"
#include <iostream>
#include <time.h>
using namespace std;
int flag[50];
int rand_Num()
{
	int num = rand()%50;
	while(flag[num])
	{
		num = rand()%50;
	}
	flag[num] = 1;
	return num;
}

int main()
{
	RBTree<int> obj;
	obj.InsertUnique(14);
	obj.InsertUnique(9);
	obj.InsertUnique(41);
	obj.InsertUnique(39);
	obj.InsertUnique(47);
	obj.InsertUnique(20);
	obj.InsertUnique(15);
	obj.InsertUnique(22);
	obj.InsertUnique(7);
	obj.InsertUnique(3);
	obj.InsertUnique(28);
	obj.InsertUnique(24);

	obj.DeleteValue(24);
	obj.DeleteValue(22);
	cout<<endl<<endl;
	obj.print();
	return 0;
}