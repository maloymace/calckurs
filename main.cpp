#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
using namespace std;

const double Pi = acos(-1); //Объявляем значение числа Пи

double Sin(double x) { //Функция для округления значения синуса
    return (round(sin(x) * 10000000) / 10000000);
}

double Cos(double x) { //Функция для округления значения косинуса
    return (round(cos(x) * 10000000) / 10000000);
}

struct Leksema //Структура, описывающая число или операцию
{
    char type; // 0 для чисел, "+" для операции сложения и т.д.
    double value; //Значение (только для чисел). У операций значение всегда "0"
};

bool Maths(stack <Leksema>& Stack_num, stack <Leksema>& Stack_oper, Leksema& item) { //Математическая функция, которая производит расчеты
    //Функция имеет тип bool, чтобы при возникновении какой-либо ошибки возвращать "false"
    double a, b, c;
    a = Stack_num.top().value; //Берется верхнее число из стека с числами
    Stack_num.pop(); //Удаляется верхнее число из стека с числами
    switch (Stack_oper.top().type) {  //Проверяется тип верхней операции из стека с операциями
        case '+': //Если тип верхней операции из стека с операциями сложение
            b = Stack_num.top().value;
            Stack_num.pop();
            c = a + b;
            item.type = '0';
            item.value = c;
            Stack_num.push(item); //Результат операции кладется обратно в стек с числами
            Stack_oper.pop();
            break;

        case '-':
            b = Stack_num.top().value;
            Stack_num.pop();
            c = b - a;
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;

        case '^':
            b = Stack_num.top().value;
            Stack_num.pop();
            c = pow(b, a);
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;

        case '*':
            b = Stack_num.top().value;
            Stack_num.pop();
            c = a * b;
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;

        case '/':
            b = Stack_num.top().value;
            if (a == 0.0) {
                cerr << "\nError, Division by Zero!\n";
                return false;
            }
            else {
                Stack_num.pop();
                c = (b / a);
                item.type = '0';
                item.value = c;
                Stack_num.push(item);
                Stack_oper.pop();
                break;
            }

        case 's':
            c = Sin(a);
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;

        case 'c':
            c = Cos(a);
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;

        case 't':
            if (Cos(a) == 0.0) {
                cerr << "\nUnable to process with cos = 0!\n";
                return false;
            }
            c = tan(a);
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;
        case 'l':
            c = log(a);
            item.type = '0';
            item.value = c;
            Stack_num.push(item);
            Stack_oper.pop();
            break;
        default:
            cerr << "\nError!\n";
            return false;
    }
    return true;
}

int getRang(char Ch) { //Функция возвращает приоритет операции: "1" для сложения и вычитания, "2" для умножения и деления и т.д.
    if (Ch == '+' || Ch == '-')return 1;
    if (Ch == '*' || Ch == '/')return 2;
    if (Ch == '^')return 3;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'l')return 4;
    else return 0;
}

int main()
{
    while (true) {
        system("cls");
        cout << "Welcome to the Calculator. To use Pi enter p. Enter the expression:";
        string str;
        getline(cin, str);
        stringstream sstr{ str };

        char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
        double value;
        bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
        stack<Leksema> Stack_num; //Стек с числами
        stack<Leksema> Stack_oper; //Стек с операциями
        Leksema item; //Объект типа Leksema
        while (true) {
            Ch = sstr.peek(); //Смотрим на первый символ
            if (Ch == '\377') break; //Если достигнут конец строки, выходим из цикла
            if (Ch == ' ') { //Игнорирование пробелов
                sstr.ignore();
                continue;
            }
            if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'l') { //Если прочитана функция
                char foo[3]; //массив на 3 символа для определения типа прочитанной функции
                for (int i = 0; i < 3; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') { //Если прочитанная функция - синус
                    item.type = 's';
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') { //Если прочитанная функция - косинус
                    item.type = 'c';
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') { //Если прочитанная функция - тангенс
                    item.type = 't';
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    continue;
                }
                if (foo[0] == 'l' && foo[1] == 'o' && foo[2] == 'g') { //Если прочитанная функция - логарифм
                    item.type = 'l';
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    continue;
                }
            }
            if (Ch == 'p') { //Если прочитано число Пи
                item.type = '0';
                item.value = Pi;
                Stack_num.push(item); //Число кладется в стек с числами
                flag = 0;
                sstr.ignore();
                continue;
            }
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_num.push(item); //Число кладется в стек с числами
                flag = 0;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //Если прочитана операция
                if (Stack_oper.size() == 0) { //Если стек с операциями пуст
                    item.type = Ch;
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
                if (Stack_oper.size() != 0 && getRang(Ch) >
                                              getRang(Stack_oper.top().type)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
                    item.type = Ch;
                    item.value = 0;
                    Stack_oper.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
                if (Stack_oper.size() != 0 && getRang(Ch) <=
                                              getRang(Stack_oper.top().type)) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
                    if (Maths(Stack_num, Stack_oper, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (Ch == '(') { //Если прочитана открывающаяся скобка
                item.type = Ch;
                item.value = 0;
                Stack_oper.push(item); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }
            if (Ch == ')') { //Если прочитана закрывающаяся скобка
                while (Stack_oper.top().type != '(') {
                    if (Maths(Stack_num, Stack_oper, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    else continue; //Если все хорошо
                }
                Stack_oper.pop();
                sstr.ignore();
                continue;
            }
            else { //Если прочитан какой-то странный символ
                cout << "\nUnexpected symbol!\n";
                system("pause");
                return 0;
            }
        }
        while (Stack_oper.size() != 0) { //Вызываем математическую функцию до тех пор, пока в стеке с операциями не будет 0 элементов
            if (Maths(Stack_num, Stack_oper, item) == false) { //Если функция вернет "false", то прекращаем работу
                system("pause");
                return 0;
            }
            else continue; //Если все хорошо
        }
        cout << "Answer is: " << Stack_num.top().value << endl; //Выводим ответ
        system("pause");
    }
    return 0;
}

