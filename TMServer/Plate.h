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

	Plate(int, std::string, long, std::string);
	
	int get_id();
	void set_id(int);

	std::string get_number();
	void set_number(std::string);

	long get_time();
	void set_time(long);

	std::string get_path();
	void set_path(std::string);

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


