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

	/*
	* ���ݿ�����
	*/
	int _id;

	/*
	* ���ƺ���
	*/
	std::string _number;

	/*
	* ����ʱ��
	*/
	long _time;

	/*
	* ͼƬ��ַ
	*/
	std::string _path;
};

#endif // !PLATE_H


