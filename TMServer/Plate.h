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

	//Plate ��ʼ��ʱ������_id
	Plate(std::string, long, std::string);
	
	int get_id() const;
	void set_id(int);

	std::string get_number() const;
	void set_number(std::string);

	long get_time() const;
	void set_time(long);

	std::string get_path() const;
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
	* ��1970-1-1ʱ��ʼ������ ����ʹ��unixʱ���
	*/
	long _time;

	/*
	* ͼƬ��ַ
	*/
	std::string _path;
};

#endif // !PLATE_H


