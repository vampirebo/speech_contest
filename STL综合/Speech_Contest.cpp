#include<iostream>
#include<vector>
#include<deque>
#include<map>
#include<algorithm>
#include<string>
#include<functional>
#include<numeric>
#include<ctime>
using namespace std;


/*
1) ����ѡ�� �� ABCDEFGHIJKLMNOPQRSTUVWX �� �������÷֣�ѡ�ֱ��

2) ��1��	ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
3) ��2��	ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
4) ��3��	ѡ�ֳ�ǩ ѡ�ֱ��� �鿴�������
*/

class Speaker
{
public:

	string m_Name; //����
	int m_Score[3];  //�÷�����
};


void createSpeaker(vector<int>&v, map<int, Speaker>&m)
{
	string nameSeed = "ABCDEFGHIJKLMNOPQRSTUVWX";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 3; j++)
		{
			sp.m_Score[j] = 0;
		}

		v.push_back(i + 100); //���  100 ~ 123
		m.insert(make_pair(i + 100, sp));
	}

}

//��ǩ
void speechDraw(vector<int>v)
{
	//ϴ��
	random_shuffle(v.begin(), v.end());
}

// 1 �ڼ���   2  v1����ѡ�ֱ�� 3  m��ѡ�ֱ�ź;���ѡ�� 4 v2 ����ѡ�ֱ������
void speechContest(int index, vector<int>&v1, map<int, Speaker>&m, vector<int>&v2)
{
	multimap<int, int, greater<int>> groupMap; // key  ����  value  ���  
	int num = 0;
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		num++;
		deque<int>d;
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60; // 60 ~100
			d.push_back(score);
		}
		//����
		sort(d.begin(), d.end());
		//ȥ�������ͷ�
		d.pop_back();
		d.pop_front();
		//�ۻ�����
		int sum = accumulate(d.begin(), d.end(), 0);
		int avg = sum / d.size();

		//��ƽ���� ���뵽m������
		m[*it].m_Score[index - 1] = avg;

		//ÿ6����  ȡǰ���� ����
		//��ʱ���� ����6����
		//��ʱ���� ��������
		groupMap.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			/*	cout << "С������ɼ����£�" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = groupMap.begin(); mit != groupMap.end();mit++)
			{
			cout << "��ţ� " << mit->second << " ������" << m[mit->second].m_Name << "�÷֣�" << m[mit->second].m_Score[index - 1] << endl;
			}
			*/
			//ȡǰ����
			int count = 0;
			for (multimap<int, int, greater<int>>::iterator mit = groupMap.begin(); mit != groupMap.end(), count < 3; mit++, count++)
			{
				//�������� ��ȡ��ȡ����
				v2.push_back(mit->second);
			}

			groupMap.clear(); //�����ʱ����
		}

	}

}


void showScore(int index, vector<int>&v, map<int, Speaker>&m)
{
	
	cout << "��" << index << "�� �����ɼ����£�" << endl;

	for (map<int, Speaker>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "ѡ�ֱ�ţ� " << it->first << " ������ " << it->second.m_Name << " ������ " << it->second.m_Score[index - 1] << endl;
	}

	cout << "����ѡ�ֱ��" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}

void test()
{
	//���������
	srand((unsigned int)time(NULL));

	vector<int>v1; //ѡ�ֱ��

	map<int, Speaker>m; //���ѡ�ֱ�� �Ͷ�Ӧ�ľ����ѡ��

						//����ѡ��
	createSpeaker(v1, m);

	//��ǩ
	speechDraw(v1);

	vector<int>v2; // ������һ�ֱ�������Ա���
				   //����
	speechContest(1, v1, m, v2);

	//��ʾ�������
	showScore(1, v2, m); // ����  �������  ������Ա��Ϣ


	//�ڶ��ֱ���
	speechDraw(v2);
	vector<int>v3;
	speechContest(2, v2, m, v3);
	showScore(2, v3, m);

	//������
	speechDraw(v3);
	vector<int>v4;
	speechContest(3, v3, m, v4);
	showScore(3, v4, m);
}
int main()
{
	test();
	system("pause");
	return EXIT_SUCCESS;
}