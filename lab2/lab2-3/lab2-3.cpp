#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ��������� ��� ��������� ������������� �������
struct EncryptedChar {
    uint16_t ascii_lower : 4;
    uint16_t position : 7;
    uint16_t ascii_upper : 4;
    uint16_t parity : 1;
};

// ������� ��� ���������� ������ �������� �� 128 �������
string pad_text(string text) {
    while (text.length() < 128) {
        text += " ";
    }

    return text;
}

// ������� ��� ���������� ������ �������
EncryptedChar encrypt_char(char c, int position) {
    EncryptedChar encrypted_char;

    // ������������ ������ � ���� ASCII-���
    uint8_t ascii_code = static_cast<uint8_t>(c);

    // ��������� ASCII-��� �� ������� � ������ �������
    encrypted_char.ascii_lower = ascii_code & 0x0F;
    encrypted_char.ascii_upper = (ascii_code >> 4) & 0x0F;

    // ��������� ������� ������� � �����
    encrypted_char.position = position;

    // ��������� �� ������� ����
    encrypted_char.parity = (encrypted_char.ascii_lower + encrypted_char.ascii_upper + encrypted_char.position) % 2;

    return encrypted_char;
}

// ������� ��� ���������� ������
EncryptedChar* encrypt_text(string text) {
    // ���������� ����� �������� �� 128 �������
    text = pad_text(text);

    // ��������� ������� ������
    int length = text.length();

    // ��������� ����� ������������ �������
    EncryptedChar* encrypted_text = new EncryptedChar[length];

    // ������� ����� ������ ������
    for (int i = 0; i < length; i++) {
        encrypted_text[i] = encrypt_char(text[i], i);
    }

    return encrypted_text;
}
// ������� ��� ������������ �������
char decrypt_char(EncryptedChar encrypted_char) {
    // ���������� ASCII-��� ������� � ������������ ����
    uint8_t ascii_code = (encrypted_char.ascii_upper << 4) | encrypted_char.ascii_lower;

    return static_cast<char>(ascii_code);
}

// ������� ��� ������������ ������
string decrypt_text(EncryptedChar* encrypted_text, int length) {
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
    EncryptedChar* encrypted_text = encrypt_text(text);

    // �������� ������������ �����
    cout << "Encrypted text: ";
    for (int i = 0; i < 128; i++) {
        cout << hex << static_cast<int>(encrypted_text[i].ascii_lower)
            << static_cast<int>(encrypted_text[i].position)
            << static_cast<int>(encrypted_text[i].ascii_upper)
            << static_cast<int>(encrypted_text[i].parity) << " ";
    }
    cout << endl;
    // ��������� ����� � �������� ���������
    string decrypted_text = decrypt_text(encrypted_text, text.length());
    cout << "Decrypted text: " << decrypted_text << endl;

    // ��������� ���'���
    delete[] encrypted_text;

    return 0;
}
