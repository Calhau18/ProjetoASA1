#include <bits/stdc++.h>
using namespace std;

class Node{
	public:
		int value;
		int pos1, pos2;
		int depth;
		int seq_count;
		
		Node(int val, int p1, int p2){
			value = val;
			pos1 = p1;
			pos2 = p2;
			seq_count = 0;
		}

		bool operator > (const Node& other){
			return this->value > other.value &&
				this->pos1 > other.pos1 && this->pos2 > other.pos2; 
		}
};

void insertNode(Node* new_node, list<Node*> * l){
	list<Node*>::iterator border = l->begin(); 
	bool inserted = false;
	for(list<Node*>::iterator it = l->begin();; ++it){
		// Case in which there is no node in l which is before the new element
		// in a possible increasing common sequence
		if(it == l->end()){
			if(!inserted){
				new_node->depth = 1;
				new_node->seq_count = 1;
				l->insert(l->end(), new_node);
			}
			break;
		}if((*it)->depth != (*border)->depth){
			if(inserted) break;
			border = it;
		// Case in which the new node is to be inserted
		}if(*new_node > **it){
			new_node->seq_count += (*it)->seq_count;
			if(!inserted){
				new_node->depth = ((*it)->depth)+1;
				l->insert(it, new_node);
				inserted = true;
			}
		}
	}
}

void solve(vector<int> v1, vector<int> v2){
	list<Node*> l;
	unordered_multimap<int,int> val2;
	for(int i=0; i<(int)v2.size(); i++){
		val2.emplace(v2[i], i);
	}

	for(int i=0; i<(int)v1.size(); i++){
		unordered_multimap<int,int>::iterator it = val2.equal_range(v1[i]).first;
		unordered_multimap<int,int>::iterator last = val2.equal_range(v1[i]).second;
		for(; it != last; it++){
			Node* new_node = new Node(v1[i], i, it->second);
			insertNode(new_node, &l);
		}
	}

	int max_seq_count = 0;
	for(list<Node*>::iterator it = l->begin(); (*it)->depth == (*(l->begin()))->depth; it++){
		max_seq_count += (*it)->seq_count;
	}

	cout << l.front()->depth << endl;
}

				
int main(){
	vector<int> v1, v2;
	int k; char c;
	do{
		scanf("%d%c", &k, &c);
		v1.push_back(k);
	}while(c - '\n');
	do{
		scanf("%d%c", &k, &c);
		v2.push_back(k);
	}while(c - '\n');

	if(v2.size() > v1.size()) 
		solve(v1, v2);
	else 
		solve(v2, v1);

	return 0;
}
