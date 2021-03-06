#include "stdafx.h"
#include "labyrinth_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	ifstream input;
	ofstream output;
	point startPoint, endPoint;
	labyrinth map;
	if (!CheckArgumentCount(argc) || !OpenFile(input, argv[1]) || !OpenFile(input, argv[2]))
	{
		return 1;
	}
	if (!ReadLabyrint(input, map, startPoint, endPoint))
	{
		cout << "You do not init start or end point" << endl;
		cout << "Init start point like '" << START_CHAR << "'";
		cout << " and ";
		cout << "end point like '" << END_CHAR << "'" << endl;
		return 1;
	}
	if (!FillLabyrinth(map, startPoint, endPoint))
	{
		cout << "Way is not found. Check labyrinth." << endl;
		return 1;
	}
	FillLabyrinthWay(map, endPoint);
	PrintWay(output, map, startPoint, endPoint);
	return 0;
}