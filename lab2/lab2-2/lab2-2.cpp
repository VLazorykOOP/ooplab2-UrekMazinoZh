#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ������� ��� ���������� ������ �������� �� 128 �������
string pad_text(string text) {
    while (text.length() < 128) {
        text += " ";
    }

    return text;
}

// ������� ��� ���������� ������ �������
uint16_t encrypt_char(char c, int position) {
    // ������������ ������ � ���� ASCII-���
    uint8_t ascii_code = static_cast<uint8_t>(c);

    // ��������� ASCII-��� �� ������� � ������ �������
    uint8_t lower_byte = ascii_code & 0x0F;
    uint8_t upper_byte = (ascii_code >> 4) & 0x0F;

    // ��������� �� ������� ����
    uint8_t parity_bit = (lower_byte + upper_byte + position) % 2;

    // ������� ������������ ����
    uint16_t encrypted_byte = (lower_byte << 8) | (upper_byte << 4) | parity_bit;

    return encrypted_byte;
}

// ������� ��� ���������� ������
uint16_t* encrypt_text(string text) {
    // ���������� ����� �������� �� 128 �������
    text = pad_text(text);

    // ��������� ������� ������
    int length = text.length();

    // ��������� ����� ������������ �������
    uint16_t* encrypted_text = new uint16_t[length];

    // ������� ����� ������ ������
    for (int i = 0; i < length; i++) {
        encrypted_text[i] = encrypt_char(text[i], i);
    }

    return encrypted_text;
}

// ������� ��� ������������ ������ �������
char decrypt_char(uint16_t encrypted_byte) {
    // ��������� ������� � ������ ������� ������������� �����
    uint8_t lower_byte = encrypted_byte & 0x0F;
    uint8_t upper_byte = (encrypted_byte >> 4) & 0x0F;

    // ���������� ASCII-��� �������
    uint8_t ascii_code = lower_byte | (upper_byte << 4);

    return static_cast<char>(ascii_code);
}
// ������� ��� ������������ ������
string decrypt_text(uint16_t* encrypted_text, int length) {
    string decrypted_text;

    for (int i = 0; i < length; i++) {
        char decrypted_char = decrypt_char(encrypted_text[i]);
        decrypted_text += decrypted_char;
    }

    return decrypted_text;
}

int main() {
    // ������� ����� ��� ����������
    string text;
    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    // ������� �����
    uint16_t* encrypted_text = encrypt_text(text);

    // �������� ������������ �����
    cout << "Encrypted text: ";
    for (int i = 0; i < 128; i++) {
        cout << hex << encrypted_text[i] << " ";
    }
    cout << endl;
    // ��������� ����� � �������� ���������
    string decrypted_text = decrypt_text(encrypted_text, text.length());
    cout << "Decrypted text: " << decrypted_text << endl;

    // ��������� ���'���, ������� ��� ������ ������������ �������
    delete[] encrypted_text;

    return 0;
}
