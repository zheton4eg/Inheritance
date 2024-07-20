#include <iostream>
#include <fstream>
#include <string> 
using std::cin;
using std::cout;
using std::endl;

class Venicle
{
public:
	virtual void move() = 0;	
};
class GroundVenicle :public Venicle {};
class Bike :public GroundVenicle
{
public:
	void move()override
	{
		cout << "Harley Davidson едет на двух колёсах " << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Venicle venicle;
	//GroundVenicle gv;
	Bike harley_davidson;
	harley_davidson.move();


}