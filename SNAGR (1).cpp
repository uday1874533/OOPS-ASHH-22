#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long llu; typedef long long int lld; typedef long double Lf; typedef double lf;


const int dx[8] { -1, 0, 1, 0, -1, -1, 1, 1}, dy[8] {0, 1, 0, -1, -1, 1, 1, -1}; // for every grid problem!!
const int32_t MOD = 1e9 + 7;
const int32_t MM = 998244353;
const int MX = (int)2e5 + 5;
const long long INF = 2e18;
const int N = 1e7 + 1;



void solve() {
	int n, q; cin >> n >> q;
	vector<string> grid(n); for (auto &i : grid) cin >> i;

	unordered_map<char, pair<int, int>> mp;
	mp['L'] = {0, -1};
	mp['R'] = {0, 1};
	mp['D'] = {1, 0};
	mp['U'] = { -1, 0};

	vector firstTime(n, vector(n, n * n + 5));  //calculated first time when {i, j} will get visited by the snake.
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == '.') continue;

			auto [dx, dy] =  mp[grid[i][j]];

			int x = i, y = j;
			for (int k = 0; k < n ; k++) {
				firstTime[x][y] = min(firstTime[x][y], k);
				x += dx ; y += dy;

				if (min(x, y) < 0 || max(x, y) >= n) break;
			}
		}
	}



	function<int(int)> bfs01 = [&](int t)->int{    //time= O(n*n)
		deque<pair<int, int>> q;
		vector<vector<int>> dist(n, vector<int>(n, n * n + 5));
		q.push_back({0, 0}); dist[0][0] = firstTime[0][0] <= t;

		while (!q.empty()) {
			auto [i, j] = q.front(); q.pop_front();

			for (int d = 0; d < 4; d++) {
				int newI = i + dx[d] , newJ = j + dy[d];
				if (min(newI, newJ) < 0  || max(newI , newJ) >= n ) continue;

				int cost = firstTime[newI][newJ] <= t;
				if (dist[newI][newJ] > dist[i][j] + cost) {
					dist[newI][newJ] = dist[i][j] + cost;

					if (cost == 0) q.push_front({newI, newJ});
					else q.push_back({newI, newJ});
				}
			}
		}

		return dist[n - 1][n - 1];
	};

	vector<int> points(n + 2);
	for (int t = 0; t <= n + 1; t++) {
// 		if (t > 0 && points[t - 1] == 2 * n - 1) points[t] = points[t - 1];
// 		else 
		points[t] = bfs01(t);
	}

	for (int i = 0, time; i < q; i++) {
		cin >> time; time--;
		cout << points[min(time, n + 1)] << '\n';
	}


}
/*
-> At time = n all the snakes will get extended to its maximum. After that time will be same.
*/

int main()
{
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

	int _ = 1;
	// cin >> _;
	while (_--) {
		// cout << "Case " << i << ": ";
		solve();
	}

	return 0;
}
