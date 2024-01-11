#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <fstream>
#include <deque>
#include <queue>
#include <map>

using namespace std;

typedef long long ll;


const long double EPS = 1e-9;
const long long mod = 1000000007;
const long long inf = 1000000000;


long long norm(long long x, long long MOD) {
	return ((x % MOD) + MOD) % MOD;
}
long long add(long long x, long long y, long long MOD) {
	return norm(norm(x, MOD) + norm(y, MOD), MOD);
}
long long sub(long long x, long long y, long long MOD) {
	return norm(norm(x, MOD) - norm(y, MOD), MOD);
}
long long mul(long long x, long long c, long long MOD) {
	return norm(norm(x, MOD) * norm(c, MOD), MOD);
}
int gcd(int a, int b) {
	if (a < b) return gcd(b, a);
	if (b == 0) return a;
	return gcd(b, a % b);
}

long long fastpow(long long a, long long n, long long MOD) {
	if (n == 0) return 1;
	if (n % 2 == 1) return (a * fastpow(a, n - 1, MOD)) % MOD;
	long long temp = fastpow(a, n / 2, MOD);
	return (temp * temp) % MOD;
}
long long Mdiv(long long a, long long b, long long PMOD) {
	return mul(a, fastpow(b, PMOD - 2, PMOD), PMOD);
}
long long gcd_ext(long long a, long long b, long long& x, long long& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long d = gcd_ext(b, a % b, x, y);
	x -= a / b * y;
	swap(x, y);
	return d;
}
vector <int> factorization(long long n) {
	vector <int> p;
	for (int d = 2; d * d <= n; d++) {
		while (n % d == 0) {
			p.push_back(d);
			n /= d;
		}
	}
	if (n > 1) p.push_back(n);
	return p;
}
int phi(int n) {
	int res = n;
	for (int p = 2; p * p <= n; p++) {
		if (n % p == 0) res -= res / p;
		while (n % p == 0) n /= p;
	}
	if (n > 1) res -= res / n;
	return res;
}

vector<vector<pair<int, int>>> gr; //куда идем, и номер ребра
vector<int>d; //Поиск мостов DFS
vector<int>dp;
vector<bool>used;
vector<int>ans;

void dfs(int v, int p = -1, int edge = -1) {//вершина, предок, ребро, по которому пришли
	if (p == -1) {
		d[v] = 0;
	}
	else {
		d[v] = d[p] + 1;
	}
	used[v] = true;
	dp[v] = d[v]; //изначально выше самой вершины не можем
	for (auto i : gr[v]) {
		if (!used[i.first]) {
			dfs(i.first, v, i.second); //если не были в вершине dfs
			dp[v] = min(dp[v], dp[i.first]); //обновляемся
		}
		else if (i.second != edge) { //если были, обновляемся
			dp[v] = min(dp[v], d[i.first]);
		}
	}
	if (p != -1 && dp[v] == d[v]) {//если не корень и dp не поменялось, то мост
		ans.push_back(v);
	}
}


const int INF = 1000000005;
const int MAXN = 200005;

int t;
int n;


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	for (int u = 0; u < t; u += 1) {
		int n;
		cin >> n;
		vector<int>arr(n);
		vector<ll> suf(n + 1,0);
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		for (int i = n - 1; i >= 0; i--) {
			suf[i] = suf[i + 1] + arr[i];
		}
		long long ans = suf[0];
		for (int i = 1; i < n; i++) {
			if (suf[i] > 0) {
				ans += suf[i];
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
