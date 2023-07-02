/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree{
public:
	BPlusTree(int deg) : root(NULL), degree(deg){};
	BPlusTree(const BPlusTree<T>& old) : degree(old.degree){
		root = this->copy_tree(old.root, NULL);
	}
	~BPlusTree(){
		this->destroy_tree(root);
		root = NULL;
	}
	BPlusTree& operator=(const BPlusTree<T>& old) {
		if (&old != this) {
			this->destroy_tree(root);
			root = this->copy_tree(old.root ,NULL);
			degree = old.degree;
		}
    	return *this;
  	}
	void insert(const T& val);
	void checkparent(BPlusTreeNode<T>*& temp);
	BPlusTreeNode<T>* find(const T& val);
	void print_BFS(std::ostream& ostr);
	void print_BFS_pretty(std::ostream& ostr);
	void print_sideways(std::ostream& ostr);

private:
	void destroy_tree(BPlusTreeNode<T>* p);
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent);
	void print_sideways(std::ostream& ostr, BPlusTreeNode<T>* p ,int depth);
	BPlusTreeNode<T>* root;
	int degree;
};

//This function will destroy the tree recursively in a post-order fashion
//deletes children first, and then the parent
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p){
	if(p==NULL){
		return;
	}
	else if(p->is_leaf()){
		delete p;
		return;
	}
	for(int i = 0; i<(p->children).size(); i++){
		destroy_tree((p->children)[i]);
	}
	
	delete p;
}

//This function recursively copies the tree in a pre order fashion. CReates a new node
//for the current node and then calls again with each of the children
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root, 
BPlusTreeNode<T>* the_parent){
	if(old_root == NULL){
		return NULL;
	}
	BPlusTreeNode<T>* newnode = new BPlusTreeNode<T>();
	newnode->keys = old_root->keys;
	for(int i = 0; i<(old_root->children).size(); i++){
		(newnode->children).push_back(copy_tree((old_root->children)[i],newnode));
	}
	newnode->parent = the_parent;
	return newnode;
}

//calls driver function
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& ostr){
	print_sideways(ostr, root, 0);
}

//recursive function to print sideways, in in-order transversing
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& ostr, BPlusTreeNode<T>* p ,int depth){
	if(p == NULL){
		ostr<<"Tree is empty.\n";
		return;
	}
	//calls print sideways until a leaf is reached for the first half of the children,
	//adds 1 to the depth with each call
	int i = 0;
	if(!(p->is_leaf())){
		for( ; i<(p->children).size()/2; i++){
			print_sideways(ostr, (p->children)[i], depth+1);
		}
	}
	//prints each of the keys separated by commas
	std::string space(depth, '\t');
	ostr<<space;
	for(int k = 0; k<(p->keys).size(); k++){
		if(k==0)
			ostr<<(p->keys)[k];
		else{
			ostr<<","<<(p->keys)[k];
		}
	}
	ostr<<std::endl;
	//calls print sideways until a leaf is reached for the second half of the children,
	//adds 1 to the depth with each call
	if(!(p->is_leaf())){
		for( ; i<(p->children).size(); i++){
			print_sideways(ostr, (p->children)[i], depth+1);
		}
	}
}

template <class T>
void BPlusTree<T>::print_BFS_pretty(std::ostream& ostr){
	if(root == NULL){
		ostr<<"Tree is empty.\n";
		return;
	}
	std::vector<BPlusTreeNode<T>*> currentlevel;
	std::vector<BPlusTreeNode<T>*> nextlevel;
	std::vector<std::vector<BPlusTreeNode<T>*> > alllevels;
	currentlevel.push_back(root);
	//for each node in current vector, adds all children to next level(BFT)
	while(currentlevel.size()!=0){
		for(int i = 0; i<currentlevel.size(); i++){
			for(int j = 0; j<(currentlevel[i]->children).size(); j++){
				nextlevel.push_back((currentlevel[i]->children)[j]);
			}
		}
		//alllevels holds all the levels of the tree, currentlevel changes to nextlevel
		//for next iteration
		alllevels.push_back(currentlevel);
		currentlevel = nextlevel;
		nextlevel.clear();
	}

	//counts all the nodes in the tree by counting all the children in alllevels
	int total = 1;
	for(int i = 0; i<alllevels.size(); i++){
		for(int j = 0; j<alllevels[i].size(); j++){
			total+=((alllevels[i][j])->children).size();
		}
	}
	//goes through each level and node and prints out the keys, wilt "total" tabs
	//before and after the keys are printed
	total = total/2;
	for(int i = 0; i<alllevels.size(); i++){
		for(int j = 0; j<alllevels[i].size(); j++){
			ostr<<std::string(total, '\t');
			for(int k = 0; k<(alllevels[i][j]->keys).size(); k++){
				if(k==0)
					ostr<<(alllevels[i][j]->keys)[k];
				else{
					ostr<<","<<(alllevels[i][j]->keys)[k];
				}
			}
			ostr<<std::string(total, '\t');
		}
		ostr<<std::endl;
		//tatoal is halved with each descending level to decrease spacing
		total = total/2;
	}
}

template <class T>
void BPlusTree<T>::print_BFS(std::ostream& ostr){
	if(root == NULL){
		ostr<<"Tree is empty.\n";
		return;
	}
	std::vector<BPlusTreeNode<T>*> currentlevel;
	std::vector<BPlusTreeNode<T>*> nextlevel;
	currentlevel.push_back(root);
	//for each node in current vector, adds all children to next level(BFT)
	while(currentlevel.size()!=0){
		for(int i = 0; i<currentlevel.size(); i++){
			for(int j = 0; j<(currentlevel[i]->children).size(); j++){
				nextlevel.push_back((currentlevel[i]->children)[j]);
			}
			for(int k = 0; k<(currentlevel[i]->keys).size(); k++){
				if(k==0)
					ostr<<(currentlevel[i]->keys)[k];
				else{
					ostr<<","<<(currentlevel[i]->keys)[k];
				}
			}
			if(i!=currentlevel.size()-1)
				ostr<<"\t";

		}
		//currentlevel changes to nextlevel for next iteration, nextlevel cleared
		ostr<<std::endl;
		currentlevel = nextlevel;
		nextlevel.clear();
	}
}

//given a value, will return a painter to the node that the value is in or should
//be in
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& val){
	BPlusTreeNode<T>* temp = root;
	//empty tree
	if(temp == NULL){
		return temp;
	}
	//compares value with the keys, finding correct pointer in children
	//to follow until a leaf is reached
	while(!(temp->is_leaf())){
		int i = 0;
		for(; i<(temp->keys).size(); i++){
			if(val<(temp->keys)[i]){
				break;
			}
		}
		temp = (temp->children)[i];
	}
	return temp;
}

//helper function for insert, is called after the basic split occurs in the leaf nodes
//because rules for splitting parents are different than leafs
template <class T>
void BPlusTree<T>::checkparent(BPlusTreeNode<T>*& temp){
	if((temp->keys).size() < degree || temp == NULL){
		return;
	}
	else{
		int mid = degree/2;
		T midval = (temp->keys)[mid];
		BPlusTreeNode<T>* sister = new BPlusTreeNode<T>();
		//add second half of keys to sister node
		for(int j = mid+1; j<degree; j++){
			(sister->keys).push_back((temp->keys)[j]);
		}
		//delete added keys from original node
		for(int j = mid; j<degree; j++){
			(temp->keys).pop_back();
		}
		//add second half of children to sister node
		for(int j = mid+1; j<degree+1; j++){
			(sister->children).push_back((temp->children)[j]);
		}
		//delete second half of children from orginal node
		for(int j = mid+1; j<degree+1; j++){
			(temp->children).pop_back();
		}
		BPlusTreeNode<T>* temp2 = temp;
		//change parents so they point ot sister node, not original
		for(int j = 0; j<(sister->children).size(); j++){
			(sister->children)[j]->parent = sister;
		}
		temp = temp2;
		if(temp->parent == NULL){
			//create new root with middle value
			BPlusTreeNode<T>* newpar = new BPlusTreeNode<T>;
			(newpar->keys).push_back(midval);
			(newpar->children).push_back(temp);
			(newpar->children).push_back(sister);
			root = newpar;
			temp->parent = newpar;
			sister->parent = newpar;
			return;
		}
		else{
			//connect sister to parent
			sister->parent = temp->parent;
			((temp->parent)->keys).push_back(midval);
			std::sort(((temp->parent)->keys).begin(),((temp->parent)->keys).end());
			int index = 0;
			//find index to insert children
			for(; index<((temp->parent)->keys).size();index++){
				if(((temp->parent)->keys)[index] == midval){
					break;
				}
			}
			//insert children
			((temp->parent)->children).insert(((temp->parent)->children).begin()
			+index+1,sister);
			//call recusrion to check overfill of parent
			checkparent(temp->parent);
		}
	}
}

//main insert function, inserts value and splits leaf if necessary, then calls
//checkparent to check for parent overflow
template <class T>
void BPlusTree<T>::insert(const T& val){
	if(root == NULL){
		root = new BPlusTreeNode<T>;
		(root->keys).push_back(val);
		return;
	}
	//finds leaf that value should be inserted in
	BPlusTreeNode<T>* temp = root;
	while(!(temp->is_leaf())){
		int i = 0;
		for(; i<(temp->keys).size(); i++){
			if(val<(temp->keys)[i]){
				break;
			}
		}
		temp = (temp->children)[i];
	}
	(temp->keys).push_back(val);
	std::sort((temp->keys).begin(), (temp->keys).end());
	if((temp->keys).size() == degree){
		int mid = degree/2;
		T midval = (temp->keys)[mid];
		BPlusTreeNode<T>* sister = new BPlusTreeNode<T>;
		//add keys, including middle, to sister
		for(int j = mid; j<degree; j++){
			(sister->keys).push_back((temp->keys)[j]);
		}
		//delete same keys from temp
		for(int j = mid; j<degree; j++){
			(temp->keys).pop_back();
		}
		if(temp->parent == NULL){
			//create new root with same value as middle
			BPlusTreeNode<T>* newpar = new BPlusTreeNode<T>;
			(newpar->keys).push_back(midval);
			(newpar->children).push_back(temp);
			(newpar->children).push_back(sister);
			root = newpar;
			temp->parent = newpar;
			sister->parent = newpar;
		}
		else{
			//connect sister to parent
			sister->parent = temp->parent;
			((temp->parent)->keys).push_back(midval);
			std::sort(((temp->parent)->keys).begin(),((temp->parent)->keys).end());
			int index = 0;
			//find index to insert children
			for(; index<((temp->parent)->keys).size();index++){
				if(((temp->parent)->keys)[index] == midval){
					break;
				}
			}
			//insert children
			((temp->parent)->children).insert(((temp->parent)->children).begin()
			+index+1,sister);
		}
		//check overflow with parent
		checkparent(temp->parent);
	}
}


#endif
