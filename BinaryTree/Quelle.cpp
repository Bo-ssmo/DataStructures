#include "BinaryTree.h"
#include "../Utility/Random.h"


class Test
{
private:
	int m_y;

public:

	Test() { m_y = Random::get().getInt(0, 200); }
	~Test() = default;

	int getY() { return m_y; }
};

int main()
{
	std::vector<Test> vecArray;

	for (unsigned int i = 0; i < 1000; i++)
		vecArray.push_back(Test());

	Node<Test>* root;
	root = buildTree(&vecArray, 8);

	std::vector<Test> nearest = getObjsAround(root, 17);
	
	for (unsigned int i = 0; i < nearest.size(); ++i)
	{
		std::cout << nearest.at(i).getY() << std::endl;
	}
	std::cout << "\n\n" << nearest.size();

	deleteTree(root);
	return 0;
}
