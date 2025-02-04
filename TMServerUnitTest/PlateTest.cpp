#include "stdafx.h"
#include "CppUnitTest.h"
#include "PlateDao.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMServerUnitTest
{
	TEST_CLASS(TestPlate)
	{
	public:
		TEST_METHOD(test_plate)
		{
			Plate p1("123", 1498824286, "D:\\vs-c");
			Assert::AreEqual(0, p1.get_id());
			std::string str1("空A 0QV05");
			p1.set_number(str1);
			Assert::AreEqual(str1, p1.get_number());
		}

		TEST_METHOD(test_PlateDao)
		{
			PlateDao dao("PlateForDao.db");
		}

		TEST_METHOD(test_save)
		{
			remove("PlateForDao.db");
			Plate p1("123", 1498824286, "D:\\vs-c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			Assert::AreEqual(dao.save(p1), 0);
			dao.release();
		}

		TEST_METHOD(test_remove)
		{
			remove("PlateForDao.db");
			Plate p1("123", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p2);
			dao.save(p3);
			Plate *p4 = dao.findById(2);
			Assert::AreEqual(dao.remove(*p4), 0);
			dao.release();
		}

		TEST_METHOD(test_update)
		{
			remove("PlateForDao.db");
			Plate p1("123", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p3);
			Plate *p4 = dao.findById(2);
			p4->set_time(123);
			dao.update(*p4);
			Plate *p5 = dao.findById(2);
			Assert::AreEqual(p5->get_time(), (long)123);
			dao.release();
		}

		TEST_METHOD(test_findById)
		{
			remove("PlateForDao.db");
			Plate p1("123", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p3);
			Plate *p4 = dao.findById(2);
			Assert::AreEqual(p4->get_id(), 2);
			std::string str("空A HZ553");
			Assert::AreEqual(p4->get_number(), str);
			dao.release();
		}

		TEST_METHOD(test_findByNumber)
		{
			remove("PlateForDao.db");
			Plate p1("空A HZ553", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p3);
			std::vector<Plate *> v = dao.findByNumber("空A HZ553");
			Assert::AreEqual((int)v.size(), 2);
			Plate *p4 = v.back();
			Assert::AreEqual(p4->get_id(), 2);
			dao.release();
		}
		
		TEST_METHOD(test_findByTime)
		{
			remove("PlateForDao.db");
			Plate p1("空A HZ553", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p3);
			std::vector<Plate *> v = dao.findByTime("2017-07-01");
			Assert::AreEqual((int)v.size(), 2);
			Plate *p4 = v.front();
			std::string got = p4->get_path();
			const char * path = got.c_str();
			Assert::AreEqual(path, "E:\\c");
			Assert::AreEqual(p4->get_time(), (long)1498872847);
			std::vector<Plate *> v2 = dao.findByTime("2017-07-06");
			Assert::AreEqual((int)v2.size(), 0);
			dao.release();
		}

		TEST_METHOD(test_findAll)
		{
			remove("PlateForDao.db");
			Plate p1("空A HZ553", 1498824286, "D:\\vs-c");
			Plate p2("空A HZ553", 1498872847, "E:\\c");
			Plate p3("空B HZ553", 1498874814, "E:\\c");
			PlateDao dao("PlateForDao.db");
			dao.init();
			dao.save(p1);
			dao.save(p2);
			dao.save(p3);
			std::vector<Plate *> v = dao.findAll();
			Assert::AreEqual((int)v.size(), 3);
			Plate *p4 = v.front();
			std::string got = p4->get_path();
			const char * path = got.c_str();
			Assert::AreEqual(path, "D:\\vs-c");
			dao.release();

			remove("PlateForDao.db");
			PlateDao dao2("PlateForDao.db");
			dao2.init();
			std::vector<Plate *> v1 = dao2.findAll();
			Assert::AreEqual((int)v1.size(), 0);
			dao.release();
		}
	};
}