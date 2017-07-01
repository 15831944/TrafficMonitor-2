#ifndef FILEINFO_H
#define FILEINFO_H

/*
* Summary: ���������ļ���Ϣ�Ľṹ�壬�����ͻ��˺ͷ�����֮�䴫�����ݵ�Э��
*/

#include <string>
#include <sys/stat.h>
#include <cstring>

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
void inline set_info_name(FileInfo &info, std::string filename)
{
	memcpy(info.filename, filename.c_str(), filename.length() + 1);
	// strncpy(info.filename, filename.c_str(), filename.length() + 1);
}

/*
* Summary: ��ȡ�ļ����ȣ����浽 FileInfo ������
* Parameters:
*		info: �ļ���Ϣ����
*		path: �ļ�����·��
*/
void set_info_len(FileInfo &info, std::string path, std::string filename)
{
	struct stat s;
	std::string fn;
	if (path.at(path.length() - 1) != '/')
		path.append("/");

	fn = path + filename;

	if (stat(fn.c_str(), &s) < 0)
		info.file_len = -1;
	info.file_len = s.st_size;
}

#endif // FILEINFO_H