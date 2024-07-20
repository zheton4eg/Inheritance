#include <iostream>
#include <fstream>
#include <string>  //�������� ����� std::string
#include <string.h>  //��������� ������� ��� ������ � NULL Terminated Lines
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 12;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//         CONSTRUCTORS:

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//           METHODS:
	virtual std::ostream& print(std::ostream& os)const
	{
		//os << strchr(typeid(*this).name(),' ')+1 << ":\t";//�������� typeid(type|value) ���������� ��� �������� �� �����
		                                      //����� name() ���������� c_string()���������� ��� ����.
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		
		ofs.width(TYPE_WIDTH);	  //����� width() ������ ������ ������
		                 //��� ������ ������ ����� width()�������� ������������ �� ������� ����
		ofs << std::left;//���������� ������������ �� ������ ����
		                 //���� ����� width() ������ ������� �� ���� ��������� ��������
		ofs << std::string(strchr(typeid(*this).name(), ' ') + 1)+":";//�������� typeid(type|value) ���������� ��� �������� �� �����
		//����� name() ���������� c_string()���������� ��� ����.
		ofs.width(LAST_NAME_WIDTH);
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs <<  age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
			return ifs;
	}
};
 std::ostream& operator <<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
 std::ofstream& operator <<(std::ofstream& ofs, const Human& obj)
 {
	 return obj.print(ofs);
 }
 std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
 {
	 return obj.read(ifs);
 }
class Student : public Human
{
	const static int SPECIALITY_WIDTH = 25;
	const static int GROUP_WIDTH = 8;
	const static int RATING_WIDTH = 8;
	const static int ATTENDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	//       CONSTRUCTOR:
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group,  rating,  attendance
	Student
	(HUMAN_TAKE_PARAMETERS,
		STUDENT_TAKE_PARAMETERS
	):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	Student(const Human& human,STUDENT_TAKE_PARAMETERS) :Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstrucror:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	//          METHODS:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) <<" " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);
		ofs<< attendance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		ifs >> speciality >> group >> rating >> attendance;
		return ifs;
	}
};
#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS  speciality, experience
class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int EXPERIANCE_WIDTH = 5;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//        CONSTRUCTORS
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//        Methods:
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << experience;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(EXPERIANCE_WIDTH);
		ofs << experience;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs);
		char sz_speciality[SPECIALITY_WIDTH + 1]{};//sz_ - String Zero(������ ��������������� ����)
		ifs.read(sz_speciality,SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 2; sz_speciality[i] == ' '; i--)sz_speciality[i] = 0;
		while (sz_speciality[0] == ' ')for (int i = 0; sz_speciality[i]; i++)sz_speciality[i] = sz_speciality[i + 1];
		speciality = sz_speciality;
		ifs >> experience;
		return ifs;

	}
};
#define GRADUATE_TAKE_PARAMETERS const std::string& subject
#define GRADUATE_GIVE_PARAMETERS subject

class Graduate : public Student
{
	static const int SUBJECT_WIDTH = 15;
private:
	std::string subject; //�������(���)
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	//  constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) :
		Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		this->subject = subject;
		cout << "GConstructor:\t" << this << endl;
	}
	Graduate(const Student& student,const std::string& subject) :Student(student)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//   Methods:

	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os)  << " " << subject;
	}

	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs.width(SUBJECT_WIDTH);
		ofs << subject;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Student::read(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

void Print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		//group[i]->print();
		if (group[i])
		{
			cout << *group[i] << endl;
			cout << delimiter << endl;
		}
	}
	cout << "���-�� ������� � ������: " << n << endl;
}
void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
		
	}
	fout.close();
	std::string cmd = "notepad "+filename;
	system(cmd.c_str());//������� system(const char*)��������� ����� ��������� ������� ����.�������
	//����� c_str() ���������� C-string (NULL Terminated Line), ��������� � ������ ������ std::string
}
Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (type =="Human:")human = new Human("", "", 0);
	if (type =="Teacher:")human = new Teacher("", "", 0, "",0);
	if (type =="Student:")human = new Student("", "", 0, "","",0,0);
	if (type =="Graduate:")human = new Graduate("", "", 0, "","",0,0,"");
	return human;
}
bool CheckType(const std::string& buffer)
	{
		return buffer.find("Human:") == std::string::npos &&
			   buffer.find("Student:") == std::string::npos &&
			   buffer.find("Teacher:") == std::string::npos &&
			   buffer.find("Graduate:") == std::string::npos;
	}
Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1)��������� ������ �����(���-�� ������� � �����):
		n = 0;
		while (!fin.eof())
		{
			std::string buffer;
			//fin.getline(); //�� ���������� ��� �������� ������ std::string
			std::getline(fin, buffer);
			//move DST, SRC;
			//strcat(DTS,SRC);
			if (CheckType(buffer))continue;
			n++;
		}
		cout << "����������� ������� � �����: " << n << endl;

		//2)�������� ������ ��� ������:
		group = new Human* [n] {};

		//3) ������������ � ������ ����� ��� ���� ����� ��������� ���������� ����� �����:
		cout << "������� ������� �� ������: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << "������� ������� �� ������: " << fin.tellg() << endl;
		//4) ������ ����:
		for (int i = 0; i < n; i++)
		{
			std::string type;
			fin >> type;
			if (CheckType(type))continue;
			group[i] = HumanFactory(type);
			if (group[i])
				fin >> *group[i];
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	return group;
}
void Clear(Human* group[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}
//#define INHERITANCE_1
//#define INHERITANCE_2
//#define SAVE_CHECK
#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;

#ifdef INHERITANCE_1
	Human human("Richter", "Jeffrey", 40);
	human.print();
	cout << delimiter << endl;

	Student student("Pinkman", "Jessie", 20, "Chenistry", "ww_220", 95, 90);
	student.print();
	cout << delimiter << endl;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();
	cout << delimiter << endl;

	Graduate graduate("Schrader", "Hank", 40, "Criminalistic", "OBN", 50, 70, "How to catch Heisenberg");
	graduate.print();
	cout << delimiter << endl;
#endif // INHERITANCE_1

#ifdef INHERITANCE_2
	Human human("Vercetty", "Tommy", 30);
	human.print();
	cout << delimiter << endl;
	Student student(human, "Theft", "Vice", 95, 98);
	student.print();
	cout << delimiter << endl;
	Graduate graduate(student, "How to make money");
	graduate.print();
	cout << delimiter << endl;
#endif // INHERITANCE_2

#ifdef SAVE_CHECK

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chenistry", "ww_220", 95, 90),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schrader", "Hank", 40, "Criminalistic", "OBN", 50, 70, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 95, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	int n = 0;
	Human** group = Load("group.txt", n);
	Print(group, n);
	Clear(group, n);
#endif // LOAD_CHECK

}