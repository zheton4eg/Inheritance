#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace Geometry
{
	enum Color
	{
		RED         = 0x000000FF, 
		GREEN       = 0x0000FF00,
		BLUE        = 0x00ff0000,
		YELLOW      = 0x0000FFFF,
		CONSOLE_RED = 0xCC,//������� 'C' - ���� ����, ������� C
		CONSOLE_GRENN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS  start_x,  start_y,  line_width, color
	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}

		virtual ~Shape() {}

		//             Encapsulation:
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{ 
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}

		//       Methods
		void set_start_x(unsigned int start_x)
		{
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			this->line_width = line_width;
		}

		//             Methods:

		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
			draw();
		}
	};
	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {};
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ �������: " << get_side() << endl;
			Shape::info();
		}
	};*/
	class Rectangle :public Shape
	{
		double width;//������
		double height;//������
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {};
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const
		{
			return width * height;
		}
		double get_perimeter()const
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//WinGDI - Windows Graphic Device Interface
			//1)�������� ���� �������:
			HWND hwnd = FindWindow(NULL,L"Inheritance - Microsoft Visual Studio");//������� GetConsoleWindow() �������� ���� �������
			//2)��� ���� ����� �������� ����� �������� ����������(Device Contex),
			//������� ���� �������� ����. �������� ���-�� ����� �������� ��� ������ ������� GetDC();
			HDC hdc = GetDC(hwnd);//�������� �������� ���� �������
			//�������� ���-�� - ��� ��, �� ��� �� ����� ��������.

			//3) ������ ��� ����� ��, ��� �� ����� ��������:
			HPEN hPen = CreatePen(PS_SOLID, 5, color); //hPen - ������ ������ ������;
			//SP_SOLID - �������� �����
			// 5       - ������� ����� 5 ��������
			HBRUSH hBrush = CreateSolidBrush(color);    //hBrush   - ������ ������� ������(SolidBrush - �������� ����)

			//4)�������� ��� � �� ��� �� ����� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) ����� ������:
			::Rectangle(hdc, start_x, start_y, start_x+width, start_y+height); //:: - Global scope(���������� ������������ ���)

			//6) hdc, hPen � hBrush �������� ������� � ����� ���� ��� �� ��� ���������������, ������� ����� ����������
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "������ ��������������: " << get_width() << endl;
			cout << "������ ��������������: " << get_height() << endl;
			Shape::info();
		}
	};
	
	//class Triangle :public Shape
	//{
	//private:
	//	double legOne;
	//	double legTwo;
	//	double hypotenuse;
	//public:
	//	Triangle(double legOne, double legTwo, double hypotenuse, Color color) :Shape(color)
	//	{
	//		set_legOne(legOne);
	//		set_legTwo(legTwo);
	//		set_hypotenuse(hypotenuse);
	//	}
	//	~Triangle() {};

	//	void set_legOne(double legOne)
	//	{
	//		this->legOne = legOne;
	//	}
	//	void set_legTwo(double legTwo)
	//	{
	//		this->legTwo = legTwo;
	//	}
	//	void set_hypotenuse(double hypotenuse)
	//	{
	//		this->hypotenuse = hypotenuse;
	//	}
	//	double get_legOne()const
	//	{
	//		return legOne;
	//	}
	//	double get_legTwo()const
	//	{
	//		return legTwo;
	//	}
	//	double get_hypotenuse()const
	//	{
	//		return hypotenuse;
	//	}
	//	double get_area()const
	//	{
	//		return (legOne * legTwo) / 2;
	//	}
	//	double get_perimeter()const
	//	{
	//		return legOne + legTwo + hypotenuse;
	//	}
	//	void draw()const override
	//	{
	//		//WinGDI - Windows Graphic Device Interface
	//		//1)�������� ���� �������:
	//		HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");//������� GetConsoleWindow() �������� ���� �������
	//		//2)��� ���� ����� �������� ����� �������� ����������(Device Contex),
	//		//������� ���� �������� ����. �������� ���-�� ����� �������� ��� ������ ������� GetDC();
	//		HDC hdc = GetDC(hwnd);//�������� �������� ���� �������
	//		//�������� ���-�� - ��� ��, �� ��� �� ����� ��������.

	//		//3) ������ ��� ����� ��, ��� �� ����� ��������:
	//		HPEN hPen = CreatePen(PS_SOLID, 5, color); //hPen - ������ ������ ������;
	//		//SP_SOLID - �������� �����
	//		// 5       - ������� ����� 5 ��������
	//		HBRUSH hBrush = CreateSolidBrush(color);    //hBrush   - ������ ������� ������(SolidBrush - �������� ����)

	//		//4)�������� ��� � �� ��� �� ����� ��������:
	//		SelectObject(hdc, hPen);
	//		SelectObject(hdc, hBrush);
	//		//5) ����� ������:
	//		::Rectangle(hdc, 500, 500, 900, 900); //:: - Global scope(���������� ������������ ���)

	//		//6) hdc, hPen � hBrush �������� ������� � ����� ���� ��� �� ��� ���������������, ������� ����� ����������
	//		DeleteObject(hBrush);
	//		DeleteObject(hPen);

	//		ReleaseDC(hwnd, hdc);
	//	}
	//	void info()const
	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "������ ����� ������������: " << get_legOne() << endl;
	//		cout << "������ ����� ������������: " << get_legTwo() << endl;
	//		cout << "���������� ������������: " << get_hypotenuse() << endl;
	//		Shape::info();
	//	}
	//};
	class Square :public Rectangle
	{
	public:
		Square(double side,SHAPE_TAKE_PARAMETERS):Rectangle(side,side,SHAPE_GIVE_PARAMETERS){}
		~Square() {};
	};
	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
		void set_radius(double radius)
		{
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			//������� �������
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������ �����: " << get_radius() << endl;
			cout << "������� �����: " << get_diameter() << endl;
			Shape:: info();
		}
	};

}
void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
Geometry:: Square square(5, 100,100,5, Geometry::Color::RED);
	/*cout << "����� �������: " << square.get_side() << endl;
	cout << "������� ��������: " << square.get_area() << endl;
	cout << "�������� ��������: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(100,50,200,100,10, Geometry::Color::BLUE);
	rect.info();
	// 
	//Geometry::Triangle trian(50,70,150, Geometry::Color::CONSOLE_RED);
	//trian.info();
	Geometry::Circle disk(9000,500,100,5,Geometry::Color::YELLOW);
	disk.info();

}
