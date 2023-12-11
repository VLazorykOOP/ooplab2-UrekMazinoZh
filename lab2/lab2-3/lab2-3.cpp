#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Структура для зберігання зашифрованого символу
struct EncryptedChar {
    uint16_t ascii_lower : 4;
    uint16_t position : 7;
    uint16_t ascii_upper : 4;
    uint16_t parity : 1;
};

// Функція для доповнення тексту пробілами до 128 символів
string pad_text(string text) {
    while (text.length() < 128) {
        text += " ";
    }

    return text;
}

// Функція для шифрування одного символу
EncryptedChar encrypt_char(char c, int position) {
    EncryptedChar encrypted_char;

    // Перетворюємо символ у його ASCII-код
    uint8_t ascii_code = static_cast<uint8_t>(c);

    // Розбиваємо ASCII-код на молодшу і старшу частини
    encrypted_char.ascii_lower = ascii_code & 0x0F;
    encrypted_char.ascii_upper = (ascii_code >> 4) & 0x0F;

    // Визначаємо позицію символу в рядку
    encrypted_char.position = position;

    // Визначаємо біт парності полів
    encrypted_char.parity = (encrypted_char.ascii_lower + encrypted_char.ascii_upper + encrypted_char.position) % 2;

    return encrypted_char;
}

// Функція для шифрування тексту
EncryptedChar* encrypt_text(string text) {
    // Доповнюємо текст пробілами до 128 символів
    text = pad_text(text);

    // Визначаємо довжину тексту
    int length = text.length();

    // Створюємо масив зашифрованих символів
    EncryptedChar* encrypted_text = new EncryptedChar[length];

    // Шифруємо кожен символ тексту
    for (int i = 0; i < length; i++) {
        encrypted_text[i] = encrypt_char(text[i], i);
    }

    return encrypted_text;
}
// Функція для дешифрування символу
char decrypt_char(EncryptedChar encrypted_char) {
    // Обчислюємо ASCII-код символу з зашифрованих полів
    uint8_t ascii_code = (encrypted_char.ascii_upper << 4) | encrypted_char.ascii_lower;

    return static_cast<char>(ascii_code);
}

// Функція для дешифрування тексту
string decrypt_text(EncryptedChar* encrypted_text, int length) {
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
    EncryptedChar* encrypted_text = encrypt_text(text);

    // Виводимо зашифрований текст
    cout << "Encrypted text: ";
    for (int i = 0; i < 128; i++) {
        cout << hex << static_cast<int>(encrypted_text[i].ascii_lower)
            << static_cast<int>(encrypted_text[i].position)
            << static_cast<int>(encrypted_text[i].ascii_upper)
            << static_cast<int>(encrypted_text[i].parity) << " ";
    }
    cout << endl;
    // Дешифруємо текст і виводимо результат
    string decrypted_text = decrypt_text(encrypted_text, text.length());
    cout << "Decrypted text: " << decrypted_text << endl;

    // Звільняємо пам'ять
    delete[] encrypted_text;

    return 0;
}
