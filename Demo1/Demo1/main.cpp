#include<iostream>
using namespace std;

int main() {
	//��ʼ�����飬����������
	int arr1[3] = { 1,2,3 };
	int arr2[3] = { -1,4,6 };

	//��ʼ������
	int arr3[6] = {};

	int index = 0;
	//������arr1��ӵ�����arr3��
	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr1[i];
	}

	//������arr2��ӵ�����arr3��
	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr2[i];
	}

	//������arr3�е����ֽ���˳������
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (arr3[j] < arr3[i]) {
				int temp = arr3[i];
				arr3[i] = arr3[j];
				arr3[j] = temp;
			}
		}
	}

	//��������arr3�е�����
	for (int i = 0; i < 6; i++) {
		cout << arr3[i] << endl;
	}


	system("pause");
	return 0;
}