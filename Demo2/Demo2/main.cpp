#include<iostream>
#include<string>
using namespace std;

int main() {
	
	//��ʼ���ַ�����
	char s1[3];
	char t1[6];
	//��ʼ���ַ���
	string s = "db";
	string t = "aedbs";

	//���ַ���ת���ַ�����
	strcpy_s(s1, s.c_str());
	strcpy_s(t1, t.c_str());

	int i = 0, j = 0;
	while (i < (sizeof(s1) / sizeof(s1[0])) && j < (sizeof(t1) / sizeof(t1[0])))
	{
		//���������ĸ�Ƚ�
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
		cout << s << "��" << t << "��������";
	}
	else
	{
		cout << s << "����" << t << "��������";
	}



	system("pause");
	return 0;
}