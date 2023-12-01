#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;
//Сортировки
void Insert(int size, int arr[]) {
    int i, buff, j;
    for (i = 1; i < size; i++) {
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
//Нахождение среднего мин. и макс.
void average(int size, int arr[]) {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;
    int index;
    Insert(size, arr);
    int min = arr[0];
    int max = arr[size - 1];
    int srMinMax = round(((min + max) / 2.0));
    cout << endl << "Среднее значение: " << srMinMax << endl;
    start = steady_clock::now();
    index = bSearch(size, arr, srMinMax);
    if (index == -1) {
        cout << "Числа " << srMinMax << " нет в массиве" << endl;
    }
    else {
        cout << "Индекс числа " << srMinMax << " - " << index << endl;
    }
    end = steady_clock::now();
    result = duration_cast<nanoseconds>(end - start);
    cout << "Время поиска " << result.count() << " наносек" << endl;
}
//Количество чисел меньше A
void numA(int size, int arr[], int A4, int& count4) {
    Insert(size, arr);
    int ind = bSearch(size, arr, A4);
    ind++;
    for (int i = 0; i < ind; i++) {
        if (arr[i] < A4) {
            count4 = count4 + 1;
        }
    }
}
//Количесиво чисел больше B
void numB(int size, int arr[], int B5, int& count5) {
    Insert(size, arr);
    int ind = bSearch(size, arr, B5);
    ind++;
    for (int i = ind; i < size; i++) {
        if (arr[i] > B5) {
            count5 = count5 + 1;
        }
    }
}

void NormalSearch(int size, int arr[], int val) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == val) {
            cout << "Индекс числа: " << i << endl;
            break;
        }
    }

}
//Обмен элементов по индексу
void exchange(int size, int arr[], int intA, int intB) {
    swap(arr[intA], arr[intB]);
}
//Вывод массива
void printArr(int size, int arr[]) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));
    int numOption, numSort, i; //переменная i нужна для выхода из основного циклв программы, используется в конце
    const int size = 100;
    int arr[size];
    cout << "Элементы массива: ";
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 198 - 99;
        cout << arr[i] << " ";
    }
    while (true) {
        time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
        nanoseconds result;
        //Окно выбора задания
        cout << endl << endl << "Выберете опцию: " << endl <<
            "1) Сортировка массива" << endl <<
            "2) Нахождение минимального или максимального значения" << endl <<
            "3) Среднее значение минимального и максимального значения" << endl <<
            "4) Количество элементво, меньшее числа 'A'" << endl <<
            "5) Количество элементов больше числа 'B'" << endl <<
            "6) Обмен элементов" << endl <<
            "7) Поиск числа в массиве" << endl <<
            "8) Изменить массив " << endl <<
            "9) Выход из программы" << endl <<
            "--->>> ";
        cin >> numOption;
        if (numOption == 1) {
            cout << endl << endl << "Выберете способ сортировки: " << endl <<
                "1) Insert sort" << endl <<
                "2) Shell sort" << endl << "Введите способ: ";
            cin >> numSort;
            switch (numSort){
                case 1:
                    start = steady_clock::now();
                    Insert(size, arr);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nСортировка заняла " << result.count() << " наносек" << endl;
                    cout << "\nОтсортированный массив: ";
                    printArr(size, arr);
                    break;

                case 2:
                    start = steady_clock::now();
                    Shell(size, arr);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "Сортировка заняла " << result.count() << " наносек" << endl;
                    cout << "\nОтсортированный массив: ";
                    printArr(size, arr);
                    break;
                default:
                    cout << "\nНеверный способ";
            }
        }
        else if (numOption == 2) {
            int h;
            int min, max;
            while (true) {
                cout << "Отсортировать массив?(1 - да, 2 - нет)\n" << "Введите ответ: ";
                cin >> h;
                switch (h) {
                case 1:
                    Insert(size, arr);
                    start = steady_clock::now();
                    min = arr[0];
                    max = arr[size - 1];
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nМинимальное значение: " << min << endl << "Максимальное значение: " << max << endl;
                    cout << "Время нахождения максимального и минимального значений:  " << result.count() << " наносек" << endl;
                    break;
                case 2:
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
                    cout << "\nМинимальное значение: " << min << endl << "Максимальное значение: " << max << endl;
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "Время нахождения максимального и минимального значений:  " << result.count() << " наносек" << endl;
                    break;
                }
            }
        }
        else if (numOption == 3) {
            average(size, arr);
        }
        else if (numOption == 4) {
            int A4, count4 = 0;
            cout << "Введите число: ";
            cin >> A4;
            numA(size, arr, A4, count4);
            cout << endl << "\nКоличество элементво меньше 'A' = " << count4 << endl;
        }
        else if (numOption == 5) {
            int B5, count5 = 0;
            cout << "Введите число: ";
            cin >> B5;
            numB(size, arr, B5, count5);
            cout << endl << "\nКоличество элементво больше 'B' = " << count5 << endl;
        }
        else if (numOption == 6) {
            int intA, intB;
            cout << "Введите первый индекс: ";
            cin >> intA;
            cout << "\nВведите второй индекс: ";
            cin >> intB;
            start = steady_clock::now();
            exchange(size, arr, intA, intB);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "\nОбмен занял " << result.count() << " наносек";
            cout << "\nМассив после обмена: ";
            printArr(size, arr);

        }
        else if (numOption == 7) {
            Insert(size, arr);
            int val7;
            int index;
            cout << "\nВведите число: ";
            cin >> val7;

            start = steady_clock::now();
            index = bSearch(size, arr, val7);
            if (index == -1) {
                cout << "Числа " << val7 << " нет в массиве" << endl;
            }
            else {
                cout << "Индекс числа " << val7 << " - " << index << endl;
            }
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Бинарный поиск занял " << result.count() << " наносек" << endl;

            start = steady_clock::now();
            NormalSearch(size, arr, val7);
            end = steady_clock::now();
            result = duration_cast<nanoseconds>(end - start);
            cout << "Перебор занял " << result.count() << " наносек" << endl;
        }
        else if (numOption == 8) {
            system("cls");
            cout << "\nЭлементы массива: ";
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 198 - 99;
                cout << arr[i] << " ";
            }
        }
        else if (numOption == 9) {
            cout << "\nПока-пока:)";
            break;
        }
        else {
            cout << "\nНеверный ввод числа\n";
        }
        cout << endl << "\nХотите выбрать опцию?(1 - да, 2 - нет(завершить программу))\n" << "Введите ответ: ";
        cin >> i;
        cout << endl;
        if (i != 1)break;
    }
    return 0;
}