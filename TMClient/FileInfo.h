#ifndef FILEINFO_H
#define FILEINFO_H

/*
* Summary: ���������ļ���Ϣ�Ľṹ�壬�����ͻ��˺ͷ�����֮�䴫�����ݵ�Э��
*/

#include <string>

#define MAX_FILE_NAME 255

typedef struct
{
	/* �ͻ��˷��͵��ļ����ļ��� */
	char filename[MAX_FILE_NAME];

	/* ���ļ��ĳ��� */
	long file_len;
} FileInfo;

/*
* Summary: ���� std::string ��ʾ���ļ������Ƶ� FileInfo ������
* Parameters:
*		info: �ļ���Ϣ����
*		filename: �ļ���
*/
extern void inline set_info_name(FileInfo &info, std::string filename);

/*
* Summary: ��ȡ�ļ����ȣ����浽 FileInfo ������
* Parameters:
*		info: �ļ���Ϣ����
*		path: �ļ�����·��
*/
extern void set_info_len(FileInfo &info, std::string path, std::string filename);

#endif // FILEINFO_H