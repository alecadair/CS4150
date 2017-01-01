#include <queue>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

typedef struct TreeNode
{
  int value;
  TreeNode *left;
  TreeNode *right;

}TreeNode;

TreeNode* AddInteger(int value, TreeNode* rootNode){
	if(rootNode == 0){
		rootNode = new TreeNode;
		rootNode->value = value;
		rootNode->left = 0;
		rootNode->right = 0;
		//rootNode->left->value = 0;
		//rootNode ->right->value = 0;
		//rootNode->right = 0;
		return rootNode;
	}
	else{
		TreeNode* currentNode = rootNode;
		while(currentNode != 0){
			if(value < currentNode->value){
				if(currentNode->left == 0){
					currentNode->left = new TreeNode;
					currentNode->left->value = value;
					currentNode->left->left = 0;
					currentNode->left->right = 0;
					currentNode = 0;
				}
				else{
					currentNode = currentNode->left;
				}
			}
			else if(value > currentNode->value){
				if(currentNode->right == 0){
					currentNode->right = new TreeNode;
					currentNode->right->value = value;
					currentNode->right->right = 0;
					currentNode->right->left = 0;
					currentNode = 0;
				}
				else{
					currentNode = currentNode->right;
				}
			}
		}
		return rootNode;
	}
}

void DestroyTree(TreeNode* node)
{
  if( node != 0 )
  {
      DestroyTree(node->left);
      DestroyTree(node->right);
      delete(node);
  }
}

/*
 * Perform a breadthfirst search to fill vector.
 */
vector<int> getTreeVector(TreeNode* rootNode){
	vector<int> result;
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(rootNode);
	TreeNode* currentNode;
	result.push_back(1);
	while(!nodeQueue.empty()){
		currentNode = nodeQueue.front();
		nodeQueue.pop();
		//currentNode = nodeQueue.pop();
		//result.push_back(1);
		if(currentNode->left != 0){
			nodeQueue.push(currentNode->left);
			result.push_back(1);
		}
		else{
			result.push_back(0);
		}
		if(currentNode->right != 0){
			nodeQueue.push(currentNode->right);
			result.push_back(1);
		}
		else{
			result.push_back(0);
		}
	}
	//if(rootNode == 0){
	//	return treeVector;
	//}

	return result;
}

int main(int argc, char* argv[]){
	string countAndSize;
	std::getline(cin,countAndSize);
	stringstream stream(countAndSize);
	int numTreeNodes;
	int numTrees;
	int count = 1;
	int streamHolder;
	while(stream >> streamHolder){
		if (count == 1){
			numTrees = streamHolder;
		}
		else{
			numTreeNodes = streamHolder;
		}
		count ++;
	}
	//cout << "count: " << numTrees << " Nodes/Tree " << numTreeNodes << endl;

	//iterate through each line and build tree. add tree to vector
	vector<TreeNode*> trees;
	for(int i = 0; i < numTrees; i++){
		string nodesList;
		int nodeValueStream = 0;
		getline(cin,nodesList);
		stringstream listStream(nodesList);
		//vector<int> resistanceVals;
		TreeNode* rootNode = 0;
		while(listStream >> nodeValueStream){
			//resistanceVals.push_back(nodeValueStream);
			rootNode = AddInteger(nodeValueStream, rootNode);
		}
		trees.push_back(rootNode);
	}
	set<vector<int> > vectorSet;
	for(int i = 0; i < trees.size();i++){
		vectorSet.insert(getTreeVector(trees.at(i)));
	}
//	vector<int> tree1 = getTreeVector(trees.at(0));
//	vector<int> tree2 = getTreeVector(trees.at(1));
//	//set<vector<int> > vectorSet;
//	vectorSet.insert(tree1);
//	vectorSet.insert(tree2);
	cout << vectorSet.size() << endl;
	for(int i = 0; i < trees.size(); i++){
		DestroyTree(trees.at(i));
	}

	return 0;
}


