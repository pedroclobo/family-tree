#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef struct {
	size_t v;
	size_t e;
	vector<vector<int>> l;
} graph;

void parse_transpose_graph(graph *transpose, vector<vector<int>> *normal) {
	cin >> transpose->v >> transpose->e;

	transpose->l.resize(transpose->v);
	(*normal).resize(transpose->v);

	int x, y;
	for (size_t i = 0; i < transpose->e; i++) {
		scanf("%d %d", &x, &y);
		x--; y--;
		transpose->l[y].push_back(x);
		(*normal)[x].push_back(y);
	}
}

void print_graph(graph *g) {
	for (size_t v = 0; v < g->v; v++) {
		cout << v + 1 << ": ";
		for (size_t e = 0; e < g->l[v].size(); e++) {
			cout << g->l[v][e] + 1 << " ";
		}
		cout << endl;
	}
}

bool dfs(graph *g, int u, int *colors) {
	colors[u] = 1;

	for (int v: g->l[u]) {
		if (colors[v] == 0) {
			if (!dfs(g, v, colors)) {
				return false;
			}
		} else if (colors[v] == 1) {
			return false;
		}
	}

	colors[u] = 2;

	return true;
}

bool valid_tree(graph *g) {
	int *colors = (int*) malloc(sizeof(int) * g->v);

	for (size_t u = 0; u < g->v; u++) {
		colors[u] = 0;
	}

	for (size_t u = 0; u < g->v; u++) {
		if (g->l[u].size() > 2) {
			free(colors);
			return false;
		}
		if (colors[u] == 0) {
			if (!dfs(g, u, colors)) {
				free(colors);
				return false;
			}
		}
	}

	free(colors);

	return true;
}

void bfs(int s, graph *g, int *commons) {
	int *colors = (int*) malloc(sizeof(int) * g->v);
	queue<int> q;

	for (size_t v = 0; v < g->v; v++) {
		colors[v] = 0;
	}

	colors[s] = 1;
	q.push(s);
	commons[s]++;

	int u, v;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (size_t e = 0; e < g->l[u].size(); e++) {
			v = g->l[u][e];
			if (colors[v] == 0) {
				colors[v] = 1;
				commons[v]++;
				q.push(v);
			}
		}
		colors[u] = 1;
	}

	free(colors);
}

int main() {
	int v1, v2;
	cin >> v1 >> v2;
	v1--; v2--;

	graph transpose;

	vector<vector<int>> normal;

	parse_transpose_graph(&transpose, &normal);

	if (!valid_tree(&transpose)) {
		cout << 0 << endl;
		return 0;
	}

	int *commons = (int*) malloc(sizeof(int) * transpose.v);

	for (size_t v = 0; v < transpose.v; v++) {
		commons[v] = 0;
	}


	bfs(v1, &transpose, commons);
	bfs(v2, &transpose, commons);

	int num_commons = 0;
	for (size_t v = 0; v < transpose.v; v++) {
		size_t size_adj = normal[v].size(); 
		bool valid = true;
		if (size_adj == 0) {
			valid = false;
		}
		for (size_t i = 0; i < size_adj; i++) {
			if (!(commons[v] == 2 && commons[normal[v][i]] != 2 && valid)) {
				valid = false;
			}
		}
		if (valid) {
			printf("%lu ", v + 1);
			num_commons++;
		}	
	}

	if (num_commons == 0) {
		cout << "-";
	}
	cout << endl;

	free(commons);

	return 0;
}