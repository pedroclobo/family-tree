#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef struct {
	size_t v;
	size_t e;
	vector<vector<int>> l;
} graph;

void parse_transpose_graph(graph *transpose) {
	cin >> transpose->v >> transpose->e;

	transpose->l.resize(transpose->v);

	int x, y;
	for (size_t i = 0; i < transpose->e; i++) {
		scanf("%d %d", &x, &y);
		x--; y--;
		transpose->l[y].push_back(x);
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

void bfs(int s, graph *g, int *commons, int *preds) {
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
				preds[v] = u;
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

	parse_transpose_graph(&transpose);

	if (!valid_tree(&transpose)) {
		cout << 0 << endl;
		return 0;
	}

	int *commons = (int*) malloc(sizeof(int) * transpose.v);
	int *pred1 = (int*) malloc(sizeof(int) * transpose.v);
	int *pred2 = (int*) malloc(sizeof(int) * transpose.v);

	for (size_t v = 0; v < transpose.v; v++) {
		commons[v] = 0;
		pred1[v] = -1;
	}
	for (size_t v = 0; v < transpose.v; v++) {
		commons[v] = 0;
		pred2[v] = -1;
	}

	bfs(v1, &transpose, commons, pred1);
	bfs(v2, &transpose, commons, pred2);

	int num_commons = 0;
	for (size_t v = 0; v < transpose.v; v++) {
		if (commons[v] == 2 && commons[pred1[v]] != 2 && commons[pred2[v]] != 2) {
			printf("%lu ", v + 1);
			num_commons++;
		}
	}

	if (num_commons == 0) {
		cout << "-";
	}
	cout << endl;

	free(commons);
	free(pred1);
	free(pred2);

	return 0;
}
