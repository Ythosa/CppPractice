#include "stdafx.h"
#include "../labyrinth/labyrinth_utils.h"

using namespace std;

bool CompareLabyrinth(const labyrinth & map1, const labyrinth & map2)
{
	for (size_t i = 0; i < map1.size(); ++i)
	{
		for (size_t j = 0; j < map1[i].size(); ++j)
		{
			if (map1[i][j] != map2[i][j])
			{
				return false;
			}
		}
	}
	return (map1.size() == map2.size());
}

void PrintLabyrinth(const labyrinth & map)
{
	for (const auto row : map)
	{
		for (const auto element : row)
		{
			std::cout << element;
		}
		cout << endl;
	}
}

BOOST_AUTO_TEST_SUITE(ReadLabyrintTest)

BOOST_AUTO_TEST_CASE(CorrectFileTest)
{
	ifstream input("map.txt");
	labyrinth map;
	point startPoint, endPoint;
	labyrinth correctMap = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1,  0,  0, -1 },
		{ -1,  0, -1,  0,  0, -1 },
		{ -1,  0,  0,  0,  0, -1 },
		{ -1, -1, -1, -1, -1, -1 }
	};
	BOOST_CHECK(ReadLabyrint(input, map, startPoint, endPoint));
	BOOST_CHECK(CompareLabyrinth(map, correctMap));
	BOOST_CHECK(startPoint.x == 1 && startPoint.y == 1);
	BOOST_CHECK(endPoint.x == 3 && endPoint.y == 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FillLabyrinthtTest)

BOOST_AUTO_TEST_CASE(CorrectLabyrinthTest)
{
	point startPoint, endPoint;
	labyrinth map = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1,  0,  0, -1 },
		{ -1,  0, -1,  0,  0, -1 },
		{ -1,  0,  0,  0,  0, -1 },
		{ -1, -1, -1, -1, -1, -1 }
	};
	startPoint.x = 1;
	startPoint.y = 1;
	startPoint.level = 0;
	endPoint.x = 3;
	endPoint.y = 1;
	labyrinth correctMap = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1,  6,  7, -1 },
		{ -1,  1, -1,  5,  6, -1 },
		{ -1,  2,  3,  4,  5, -1 },
		{ -1, -1, -1, -1, -1, -1 },

	};
	FillLabyrinth(map, startPoint, endPoint);
	BOOST_CHECK(CompareLabyrinth(map, correctMap));
}

BOOST_AUTO_TEST_CASE(IncorrectLabyrinth)
{
	point startPoint, endPoint;
	labyrinth map = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1,  0,  0, -1 },
		{ -1,  0, -1,  0,  0, -1 },
		{ -1,  0, -1,  0,  0, -1 },
		{ -1, -1, -1, -1, -1, -1 }
	};
	startPoint.x = 1;
	startPoint.y = 1;
	endPoint.x = 3;
	endPoint.y = 1;
	BOOST_CHECK(!FillLabyrinth(map, startPoint, endPoint));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(FillLabyrinthWayTest)

BOOST_AUTO_TEST_CASE(CorrectLabyrinth)
{
	point startPoint, endPoint;
	labyrinth map = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1,  6,  0, -1 },
		{ -1,  1, -1,  5,  6, -1 },
		{ -1,  2,  3,  4,  5, -1 },
		{ -1, -1, -1, -1, -1, -1 }
	};
	startPoint.x = 1;
	startPoint.y = 1;
	endPoint.x = 3;
	endPoint.y = 1;
	labyrinth correctMap = {
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -3, -1, -2,  0, -1 },
		{ -1, -2, -1, -2,  6, -1 },
		{ -1, -2, -2, -2,  5, -1 },
		{ -1, -1, -1, -1, -1, -1 },

	};
	FillLabyrinthWay(map, endPoint);
	BOOST_CHECK(CompareLabyrinth(map, correctMap));
}

BOOST_AUTO_TEST_SUITE_END()