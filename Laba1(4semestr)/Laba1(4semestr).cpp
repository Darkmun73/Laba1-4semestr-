#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <intrin.h> 
#pragma intrinsic(__rdtsc)
using namespace std;

void generate_input(size_t n, string out_fyle) {
    setlocale(LC_ALL, "rus");
    string lane;
    string direct[] = { "a"/*"Fizika", "Psihologiya", "Economica", "Himiya", "Geologiya",
        "Geographiya", "Biologiya", "Arhitektura", "Mashinostroenie", "Innovatika"*/ };

    string grp_num[] = { "Б9120-09.03.04прогин","Б9119-09.03.04прогин", "Б9120-09.03.03прогин",
        "М3121-26.04.02кто", "М3121-26.04.02ксо", "М4120-37.04.01пм", "С3120-08.05.01сгспо",
        "С3216-20.05.01птпп", "С3216-21.05.04мрд", "А8121-04.06.01фх", "А8121-04.06.01бох" };

    string FIO[] = { "Агеев Андрей Владиславович","Аксенова Алёна Егоровна","Анохин Марк Николаевич",
        "Безруков Иван Никитич","Ильина Варвара Львовна","Ильина Дарья Константиновна","Казанцев Григорий Михайлович",
        "Калугина Виктория Дмитриевна","Кириллова Алиса Демьяновна",
        "Киселева Арина Александровна","Ковалев Роман Александрович",
        "Ковалев Артём Егорович","Козина Василиса Марковна","Козырев Кирилл Иванович",
        "Лебедева Анна Львовна","Орлов Илья Русланович","Сорокина Валерия Тимуровна","Шестакова Таисия Павловна" };

    srand(time(0));
    ofstream output(out_fyle, 'w');
    output << n;
    for (int i = 0; i < n; i++) {
        output << "\n";
        lane = "";
        int phone1 = rand() % 900 + 100;
        int phone2 = rand() % 9000 + 1000;
        int month = rand() % 12 + 1;
        int day;
        if (month == 2) {
            day = rand() % 27 + 1;
        }
        else if (month % 2 == 1 or month == 8) {
            day = rand() % 31 + 1;
        }
        else  day = rand() % 30 + 1;
        int year = rand() % 4 + 2000;
        lane += FIO[rand() % 18] + ' ' + direct[0/*rand() % 10*/] + ' ' + grp_num[rand() % 11];
        lane += ' ' + (day < 10 ? '0' + to_string(day) : to_string(day)) + '.'
            + (month < 10 ? '0' + to_string(month) : to_string(month)) + '.' + to_string(year) + " 8914" + to_string(phone1) + to_string(phone2);

        output << lane;
    }
    output.close();
}

void split(string s, char delim, vector<string>& data)
{
    while (!s.empty())
    {
        auto word_end = s.find(delim);
        if (word_end == -1)
        {
            data.push_back(s);
            s.clear();
        }
        else
        {
            data.push_back(s.substr(0, word_end));
            s.erase(0, word_end + 1);
        }
    }
}

struct FIO
{
    string f;
    string i;
    string o;
};

struct BirthDate
{
    int dd;
    int mm;
    int yy;
};

struct Student
{
    FIO fio;
    string direct;
    string group_num;
    BirthDate bdate;
    string phone_num;
};

bool operator <(Student& l, Student& r)
{
    string tempL = l.fio.f + " " + l.fio.i + " " + l.fio.o;
    string tempR = r.fio.f + " " + r.fio.i + " " + r.fio.o;

    if (l.bdate.yy < r.bdate.yy)
        return true;
    else if (l.bdate.yy > r.bdate.yy)
        return false;
    else if (l.bdate.yy == r.bdate.yy)
    {
        if (l.bdate.mm < r.bdate.mm)
            return true;
        else if (l.bdate.mm > r.bdate.mm)
            return false;
        else if (l.bdate.mm == r.bdate.mm)
        {
            if (l.bdate.dd < r.bdate.dd)
                return true;
            else if (l.bdate.dd > r.bdate.dd)
                return false;
            else if (l.bdate.dd == r.bdate.dd)
            {
                if (l.group_num < r.group_num)
                    return true;
                else if (l.group_num > r.group_num)
                    return false;
                else if (l.group_num == r.group_num)
                {
                    if (tempL < tempR)
                        return true;
                    else if (tempL >= tempR)
                        return false;
                }
            }
        }
    }
}

//Вывод
void outStudents(ofstream& fout, Student* studentsWithFoundPattern, double time, size_t count)
{
    fout << time;
    for (size_t i = 0; i < count; i++)
    {
        fout << "\n";
        //studentsWithFoundPattern[i].bdate.dd < 10 ? '0' + to_string(day) : to_string(day)
        fout << (studentsWithFoundPattern[i].bdate.dd < 10 ? '0' + to_string(studentsWithFoundPattern[i].bdate.dd) : to_string(studentsWithFoundPattern[i].bdate.dd)) << "." <<
            (studentsWithFoundPattern[i].bdate.mm < 10 ? '0' + to_string(studentsWithFoundPattern[i].bdate.mm) : to_string(studentsWithFoundPattern[i].bdate.mm)) << "." <<
            (studentsWithFoundPattern[i].bdate.yy) << " ";
        int l = 23 - studentsWithFoundPattern[i].group_num.size();
        fout << studentsWithFoundPattern[i].group_num;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        string fio = studentsWithFoundPattern[i].fio.f + " " + studentsWithFoundPattern[i].fio.i + " " + studentsWithFoundPattern[i].fio.o;
        l = 31 - fio.size();
        fout << fio;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        l = 47 - studentsWithFoundPattern[i].direct.size();
        fout << studentsWithFoundPattern[i].direct;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        fout << studentsWithFoundPattern[i].phone_num;
    }
}

//Таблица сдвигов
int* shiftTable(std::string pattern)
{
    int* table = new int[256];
    for (size_t i = 0; i < 256; i++)
        table[i] = pattern.length();
    for (size_t i = 0; i < pattern.length() - 1; i++)
        table[pattern[i]] = pattern.length() - 1 - i;
    return table;
}

//Поиск Бойера-Мура-Хорспула с таблицей сдвигов shiftTab, ищущий в строке text шаблон pattern с длиной patternLength. Если шаблон встретился ровно k раз, то функция возвращает значение true
bool BoyerMooreHorspoolSearch(std::string text, std::string pattern, int k, int* shiftTab, int patternLength)
{
    char last;
    int howManyTimesPatternOccurs = 0;
    int startOfPatternInText = 0;
    int endOfPatternInText = startOfPatternInText + patternLength;

    while (endOfPatternInText <= text.length())
    {
        for (size_t i = endOfPatternInText - 1; text[i] == pattern[i - startOfPatternInText]; i--)
        {
            if ((i - startOfPatternInText) == 0)
            {
                howManyTimesPatternOccurs += 1;
                break;
            }
        }
        last = text[endOfPatternInText - 1];
        startOfPatternInText += shiftTab[last];
        endOfPatternInText = startOfPatternInText + patternLength;
    }
    if (howManyTimesPatternOccurs == k)
        return true;
    else
        return false;
}

//Линейный поиск, ищущий в строке text шаблон pattern с длиной patternLength. Если шаблон встретился ровно k раз, то функция возвращает значение true
bool naiveSearch(std::string text, std::string pattern, int k, int patternLength)
{
    int howManyTimesPatternOccurs = 0;
    for (size_t i = 0; i < text.length(); i++)
    {
        for (size_t j = 0; j < patternLength; j++)
        {
            if (text[i + j] != pattern[j])
                break;
            else if (j == (patternLength - 1))
                howManyTimesPatternOccurs += 1;
        }
    }
    if (howManyTimesPatternOccurs == k)
        return true;
    else
        return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string temp;
    vector<string> record;
    vector<string> sub_record;
    //generate_input(50, "C:\\Users\\mrgam\\OneDrive - ДВФУ\\Документы\\repos\\Laba3(fix)\\Laba3(fix)\\In_DVFUStudents_50.txt");
    //generate_input(20, "In_DVFUStudents_20.txt");
    //generate_input(100000, "In_DVFUStudents_best.txt");
    //generate_input(5000, "In_DVFUStudents_5000.txt");
    //generate_input(50000, "In_DVFUStudents_50000.txt");
    //generate_input(1000000, "DVFUStudents6.txt");

    ifstream fi1("In_DVFUStudents_best.txt");
    ofstream fout1("OutBMH_DVFUStudents_best.txt");
    ofstream fout2("Out_DVFUStudents_best.txt");

    getline(fi1, temp);
    const int n = stoi(temp);
    Student* students = new Student[n];
    for (size_t i = 0; i < n; i++)
    {
        getline(fi1, temp);
        split(temp, ' ', record);
        students[i].fio.f = record[0];
        students[i].fio.i = record[1];
        students[i].fio.o = record[2];
        students[i].direct = record[3];
        students[i].group_num = record[4];
        split(record[5], '.', sub_record);
        students[i].bdate.dd = stoi(sub_record[0]);
        students[i].bdate.mm = stoi(sub_record[1]);
        students[i].bdate.yy = stoi(sub_record[2]);
        students[i].phone_num = record[6];
        sub_record.clear();
        record.clear();
    }

    //Поиск Бойера-Мура-Хорспула
    size_t count = 0;
    Student* studentsWithFoundPattern = new Student[n];
    string pattern = "a";
    int patternLength = pattern.length();
    int* shiftTab = shiftTable(pattern); //таблица сдвигов

    double begin = clock();
    for (size_t i = 0; i < n; i++)
    {
        if (BoyerMooreHorspoolSearch(students[i].direct, pattern, 1, shiftTab, patternLength))
        {
            studentsWithFoundPattern[count] = students[i];
            count += 1;
        }
    }
    double end = clock();
    double t1 = (end - begin);

    //Вывод
    outStudents(fout1, studentsWithFoundPattern, t1, count);

    //Линейный поиск
    count = 0;

    begin = clock();
    for (size_t i = 0; i < n; i++)
    {
        if (naiveSearch(students[i].direct, pattern, 1, patternLength))
        {
            studentsWithFoundPattern[count] = students[i];
            count += 1;
        }
    }
    end = clock();
    t1 = (end - begin);


    //Вывод
    outStudents(fout2, studentsWithFoundPattern, t1, count);

    fi1.close();
    fout1.close();
    fout2.close();
}

/*if (text[i] != pattern[i - startOfPatternInText])
            {
                last = text[startOfPatternInText + pattern.length() - 1];
                startOfPatternInText += shiftTab[last];
                break;
            }
            else if ((i - startOfPatternInText) == 0)
            {
                howManyTimesPatternOccurs += 1;
                if (howManyTimesPatternOccurs == k)
                    return true;
                startOfPatternInText += pattern.length();
            }*/