#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
vector<pii> v;

int main(void) {
	ifstream in("sjf.inp");
	ofstream out("sjf.out");
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		int arrive, work;
		in >> arrive >> work;
		v.push_back({ work,arrive }); // first = work,  second = arrive;
	}
	int sum = v[0].first;
	int ans = 0;
	if (v[0].second != 0)
		sum += v[0].second;
	v.erase(v.begin());
	stable_sort(v.begin(), v.end());
	/*
		sort 우선 순위
		1. 실행시간 빠름
		2. 도착시간 빠름
		3. 입력시간(프로세스 번호) 빠름
	*/	
	int index;
	while (!v.empty()) {
		int nxt = 100000001; // reset
		int temp = sum; // check sum
		for (int i = 0; i < v.size(); i++) {
			if (sum >=v[i].second) { 
				ans += (sum - v[i].second);
				sum += v[i].first;
				v.erase(v.begin() + i);
				break;
				if (v.empty())
					break;
			}
			else { // nxt = save quick arrival time, index = nxt's vector index
				if (nxt > v[i].second) {
					nxt = v[i].second;
					index = i;
				}
			}
		}
		if (sum == temp) { // working time sum check
			sum = v[index].first + v[index].second;
			v.erase(v.begin() + index);
		}
	}
	out << ans;
	return 0;
}