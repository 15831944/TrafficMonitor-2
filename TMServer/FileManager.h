#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

/*
* Summary: ����һ��������·������·����ʾ���ļ�������
* Parameters: 
*		full_name: ������·��������Ŀ¼���ļ������������
* Return: ����·�����ļ���
*/
std::string parse_filename(const char *full_name);

/*
* Summary: ��Ŀ¼���ļ���ƴ��һ��������·����
* Parameters: 
*		path: Ŀ¼��
*		filename: �ļ���
*/
std::string get_full_name(const char *path, const char *filename);

/*
* Summary: ����һ������"_xxx"������ַ���
* Parameters:
*		len: �ַ������ȣ���������ͷ��'_'�ַ��ͽ�β��'\0'�ַ�
*/
std::string get_postfix(int len);

/*
* Summary: ��һ���ļ� file �ƶ��� dest ��ʾ��Ŀ¼��
* Parameters:
*		file: �ļ�·������Ӧ������ȷ�ر����ʵ�
*		dest: Ŀ��Ŀ¼
*/
int move_to_path(const char *file, const char *dest);

/*
* Summary: ���ַ��� s �����е� c1 �ַ��滻�� c2
*/
void replace_char(std::string &s, char c1, char c2);

const char *get_raw_path();

const char *get_recognized_path();

const char *get_unrecognized_path();

#endif // !FILE_MANAGER_H








