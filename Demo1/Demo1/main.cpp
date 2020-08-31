#include<iostream>
using namespace std;

int main() {
	//初始化数组，并加入数据
	int arr1[3] = { 1,2,3 };
	int arr2[3] = { -1,4,6 };

	//初始化数组
	int arr3[6] = {};

	int index = 0;
	//将数组arr1添加到数组arr3中
	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr1[i];
	}

	//将数组arr2添加到数组arr3中
	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr2[i];
	}

	//将数组arr3中的数字进行顺序排序
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (arr3[j] < arr3[i]) {
				int temp = arr3[i];
				arr3[i] = arr3[j];
				arr3[j] = temp;
			}
		}
	}

	//遍历数组arr3中的数字
	for (int i = 0; i < 6; i++) {
		cout << arr3[i] << endl;
	}


	system("pause");
	return 0;
}