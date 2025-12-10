#include "AuxPort/AuxPort.h"
#include "Core/Tree/AuxAVL.h"

int main(int argc, char* argv[])
{
	AvlTree avltree(5);
	avltree.add(9);
	avltree.add(4);
	avltree.add(6);
	avltree.add(2);
	avltree.add(10);
	avltree.add(1);
	avltree.add(-3);
}


