#include "stdafx.h"
#include "ImageProcessor.h"
#include "FileManager.h"

using namespace std;

ImageProcessor::ImageProcessor()
	:_timeval(5), _running(false)
{
}


ImageProcessor::~ImageProcessor()
{
}


void ImageProcessor::set_running(bool running)
{
	_running_mutex.lock();
	_running = running;
	_running_mutex.unlock();
}

void ImageProcessor::start()
{
	set_running(true);
	_thread = new thread([this]() {
		bool running;
		string s;
		string res;
		while (1)
		{
			// ����Ƿ���������
			_running_mutex.lock();
			running = _running;
			_running_mutex.unlock();

			if (!running)
				break;

			// �������Ƿ�Ϊ��
			_queue_mutex.lock();
			if (!_msgqueue.empty())
			{
				s = _msgqueue.front();
				_msgqueue.pop();
				_queue_mutex.unlock();
			} 
			else
			{
				// ����Ϊ�գ�˯��5s
				_queue_mutex.unlock();
				std::this_thread::sleep_for(5s);
				continue;
			}
			
			if (s.empty())
				continue;

			res = _recognizer.recognize(s);
			if (res.length() > 0)
			{
				//�ƶ��� recognized
				move_to_path(res.c_str(), get_recognized_path());

				// todo: ��������

			}
			else
			{
				// �ƶ��� unrecognized
				move_to_path(res.c_str(), get_unrecognized_path());
			}
		}
	});
}

void ImageProcessor::stop()
{
	set_running(false);

	if (_thread != nullptr)
	{
		_thread->join();
		delete _thread;
	}
}

void ImageProcessor::put(string file)
{
	_queue_mutex.lock();
	_msgqueue.push(file);
	_queue_mutex.unlock();
}