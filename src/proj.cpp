#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int parse_inverse(vector<int> *v, vector<vector<int>> *a, int edg_qnt) {
	int start, end;
	for (int i = 0; i < edg_qnt;  i++) {
		cin >> end;
		cin >> start;
		start--;
		end--;
		(*v)[start]++;
		if ((*v)[start] <= 2) {
			((*a)[start]).push_back(end);
		}
		else {
			cout << 0 << endl;
			return -1;
		}
	}
	return 0;
}

void* bfs(int start, vector<int> *vt, vector<vector<int>> *a, int vert_qnt, int edg_qnt) {
	int u;
	int v;
	vector<int> color;
	vector<int> dist;
	vector<int> pred;
	queue<int> q;
	for (int i = 0; i < vert_qnt; i++) {
		color.push_back(0);
		dist.push_back(0);
		pred.push_back(-1);
	}
	color[start] = 1;
	q.push(start);
	while(!q.empty()) {
		u = q.front(); 
		q.pop();
		for (int i = 0; i < ((*a)[u]).size(); i++) {
			v = (*a)[u][i];
			if (color[v] == 0) {
				color[v] = 1;
				(*vt)[v]++;
				dist[v] = dist[u] + 1;
				pred[v] = u;
				q.push(v);
			}
		}
	}
}

int main() {
	vector<int> vertexes;
	vector<vector<int>> adjecent;
	int v1, v2, vert_qnt, edg_qnt;
	cin >> v1;
	cin >> v2;
	cin >> vert_qnt;
	cin >> edg_qnt;
	v1--;
	v2--;
	for (int i = 0; i < vert_qnt; i++) {
		vertexes.push_back(0);
	}
	if (parse_inverse(&vertexes, &adjecent, edg_qnt) == -1) {
		return 0;
	}
	for (int i = 0; i < vert_qnt; i++) {
		vertexes[i] = 0;
	}
	bfs(v1, &vertexes, &adjecent, vert_qnt, edg_qnt);
	bfs(v2, &vertexes, &adjecent, vert_qnt, edg_qnt);
	return 0;
}
