#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Функція для створення текстового файлу F
void CreateFile(const char* filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Error: Cannot create file " << filename << endl;
        return;
    }
    cout << "Enter lines for the file " << filename << " (type 'END' to finish):" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "END") break; // Вихід, якщо введено "END"
        fout << line << endl;
    }
    fout.close();
}

// Функція для пошуку рядків у файлі F, які містять рядок S, і запису їх до файлу G
void ProcessFile(const char* fileF, const char* fileG, const string& S) {
    ifstream fin(fileF);
    if (!fin.is_open()) {
        cerr << "Error: Cannot open file " << fileF << endl;
        return;
    }

    ofstream fout(fileG);
    if (!fout.is_open()) {
        cerr << "Error: Cannot create file " << fileG << endl;
        fin.close(); // Закриваємо файл F перед виходом
        return;
    }

    string line;
    int count = 0;

    while (getline(fin, line)) {
        if (line.find(S) != string::npos) { // Якщо рядок містить підрядок S
            fout << line << endl;
            count++;
        }
    }

    fout << "Number of matching lines: " << count << endl; // Записуємо кількість рядків
    fin.close();
    fout.close();
}

// Основна функція
int main() {
    const char* fileF = "fileF.txt";
    const char* fileG = "fileG.txt";

    // Створюємо файл F
    CreateFile(fileF);

    // Вводимо рядок S
    cout << "Enter the string to search (S): ";
    string S;
    getline(cin, S);

    // Обробляємо файл F і створюємо файл G
    ProcessFile(fileF, fileG, S);

    // Виводимо вміст файлу G
    cout << "Contents of the file " << fileG << ":" << endl;
    ifstream fin(fileG);
    if (fin.is_open()) {
        string line;
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }
    else {
        cerr << "Error: Cannot open file " << fileG << endl;
    }

    return 0;
}
