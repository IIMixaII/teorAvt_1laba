#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
int get_number(string word, vector<char> alphabet) {

    // Количество символов в алфавите
    int n = alphabet.size();
    // Количество символов в слове
    int k = word.size();

    cout << " n = " << n << ", k = " << k << endl;
    string formula = " ";

    int result = 0;
    for (int i = 1; i <= k; ++i) {
        char ch = word[i - 1];
        int char_index = 0;
        bool char_found = false;
        for (int j = 0; j < n; ++j) {
            if (alphabet[j] == ch) {
                char_index = j + 1;
                char_found = true;
                break;
            }
        }
        if (!char_found) {
            cout << "Ошибка: Символ '" << ch << "' не найден в алфавите." << endl;
            return 0; // Возвращаем 0 в случае ошибки
        }
        result += pow(n, k - i) * char_index;
        formula += to_string(n) + "^" + to_string(k - i) + " * " + to_string(char_index) + " + ";
    }

    formula = formula.substr(0, formula.size() - 3) + " = " + to_string(result);
    cout << formula << endl;  // Опционально - вывод в логи формулу

    return result;
}
string get_word(int number, const vector<string>& alphabet) {
    // Кол-во символов в алфавите
    int n = alphabet.size();

    // Если номер <= длине алф, то он либо индекс буквы, либо пустой символ
    if (number <= n) {
        if (number == 0) {
            return "*Пустой символ*";
        }
        return alphabet[number - 1];
    }

    // Выведем входные данные и определим шаблоны для вывода лога подробного решения
    cout << " n = " << n << ", number = " << number << endl;
    string formula_temp = "({k}) * " + to_string(n) + " + {remainder} ";
    string formula = formula_temp;
    string left_part = "";

    // Индексы слов в алфавите, причем [1, n]
    vector<int> char_index_list;

    int k = number;
    while (true) {
        // Остаток от деления должен быть на [1, n]
        int remainder;
        if (k % n == 0) {
            k = (k / n) - 1;
            remainder = n;
        }
        else {
            remainder = k % n;
            k = k / n;
        }

        char_index_list.push_back(remainder);
        if (k > n) {
            left_part += formula;
            left_part.replace(left_part.find("{k}"), 3, to_string(k));
            left_part.replace(left_part.find("{remainder}"), 11, to_string(remainder));
            left_part += " = ";
            //cout << left_part << endl;
            formula = formula_temp;
            formula.replace(formula.find("{k}"), 3, "(" + formula_temp + ")");
            formula.replace(formula.find("{remainder}"), 11, to_string(remainder));

        }
        else {
            char_index_list.push_back(k);
            formula.replace(formula.find("{k}"), 3, to_string(k));
            formula.replace(formula.find("{remainder}"), 11, to_string(remainder));
            break;
        }
    }

    reverse(char_index_list.begin(), char_index_list.end());

    // Вывод промежуточных результатов
    cout << " Номера букв в алфавите: ";
    for (int index : char_index_list) {
        cout << index << " ";
    }
    cout << endl;
    cout << left_part << endl;

    // Формирование конечной формулы и слова
    string debug_end_formula;
    string word;
    // Кол-во букв в слове
    int k_size = char_index_list.size();
    for (int index : char_index_list) {
        word += alphabet[index - 1];
        k_size--;
        debug_end_formula += to_string(n) + "^" + to_string(k_size) + " * " + to_string(index) + " + ";
    }

    debug_end_formula = debug_end_formula.substr(0, debug_end_formula.size() - 3);
    // Вывод конечного слова
    cout << debug_end_formula << endl;

    return word;
}


int main() {
    setlocale(LC_ALL, "rus");
    int number;
    int choice;
    string word;
    vector<char> alphabet;
    do {
        cout << "Выберите действие:\n"
            "1. Нахождение номера по слову:\n"
            "2. Нахождение слова по номеру\n"
            "3. Выйти\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice) {
        case 1:
            char ch;
            cout << "Введите алфавит (каждую букву с новой строки), для окончания введите '.' : " << endl;
            while (cin >> ch && ch != '.') {
                alphabet.push_back(ch);
            }
            cout << "Введите слово: " << endl;
            while (cin >> ch && ch != '.') {
                word += ch;
            }



            for (char ch : word) {
                bool char_in_alphabet = false;
                for (char alpha_ch : alphabet) {
                    if (alpha_ch == ch) {
                        char_in_alphabet = true;
                        break;
                    }
                }
                if (!char_in_alphabet) {
                    cout << "Ошибка: Символ '" << ch << "' не найден в алфавите." << endl;
                    return 0; // Возвращаем 1 в случае ошибки

                }
            }
            number = get_number(word, alphabet);
            cout << "Number: " << number << endl;
            break;
        case 2:
            vector<string> alphabet1;
            int alphabet_size;
            cout << "Введите размер алфавита: ";
            cin >> alphabet_size;
            cout << "Введите символы алфавита: ";
            for (int i = 0; i < alphabet_size; ++i) {
                string symbol;
                cin >> symbol;
                alphabet1.push_back(symbol);
            }
            int number1;
            cout << "Введите номер: ";
            cin >> number1;
            string result = get_word(number1, alphabet1);
            cout << "Слово: " << result << endl;
            break;
        }
    } while (choice != 3);
}


