#include <iostream>

using namespace std;

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	// ���������� 200 * a
	int temp = a;
	a = a << 7;
	a += temp;

	// ���������� 312 * c
	temp = c;
	c = c << 6;
	c += temp;

	// ���������� 16 * d * 120
	int mul = d << 4;
	mul *= 120;

	// ���������� c * 124
	int sum = c << 7;
	sum += 124;

	// ���������� ������
	int result = a + c + mul + sum;

	cout << result << endl;

	return 0;
}
