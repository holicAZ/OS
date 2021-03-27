#include<iostream>
#include<vector>
using namespace std;
typedef pair<int, int> pii;
vector<pii> v;
int main(void) {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int arrive, work;
		cin >> arrive >> work;
		v.push_back({ arrive,work });
	}
	int sum = v[0].second; // working time, + P1 working time
	int ans = 0; // waiting time
	if (v[0].first != 0) {
		ans = v[0].first * (n - 1);
	}
	for (int i = 1; i < n; i++) {
		if (sum < v[i].first) {
			sum += v[i].second;
		}
		else
			ans += sum - v[i].first;
		
	}
	cout << ans;
	return 0;
}
