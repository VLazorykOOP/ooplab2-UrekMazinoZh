#include <iostream>
#include <ctime>   
#include <cstdlib> 

using namespace std;

// ������� ��� ��������� ����������� ������� ������ 8x8
void generateRandomImage(unsigned char image[8]) {
    for (int i = 0; i < 8; i++) {
        image[i] = rand() % 256; // �������� ���������� ���� (0-255)
    }
}

// ������� ��� ��������� ������� ������ 8x8
void printImage(const unsigned char image[8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // ��������� �������� ��� � ����� image[i]
            // ���� �� ������� 0, �������� �����, � ������ ������� - "�"
            char pixel = (image[i] & (1 << (7 - j))) ? 'O' : ' ';
            cout << pixel;
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // ���������� ��������� ���������� ����� ������� �� ����

    unsigned char image[8]; // ����� ��� ��������� ������� ������

    // �������� ���������� ������ �����
    generateRandomImage(image);

    // �������� ������ �����
    printImage(image);

    return 0;
}
