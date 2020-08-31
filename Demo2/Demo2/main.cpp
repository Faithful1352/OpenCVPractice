#include<iostream>
#include<string>
using namespace std;

int main() {
	
	//初始化字符数组
	char s1[3];
	char t1[6];
	//初始化字符串
	string s = "db";
	string t = "aedbs";

	//将字符串转成字符数组
	strcpy_s(s1, s.c_str());
	strcpy_s(t1, t.c_str());

	int i = 0, j = 0;
	while (i < (sizeof(s1) / sizeof(s1[0])) && j < (sizeof(t1) / sizeof(t1[0])))
	{
		//进行逐个字母比较
		if (s1[i] == t1[j]) {
			i++;
			j++;
		}
		else
		{
			j++;
		}
	}

	if (i = (sizeof(s1) / sizeof(s1[0]))) {
		cout << s << "是" << t << "的子序列";
	}
	else
	{
		cout << s << "不是" << t << "的子序列";
	}



	system("pause");
	return 0;
}