#ifndef PLATE_H
#define PLATE_H

/*
* Summary: ���ݱ��Ӧ��������
*/

#include <string>

class Plate
{
public:
	Plate();
	~Plate();
	
	// todo: ��� Getter �� Setter
private:
	int _id;
	std::string _number;
	long _time;
	std::string _path;
};

#endif // !PLATE_H


