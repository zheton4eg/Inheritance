//Files
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello Files" << endl;


	std::ofstream fout;           //1) ������ �����
	fout.open("File.txt", std::ios_base::app);        //2) ��������� �����. ��� �������� ������, �� ��������� � ����� ������ ���� �� ����� ������.
	//std::ios_base::app(append) - ���������� � ����� �����
	fout << "Hello Files" << endl;//4)����� � �����
	fout << "������" << endl;
	fout.close();                 //3)��������� �����. ����������� ���������, ���� �� ������� �� ������� � ��������� ������������

	system("notepad File.txt");
#endif // WRITE_TO_FILE
	//1)�������� � �������� ������ ����� ����������
	std::ifstream fin("File.txt");  
	//2) ��� ������� ����������� ����� ���������, �������� �����, ��� ���
	if (fin.is_open())
	{
		   //3) ������ �� �����: 
		while (!fin.eof()) //���� �� ����� ����� - eof(End of file) ������ �����
		{
			const int SIZE = 1024000;
			char buffer[SIZE]{};
			//fin>>buffer;
			fin.getline(buffer,SIZE);
			cout << buffer << endl;
		}
		//4) ����� ���� ����� ��������� ������ � ��� �������=, ���� �� ��� ������
		fin.close();    
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}