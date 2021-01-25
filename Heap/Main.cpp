#include "MinHeap.h"
#include "MaxHeap.h"
#include "../Utility/Random.h"

int main()
{
	std::vector<int> nums = Random::get().getRandVec<int>(10, 0, 100);
	MinHeap<int> minHeap;
	MaxHeap<int> maxHeap;

	// fill MinHeap
	for (int &i : nums)
		minHeap.insertElement(i);

	for(int i = 0; i < 10; ++i)
		std::cout << minHeap.extractNext() << std::endl;
		
	std::cout << "\n\n";

	// fill MaxHeap
	for (int& i : nums)
		maxHeap.insertElement(i);

	for (int i = 0; i < 10; ++i)
		std::cout << maxHeap.extractNext() << std::endl;


	return 0;
}