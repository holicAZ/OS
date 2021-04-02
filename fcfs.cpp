#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
typedef pair<int, int> pii;
vector<pii> v;
int main(void) {
	ifstream in("fcfs.inp");
	ofstream out("fcfs.out");
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		int arrive, work;
		in >> arrive >> work;
		v.push_back({ arrive,work });
	}
	int sum = v[0].second; // working time, + P1 working time
	int ans = 0; // waiting time
	if (v[0].first != 0) {
		sum += v[0].first;
	}

	for (int i = 1; i < n; i++) {
		if (sum < v[i].first) {
			sum = v[i].first + v[i].second;
		}
		else {
			ans += sum - v[i].first;
			sum += v[i].second;
		}
	}
	out << ans;
	return 0;
}