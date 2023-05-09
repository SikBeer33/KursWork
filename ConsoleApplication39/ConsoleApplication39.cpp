#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

ofstream ofs;
ifstream ifs;

struct Date
{
	int day;
	int month;
	int year;
};

struct subject
{
	string subject1;
	int estimation1[8];
};

struct subject2
{
	string subject3;
	string offset[8];
};

struct institution
{
	string faculty;
	string department;
	string group;
	string number;
};

struct student
{
	string surname;
	string name;
	string patronymic;
	struct Date date;
	struct Date admission;
	struct institution Institution;
	int gender;
	struct subject Subject[5];
	struct subject2 Offset[5];
};

struct Node
{
	student info;
	struct Node* next;
};

struct Node* myhead;
int index = 0;

void add(student info)
{
	struct Node* newitem = new Node();
	newitem->info = info;
	if (index == 0)
	{
		myhead = newitem;
		newitem->next = NULL;
	}
	else
	{
		struct Node* current = myhead;
		while (current->next != NULL)
		{
			current = current->next;
		}

		newitem->next = NULL;
		current->next = newitem;
	}
	index++;
}

void printitem()
{
	struct Node* newitem = myhead;
	cout << endl;
	system("cls");
	cout << "0) Добавить студента" << endl;
	cout << endl;
	if (index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			cout << i + 1 << ") ";
			cout << newitem->info.surname << " " << newitem->info.name << " " << newitem->info.patronymic << " " << newitem->info.Institution.group;
			cout << endl;
			newitem = newitem->next;
		}
	}
}

bool checkdate(Date date)
{
	if (date.day <= 31 && date.day >= 1 && date.month >= 1 && date.month <= 12 && date.year >= 1000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkadmissiondata(Date date, Date admissiondate)
{
	if (admissiondate.day <= 31 && admissiondate.day >= 1 && admissiondate.month >= 1 && admissiondate.month <= 12 && admissiondate.year >= 1000 && date.year < admissiondate.year) {
		return true;
	}
	else
	{
		return false;
	}
}

bool checkdateword1(string word)
{
	for (char n : word)
	{
		if (!isdigit(n))
		{
			return false;
		}
	}
	return true;
}
int checkday()
{
	string number;
y1:cin >> number;
	if (checkdateword1(number))
	{
		return stoi(number);
	}
	else
	{
		//cout << endl;
		cout << "День введён неверно!\n";
		//cout << endl;
		cout << "Введите день -> ";
		goto y1;
	}
}

int checkmonth()
{
	string number;
y2:cin >> number;
	if (checkdateword1(number))
	{
		return stoi(number);
	}
	else
	{
		//cout << endl;
		cout << "Месяц введён неверно!\n";
		//cout << endl;
		cout << "Введите месяц -> ";
		goto y2;
	}
}

int checkyear()
{
	string number;
y3:cin >> number;
	if (checkdateword1(number))
	{
		return stoi(number);
	}
	else
	{
		//cout << endl;
		cout << "Год введён неверно!\n";
		//cout << endl;
		cout << "Введите год -> ";
		goto y3;
	}
}

int checkagender()
{
	string gender;
f1: cout << "Введите пол: Мужской(0) Женский(1) -> ";
	cin >> gender;
	int gen;
	for (char n : gender)
	{
		if (!isdigit(n))
		{
			cout << "Неправильный индекс пола\n";
			goto f1;
		}
	}
	gen = stoi(gender);
	if (gen >= 0 && gen <= 1)
	{
		return gen;
	}
	else
	{
		cout << "Неправильный индекс пола\n";
		goto f1;
	}


}

void safe()
{
	ofs.open("test", ios_base::out);
	class Node* current = myhead;
	while (current)
	{
		ofs << current->info.surname << ' ' << current->info.name << ' ' << current->info.patronymic << ' ';
		ofs << current->info.date.day << ' ' << current->info.date.month << ' ' << current->info.date.year << ' ';
		ofs << current->info.admission.day << ' ' << current->info.admission.month << ' ' << current->info.admission.year << ' ';
		ofs << current->info.Institution.faculty << ' ' << current->info.Institution.department << ' ' << current->info.Institution.group << ' ' << current->info.Institution.number << ' ';
		ofs << current->info.gender << ' ';
		for (int i = 0; i < 5; i++)
		{
			ofs << current->info.Subject[i].subject1 << ' ';

			for (int j = 0; j < 8; j++)
			{
				ofs << current->info.Subject[i].estimation1[j] << ' ';
			}
		}
		for (int i = 0; i < 5; i++)
		{
			ofs << current->info.Offset[i].subject3 << ' ';

			for (int j = 0; j < 8; j++)
			{
				ofs << current->info.Offset[i].offset[j] << ' ';
			}
		}

		ofs << endl;
		current = current->next;
	}
	ofs.close();
}
void deleteitem(int choice)
{
	if (index > 0 and choice > 0 and index <= choice)
	{

		class Node* current = myhead;
		class Node* old;
		if (index == 1)
		{
			old = myhead;
			myhead = current->next;
			delete old;
			index--;
		}
		else {
			int i = 0;
			while (current)
			{
				if (i == index - 2) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					index--;
					break;
				}
				current = current->next;
				i++;
			}

		}
	}
	safe();
}

void printDate(struct Date d) {
	cout << left;
	cout.width(0); cout.fill(' '); cout << " ";
	if (d.day > 9) {
		cout << d.day;
	}
	else {
		cout << "0" << d.day;
	}
	cout << ".";
	if (d.month > 9) {
		cout << d.month;
	}
	else {
		cout << "0" << d.month;
	}
	cout << ".";
	cout << d.year;
	cout.width(0); cout.fill(' '); cout << " ";
}


bool checkoption() 
{
	string optionExit;
	int exit;
	p3:cout << "Введите 0 для выхода --> ";
	cin >> optionExit;
	for (char c : optionExit)
	{
		if (!isdigit(c))
		{
			cout << "Ошибка ввода!\n";
			goto p3;
		}
	}
	exit = stoi(optionExit);
	if (!(exit == 0)) 
	{
		cout << "Ошибка ввода!\n";
		goto p3;
	}
	else 
	{
		return true;
	}


}

int newsubject() {
	string newsubject;
	int numberchoice;
	p4:cin >> newsubject;
	for (char c : newsubject)
	{
		if (!isdigit(c))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto p4;
		}
	}
	numberchoice = stoi(newsubject);
	return numberchoice;
}

int newestimation1(int numb)
{
	struct Node* current = myhead;
	if (numb <= index && numb >= 0 && index > 0)
	{
		if (index > 1 && numb >= 1)
		{
			for (int i = 0; i < numb - 1; i++)
			{
				current = current->next;
			}
		}

	}
	m1:system("cls");
	int choiceType;
	cout << "Выберите тип предмета: Экзамен(1) Зачёт(2)\n";
	choiceType = newsubject();
	if (!(choiceType >= 1 && choiceType <= 2))
	{
		goto m1;
	}
	if (choiceType == 1)
	{
		cout << "Выберите предмет:\n";
		cout << "1)" << current->info.Subject[0].subject1 << "\n";
		cout << "2)" << current->info.Subject[1].subject1 << "\n";
		cout << "3)" << current->info.Subject[2].subject1 << "\n";
		cout << "4)" << current->info.Subject[3].subject1 << "\n";
		cout << "5)" << current->info.Subject[4].subject1 << "\n";
		cout << "---> ";
		m2:int choiceSubject = newsubject() - 1;
		if (!(choiceSubject >= 0 && choiceSubject <= 4))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto m2;
		}
		cout << "Оценки по предмету -> " << current->info.Subject[choiceSubject].subject1 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i+1 << " Семестр -> " << current->info.Subject[choiceSubject].estimation1[i];
			cout << endl;
		}
		cout << "Выберите номер семестра в котором хотите изменить оценку -> ";
		m3:int semester = newsubject() - 1;
		if (!(semester >= 0 && semester <= 7))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto m3;
		}
		cout << "Введите новую оценку -> ";
		m4:int estimate = newsubject();
		if (!(estimate >= 2 && estimate <= 5))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto m4;
		}
		current->info.Subject[choiceSubject].estimation1[semester] = estimate;
		safe();
		return 0;
	}
	if (choiceType == 2) {
		cout << "Выберите предмет:\n";
		cout << "1)" << current->info.Offset[0].subject3 << "\n";
		cout << "2)" << current->info.Offset[1].subject3 << "\n";
		cout << "3)" << current->info.Offset[2].subject3 << "\n";
		cout << "4)" << current->info.Offset[3].subject3 << "\n";
		cout << "5)" << current->info.Offset[4].subject3 << "\n";
		cout << "---> ";
		m5:int choiceOffset = newsubject() - 1;
		if (!(choiceOffset >= 0 && choiceOffset <= 4))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto m5;
		}
		cout << "Оценки по предмету -> " << current->info.Offset[choiceOffset].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[choiceOffset].offset[i];
			cout << endl;
		}
		cout << "Выберите номер семестра в котором хотите изменить оценку -> ";
		m6:int choicesemester = newsubject() - 1;
		if (!(choicesemester >= 0 && choicesemester <= 7))
		{
			cout << "Ошибка ввода! Повторите ввод -> ";
			goto m6;
		}
		m7:cout << "Введите Зачёт/Незачёт -> ";
		string newestimate;
		cin >> newestimate;
		string checkoffsett = "Зачёт";
		string checkoffsett2 = "Незачёт";
		string checkoffsett3 = "незачёт";
		string checkoffsett4 = "зачёт";
		if (newestimate == checkoffsett || newestimate == checkoffsett2 || newestimate == checkoffsett3 || newestimate == checkoffsett4)
		{
			current->info.Offset[choiceOffset].offset[choicesemester] = newestimate;
			safe();
			return 0;
		}
		else
		{
			cout << "Ошибка ввода зачёт/незачёт!\n";
			goto m7;
		}
	}



}


 int printsubject(int numb)
{
	struct Node* current = myhead;
	if (numb <= index && numb >= 0 && index > 0)
	{
		if (index > 1 && numb >= 1)
		{
			for (int i = 0; i < numb-1; i++)
			{
				current = current->next;
			}
		}
		
	}
	p2:system("cls");
	string option;
	int option2;
	cout << "Выберите предмет:\n";
	cout << "1)" << current->info.Subject[0].subject1 << "\n";
	cout << "2)" << current->info.Subject[1].subject1 << "\n";
	cout << "3)" << current->info.Subject[2].subject1 << "\n";
	cout << "4)" << current->info.Subject[3].subject1 << "\n";
	cout << "5)" << current->info.Subject[4].subject1 << "\n";
	cout << "6)" << current->info.Offset[0].subject3 << "\n";
	cout << "7)" << current->info.Offset[1].subject3 << "\n";
	cout << "8)" << current->info.Offset[2].subject3 << "\n";
	cout << "9)" << current->info.Offset[3].subject3 << "\n";
	cout << "10)" << current->info.Offset[4].subject3 << "\n";
	cout << endl;
	cout << "Редактирование:\n";
	cout << "11) Изменить название предмета\n";
	cout << "12) Изменить оценки\n";
	cout << endl;
	cout << "0)ВЫХОД\n";
	cout << "----> ";
	cin >> option;
	for (char c : option)
	{
		if (!isdigit(c))
		{
			goto p2;
		}
	}
	option2 = stoi(option);
	if (!(option2 <= 12 && option2 >= 0))
	{
		goto p2;
	}

	switch (option2)
	{
	case 1:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Subject[0].subject1 << "\n";
		for (int i = 0; i < 8; i++) 
		{
			cout << i + 1 << " Семестр -> " << current->info.Subject[0].estimation1[i];
			cout << endl;
		}
		if (checkoption()) 
		{
			goto p2;
		}
	case 2:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Subject[1].subject1 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Subject[1].estimation1[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 3:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Subject[2].subject1 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Subject[2].estimation1[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 4:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Subject[3].subject1 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Subject[3].estimation1[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 5:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Subject[4].subject1 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Subject[4].estimation1[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 6:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Offset[0].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[0].offset[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 7:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Offset[1].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[1].offset[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 8:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Offset[2].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[2].offset[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 9:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Offset[3].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[3].offset[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 10:
		system("cls");
		cout << "Оценки по предмету -> " << current->info.Offset[4].subject3 << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " Семестр -> " << current->info.Offset[4].offset[i];
			cout << endl;
		}
		if (checkoption())
		{
			goto p2;
		}
	case 11:
		system("cls");
	p10:cout << "Выберите тип предмета: Экзамен(1) Зачёт(2) (При выборе предметов зачётной сессии просьба продублировать!)\n";
		if ((newsubject() == 1)) 
		{
			cout << "Выберите предмет:\n";
			cout << "1)" << current->info.Subject[0].subject1 << "\n";
			cout << "2)" << current->info.Subject[1].subject1 << "\n";
			cout << "3)" << current->info.Subject[2].subject1 << "\n";
			cout << "4)" << current->info.Subject[3].subject1 << "\n";
			cout << "5)" << current->info.Subject[4].subject1 << "\n";
			cout << "---> ";
		p11:int nomer = newsubject() - 1;
			if (!(nomer >= 0 && nomer <= 4)) 
			{
				cout << "Ошибка ввода! Повторите ввод -> ";
				goto p11;
			}
			else 
			{
				cout << "Введите новое название предмета (1 слово) -> ";
				cin >> current->info.Subject[nomer].subject1;
				safe();
				goto p2;
			}
		}
		else if((newsubject() == 2))
		{
			cout << "Выберите предмет:\n";
			cout << "1)" << current->info.Offset[0].subject3 << "\n";
			cout << "2)" << current->info.Offset[1].subject3 << "\n";
			cout << "3)" << current->info.Offset[2].subject3 << "\n";
			cout << "4)" << current->info.Offset[3].subject3 << "\n";
			cout << "5)" << current->info.Offset[4].subject3 << "\n";
			cout << "---> ";
		p12:int nomer2 = newsubject() - 1;
			if (!(nomer2 >= 0 && nomer2 <= 4))
			{
				cout << "Ошибка ввода! Повторите ввод -> ";
				goto p12;
			}
			else
			{
				cout << "Введите новое название предмета (1 слово) -> ";
				cin >> current->info.Offset[nomer2].subject3;
				safe();
				goto p2;
			}
		}
		else 
		{
			cout << "Ошибка ввода!\n";
			goto p10;
		}
	case 12:
		system("cls");
		newestimation1(numb);
		goto p2;
		

	default:
		return 0;
	}



}

int Informationitem(int choice)
{
	struct Node* current = myhead;
	if (choice <= index && choice >= 0 && index > 0)
	{
		if (index > 1 && choice >=1) 
		{
			for (int i = 0; i < choice-1; i++)
			{
				current = current->next;
			}
		}
		p1:system("cls");
		cout << "ИНФОРМАЦИЯ О СТУДЕНТЕ:\n";
		cout << "Ф.И.О. -> " << current->info.surname << " " << current->info.name << " " << current->info.patronymic << "\n";
		cout << "Дата рождения ->";
		printDate(current->info.date);
		cout << endl;
		cout << "Название Института -> " << current->info.Institution.faculty << "\n";
		cout << "Кафедра -> " << current->info.Institution.department << "\n";
		cout << "Номер группы -> " << current->info.Institution.group << "\n";
		cout << "Номер зачётной книжки -> " << current->info.Institution.number << "\n";
		cout << "Дата поступления ->";
		printDate(current->info.admission);
		cout << endl;
		if (current->info.gender == 0) 
		{
			cout << "Пол -> " << "Мужчина\n";
		}
		else 
		{
			cout << "Пол -> " << "Женщина\n";
		}
		string in;
		int cho;
		cout << endl;
		cout << "ВЫБЕРИТЕ ДЕЙСТВИЕ";
		cout << endl;
		cout << endl;
		cout << "Просмотр Информации:\n";
		cout << "1)Просмотр оценок\n";
		cout << endl;
		cout << "Редактирование информации о студенте:\n";
		cout << "2)Удалить студента\n";
		cout << "3)Изменить Фамилию\n";
		cout << "4)Изменить Имя\n";
		cout << "5)Изменить Отчество\n";
		cout << "6)Изменить дату рождения\n";
		cout << "7)Изменить название института\n";
		cout << "8)Изменить кафедру\n";
		cout << "9)Изменить номер группы\n";
		cout << "10)Изменить номер зачётной книжки\n";
		cout << "11)Изменить дату поступления\n";
		cout << "12)Изменить пол\n";
		cout << endl;
		cout << "0)ВЫХОД\n";
		cout << "----> ";
		cin >> in;
		for (char c : in)
		{
			if (!isdigit(c))
			{
				goto p1;
			}
		}
		cho = stoi(in);
		if (!(cho <= 12 && cho >=0)) 
		{
			goto p1;
		}

		switch (cho)
		{
		case 1:
			printsubject(choice);
			goto p1;
		case 2:
			deleteitem(choice);
			return 1;
		case 3:
		k1: system("cls");
			cout << "Введите новую фамилию -> ";
			char newsurname[300];
			cin >> newsurname;
			for (int i = 0; i < strlen(newsurname); i++)
				if (newsurname[i] >= '\0' && newsurname[i] <= '@' or newsurname[i] >= '[' && newsurname[i] <= '`' or newsurname[i] >= '{' && newsurname[i] <= 191)
				{
					cout << "Ошибка ввода. Фамилия должна содержать только буквы латинского или русского алфавита\n";
					goto k1;
				}
			current->info.surname = newsurname;
			safe();
			goto p1;
		case 4:
		k2: system("cls");
			cout << "Введите новое имя -> ";
			char newname[300];
			cin >> newname;
			//cout << endl;
			for (int i = 0; i < strlen(newname); i++)
				if (newname[i] >= '\0' && newname[i] <= '@' or newname[i] >= '[' && newname[i] <= '`' or newname[i] >= '{' && newname[i] <= 191)
				{
					cout << "Ошибка ввода. Имя должно содержать только буквы латинского или русского алфавита\n";
					goto k2;
				}
			current->info.name = newname;
			safe();
			goto p1;
		case 5:
		k3: system("cls");
			cout << "Введите новое отчество -> ";
			char newpatronymic[300];
			cin >> newpatronymic;
			for (int i = 0; i < strlen(newpatronymic); i++)
				if (newpatronymic[i] >= '\0' && newpatronymic[i] <= '@' or newpatronymic[i] >= '[' && newpatronymic[i] <= '`' or newpatronymic[i] >= '{' && newpatronymic[i] <= 191)
				{
					cout << "Ошибка ввода. Отчество должно содержать только буквы латинского или русского алфавита\n";
					goto k3;
				}
			current->info.patronymic = newpatronymic;
			safe();
			goto p1;
		case 6:
		k4: system("cls");
			cout << "Введите новую дату рождения:\n";
			Date newdate;
			cout << "Введите день -> ";
			newdate.day = checkday();
			cout << "Введите месяц -> ";
			newdate.month = checkmonth();
			cout << "Введите год -> ";
			newdate.year = checkyear();
			if (checkdate(newdate))
			{
				current->info.date = newdate;
				safe();
				goto p1;
			}
			else
			{
				cout << "Дата рождения введена с ошибкой\n";
				goto k4;
			}

		case 7:
			system("cls");
			cout << "Введите новое название института -> ";
			cin >> current->info.Institution.faculty;
			safe();
			goto p1;
		case 8:
			system("cls");
			cout << "Введите новое название кафедры -> ";
			cin >> current->info.Institution.department;
			safe();
			goto p1;
		case 9:
			system("cls");
			cout << "Введите новый номер группы -> ";
			cin >> current->info.Institution.group;
			safe();
			goto p1;
		case 10:
			system("cls");
			cout << "Введите новый номер зачётной книжки -> ";
			cin >> current->info.Institution.number;
			safe();
			goto p1;
		case 11:
		k5: system("cls");
			cout << "Введите новую дату поступления:\n";
			Date newadmissiondate;
			//cout << endl;
			cout << "Введите день -> ";
			newadmissiondate.day = checkday();
			//cout << endl;
			cout << "Введите месяц -> ";
			newadmissiondate.month = checkmonth();
			//cout << endl;
			cout << "Введите год -> ";
			newadmissiondate.year = checkyear();
			//cout << endl;
			if (checkadmissiondata(current->info.date, newadmissiondate))
			{
				current->info.admission = newadmissiondate;
				safe();
				goto p1;
			}
			else
			{
				cout << "Новая дата поступления введена с ошибкой (Обратите внимание ГОД РОЖДЕНИЯ не может быть больше ГОДА ПОСТУПЛЕНИЯ)\n";
				goto k5;
			}

		case 12:
			system("cls");
			current->info.gender = checkagender();
			safe();
			goto p1;

		default:
			return 0;
			
		}
		
	}
}





int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student students;
	setlocale(LC_ALL, "ru");
	int count = 0;
	int choice;
	string input;

	ofs.open("test", ios_base::app);
	ofs.close();
	ifs.open("test", ios_base::in);

	while (!ifs.eof())
	{
		if (ifs.get() == '\n')
		{
			count++;
		}
	}
	//ifs.clear();

	//ifs.seekg(0, ios::end);
	//if (ifs.tellg() > 0)
	//{
		//ifs.seekg(0, ios::beg);
		//if (ifs.get() != '\n')
		//{
			//count++;
		//}
		//cout << count << endl;
	//}
	ifs.close();

	int& Count = count;
	int max = count;

	ifs.open("test", ios_base::in);
	for (int i = 0; i < max; i++) {
		ifs >> students.surname >> students.name >> students.patronymic >> students.date.day >> students.date.month >> students.date.year;
		ifs >> students.admission.day >> students.admission.month >> students.admission.year;
		ifs >> students.Institution.faculty >> students.Institution.department >> students.Institution.group >> students.Institution.number >> students.gender;
		for (int k = 0; k < 5; k++) {

			ifs >> students.Subject[k].subject1;

			for (int j = 0; j < 8; j++) {

				ifs >> students.Subject[k].estimation1[j];
			}
		}
		for (int l = 0; l < 5; l++) {

			ifs >> students.Offset[l].subject3;

			for (int m = 0; m < 8; m++) {

				ifs >> students.Offset[l].offset[m];
			}
		}
		add(students);
	}
	ifs.close();

a1:printitem();

	if (index == 0)
	{
		cout << endl;
		cout << "Добавить студената (0) -> ";
		cin >> input;

	}
	else if (index == 1) 
	{
		cout << endl;
		cout << "Добавить студената (0) / Подробнее о студенте (1) -> ";
		cin >> input;
	}
	else
	{
		cout << endl;
		cout << "Добавить студената (0) / Подробнее о студенте" << " (1-" << index << ") -> ";
		cin >> input;
	}

	for (char c : input)
	{
		if (!isdigit(c))
		{
			goto a1;
		}
	}
	choice = stoi(input);
	cout << endl;

	if (!(choice <= index && choice >= 0))
	{
		goto a1;
	}

	switch (choice)
	{
	case 0:
	b1: cout << "Введите фамилию -> ";
		char a[300];
		cin >> a;
		//cout << endl;
		for (int i = 0; i < strlen(a); i++)
			if (a[i] >= '\0' && a[i] <= '@' or a[i] >= '[' && a[i] <= '`' or a[i] >= '{' && a[i] <= 191)
			{
				cout << "Ошибка ввода. Фамилия должна содержать только буквы латинского или русского алфавита\n";
				//cout << endl;
				goto b1;
			}
		students.surname = a;
	b2: cout << "Введите имя -> ";
		char b[300];
		cin >> b;
		//cout << endl;
		for (int i = 0; i < strlen(b); i++)
			if (b[i] >= '\0' && b[i] <= '@' or b[i] >= '[' && b[i] <= '`' or b[i] >= '{' && b[i] <= 191)
			{
				cout << "Ошибка ввода. Имя должно содержать только буквы латинского или русского алфавита\n";
				//cout << endl;
				goto b2;
			}
		students.name = b;
	b3: cout << "Введите отчество -> ";
		char d[300];
		cin >> d;
		//cout << endl;
		for (int i = 0; i < strlen(d); i++)
			if (d[i] >= '\0' && d[i] <= '@' or d[i] >= '[' && d[i] <= '`' or d[i] >= '{' && d[i] <= 191)
			{
				cout << "Ошибка ввода. Отчество должно содержать только буквы латинского или русского алфавита\n";
				//cout << endl;
				goto b3;
			}
		students.patronymic = d;
	z1: cout << "Введите дату рождения:\n";
		//cout << endl;
		Date tempdate;
		cout << "Введите день -> ";
		tempdate.day = checkday();
		//cout << endl;
		cout << "Введите месяц -> ";
		tempdate.month = checkmonth();
		//cout << endl;
		cout << "Введите год -> ";
		tempdate.year = checkyear();
		if (checkdate(tempdate))
		{
			students.date = tempdate;
		}
		else
		{
			//cout << endl;
			cout << "Дата рождения введена с ошибкой\n";
			//cout << endl;
			goto z1;
		}
		//cout << endl;
	z2: cout << "Введите дату поступления:\n";
		Date admissiondate;
		//cout << endl;
		cout << "Введите день -> ";
		admissiondate.day = checkday();
		//cout << endl;
		cout << "Введите месяц -> ";
		admissiondate.month = checkmonth();
		//cout << endl;
		cout << "Введите год -> ";
		admissiondate.year = checkyear();
		//cout << endl;
		if (checkadmissiondata(tempdate, admissiondate))
		{
			students.admission = admissiondate;
		}
		else
		{
			cout << "Дата поступления введена с ошибкой (Обратите внимание ГОД РОЖДЕНИЯ не может быть больше ГОДА ПОСТУПЛЕНИЯ)\n";
			goto z2;
		}
		cout << "Введите институт -> ";
		cin >> students.Institution.faculty;
		//cout << endl;
		cout << "Введите кафедру -> ";
		cin >> students.Institution.department;
		//cout << endl;
		cout << "Введите номер группы -> ";
		cin >> students.Institution.group;
		//cout << endl;
		cout << "Введите номер зачётной книжки -> ";
		cin >> students.Institution.number;
		//cout << endl;
		students.gender = checkagender();
		for (int i = 0; i < 5; i++) 
		{
			cout << "Введите название предмета экзаменационной сессии (1 слово) -> ";
			cin >> students.Subject[i].subject1;
			cout << "Введите оценки (2-5) по семестрам:\n";
			for (int j = 0; j < 8; j++) 
			{
				string checkestimation;
				int score;
				x1:cout << j + 1 << " семестр -> ";
				cin >> checkestimation;
				for (char n : checkestimation)
				{
					if (!isdigit(n))
					{
						cout << "Ошибка ввода оценки!\n";
						goto x1;
					}
				}
				score = stoi(checkestimation);
				if (score >= 2 && score <= 5) 
				{
					students.Subject[i].estimation1[j] = score;
				}
				else 
				{
					cout << "Ошибка ввода оценки! Оценка не может быть меньше 2 или больше 5\n";
					goto x1;
				}
			}
		}
		for (int i = 0; i < 5; i++) 
		{
			cout << "Введите название предмета зачётной сессии (1 слово) -> ";
			cin >> students.Offset[i].subject3;
			cout << "Введите зачёт/незачёт по семестрам:\n";
			for (int j = 0; j < 8; j++) 
			{
				string checkoffset = "Зачёт";
				string checkoffset2 = "Незачёт";
				string checkoffset3 = "незачёт";
				string checkoffset4 = "зачёт";
				string offset1;
			x2: cout << j + 1 << " семестр -> ";
				cin >> offset1;
				if (offset1 == checkoffset || offset1 == checkoffset2 || offset1 == checkoffset3 || offset1 == checkoffset4) 
				{
					students.Offset[i].offset[j] = offset1;
				}
				else 
				{
					cout << "Ошибка ввода зачёт/незачёт!\n";
					goto x2;
				}
			}
		}
		add(students);
		safe();
		goto a1;




	default:
		Informationitem(choice);
		goto a1;
	}

}









