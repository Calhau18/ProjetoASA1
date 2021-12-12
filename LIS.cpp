#include <bits/stdc++.h>
using namespace std;

class Node{
	public:
		int value;
		int depth;
		unsigned long long cum_seq_count;

		Node(int v){ value = v; cum_seq_count = 0; }

		bool operator > (const Node& other){
			return this-> value > other.value;
		}
};

bool comp(const Node* a, const Node* b){
	return a->value < b->value;
}

void insertNode(Node * new_node, vector<Node*> * top, vector< vector<Node*> > * piles){
	// Get iterator and position of the pile in which new_node is to be inserted
	auto pile = lower_bound(top->begin(), top->end(), new_node, comp);
	int index = pile - top->begin();

	// Define new_node's depth and cum_seq_count value
	new_node->depth = index+1;
	if(piles->size() == 0){
		new_node->cum_seq_count = 1;
	}else if(index == 0){
		new_node->cum_seq_count = (*piles)[0].size()+1;	
	}else{
		if(pile != top->end())
			new_node->cum_seq_count = (*piles)[index].back()->cum_seq_count;

		vector<Node*> v = (*piles)[index-1];
		auto it = lower_bound(v.rbegin(), v.rend(), new_node, comp); 
		if(it != v.rend())
			new_node->cum_seq_count += v.back()->cum_seq_count - (*it)->cum_seq_count;
		else
			new_node->cum_seq_count += v.back()->cum_seq_count;
	}
	
	// Insert new_node in the table
	if(pile != top->end()){
		(*top)[index] = new_node;
		(*piles)[index].push_back(new_node);
	}else{
		top->push_back(new_node);
		vector<Node*> v(1, new_node);
		piles->push_back(v);
	}
}

void solve(vector<int> v){
	vector<Node*> top;
	vector< vector<Node*> > piles;
	for(int i=0; i<(int)v.size(); i++){
		Node * new_node = new Node(v[i]);
		insertNode(new_node, &top, &piles);
	}
	cout << top.back()->depth << " " << top.back()->cum_seq_count << endl;
}

int main(){
	vector<int> v;
	int k; char c;
	do{
        scanf("%d%c", &k, &c);
        v.push_back(k);
    }while(c != '\n');

	solve(v);

	return 0;
}
