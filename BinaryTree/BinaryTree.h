#pragma once
#include <vector>
#include <iostream>

/*
	This Tree will divide the dataset along one axis
*/


template<class T>
struct Node
{
	Node* topNode = nullptr;
	Node* bottomNode = nullptr;

	float n_yMin = 0, n_yMax = 0;
	std::vector<T> objs;
};

//############################################
// Functions for building the tree
//############################################

template<class T>
Node<T>* createNode(float yMin, float yMax)
{
	Node<T>* temp = new Node<T>;
	temp->bottomNode = temp->topNode = nullptr;

	temp->n_yMin = yMin;
	temp->n_yMax = yMax;

	return temp;
}

template<class T>
float highestVal(std::vector<T>* objs)
// passed object needs to have getY() memberfunction
{
	float max = 0;
	for (unsigned int i = 0; i < objs->size(); ++i)
	{
		if (objs->at(i).getY() > max)
			max = static_cast<float>(objs->at(i).getY());
	}
	return max;
}

template<class T>
float lowestVal(std::vector<T>* objs)
// passed object needs to have getY() memberfunction
{
	float min = 0;
	for (unsigned int i = 0; i < objs->size(); ++i)
	{
		if (objs->at(i).getY() < min)
			min = static_cast<float>(objs->at(i).getY());
	}
	return min;
}

float getMedian(float x1, float x2)
{
	return std::abs(x2 - x1) / 2;
}

template<class T>
Node<T>* buildTree(std::vector<T>* objs, unsigned short depthOfNodes)
{
	float yMin = lowestVal(objs);
	float yMax = highestVal(objs);

	Node<T>* temp = nullptr;
	temp = addNode(temp, yMin, yMax, 0, depthOfNodes);

	insertObjects(temp, objs);

	return temp;
}

template<class T>
Node<T>* addNode(Node<T>* rootNode, float yMin, float yMax, unsigned short depth, unsigned short maxDepth)
{
	if (rootNode == nullptr)
	{
		rootNode = createNode<T>(yMin, yMax);	
		addNode(rootNode, yMin, yMax, ++depth, maxDepth);
	}
	
	if (depth == maxDepth)
	{
		return rootNode;
	}
	
	if(rootNode->topNode == nullptr)
		rootNode->topNode = createNode<T>(getMedian(rootNode->n_yMin, rootNode->n_yMax) + rootNode->n_yMin, rootNode->n_yMax);
	if(rootNode->bottomNode == nullptr)
		rootNode->bottomNode = createNode<T>(rootNode->n_yMin, rootNode->n_yMax - getMedian(rootNode->n_yMin, rootNode->n_yMax));

	++depth;

	addNode(rootNode->topNode, rootNode->topNode->n_yMin, rootNode->topNode->n_yMax, depth, maxDepth);
	addNode(rootNode->bottomNode, rootNode->bottomNode->n_yMin, rootNode->bottomNode->n_yMax, depth, maxDepth);
	
	
	return rootNode;
}


//############################################
// Functions that insert or return objects from Nodes
//############################################

template<class T>
void insertObjects(Node<T>* rootNode, std::vector<T>* objs)
{
	for (unsigned int i = 0; i < objs->size(); ++i)
	{
		insert(rootNode, objs->at(i));
	}
}

template<class T>
void insert(Node<T>* rootNode, T obj)
// obj must have getY() memberfunction
{
	if (rootNode->bottomNode != nullptr && rootNode->topNode != nullptr)
	{
		if (obj.getY() < rootNode->topNode->n_yMin)
			insert(rootNode->bottomNode, obj);

		if (obj.getY() > rootNode->bottomNode->n_yMax)
			insert(rootNode->topNode, obj);
	}
	else
		rootNode->objs.push_back(obj);
}

template<class T>
std::vector<T>& getObjsAround(Node<T>* rootNode, float position)
{
	if (rootNode->bottomNode != nullptr && rootNode->topNode != nullptr)
	{
		if (position < rootNode->topNode->n_yMin)
			return getObjsAround(rootNode->bottomNode, position);
		else
			return getObjsAround(rootNode->topNode, position);
	}
	else
	{
		return rootNode->objs;
	}
}


//############################################################
// tree destruction
//############################################################
     
template<class T>
void deleteTree(Node<T>* rootNode)
{
	if (rootNode == nullptr) 
		return;

	deleteTree(rootNode->topNode);
	deleteTree(rootNode->bottomNode);

	delete rootNode;
}
