#include<iostream>
#include<vector>
#include<fstream>
#define INF 987654321
using namespace std;
typedef pair<int, vector<int> > piv;

vector<int> burst;
vector<piv> process;
int main(void) {
	ifstream in("rr.inp");
	ofstream out("rr.out");
	int n, q;
	in >> n >> q;
	vector<int> waiting(n, 0); // wating time sum
	vector<int> check(n, 0); // 입출력 check 0: 시작, 1: 입출력 완료, 2: timeOut
	for (int i = 0; i < n; i++) {
		int start, num;
		in >> start >> num;
		for (int k = 0; k < num; k++) {
			int ci;
			in >> ci;
			burst.push_back(ci);
		}
		process.push_back({ start,burst });
		burst.clear(); // 초기화
	}
	int time = process[0].first; // 현재 시간
	int end = n;
	while (end) {
		int turn = INF;
		int index = 0;
		int i = 0;
		for (piv temp : process) { // 다음 실행시킬 Process 찾기

			if (temp.first < turn) {
				turn = temp.first;
				i = index;
			}
			else if (temp.first == turn) { // 도착시간이 같으면 우선순위 비교
				/*
					1. 처음 시작하는 P == 0
					2. 입출력 완료 P == 1
					3. timeSlice 소진 P == 2
				*/
				if (check[i] > check[index]) { // 새로 들어오는 값의 우선순위가 작을때 변경
					turn = temp.first;
					i = index;
				}
			}
			index++;
		}
		if (time >= process[i].first) { // 대기 시간 발생
			waiting[i] += (time - process[i].first);
		}
		else if (time < process[i].first) { // 도착시간 JUMP
			time = process[i].first;
		}

		if (q >= process[i].second[0]) { // timeSlice 내에 종료 가능한지 check	
			// 종료 가능하면 			
			time = time + process[i].second[0]; // 총 실행시간(time)에 가산  
			if (process[i].second.size() == 1) { // 마지막 cpu burst check
				end--;
				process[i].first = INF; // 프로세스 종료 -> INF로 초기화
				continue;
			}
			process[i].first = (time + process[i].second[1]); // 도착시간(start) 변경 
			process[i].second.erase(process[i].second.begin(), process[i].second.begin() + 2); // cpu/io burst 삭제
			check[i] = 1;
		}
		else {
			// 종료 x
			time += q;
			process[i].second[0] -= q; // timeSlice 만큼 단축
			process[i].first = time; // 도착시간 증가
			check[i] = 2;
		}
	}
	for (int i = 0; i < n; i++) {
		out << i + 1 << " " << waiting[i] << "\n";
	}
	return 0;
}