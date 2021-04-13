#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

typedef pair<int, int> pii;
vector<pii> v;

int main(void) {
	ifstream in("hrrn.inp");
	ofstream out("hrrn.out");
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		int arrive, work;
		in >> arrive >> work;
		v.push_back({ arrive,work });
	}
	int sum = v[0].first + v[0].second;
	int ans = 0;
	v.erase(v.begin());
	
	while (!v.empty()) {
		int nxt = 0;
		double temp = -1;
		
		for (int i = 0; i < v.size(); i++) {
			if (v[i].first < sum) {
				double pri = ((double)((sum - v[i].first) + v[i].second) / (double)v[i].second); // 우선순위 구하기
				if (pri > temp) {
					nxt = i;
					temp = pri;
				}
			}
		}
		if (sum <= v[0].first) {
			sum = v[0].first + v[0].second;
			v.erase(v.begin());
			continue;
		}
		ans += sum - v[nxt].first;
		sum += v[nxt].second;
		v.erase(v.begin() + nxt);
	}
	out << ans;
	return 0;
}