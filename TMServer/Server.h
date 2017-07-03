#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <mutex>
#include <vector>

/*******************************************************************************
* Author: WqyJh
* Date: 2017/06/29
* Summary: һ���򵥵�socket�����������Խ��ܴӿͻ��˴������ļ���
*			�ͻ��˷����ļ�����֮ǰ�����뷢��һ�� FileInfo ʵ����
*			��ʵ���������ļ������ļ����ȣ�һ��������԰�˳���Ͷ���ļ�
*			ע�⣺�����û��Ĭ�Ϲ��캯�����ڹ����ʱ����봫���ַ�Ͷ˿�
*******************************************************************************/

class Server
{
public:

	~Server();

	/*
	* Summary: ����һ��������ʵ��
	*		ip: �������󶨵� ip ��ַ��һ����˵�� "127.0.0.1"
	*		port: �����Ķ˿ں�
	*/
	Server(std::string ip, int port);

	/*
	* Summary: ��ʼ����������ʹ�÷�����֮ǰ�����ʼ����
	*			�����Ӧ�ó����ʼ����ʱ������������
	* Return: 0 ��ʾ��ʼ���ɹ�������������ʹ�ã�������ʹ�÷�����
	*/
	int init();

	/*
	* Summary: ��ʼ���񣬷�������������һ�����߳������������ǰ�߳�
	* Return: 0 ��ʾ��������ɹ���1 ��ʾʧ�ܣ�ԭ��������Ѿ���һ������������
	*/
	int serve();

	/*
	* Summary: ֹͣ����
	*/
	void stop();

	/*
	* Summary: �жϷ������Ƿ���������
	* Return: true ��ʾ��������������
	*/
	bool is_running();

private:

	Server() = delete;

	Server(const Server &) = delete;

	Server &operator=(const Server &) = delete;

	WSADATA _wsa_data;

	SOCKET _sock;

	std::string _ip;

	int _port;

	int _buf_size;

	volatile bool _running;

	std::mutex _running_mutex;

	std::thread *_serv_thread;

	void set_running(bool running);

	int create_bind_listen();

	void loop();

	int accept_file(int clnt_sock);

	int send_message(SOCKET clnt_sock, std::string msg);

};

#endif // SERVER_H

