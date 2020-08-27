#include<iostream>
using namespace std;

int main() {
	int arr1[3] = { 1,2,3 };
	int arr2[3] = { -1,4,6 };

	int arr3[6] = {};
	int index = 0;
	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr1[i];
	}

	for (int i = 0; i < 3; i++) {
		arr3[index++] = arr2[i];
	}

	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (arr3[j] < arr3[i]) {
				int temp = arr3[i];
				arr3[i] = arr3[j];
				arr3[j] = temp;
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		cout << arr3[i] << endl;
	}


	system("pause");
	return 0;
}