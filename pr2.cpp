#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;
//Сортировки
void insert(int size, int arr[]) {
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

void shell(int size, int arr[]) {
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
int bSearch(int size, int arr[], int value) {
    int left = 0;
    int right = size - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (value == arr[middle]) {
            return middle;
        }
        else if (value > arr[middle]) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}
//Количество чисел меньше value
void lessValue(int size, int arr[], int& value, int& count) {
    count = 0;
    insert(size, arr);
    int index = bSearch(size, arr, value);
    index++;
    for (int i = 0; i < index; i++) {
        if (arr[i] < value) {
            count += 1;
        }
    }
}
//Количесиво чисел больше value
void moreValue(int size, int arr[], int& value, int& count) {
    count = 0;
    insert(size, arr);
    int index = bSearch(size, arr, value);
    index++;
    for (int i = index; i < size; i++) {
        if (arr[i] > value) {
            count += 1;
        }
    }
}
// Поиск перебором
void normalSearch(int size, int arr[], int& value) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == value) {
            cout << "Индекс числа: " << i << "\n";
            break;
        }
    }

}
//Обмен элементов по индексу
void exchangeElements(int size, int arr[], int& indexA, int& indexB) {
    swap(arr[indexA], arr[indexB]);
}

void printArr(int size, int arr[]) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

int main() {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int choise, value, min, max, index, indexA, indexB, count = 0;
    const int SIZE = 100;
    int arr[SIZE];

    cout << "Элементы массива: ";
    for (int i = 0; i < SIZE; i++) {
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
            "9) Выход\n" <<
            "--->>> ";
        cin >> choise;

        if (choise == 1) {
            cout << "\n\nВыберете способ сортировки:\n" <<
                "1) insert sort\n" <<
                "2) shell sort" << "\nВведите способ: ";
            cin >> choise;
            switch (choise) {
            case 1:
                start = steady_clock::now();
                insert(SIZE, arr);
                end = steady_clock::now();
                result = duration_cast<nanoseconds>(end - start);
                cout << "\nСортировка заняла " << result.count() << " наносек\n\nОтсортированный массив:";
                printArr(SIZE, arr);
                break;

            case 2:
                start = steady_clock::now();
                shell(SIZE, arr);
                end = steady_clock::now();
                result = duration_cast<nanoseconds>(end - start);
                cout << "Сортировка заняла " << result.count() << " наносек\n";
                cout << "\nОтсортированный массив: ";
                printArr(SIZE, arr);
                break;
            default:
                cout << "\nНеверный способ";
            }
        }
        else if (choise == 2) {
            // В неотсортированном
            min = arr[0];
            max = arr[0];
            start = steady_clock::now();
            for (int i = 1; i < SIZE; i++) {
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
            insert(SIZE, arr);
            start = steady_clock::now();
            min = arr[0];
            max = arr[SIZE - 1];
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "\nМинимальное значение: " << min << "\nМаксимальное значение: " << max << "\n";
            cout << "Время нахождения в отсортированном массиве :  " << result.count() << " наносек\n";


        }
        else if (choise == 3) {
            insert(SIZE, arr);
            min = arr[0];
            max = arr[SIZE - 1];
            int avMinMax = round(((min + max) / 2.0));
            cout << endl << "Среднее значение: " << avMinMax << endl;

            start = steady_clock::now();
            index = bSearch(SIZE, arr, avMinMax);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);

            if (index == -1) {
                cout << "Числа " << avMinMax << " нет в массиве\nВремя поиска " << result.count() << " наносек\n";
            }
            else {
                cout << "Индекс числа " << avMinMax << " = " << index << "\nВремя поиска " << result.count() << " наносек\n";
            }
        }
        else if (choise == 4) {
            cout << "Введите число: ";
            cin >> value;
            lessValue(SIZE, arr, value, count);
            cout << "\n\nКоличество элементво меньше 'A' = " << count << "\n";
        }
        else if (choise == 5) {
            cout << "Введите число: ";
            cin >> value;
            moreValue(SIZE, arr, value, count);
            cout << "\n\nКоличество элементво больше 'B' = " << count << "\n";
        }
        else if (choise == 6) {
            cout << "Введите первый индекс: ";
            cin >> indexA;
            cout << "\nВведите второй индекс: ";
            cin >> indexB;

            start = steady_clock::now();
            exchangeElements(SIZE, arr, indexA, indexB);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "\nОбмен занял " << result.count() << " наносек";
            cout << "\nМассив после обмена : ";
            printArr(SIZE, arr);

        }
        else if (choise == 7) {
            insert(SIZE, arr);
            cout << "\nВведите число: ";
            cin >> value;

            start = steady_clock::now();
            index = bSearch(SIZE, arr, value);
            if (index == -1) {
                cout << "Числа " << value << " нет в массиве" << "\n";
            }
            else {
                cout << "Индекс числа " << value << " - " << index << "\n";
            }
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Бинарный поиск занял " << result.count() << " наносек\n";

            start = steady_clock::now();
            normalSearch(SIZE, arr, value);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Перебор занял " << result.count() << " наносек\n";
        }
        else if (choise == 8) {
            system("cls");
            cout << "\nЭлементы массива: ";
            for (int i = 0; i < SIZE; i++) {
                arr[i] = rand() % 198 - 99;
                cout << arr[i] << " ";
            }
        }
        else if (choise == 9) {
            exit(0);
        }
        else {
            cout << "\nОшибка!Попробуйте снова\n";
        }
    }
    return 0;
}
