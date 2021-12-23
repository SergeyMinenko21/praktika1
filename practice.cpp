#include <iostream>
#include <iomanip>
#include <locale.h>
using namespace std;

enum errorcode {
    OK = 0,
    ERR = -1
};

enum {
    NAME_SIZE = 32,
    GROUP_MAX_SIZE = 100
    
};

enum MainMenuOptions {
    INPUTALL = 1,
    OUTPUTALL,
    OUTPUTREQ,
    ADDSTUD,
    EDITSTUD,
    DELSTUD,
    SORTARR,
    EXIT = 0
};

typedef struct Student {
    char surname[NAME_SIZE];
    char name[NAME_SIZE];
    char patronym[NAME_SIZE];
    int grade;
    int year;
    struct Marks {
        int math;
        int geom;
        int prog;
        int graph;
    } marks;
} student_t;

int groupInputKey(student_t* group, int* groupsize);
int groupPrintTerm(student_t* group, int groupsize);
int printRequest(student_t* group, int groupsize);
int addStudent(student_t* group, int groupsize);
int cinFailCheck();

int main() {
    setlocale(LC_ALL, "");
    int menu_opt;
    student_t group[GROUP_MAX_SIZE]; int groupsize{};
    do
    {
        cout << "����� ����" << endl;
        cout << "1 - ������ ����� ���� ������" << endl;
        cout << "2 - ������� ��� ������" << endl;
        cout << "3 - ������� ������ �� �������" << endl;
        cout << "4 - �������� �������� (�� �����������)" << endl;
        cout << "5 - ������������� ������ �������� (�� �����������)" << endl;
        cout << "6 - ������� ������ �������� (�� �����������)" << endl;
        cout << "7 - ����������� ������ (�� �����������)" << endl;
        cout << "0 - �����" << endl;
        cin >> menu_opt;
        switch (menu_opt) {
        case INPUTALL:
            groupInputKey(group, &groupsize);
            break;
        case OUTPUTALL:
            groupPrintTerm(group, groupsize);
            break;
        case OUTPUTREQ:
            printRequest(group, groupsize);
            break;
        default:
            break;
        }
    } while (menu_opt);
    

    return 0;
}

int cinFailCheck() {
    int flag = OK;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        flag = ERR;
    }
    return flag;
}

int groupInputKey(student_t* group, int* groupsize) {
    cout << "������� ��������������� �������, ���, ��������, ����, ��� �����������, 4 ������" << endl;
    cout << "������� 0, ����� ��������� ����" << endl;
    
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
        while (cinFailCheck() || group[i].grade <= 0 || group[i].grade > 6) {
            cout << "����� ����� ������ ���� �������������, �� ������ 6. ���������� �����" << endl;
            cin >> group[i].grade;
        }
        cin >> group[i].year;
        while (cinFailCheck() || group[i].year <= 1900) {
            cout << "��� ����������� ������ ���� �� ������ 1900. ���������� �����" << endl;
            cin >> group[i].year;
        }
        cin >> group[i].marks.math >> group[i].marks.geom >> group[i].marks.prog >> group[i].marks.graph;
        while (cinFailCheck() ||  group[i].marks.math < 0 || group[i].marks.math > 5 || group[i].marks.geom < 0 || group[i].marks.geom > 5 || 
        group[i].marks.prog < 0 || group[i].marks.prog > 5 || group[i].marks.graph < 0 || group[i].marks.graph > 5) {
            cout << "������ ����� ���� � �������� �� 0 �� 5. ������� ������ �������" << endl;
            cin >> group[i].marks.math >> group[i].marks.geom >> group[i].marks.prog >> group[i].marks.graph;
        }
        i++;
        cout << "������ ������� �������" << endl;
    } while (group && i < GROUP_MAX_SIZE);
    *groupsize = i;
    if (i == GROUP_MAX_SIZE)
        cout << "��������� ������������ ������ ������" << endl;
    return OK;
}

int groupPrintTerm(student_t* group, int groupsize) {
    cout << setw(6) << left << "�����"; 
    cout << setw(22) << left << "�������"; 
    cout << setw(22) << left << "���"; 
    cout << setw(22) << left << "��������";
    cout << setw(5) << left << "����";
    cout << setw(16) << left << "��� �����������";
    cout << setw(11) << left << "���.������"; 
    cout << setw(13) << left << "������.����."; 
    cout << setw(9) << left << "�������."; 
    cout << setw(10) << left << "���.����." << endl;
    for (int i = 0; i < groupsize; i++) {
        cout << setw(6) << left << i + 1;
        cout << setw(22) << left << group[i].surname;
        cout << setw(22) << left << group[i].name;
        cout << setw(22) << left << group[i].patronym;
        cout << setw(5) << left << group[i].grade;
        cout << setw(16) << left << group[i].year;
        cout << setw(11) << left << group[i].marks.math;
        cout << setw(13) << left << group[i].marks.geom;
        cout << setw(9) << left << group[i].marks.prog;
        cout << setw(10) << left << group[i].marks.graph;
        cout << endl;
    }
    return OK;
}

int printRequest(student_t* group, int groupsize) {
    int sum{}, amount{}, year{};
    double res{};
    cout << "������� ��� �����������" << endl;
    cin >> year;
    for (int i = 0; i < groupsize; i++)
    {
        if (group[i].year == year) {
            sum = sum + group[i].marks.math + group[i].marks.geom + group[i].marks.prog + group[i].marks.graph;
            amount += 4;
        }
    }

    if (sum == 0)
        cout << "��� ��������� � ����� ����� �����������" << endl;
    else {
        res = 1.0 * sum / amount;
        cout << "������� ���� �� ��� " << year << " = " << res << endl;
    }
    return OK;
}

int addStudent(student_t* group, int groupsize, int i) {
    cin >> group[i].surname;
        if (group[i].surname[0] == '0') {
            return OK;
        }
        cin >> group[i].name;
        cin >> group[i].patronym;
        cin >> group[i].grade;
        while (cinFailCheck() || group[i].grade <= 0 || group[i].grade > 6) {
            cout << "����� ����� ������ ���� �������������, �� ������ 6. ���������� �����" << endl;
            cin >> group[i].grade;
        }
        cin >> group[i].year;
        while (cinFailCheck() || group[i].year <= 1900) {
            cout << "��� ����������� ������ ���� �� ������ 1900. ���������� �����" << endl;
            cin >> group[i].year;
        }
        cin >> group[i].marks.math >> group[i].marks.geom >> group[i].marks.prog >> group[i].marks.graph;
        while (cinFailCheck() ||  group[i].marks.math < 0 || group[i].marks.math > 5 || group[i].marks.geom < 0 || group[i].marks.geom > 5 || 
        group[i].marks.prog < 0 || group[i].marks.prog > 5 || group[i].marks.graph < 0 || group[i].marks.graph > 5) {
            cout << "������ ����� ���� � �������� �� 0 �� 5. ������� ������ �������" << endl;
            cin >> group[i].marks.math >> group[i].marks.geom >> group[i].marks.prog >> group[i].marks.graph;
        }
        i++;
        cout << "������ ������� �������" << endl;
    return i;
}