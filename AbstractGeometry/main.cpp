
#include <Windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace Geometry
{
	enum Color
	{
		CONSOLE_RED = 0xCC,//старшая 'C' - цвет фона, младшая C
		CONSOLE_GRENN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};
	class Shape
	{
	protected:
		Color color;
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};
	class Square :public Shape
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
			cout << "Длинна стороны: " << get_side() << endl;
			Shape::info();
		}
	};
	class Rectangle :public Shape
	{
		double width;//Ширина
		double height;//Высота
	public:
		Rectangle(double width, double height, Color color) : Shape(color)
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
			//1)Получаем окно консоли:
			HWND hwnd = FindWindow(NULL,L"Inheritance - Microsoft Visual Studio");//Функция GetConsoleWindow() получает окно консоли
			//2)Для того чтобы рисовать нужен контекст устройства(Device Contex),
			//Который есть укаждого окна. Контекст уст-ва можно получить при помощи функции GetDC();
			HDC hdc = GetDC(hwnd);//получаем контекст окна консоли
			//Контекст уст-ва - это то, на чём мы будем рисовать.

			//3) Теперь нам нужно то, чем мы будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color); //hPen - рисует контур фигуры;
			//SP_SOLID - сплошная линия
			// 5       - толщина линий 5 пикселов
			HBRUSH hBrush = CreateSolidBrush(color);    //hBrush   - рисует заливку фигуры(SolidBrush - сплошной цвет)

			//4)Выбираем чем и на чём мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//5) Рисум фигуру:
			::Rectangle(hdc, 500, 100, 900, 300); //:: - Global scope(Глобальное пространство имён)

			//6) hdc, hPen и hBrush занимает ресурсы и после того как мы ими воспользовались, ресурсы нужно освободить
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << get_width() << endl;
			cout << "Высота прямоугольника: " << get_height() << endl;
			Shape::info();
		}
	};
}
void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
Geometry:: Square square(5, Geometry::Color::CONSOLE_RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(100,50, Geometry::Color::CONSOLE_BLUE);
	rect.info();
}
