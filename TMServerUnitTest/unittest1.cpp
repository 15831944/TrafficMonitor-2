#include "stdafx.h"
#include "CppUnitTest.h"
#include "Plate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMServerUnitTest
{		
	TEST_CLASS(TestPlate)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Plate p(1, "123", 20170630, "D:\\vs-c");
			Assert::AreEqual(1, p.get_id());
			// TODO: �ڴ�������Դ���
		}

	};
}