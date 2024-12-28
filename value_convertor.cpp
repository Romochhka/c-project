#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <limits> // Для numeric_limits
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Класс для управления курсами валют и конвертацией
class CurrencyConverter {
private:
    map<string, double> exchangeRates; // Хранение курсов валют

public:
    // Метод для добавления или обновления курса валюты
    void AddOrUpdateRate(const string& currency, double rate) {
        exchangeRates[currency] = rate;
    }

    // Метод для конвертации суммы из одной валюты в другую
    double Convert(const string& fromCurrency, const string& toCurrency, double amount) {
        if (exchangeRates.find(fromCurrency) == exchangeRates.end()) {
            cout << "Ошибка: Валюта " << fromCurrency << " не найдена.\n";
            return -1;
        }
        if (exchangeRates.find(toCurrency) == exchangeRates.end()) {
            cout << "Ошибка: Валюта " << toCurrency << " не найдена.\n";
            return -1;
        }

        double fromRate = exchangeRates[fromCurrency];
        double toRate = exchangeRates[toCurrency];
        return (amount / fromRate) * toRate;
    }

    // Метод для отображения всех доступных курсов
    void DisplayRates() {
        cout << left << setw(10) << "Валюта" << "Курс" << endl;
        cout << string(20, '-') << endl;
        for (const auto& rate : exchangeRates) {
            cout << left << setw(10) << rate.first << rate.second << endl;
        }
    }
};

void ShowMenu() {
    cout << "\n==== Меню ====\n";
    cout << "1. Добавить или обновить курс валюты\n";
    cout << "2. Конвертировать валюту\n";
    cout << "3. Показать курсы валют\n";
    cout << "4. Выйти\n";
    cout << "Выберите опцию: ";
}

int main() {
    // Установка кодировки UTF-8 для Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    CurrencyConverter converter;
    int choice;

    // Добавление базовых курсов валют
    converter.AddOrUpdateRate("USD", 1.0); // Базовая валюта - доллар
    converter.AddOrUpdateRate("EUR", 0.92);
    converter.AddOrUpdateRate("KZT", 450.0);
    converter.AddOrUpdateRate("RUB", 85.0);

    while (true) {
        ShowMenu();
        if (!(cin >> choice)) {
            cin.clear(); // Сброс состояния ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка ввода
            cout << "Ошибка: введите число от 1 до 4.\n";
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                string currency;
                double rate;

                cout << "Введите код валюты (например, USD): ";
                cin >> currency;
                cout << "Введите курс валюты относительно USD: ";
                cin >> rate;

                converter.AddOrUpdateRate(currency, rate);
                cout << "Курс валюты успешно добавлен или обновлен.\n";
                break;
            }
            case 2: {
                string fromCurrency, toCurrency;
                double amount;

                cout << "Введите валюту источника (например, USD): ";
                cin >> fromCurrency;
                cout << "Введите целевую валюту (например, EUR): ";
                cin >> toCurrency;
                cout << "Введите сумму: ";
                cin >> amount;

                double result = converter.Convert(fromCurrency, toCurrency, amount);
                if (result != -1) {
                    cout << fixed << setprecision(2);
                    cout << amount << " " << fromCurrency << " = " << result << " " << toCurrency << "\n";
                }
                break;
            }
            case 3:
                converter.DisplayRates();
                break;
            case 4:
                cout << "Выход из программы. До свидания!\n";
                return 0;
            default:
                cout << "Ошибка: Неверный ввод. Попробуйте снова.\n";
        }
    }

    return 0;
}
