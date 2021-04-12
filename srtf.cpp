#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
typedef pair<int, int> pii;
vector<pii> v;
int main(void) {
	int n;
	ifstream in("srtf.inp");
	ofstream out("srtf.out");
	in >> n;
	for (int i = 0; i < n; i++) {
		int arrive, work;
		in >> arrive >> work;
		v.push_back({ arrive,work });
	}
	sort(v.begin(), v.end());

	int ans = 0;
	int sum = v[0].first;
	int tmp = v[0].second;
	v.erase(v.begin());
	while (!v.empty()) {
		bool flag = false;
		for (int k = 0; k < v.size(); k++) {	
			if (sum > v[k].first) continue;
			int leftwork = tmp - abs(sum-v[k].first); // 다음 프로세스 도착시간 까지 실행한 후 남은 시간
				
			if (leftwork < 0) { // 다음 프로세스 도착전에 이전 프로세스 끝날 경우			
				if (sum+tmp < v[0].first) { // jump(다음 프로세스 도착시간이 너무 뒤일 경우) 경우
					flag = true;
					break;
				}
				break;
			}
			if (leftwork == 0) { // 다음 프로세스 도착과 동시에 끝난경우
				break;
			}
			if (leftwork > v[k].second) { // 다음 프로세스의 실행시간과 비교 > 이면 교체
				if (sum == v[k].first) {
					ans += tmp;
					sum += tmp;
					tmp = v[k].second;
					v.erase(v.begin());
					k=-1;
					continue;
				}
				if (sum - v[k].first > 0)
					ans += sum - v[k].first;
				tmp = v[k].second;
				sum += v[k].first - sum;
				v.erase(v.begin()+k);
				v.push_back({ sum,leftwork });
				sort(v.begin(), v.end());
				continue;
			}
			
		}
		if (flag) {
			sum = v[0].first;
			tmp = v[0].second;
			v.erase(v.begin());
			continue;
		}
		sum += tmp;
		int min = 1001;
		int index = 0;
		
		for (int i = 0; i < v.size(); i++) {
			if (sum < v[i].first) break;
			if (min > v[i].second) {
				min = v[i].second;
				index = i;
			}
		}
		tmp = v[index].second;
		ans += sum - v[index].first;
		v.erase(v.begin() + index);

	}
	out << ans ;
	return 0;
}