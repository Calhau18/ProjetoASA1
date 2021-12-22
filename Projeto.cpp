#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Node{
	public:
		int value;
		int pos1, pos2;
		int depth;
		unsigned long long seq_count, cum_seq_count;

		Node(int val){
			value = val;
			cum_seq_count = 0;
			pos1 = -1;
			pos2 = -1;
			seq_count = 1;
		}

		Node(int val, int p1, int p2){
			value = val;
			pos1 = p1;
			pos2 = p2;
			seq_count = 0;
			cum_seq_count = -1;
		}

		bool operator > (const Node& other){
			return this->value > other.value &&
				this->pos1 >= other.pos1 && this->pos2 >= other.pos2; 
		}
};

bool comp(const Node* a, const Node* b){
	return a->value < b->value;
}

void insertNode1(Node * new_node, vector<Node*> * top, vector< vector<Node*> > * piles){
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

void solve1(vector<int> v){
	vector<Node*> top;
	vector< vector<Node*> > piles;
	for(int i=0; i<(int)v.size(); i++){
		Node * new_node = new Node(v[i]);
		insertNode1(new_node, &top, &piles);
	}
	cout << top.back()->depth << " " << top.back()->cum_seq_count << endl;
}

void insertNode2(Node* new_node, list<Node*> * l){
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
				l->insert(border, new_node);
				inserted = true;
			}
		}
	}
}

void solve2(vector<int> v1, vector<int> v2){
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
			insertNode2(new_node, &l);
		}
	}
	cout << l.front()->depth << endl;
	// To get number of maximum length increasing common subsequences just sum 
	// seq_count for x from l.begin() while x->depth == l.begin()->depth
}

				
int main(){
	int prob_num; cin >> prob_num;
	int k; char c;
	if(prob_num == 1){
		vector<int> v;
		do{
			scanf("%d%c", &k, &c);
			v.push_back(k);
		}while(c - '\n');
		solve1(v);
	}

	if(prob_num == 2){
		vector<int> v1, v2;
		do{
			scanf("%d%c", &k, &c);
			v1.push_back(k);
		}while(c - '\n');
		do{
			scanf("%d%c", &k, &c);
			v2.push_back(k);
		}while(c - '\n');

		if(v2.size() > v1.size()) 
			solve2(v1, v2);
		else 
			solve2(v2, v1);
	}

	return 0;
}
