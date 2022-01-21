#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef struct {
	size_t v;
	size_t e;
	vector<vector<int>> l;
} graph;

typedef enum { WHITE = 0, GRAY = 1, BLACK = 2 } color;

void parse_transpose_graph(graph *transpose) {
	cin >> transpose->v >> transpose->e;

	transpose->l.resize(transpose->v);

	int x, y;
	for (size_t e = 0; e < transpose->e; e++) {
		scanf("%d %d", &x, &y);
		x--; y--;
		transpose->l[y].push_back(x);
	}
}

void build_common_graph(graph *commons, graph *transpose, int *visited) {
	commons->v = transpose->v;
	commons->e = transpose->e;
	commons->l.resize(transpose->v);

	int y;
	for (size_t v = 0; v < transpose->v; v++) {
		if (visited[v] == 2) {
			for (size_t e = 0; e < transpose->l[v].size(); e++) {
				y = transpose->l[v][e];
				if (visited[y] == 2) {
					commons->l[y].push_back(v);
				}
			}
		}
	}
}

bool tree_dfs_visit(graph *g, int u, color *colors) {
	colors[u] = GRAY;

	for (int v: g->l[u]) {
		if (colors[v] == WHITE) {
			if (!tree_dfs_visit(g, v, colors)) {
				return false;
			}
		} else if (colors[v] == GRAY) {
			return false;
		}
	}

	colors[u] = BLACK;

	return true;
}

bool valid_tree(graph *g) {
	color *colors = (color*) malloc(sizeof(color) * g->v);
	for (size_t u = 0; u < g->v; u++) {
		colors[u] = WHITE;
	}

	for (size_t u = 0; u < g->v; u++) {
		if (g->l[u].size() > 2) {
			free(colors);
			return false;
		}
		if (colors[u] == WHITE) {
			if (!tree_dfs_visit(g, u, colors)) {
				free(colors);
				return false;
			}
		}
	}

	free(colors);

	return true;
}

void bfs(int s, graph *g, int *visited) {
	color *colors = (color*) malloc(sizeof(color) * g->v);
	for (size_t v = 0; v < g->v; v++) {
		colors[v] = WHITE;
	}

	colors[s] = GRAY;
	visited[s]++;

	queue<int> q;
	q.push(s);

	int u, v;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (size_t e = 0; e < g->l[u].size(); e++) {
			v = g->l[u][e];
			if (colors[v] == 0) {
				colors[v] = GRAY;
				visited[v]++;
				q.push(v);
			}
		}
		colors[u] = BLACK;
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

	int *visited = (int*) malloc(transpose.v * sizeof(int));
	for (size_t v = 0; v < transpose.v; v++) {
		visited[v] = 0;
	}

	bfs(v1, &transpose, visited);
	bfs(v2, &transpose, visited);

	graph commons;
	build_common_graph(&commons, &transpose, visited);

	int num_visited = 0;
	for (size_t v = 0; v < transpose.v; v++) {
		if (visited[v] == 2 && commons.l[v].size() == 0) {
			cout << v + 1 << " ";
			num_visited++;
		}
	}

	if (num_visited == 0) {
		cout << "-";
	}
	cout << endl;

	free(visited);

	return 0;
}
