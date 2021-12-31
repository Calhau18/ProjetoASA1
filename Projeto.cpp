#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Node{
	public:
		int value;
		int pos1, pos2;
		int cum_seq_count;

		Node(int val){
			value = val;
			cum_seq_count = 0;
		}

		Node(int val, int p1, int p2){
			value = val;
			pos1 = p1;
			pos2 = p2;
		}
};

bool comp(Node* a, Node* b){
	return a->value < b->value;
}

void solve1(vector<int> v){
	vector<int> top;
	vector< vector<Node*> > piles;
	for(int i=0; i<(int)v.size(); i++){
		Node * new_node = new Node(v[i]);
		// Get iterator and position of the pile in which new_node is to be inserted
		vector<int>::iterator pile = lower_bound(top.begin(), top.end(), new_node->value);
		int index = pile - top.begin();

		if(piles.size() == 0){
			new_node->cum_seq_count = 1;
		}else if(index == 0){
			new_node->cum_seq_count = piles[0].size()+1;	
		}else{
			if(index != (int)top.size()-1)
				new_node->cum_seq_count = piles[index].back()->cum_seq_count;

			vector<Node*> v = piles[index-1];
			auto it = lower_bound(v.rbegin(), v.rend(), new_node, comp); 
			if(it != v.rend())
				new_node->cum_seq_count += v.back()->cum_seq_count - (*it)->cum_seq_count;
			else
				new_node->cum_seq_count += v.back()->cum_seq_count;
		}

		// Insert new_node in the table
		if(index != (int)top.size()-1){
			top[index] = new_node->value;
			piles[index].push_back(new_node);
		}else{
			top.push_back(new_node->value);
			vector<Node*> v(1, new_node);
			piles.push_back(v);
		}
	}
	cout << piles.size() << " " << piles.back().back()->cum_seq_count << endl;
}

bool bigger(Node* a, Node* b){
	return a->value > b->value && a->pos1 > b->pos1 && a->pos2 > b->pos2;
}

void solve2(vector<int> v1, vector<int> v2){
	vector< vector<Node*> > piles;
	unordered_multimap<int,int> val2;
	for(int i=0; i<(int)v2.size(); i++){
		val2.emplace(v2[i], i);
	}

	for(int k=0; k<(int)v1.size(); k++){
		unordered_multimap<int,int>::iterator it = val2.equal_range(v1[k]).first;
		unordered_multimap<int,int>::iterator last = val2.equal_range(v1[k]).second;
		Node* new_node;
		if(piles.size() == 0 && it != last){
			new_node = new Node(v1[k], k, it->second);
			vector<Node*> v(1, new_node);
			piles.push_back(v);
			it++;
		}
		bool just_inserted = true;
		for(int i=(int)piles.size()-1; i>=0 && it != last; i--){
			for(int j=0; j<(int)piles[i].size() && it != last; j++){
				if(just_inserted){
					new_node = new Node(v1[k], k, it->second);
					just_inserted = false;
				}
				if(bigger(new_node, piles[i][j])){
					if(i == (int)piles.size()-1){
						vector<Node*> v(1, new_node);
						piles.push_back(v);
					}else{
						piles[i+1].push_back(new_node);
					}
					it++;
					j--;
					just_inserted = true;
				}
			}
		}
		while(it != last){
			new_node = new Node(v1[k], k, it->second);
			piles[0].push_back(new_node);
			it++;
		}
	}
	cout << piles.size() << endl;
}

int main(){
	int prob_num; cin >> prob_num;
	int k; char c = 0;
	if(prob_num == 1){
		vector<int> v;
		while(c != '\n' && c != EOF){
			scanf("%d%c", &k, &c);
			v.push_back(k);
		}
		solve1(v);
	}

	if(prob_num == 2){
		vector<int> v1, v2;
		while(c != '\n' && c != EOF){
			scanf("%d%c", &k, &c);
			v1.push_back(k);
		}
		c = 0;
		while(c != '\n' && c != EOF){
			scanf("%d%c", &k, &c);
			v2.push_back(k);
		}

		if(v1.size() > v2.size())
			solve2(v2, v1);
		else solve2(v1, v2);

	}

	return 0;
}

