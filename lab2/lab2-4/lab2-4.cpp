#include <iostream>
#include <ctime>   
#include <cstdlib> 

using namespace std;

// Функція для генерації випадкового бітового образу 8x8
void generateRandomImage(unsigned char image[8]) {
    for (int i = 0; i < 8; i++) {
        image[i] = rand() % 256; // Генеруємо випадковий байт (0-255)
    }
}

// Функція для виведення бітового образу 8x8
void printImage(const unsigned char image[8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Визначаємо значення біта в рядку image[i]
            // Якщо біт дорівнює 0, виводимо пробіл, в іншому випадку - "О"
            char pixel = (image[i] & (1 << (7 - j))) ? 'O' : ' ';
            cout << pixel;
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Ініціалізуємо генератор випадкових чисел залежно від часу

    unsigned char image[8]; // Масив для зберігання бітового образу

    // Генеруємо випадковий бітовий образ
    generateRandomImage(image);

    // Виводимо бітовий образ
    printImage(image);

    return 0;
}
