#include<cstdio>
#include<vector>
int bit[2000006], n, f[2000006], cnt, in[2000006], out[2000006];
std::vector<int> E[2000006], e[2000006], _e[2000006];
long long ans;
int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
void add(int x, int y) {
	while (x <= n) bit[x] += y, x += x & -x;
}
int ask(int x) {
	int ret = 0;
	while (x) ret += bit[x], x -= x & -x;
	return ret;
}
void dfs(int u) {
	in[u] = ++cnt;
	for (int v : _e[u]) dfs(v);
	out[u] = cnt;
}
void solve(int u) {
	add(in[u], 1), add(out[u] + 1, -1);
	int cur = ask(in[u]);
	for (int v : e[u]) solve(v);
	ans += ask(in[u]) - cur;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		if (x) E[x].push_back(i), E[i].push_back(x);
	}
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 1; i <= n; i++) {
		for (int j : E[i]) {
			if (j < i && find(j) != find(i)) {
				e[find(i)].push_back(find(j));
				f[find(j)] = find(i);
			}
		}
	}
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = n; i >= 1; i--) {
		for (int j : E[i]) {
			if (j > i && find(j) != find(i)) {
				_e[find(i)].push_back(find(j));
				f[find(j)] = find(i);
			}
		}
	}
	dfs(1), solve(n);
	printf("%lld\n", ans);
}
