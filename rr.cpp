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
	vector<int> check(n, 0); // ����� check 0: ����, 1: ����� �Ϸ�, 2: timeOut
	for (int i = 0; i < n; i++) {
		int start, num;
		in >> start >> num;
		for (int k = 0; k < num; k++) {
			int ci;
			in >> ci;
			burst.push_back(ci);
		}
		process.push_back({ start,burst });
		burst.clear(); // �ʱ�ȭ
	}
	int time = process[0].first; // ���� �ð�
	int end = n;
	while (end) {
		int turn = INF;
		int index = 0;
		int i = 0;
		for (piv temp : process) { // ���� �����ų Process ã��

			if (temp.first < turn) {
				turn = temp.first;
				i = index;
			}
			else if (temp.first == turn) { // �����ð��� ������ �켱���� ��
				/*
					1. ó�� �����ϴ� P == 0
					2. ����� �Ϸ� P == 1
					3. timeSlice ���� P == 2
				*/
				if (check[i] > check[index]) { // ���� ������ ���� �켱������ ������ ����
					turn = temp.first;
					i = index;
				}
			}
			index++;
		}
		if (time >= process[i].first) { // ��� �ð� �߻�
			waiting[i] += (time - process[i].first);
		}
		else if (time < process[i].first) { // �����ð� JUMP
			time = process[i].first;
		}

		if (q >= process[i].second[0]) { // timeSlice ���� ���� �������� check	
			// ���� �����ϸ� 			
			time = time + process[i].second[0]; // �� ����ð�(time)�� ����  
			if (process[i].second.size() == 1) { // ������ cpu burst check
				end--;
				process[i].first = INF; // ���μ��� ���� -> INF�� �ʱ�ȭ
				continue;
			}
			process[i].first = (time + process[i].second[1]); // �����ð�(start) ���� 
			process[i].second.erase(process[i].second.begin(), process[i].second.begin() + 2); // cpu/io burst ����
			check[i] = 1;
		}
		else {
			// ���� x
			time += q;
			process[i].second[0] -= q; // timeSlice ��ŭ ����
			process[i].first = time; // �����ð� ����
			check[i] = 2;
		}
	}
	for (int i = 0; i < n; i++) {
		out << i + 1 << " " << waiting[i] << "\n";
	}
	return 0;
}