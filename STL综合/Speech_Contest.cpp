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
1) 产生选手 （ ABCDEFGHIJKLMNOPQRSTUVWX ） 姓名、得分；选手编号

2) 第1轮	选手抽签 选手比赛 查看比赛结果
3) 第2轮	选手抽签 选手比赛 查看比赛结果
4) 第3轮	选手抽签 选手比赛 查看比赛结果
*/

class Speaker
{
public:

	string m_Name; //姓名
	int m_Score[3];  //得分数组
};


void createSpeaker(vector<int>&v, map<int, Speaker>&m)
{
	string nameSeed = "ABCDEFGHIJKLMNOPQRSTUVWX";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 3; j++)
		{
			sp.m_Score[j] = 0;
		}

		v.push_back(i + 100); //编号  100 ~ 123
		m.insert(make_pair(i + 100, sp));
	}

}

//抽签
void speechDraw(vector<int>v)
{
	//洗牌
	random_shuffle(v.begin(), v.end());
}

// 1 第几轮   2  v1比赛选手编号 3  m是选手编号和具体选手 4 v2 晋级选手编号容器
void speechContest(int index, vector<int>&v1, map<int, Speaker>&m, vector<int>&v2)
{
	multimap<int, int, greater<int>> groupMap; // key  分数  value  编号  
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
		//排序
		sort(d.begin(), d.end());
		//去除最高最低分
		d.pop_back();
		d.pop_front();
		//累积分数
		int sum = accumulate(d.begin(), d.end(), 0);
		int avg = sum / d.size();

		//将平均分 放入到m容器中
		m[*it].m_Score[index - 1] = avg;

		//每6个人  取前三名 晋级
		//临时容器 保存6个人
		//临时容器 存入数据
		groupMap.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			/*	cout << "小组比赛成绩如下：" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = groupMap.begin(); mit != groupMap.end();mit++)
			{
			cout << "编号： " << mit->second << " 姓名：" << m[mit->second].m_Name << "得分：" << m[mit->second].m_Score[index - 1] << endl;
			}
			*/
			//取前三名
			int count = 0;
			for (multimap<int, int, greater<int>>::iterator mit = groupMap.begin(); mit != groupMap.end(), count < 3; mit++, count++)
			{
				//晋级容器 获取获取数据
				v2.push_back(mit->second);
			}

			groupMap.clear(); //清空临时容器
		}

	}

}


void showScore(int index, vector<int>&v, map<int, Speaker>&m)
{
	
	cout << "第" << index << "轮 比赛成绩如下：" << endl;

	for (map<int, Speaker>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "选手编号： " << it->first << " 姓名： " << it->second.m_Name << " 分数： " << it->second.m_Score[index - 1] << endl;
	}

	cout << "晋级选手编号" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}

void test()
{
	//随机数种子
	srand((unsigned int)time(NULL));

	vector<int>v1; //选手编号

	map<int, Speaker>m; //存放选手编号 和对应的具体的选手

						//创建选手
	createSpeaker(v1, m);

	//抽签
	speechDraw(v1);

	vector<int>v2; // 进入下一轮比赛的人员编号
				   //比赛
	speechContest(1, v1, m, v2);

	//显示比赛结果
	showScore(1, v2, m); // 轮数  晋级编号  具体人员信息


	//第二轮比赛
	speechDraw(v2);
	vector<int>v3;
	speechContest(2, v2, m, v3);
	showScore(2, v3, m);

	//第三轮
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