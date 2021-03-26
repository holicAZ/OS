#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;
typedef pair<string, string> pss;
typedef pair<string, pss> pis;
vector <pis> v;
vector <string> same;

int main(void) {
	ifstream in("test.inp");
	ofstream out("test.out");
	int n, len=0;
	in >> n;
	string num, first, last;
	for (int i = 0; i < n; i++) {
		
		in >> num >> first >> last;
		v.push_back({ num,{first,last} });
			
		if (len < first.length())
			len = first.length();

		same.push_back(last);
	}
	sort(v.begin(), v.end());
	sort(same.begin(), same.end());
	cout << len;
	for (pis a : v) {
		out << a.first << " " << a.second.first << " ";
		int cnt = len - a.second.first.length();
		for (int i = 0; i < cnt; i++)
			out << " ";
		out << a.second.second << "\n";
	}
	
	int point = 0;
	while (point!=same.size()) {
		int ans = count(same.begin(), same.end(), same[0 + point]);
		if (ans > 1) {
			out <<"\n" << same[0 + point] << " " << ans;
		}
		point += ans;
	}
	return 0;
}