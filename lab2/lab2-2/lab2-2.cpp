#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Функція для доповнення тексту пробілами до 128 символів
string pad_text(string text) {
    while (text.length() < 128) {
        text += " ";
    }

    return text;
}

// Функція для шифрування одного символу
uint16_t encrypt_char(char c, int position) {
    // Перетворюємо символ у його ASCII-код
    uint8_t ascii_code = static_cast<uint8_t>(c);

    // Розбиваємо ASCII-код на молодшу і старшу частини
    uint8_t lower_byte = ascii_code & 0x0F;
    uint8_t upper_byte = (ascii_code >> 4) & 0x0F;

    // Визначаємо біт парності полів
    uint8_t parity_bit = (lower_byte + upper_byte + position) % 2;

    // Формуємо зашифрований байт
    uint16_t encrypted_byte = (lower_byte << 8) | (upper_byte << 4) | parity_bit;

    return encrypted_byte;
}

// Функція для шифрування тексту
uint16_t* encrypt_text(string text) {
    // Доповнюємо текст пробілами до 128 символів
    text = pad_text(text);

    // Визначаємо довжину тексту
    int length = text.length();

    // Створюємо масив зашифрованих символів
    uint16_t* encrypted_text = new uint16_t[length];

    // Шифруємо кожен символ тексту
    for (int i = 0; i < length; i++) {
        encrypted_text[i] = encrypt_char(text[i], i);
    }

    return encrypted_text;
}

// Функція для дешифрування одного символу
char decrypt_char(uint16_t encrypted_byte) {
    // Визначаємо молодшу і старшу частини зашифрованого байта
    uint8_t lower_byte = encrypted_byte & 0x0F;
    uint8_t upper_byte = (encrypted_byte >> 4) & 0x0F;

    // Обчислюємо ASCII-код символу
    uint8_t ascii_code = lower_byte | (upper_byte << 4);

    return static_cast<char>(ascii_code);
}
// Функція для дешифрування тексту
string decrypt_text(uint16_t* encrypted_text, int length) {
    string decrypted_text;

    for (int i = 0; i < length; i++) {
        char decrypted_char = decrypt_char(encrypted_text[i]);
        decrypted_text += decrypted_char;
    }

    return decrypted_text;
}

int main() {
    // Вводимо текст для шифрування
    string text;
    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    // Шифруємо текст
    uint16_t* encrypted_text = encrypt_text(text);

    // Виводимо зашифрований текст
    cout << "Encrypted text: ";
    for (int i = 0; i < 128; i++) {
        cout << hex << encrypted_text[i] << " ";
    }
    cout << endl;
    // Дешифруємо текст і виводимо результат
    string decrypted_text = decrypt_text(encrypted_text, text.length());
    cout << "Decrypted text: " << decrypted_text << endl;

    // Звільняємо пам'ять, виділену для масиву зашифрованих символів
    delete[] encrypted_text;

    return 0;
}
