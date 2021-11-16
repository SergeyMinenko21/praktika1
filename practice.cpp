//13 variant
#include <iostream>
#include <iomanip>
using namespace std;

enum error_code {
    OK = 0

};

enum {
    NAME_SIZE = 20,
    GROUP_MAX_SIZE = 100
    
};

enum menu_options {
    INPUTALL = 1,
    OUTPUTALL,
    OUTPUTREQ,
    ADDSTUD,
    EDITSTUD,
    DELSTUD,
    SORTARR,
    EXIT = 0
};

typedef struct student {
    char surname[NAME_SIZE];
    char name[NAME_SIZE];
    char patronym[NAME_SIZE];
    int grade;
    int year;
    struct marks {
        int math;
        int geom;
        int prog;
        int graph;
    } marks;
    
} student_t;

int group_input(student_t* group, int* groupsize);
int group_print(student_t* group, int groupsize);
int print_request(student_t* group, int groupsize);

int main() {
    setlocale(LC_ALL, "");
    int menu_opt;
    student_t group[GROUP_MAX_SIZE]; int groupsize{};
    do
    {
        cout << "Опции меню" << endl;
        cout << "1 - Ввести новую базу данных" << endl;
        cout << "2 - Вывести все данные" << endl;
        cout << "3 - Вывести данные по запросу" << endl;
        cout << "4 - Добавить студента (не реализовано)" << endl;
        cout << "5 - Редактировать данные студента (не реализовано)" << endl;
        cout << "6 - Удалить данные студента (не реализовано)" << endl;
        cout << "7 - Сортировать данные (не реализовано)" << endl;
        cout << "0 - Выход"<< endl;
        cin >> menu_opt;
        switch (menu_opt) {
        case INPUTALL:
            group_input(group, &groupsize);
            break;
        case OUTPUTALL:
            group_print(group, groupsize);
            break;
        case OUTPUTREQ:
            print_request(group, groupsize);
            break;
        default:
            break;
        }
    } while (menu_opt);
    

    return 0;
}

int group_input(student_t* group, int* groupsize) {
    cout << "Вводите последовательно фамилию, имя, отчество, курс, год поступления, оценки" << endl;
    cout << "Введите 0, чтобы закончить ввод" << endl;
    
    int i{};
    do
    {
        cin >> group[i].surname;
        if (group[i].surname[0] == '0') {
            break;
        }
        cin >> group[i].name;
        cin >> group[i].patronym;
        cin >> group[i].grade;
        if (group[i].grade < 0 || group[i].grade > 6) {
            cout << "Номер курса должен быть положительным, не больше 6" << endl;
            continue;
        }
        cin >> group[i].year;
        if (group[i].year < 0) {
            cout << "Год поступления должен быть положительным" << endl;
            continue;
        }
        cin >> group[i].marks.math >> group[i].marks.geom >> group[i].marks.prog >> group[i].marks.graph;
        if ((group[i].marks.math < 0 || group[i].marks.math > 5) || (group[i].marks.geom < 0 || group[i].marks.geom > 5) || 
        (group[i].marks.prog < 0 || group[i].marks.prog > 5) || (group[i].marks.graph < 0 || group[i].marks.graph > 5)) {
            cout << "Оценка может быть в пределах от 0 до 5" << endl;
            continue;
        }
        if (cin.fail()) {
            cout << "Ошибка ввода. Попробуйте снова" << endl;
            cin.clear();
            cin.ignore(32767, '\n');
        }
        else {
            i++;
            cout << "Запись успешно введена" << endl;
        }
            
    } while (group && i < GROUP_MAX_SIZE);
    *groupsize = i;
    return OK;
}

int group_print(student_t* group, int groupsize) {
    // Как бороться со кривой кодировкой?
    cout << setw(6) << left << "Номер"; 
    cout << setw(21) << left << "Фамилия"; 
    cout << setw(21) << left << "Имя"; 
    cout << setw(21) << left << "Отчество";
    cout << setw(5) << left << "Курс";
    cout << setw(16) << left << "Год поступления";
    cout << setw(11) << left << "Мат.анализ"; 
    cout << setw(13) << left << "Аналит.геом."; 
    cout << setw(9) << left << "Програм."; 
    cout << setw(10) << left << "Инж.граф." << endl;
    for (int i = 0; i < groupsize; i++) {
        cout << setw(6) << left << i + 1;
        cout << setw(21) << left << group[i].surname;
        cout << setw(21) << left << group[i].name;
        cout << setw(21) << left << group[i].patronym;
        cout << setw(5) << left << group[i].grade;
        cout << setw(16) << left << group[i].year;
        cout << setw(11) << left << group[i].marks.math;
        cout << setw(13) << left << group[i].marks.geom;
        cout << setw(9) << left << group[i].marks.prog;
        cout << setw(10) << left << group[i].marks.graph;
        cout << endl;
    }
//    cout << "Владимирович"; // char[25]
    return OK;
}

int print_request(student_t* group, int groupsize) {
    int sum{}, amount{}, year{};
    double res{};
    cout << "Введите год поступления" << endl;
    cin >> year;
    for (int i = 0; i < groupsize; i++)
    {
        if (group[i].year == year) {
            sum = sum + group[i].marks.math + group[i].marks.geom + group[i].marks.prog + group[i].marks.graph;
            amount += 4;
        }
    }

    if (sum == 0)
        cout << "Нет студентов с таким годом поступления" << endl;
    else {
        res = 1.0 * sum / amount;
        cout << "Средний балл за год " << year << " = " << res << endl;
    }
    return OK;
}