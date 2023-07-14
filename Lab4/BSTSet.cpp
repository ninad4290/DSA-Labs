#include "BSTSet.h"
#include <iostream>
#include <vector>
#include "ArrayStack.h"
using namespace std;
#include <stack>

BSTSet::BSTSet()////space and time complexity for this is theta(1)
{

	root = NULL;
}

BSTSet::BSTSet(const std::vector<int>& input)////time complexity is theta(nlogn) for this and space complexity is theta(n)
{

	root = NULL;
	for (unsigned int i=0; i<input.size(); i++) {
		add(input[i]);
	}
}

void BSTSet::DeleteTree(TNode* subroot) {////time complexity is theta(n) for this and space complexity is theta(1)


    if (subroot != NULL) {
        DeleteTree(subroot->right);
        DeleteTree(subroot->left);
        delete subroot;
    }
}

BSTSet::~BSTSet()
{

	DeleteTree(root);

}

bool BSTSet::isInHelper(int v) const {///time complexity is theta(logn) for this and space complexity is theta(1)
	TNode* currentNode = root;

	while (currentNode) {

    	if (v < currentNode->element) {
			currentNode = currentNode->left;
    	}
		else if (v > currentNode->element) {

			currentNode = currentNode->right;
    	}
    	else {
    	    return true;
    	}
	}

    return false;
}

bool BSTSet::isIn(int v)

{

	return isInHelper(v);
}


void BSTSet::add(int v)////time complexity is theta(n) for this and space complexity is theta(1)

{
	if (root==NULL) {
		root = new TNode(v, NULL, NULL);
		return;
	}

	TNode* currentNode = root;

	while (currentNode) {
		if (v < currentNode->element) {
			if (currentNode->left!=NULL) {
				currentNode = currentNode->left;
			}
			else {
				currentNode->left = new TNode(v, NULL, NULL);
				return;
			}
		}

		else if (v > currentNode->element) {
			if (currentNode->right!=NULL) {
				currentNode = currentNode->right;
			}
			else {
				currentNode->right = new TNode (v, NULL, NULL);
				return;
			}
		}

		else {
			return;
		}
	}
}

TNode* BSTSet::findMin(TNode* subroot) {////time complexity is theta(n) for this and space complexity is theta(1)

	TNode* currentNode = subroot;
	while (currentNode->left!=NULL) {
		currentNode=currentNode->left;
	}
	return currentNode;
}

void BSTSet::removeFunc(int v, TNode*& subroot) {//both time and space complexities are theta(n)


    if (subroot == NULL) {
    	return;
    }
	if (v < subroot->element) {
        removeFunc(v, subroot->left);
    }
    else if (v > subroot->element) {
        removeFunc(v, subroot->right);
    }
    else if (subroot->left!=NULL && subroot->right!=NULL) {
        subroot -> element = findMin(subroot->right)->element;

        removeFunc(subroot->element, subroot->right);
    }
    else {
    	TNode* toDelete = subroot;
    	subroot = (subroot->left != NULL) ? subroot->left : subroot->right;
        delete toDelete;
    }
}

bool BSTSet::remove(int v)

{

	if (isIn(v)==true) {
		removeFunc(v, root);
		return true;
	}
	else {
		return false;
	}


}
void BSTSet::UnionHelper(TNode* subroot) {//timecomplexity is theta(nlogn) space complexity is theta(n)
    if (subroot != NULL) {
        UnionHelper(subroot->left);
        add(subroot->element);
        UnionHelper(subroot->right);
    }
}


void BSTSet::Union(const BSTSet& s) {//time complexity of theta(nlogn) space complexity theta(n)
	if (s.root == NULL) {
		return;
	}

	std::stack<TNode*> stack1, stack2;

	TNode* current1 = root;
	TNode* current2 = s.root;

	while (current1 != NULL || !stack1.empty() || current2 != NULL || !stack2.empty()) {
		if (current1 != NULL || current2 != NULL) {
			if (current1 != NULL) {
				stack1.push(current1);
				current1 = current1->left;
			}
			if (current2 != NULL) {
				stack2.push(current2);
				current2 = current2->left;
			}
		}
		else {
			if (stack1.empty()) {
				while (!stack2.empty()) {
					current2 = stack2.top();
					stack2.pop();
					add(current2->element);
					UnionHelper(current2->right);
				}
				return;
			}
			if (stack2.empty()) {
				while (!stack1.empty()) {
					current1 = stack1.top();
					stack1.pop();
					add(current1->element);
					UnionHelper(current1->right);
				}
				return;
			}

			current1 = stack1.top();
			stack1.pop();
			current2 = stack2.top();
			stack2.pop();

			if (current1->element < current2->element) {
				add(current1->element);
				current1 = current1->right;
				stack2.push(current2);
				current2 = NULL;
			}
			else {
				add(current2->element);
				current2 = current2->right;
				stack1.push(current1);
				current1 = NULL;
			}
		}
	}
}


void BSTSet::IntersectionHelper(TNode* subroot, const BSTSet& toTraverse) { //both space and time complexity is theta(n)

    if (subroot!=NULL) {
        IntersectionHelper(subroot->left, toTraverse);
		IntersectionHelper(subroot->right, toTraverse);
        if (toTraverse.isInHelper(subroot->element)==false) {
        	remove(subroot->element);
        }
    }
}


void BSTSet::intersection(const BSTSet& s)//

{

	IntersectionHelper(root, s);

}


void BSTSet::difference(const BSTSet& toTraverse) {//time complexity is theta(nlogn) and space complexity theta(n)
    if (root == NULL) {
        return;
    }

    stack<TNode*> s1;
    stack<TNode*> s2;
    s1.push(root);

    while (!s1.empty()) {
        TNode* temp = s1.top();
        s1.pop();
        s2.push(temp);

        if (temp->left != NULL) {
            s1.push(temp->left);
        }
        if (temp->right != NULL) {
            s1.push(temp->right);
        }
    }

    while (!s2.empty()) {
        TNode* subroot = s2.top();
        s2.pop();

        if (toTraverse.isInHelper(subroot->element)) {
            remove(subroot->element);
        }
    }
}

int BSTSet::size() {//timecomplexity is theta(n) and space complexity is theta(n)
    if (!root) {
        return 0;
    }
    int count = 1;
    std::stack<TNode*> stack;
    stack.push(root);
    while (!stack.empty()) {
        TNode* current = stack.top();
        stack.pop();
        if (current->left) {
            stack.push(current->left);
            count++;
        }
        if (current->right) {
            stack.push(current->right);
            count++;
        }
    }
    return count;
}


int heightBST(TNode* subroot) {//timecomplexity is theta(n) and space complexity is theta(logn)

    if (subroot == NULL) {
        return 0;
    }
    else {

        int LeftHeight = heightBST(subroot->left);

        int RightHeight = heightBST(subroot->right);


        if (LeftHeight>RightHeight) {
            return LeftHeight+1;
        }
        else {
            return RightHeight+1;
        }
    }
}

int BSTSet::height()

{

	return heightBST(root)-1;
}


void BSTSet::printNonRec()//spacecomplexity is theta(n) and time complexity is theta(n)

{


	if (root==NULL) {
		return;
	}

	ArrayStack<TNode*> print;
	TNode* currentNode = root;

	while (currentNode!=NULL || print.isEmpty()==false) {
		while (currentNode) {
			print.push(currentNode);
			currentNode=currentNode->left;
		}

		currentNode=print.top();
		cout<<(print.pop()->element)<<",";
		currentNode=currentNode->right;
	}
	return;
}




void BSTSet::printBSTSet()//both space and time complexity is theta(n)
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)///both space and time complexity is theta(n)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}