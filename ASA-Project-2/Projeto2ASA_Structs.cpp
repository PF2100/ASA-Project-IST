#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node{
	int _value;
	int _parent;
	int _rank;
};

struct Edge{
	Node _u;
	Node _v;
	int _trade_amount;
};

int trades;
int nodes;
int edges;
Node* _nodes;
Edge* _edges; 

bool comparator(Edge edge1, Edge edge2) {
    return edge1._trade_amount > edge2._trade_amount;
}

void graphInit(){
    scanf("%d\n%d",&nodes,&edges);
    _nodes = new Node[nodes + 1];
    for(int node = 0; node <= nodes ; node++){
        _nodes[node] = Node{node,node,0};
    }
    _edges = new Edge[edges];
    for(int edge = 0 ; edge < edges; edge++){
		int u;
		int v;
		int trade_value;
        scanf("%d",&u);
        scanf("%d",&v);
        scanf("%d",&trade_value);
		_edges[edge] = Edge{_nodes[u],_nodes[v],trade_value};

    }
    sort(_edges, _edges + edges, comparator);
}

int find_set(Node* node){
    if ( node->_value != node->_parent){
      node->_parent = find_set(&_nodes[node->_parent]);
    }
    return node->_parent;
}

void unite_set(Node* u, Node* v){
    if(u->_rank > v->_rank){
        v->_parent = u->_value;
    }
    else{
        u->_parent = v->_value;
        if(u->_rank == v->_rank){
            v->_rank++;
        }
    }
}

void calculate_trades(){
    for(int i = 0 ; i < edges ; i++){
		Edge edge = _edges[i];
        Node* u = &_nodes[edge._u._value];
        Node* v = &_nodes[edge._v._value];
        if( find_set(u) != find_set(v) ) {
            unite_set(&_nodes[u->_parent], &_nodes[v->_parent]);
            trades += edge._trade_amount;
        }
    }
}

int main(){
    graphInit();
    if(nodes != 0 && edges != 0){
        calculate_trades();
    }
    printf("%d\n",trades);
}