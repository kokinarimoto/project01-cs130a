project1.out: ternarySearchTree.o ternaryTreeNode.o main.o
	g++ ternarySearchTree.cpp ternaryTreeNode.cpp main.cpp -o project1.out

clean:
	rm ternarySearchTree.o ternaryTreeNode.o main.o project1.out