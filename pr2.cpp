#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;
//Сортировки
void Insert(int size, int arr[]) {
    int buff, j;
    for (int i = 1; i < size; i++) {
        buff = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > buff) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = buff;
    }
}

void Shell(int size, int arr[]) {
    int i, j, step;
    int tmp;
    for (step = size / 2; step > 0; step = step / 2)
        for (i = step; i < size; i++)
        {
            tmp = arr[i];
            for (j = i; j >= step; j = j - step)
            {
                if (tmp < arr[j - step])
                    arr[j] = arr[j - step];
                else
                    break;
            }
            arr[j] = tmp;
        }


}
//Бинарный поиск
int bSearch(int size, int arr[], int val) {
    int l = 0;
    int r = size - 1;
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        if (val == arr[m]) {
            return m;
        }
        else if (val > arr[m]) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    return -1;
}
//Количество чисел меньше A
void numA(int size, int arr[], int& val, int& count) {
    count = 0;
    Insert(size, arr);
    int ind = bSearch(size, arr, val);
    ind++;
    for (int i = 0; i < ind; i++) {
        if (arr[i] < val) {
            count += 1;
        }
    }
}
//Количесиво чисел больше B
void numB(int size, int arr[], int& val, int& count) {
    count = 0;
    Insert(size, arr);
    int ind = bSearch(size, arr, val);
    ind++;
    for (int i = ind; i < size; i++) {
        if (arr[i] > val) {
            count += 1;
        }
    }
}
// Поиск перебором
void NormalSearch(int size, int arr[], int& val) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == val) {
            cout << "Индекс числа: " << i << "\n";
            break;
        }
    }

}
//Обмен элементов по индексу
void exchange(int size, int arr[], int& indexA, int& indexB) {
    swap(arr[indexA], arr[indexB]);
}
//Вывод массива
void printArr(int size, int arr[]) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

int main() {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int numOption, choise, val, min, max, ind, indexA, indexB, count = 0;
    const int size = 100;
    int arr[size];

    cout << "Элементы массива: ";
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 198 - 99;
        cout << arr[i] << " ";
    }

    while (true) {
        cout << "\n\nВыберете опцию : \n" <<
            "1) Сортировка массива\n" <<
            "2) Нахождение минимального или максимального значения\n" <<
            "3) Среднее значение минимального и максимального значения\n" <<
            "4) Количество элементво, меньшее числа 'A'\n" <<
            "5) Количество элементов больше числа 'B'\n" <<
            "6) Обмен элементов\n" <<
            "7) Поиск числа в массиве\n" <<
            "8) Изменить массив\n" <<
            "9) Выход из программы\n" <<
            "--->>> ";
        cin >> numOption;

        if (numOption == 1) {
            cout << "\n\nВыберете способ сортировки:\n" <<
                "1) Insert sort\n" <<
                "2) Shell sort" << "\nВведите способ: ";
            cin >> choise;
            switch (choise) {
            case 1:
                start = steady_clock::now();
                Insert(size, arr);
                end = steady_clock::now();
                result = duration_cast<nanoseconds>(end - start);
                cout << "\nСортировка заняла " << result.count() << " наносек\n\nОтсортированный массив:";
                printArr(size, arr);
                break;

            case 2:
                start = steady_clock::now();
                Shell(size, arr);
                end = steady_clock::now();
                result = duration_cast<nanoseconds>(end - start);
                cout << "Сортировка заняла " << result.count() << " наносек\n";
                cout << "\nОтсортированный массив: ";
                printArr(size, arr);
                break;
            default:
                cout << "\nНеверный способ";
            }
        }
        else if (numOption == 2) {
            // В неотсортированном
            min = arr[0];
            max = arr[0];
            start = steady_clock::now();
            for (int i = 1; i < size; i++) {
                if (arr[i] < min)
                    min = arr[i];
                if (arr[i] > max)
                    max = arr[i];
            }

            end = steady_clock::now();
            cout << "\nМинимальное значение: " << min << "\nМаксимальное значение: " << max << "\n";
            result = duration_cast<nanoseconds>(end - start);
            cout << "Время нахождения в неотсортированном массиве :  " << result.count() << " наносек\n";
            // В отсортированном
            Insert(size, arr);
            start = steady_clock::now();
            min = arr[0];
            max = arr[size - 1];
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "\nМинимальное значение: " << min << "\nМаксимальное значение: " << max << "\n";
            cout << "Время нахождения в отсортированном массиве :  " << result.count() << " наносек\n";
            
                    
        }
        else if (numOption == 3) {
            Insert(size, arr);
            min = arr[0];
            max = arr[size - 1];
            int avMinMax = round(((min + max) / 2.0));
            cout << endl << "Среднее значение: " << avMinMax << endl;

            start = steady_clock::now();
            ind = bSearch(size, arr, avMinMax);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);

            if (ind == -1) {
                cout << "Числа " << avMinMax << " нет в массиве\nВремя поиска " << result.count() << " наносек\n";
            }
            else {
                cout << "Индекс числа " << avMinMax << " = " << ind << "\nВремя поиска " << result.count() << " наносек\n";
            }
        }
        else if (numOption == 4) {
            cout << "Введите число: ";
            cin >> val;
            numA(size, arr, val, count);
            cout << "\n\nКоличество элементво меньше 'A' = " << count << "\n";
        }
        else if (numOption == 5) {
            cout << "Введите число: ";
            cin >> val;
            numB(size, arr, val, count);
            cout << "\n\nКоличество элементво больше 'B' = " << count << "\n";
        }
        else if (numOption == 6) {
            cout << "Введите первый индекс: ";
            cin >> indexA;
            cout << "\nВведите второй индекс: ";
            cin >> indexB;

            start = steady_clock::now();
            exchange(size, arr, indexA, indexB);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "\nОбмен занял " << result.count() << " наносек";
            cout << "\nМассив после обмена : ";
            printArr(size, arr);

        }
        else if (numOption == 7) {
            Insert(size, arr);
            cout << "\nВведите число: ";
            cin >> val;

            start = steady_clock::now();
            ind = bSearch(size, arr, val);
            if (ind == -1) {
                cout << "Числа " << val << " нет в массиве" << "\n";
            }
            else {
                cout << "Индекс числа " << val << " - " << ind << "\n";
            }
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Бинарный поиск занял " << result.count() << " наносек\n";

            start = steady_clock::now();
            NormalSearch(size, arr, val);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Перебор занял " << result.count() << " наносек\n";
        }
        else if (numOption == 8) {
            system("cls");
            cout << "\nЭлементы массива: ";
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 198 - 99;
                cout << arr[i] << " ";
            }
        }
        else {
            cout << "\nНеверный ввод числа\n";
        }
        cout << "\nХотите выбрать опцию?(1 - да, 0 - нет(завершить программу))\n" << "Введите ответ: ";
        cin >> numOption;
        cout << endl;
        if (numOption != 1)break;
    }
    return 0;
}
