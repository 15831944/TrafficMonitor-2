#include <iostream>
#include <fstream>
#include "Uploader.h"
#include "FileInfo.h"
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

using namespace std;


Uploader::Uploader()
	:_sock(0), _buf_size(1024)
{
}


Uploader::~Uploader()
{
	if (_sock)
	{
		disconnect();
	}
}

int Uploader::initialize()
{
	return WSAStartup(MAKEWORD(2, 2), &_wsa_data);
}

int Uploader::terminate()
{
	return WSACleanup();
}

static wstring Ansi2WChar(const char* pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, pszSrc, nLen, 0, 0);
	if (nSize <= 0) return NULL;

	wchar_t *pwszDst = new wchar_t[nSize + 1];
	if (NULL == pwszDst) return NULL;

	MultiByteToWideChar(CP_ACP, 0, pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;

	if (pwszDst[0] == 0xFEFF)                    // skip Oxfeff  
		for (int i = 0; i < nSize; i++)
			pwszDst[i] = pwszDst[i + 1];

	wstring wcharString(pwszDst);
	delete pwszDst;

	return wcharString;
}

int Uploader::connect_server(const std::string &ip, int port)
{
	//�����׽���
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (_sock == INVALID_SOCKET)
		return 1;

	//����������ض���IP�Ͷ˿ڣ���������
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //ÿ���ֽڶ���0���
	serv_addr.sin_family = AF_INET;  //ʹ��IPv4��ַ
	serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());  //�����IP��ַ

	serv_addr.sin_port = htons(port);  //�˿�
	connect(_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
}

void Uploader::disconnect()
{
	closesocket(_sock);
}

int Uploader::upload(const std::string &path, const std::string &filename)
{
	if (_sock <= 0)
		return 1;

	FileInfo info;
	set_info_name(info, filename);
	set_info_len(info, path, filename);

	// ����FileInfo
	send(_sock, (char *)&info, sizeof(FileInfo), 0);

	// �����ļ�����
	char *buf = new char[_buf_size];
	// �����ļ�����
	ifstream file(filename, ios::in | ios::binary);
	if (!file.good())
		return 1;
	streamsize sz;
	while ((sz = file.readsome(buf, _buf_size)) > 0)
	{
		send(_sock, buf, (size_t)sz, 0);
	}
	file.close();
	delete[] buf;
	return 0;

}

int Uploader::batch_upload(const std::string &path,
	const std::vector<std::string> &filenames)
{
	int ret = 0;
	auto it = filenames.begin();
	for (; it != filenames.end(); ++it) {
		if (upload(path, *it) == 0)
		{
			++ret;
		}
	}
	return ret;
}