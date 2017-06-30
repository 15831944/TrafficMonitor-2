#ifndef PLATE_DAO_H
#define PLATE_DAO_H

#include "Plate.h"
#include <vector>

class PlateDao
{
public:
	PlateDao();
	~PlateDao();

	/*
	* Summary: ��һ��Plateʵ�����浽���ݿ���
	* Parameters:
	*		plate: һ��Plateʵ��
	* Return: 
	*		0��ʾ�ɹ�����0��ʾʧ��
	*/
	int save(const Plate &plate);

	/*
	* Summary: �����ݿ����Ƴ�һ��Plateʵ����Ӧ��������
	* Parameters:
	*		plate: һ��Plateʵ��
	* Return:
	*		0��ʾ�ɹ�����0��ʾʧ��
	*/
	int remove(const Plate &plate);

	int update(const Plate &plate);

	Plate &findById(int id);

	std::vector<Plate *> &findByNumber(std::string number);

	std::vector<Plate *> findByTime(std::string time);
};

#endif // !PLATE_DAO_H



