#include"HashTable.h"
#include"BinarySearchTree.h"

void visit(Book*& item)
{
	std::cout << *item << std::endl;
}

int main()
{
	Book* bookptr1=  new Book("11111111", "11111111", "1111111", "1111111");
	Book* bookptr2 = new Book("2222222", "222222", "22222222", "2222222");
	Book* bookptr3 = new Book("333333", "333333333", "3333333333", "33333333");
	Book* bookptr4 = new Book("444444", "4444", "44444", "44444444");
	Book* bookptr5 = new Book("555555", "5555555", "5555555", "5555555");
	Book* bookptr6 = new Book("666666666", "66666666", "66666666", "6666666");

	BinarySearchTree<std::string, Book*> btree;
	btree.add("333333", bookptr3);
	btree.add("11111111",bookptr1);
	btree.add("2222222", bookptr2);	
	btree.add("444444", bookptr4);
	btree.add("555555", bookptr5);
	btree.add("666666666", bookptr6);
	btree.graph();
	btree.remove("2222222");
	btree.breadthFirstTraverse(visit);
	btree.graph();



	HashTable* table = new HashTable;
	table->add("11111111",bookptr1);
	table->add("222222", bookptr2);
	table->add("333333333", bookptr3);
	table->add("4444", bookptr4);
	table->add("5555555", bookptr5);
	table->add("66666666", bookptr6);
	//table->tabledisplay();
	//std::cout << *(table->getData("222222")) << std::endl;

	
	table->caculateStatus();
	//table->removeData("222222");
	table->tabledisplay();

	delete bookptr1;
	delete bookptr2;
	delete bookptr3;
	delete bookptr4;
	delete bookptr5;
	delete bookptr6;	
	delete table;
	
	


	
	
	
	system("pause");
	return 0;

}