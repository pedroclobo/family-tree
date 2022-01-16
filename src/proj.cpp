#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef struct {
	size_t v;
	size_t e;
	vector<int> *l;
} graph;

typedef enum { WHITE = 0, GRAY = 1, BLACK = 2 } color;

void parse_graph(graph *g) {
	cin >> g->v >> g->e;

	g->l = new vector<int>[g->v];

	int x, y;
	for (size_t i = 0; i < g->e; i++) {
		cin >> x >> y;
		x--; y--;
		g->l[x].push_back(y);
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

bool dfs(graph *g, int u, color *colors) {
	colors[u] = GRAY;

	for (int v: g->l[u]) {
		if (colors[v] == WHITE) {
			if (!dfs(g, v, colors)) {
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
	color colors[g->v];

	for (size_t u = 0; u < g->v; u++) {
		colors[u] = WHITE;
	}

	for (size_t u = 0; u < g->v; u++) {
		if (g->l[u].size() > 2) {
			return false;
		}
		if (colors[u] == WHITE) {
			if (!dfs(g, u, colors)) {
				return false;
			}
		}
	}

	return true;
}

void inverse_graph(graph *g, graph *inverse) {
	inverse->v = g->v;
	inverse->e = g->e;
	inverse->l = new vector<int>[g->v];

	int y;
	for (size_t v = 0; v < g->v; v++) {
		for (size_t e = 0; e < g->l[v].size(); e++) {
			y = g->l[v][e];
			inverse->l[y].push_back(v);
		}
	}
}

void bfs(int s, graph *g) {
	color colors[g->v];
	int d[g->v];
	int pi[g->v];
	queue<int> q;

	for (size_t v = 0; v < g->v; v++) {
		colors[v] = WHITE;
		d[v] = 0;
		pi[v] = -1;
	}

	colors[s] = GRAY;
	q.push(s);

	int u, v;
	while(!q.empty()) {
		u = q.front();
		q.pop();
		for (size_t e = 0; e < g->l[u].size(); e++) {
			v = g->l[u][e];
			if (colors[v] == WHITE) {
				colors[v] = GRAY;
				d[v] = d[u] + 1;
				pi[v] = u;
				q.push(v);
			}
		}
	}
}

int main() {
	int v1, v2;
	cin >> v1 >> v2;
	v1--; v2--;

	graph g;
	parse_graph(&g);

	if (!valid_tree(&g)) {
		cout << 0 << endl;
		return 0;
	}

	graph inverse;
	inverse_graph(&g, &inverse);

	bfs(v1, &inverse);
	bfs(v2, &inverse);

	delete[] g.l;
	delete[] inverse.l;

	return 0;
}
