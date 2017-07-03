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

static string get_full_path(const string &path, const string &filename)
{
	string fullpath;
	char c = path.at(path.length() - 1);
	if (c == '\\' || c == '/')
	{
		fullpath = path + filename;
	}
	else
	{
		fullpath = path + '\\' + filename;
	}
	return fullpath;
}

int Uploader::connect_server(const std::string &ip, int port)
{
	//�����׽���
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (_sock == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to create socket\n");
		return 1;
	}
	printf("Succeed to create server\n");

	//����������ض���IP�Ͷ˿ڣ���������
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));  //ÿ���ֽڶ���0���
	serv_addr.sin_family = AF_INET;  //ʹ��IPv4��ַ
	serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());  //�����IP��ַ

	serv_addr.sin_port = htons(port);  //�˿�
	int ret = connect(_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (ret != 0)
	{
		fprintf(stderr, "Failed to connect to server\n");
		ret = 1;
	}
	printf("Connect to server\n");
	return ret;
}

void Uploader::disconnect()
{
	closesocket(_sock);
}

int Uploader::upload(const std::string &path, const std::string &filename)
{

	if (_sock <= 0)
		return 1;

	int ret = 0;
	int length;
	FileInfo info;
	set_info_name(info, filename);
	set_info_len(info, path, filename);

	// ����FileInfo
	length = send(_sock, (char *)&info, sizeof(FileInfo), 0);
	printf("Sending %s\n", filename.c_str());
	if (length == sizeof(FileInfo))
	{
		// �����ļ�����
		char *buf = new char[_buf_size];
		// �����ļ�����
		string file_full_path = get_full_path(path, filename);
		ifstream file(file_full_path, ios::in | ios::binary);
		if (!file.eof())
		{
			
			streamsize sz;
			do
			{
				file.read(buf, _buf_size);
				sz = file.gcount();
				printf("send %d\n", (int)sz);
				send(_sock, buf, (int)sz, 0);
			} while (!file.eof());
			file.close();
		}
		else 
		{
			fprintf(stderr, "Failed to open file %s\n", filename.c_str());
			ret = 1;
		}
		delete[] buf;
	} 
	else
	{
		fprintf(stderr, "Failed to send filename\n");
		ret = 1;
	}
	return ret;
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