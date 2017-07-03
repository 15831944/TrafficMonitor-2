#include "stdafx.h"
#include "ImageProcessor.h"
#include "FileManager.h"

using namespace std;

ImageProcessor::ImageProcessor()
	:_timeval(5), _running(false), _db_name("database.db")
{
	_dao.set_gszFile(const_cast<char *>(_db_name.c_str()));
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
	_dao.init();

	set_running(true);
	_thread = new thread([this]() {
		bool running;
		string s_file;
		string to_path;
		string plate_number;
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
				s_file = _msgqueue.front();
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
			
			if (s_file.empty())
				continue;
			plate_number = _recognizer.recognize(s_file);
			if (plate_number.length() >= 8)
			{
				to_path = get_recognized_path();
				//�ƶ��� recognized
				move_to_path(s_file.c_str(), to_path.c_str());

				// todo: ��������
				long t = time(NULL);
				string nfn = get_full_name(to_path.c_str(),
					parse_filename(s_file.c_str()).c_str());
				Plate plate(plate_number, t, nfn.c_str());
				_dao.save(plate);
			}
			else
			{
				// �ƶ��� unrecognized
				move_to_path(s_file.c_str(), get_unrecognized_path());
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

	_dao.release();
}

void ImageProcessor::put(string file)
{
	_queue_mutex.lock();
	_msgqueue.push(file);
	_queue_mutex.unlock();
}