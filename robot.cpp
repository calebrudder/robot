// Robot Motion
// Caleb Rudder
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct position {
	int x;
	int y;
};
void main() {
	ifstream fin("robot.in");
	if (fin.is_open()) {
		ofstream fout("robot.out");

		int rows;
		int columns;
		int startX;
		int startY;
		int instructionsCount;
		int loopCount;
		char direction;
		bool outOfBounds;

		fin >> rows >> columns >> startX >> startY;

		while (rows > 0 || columns > 0 || startX > 0 || startY > 0) {
			outOfBounds = false;
			vector < vector<pair<char, int>>> robotMap;
			vector <pair<char, int>> pairs;
			pair<char, int> pair;
			position loopStart;
			position position;
			position.x = startX-1;
			position.y = startY-1;
			instructionsCount = 0;
			loopCount = 0;
			//read file and stor into vector of vector of pairs
			for (int row = 0; row < rows; row++) {
				for (int col = 0; col < columns; col++) {
					fin >> direction;
					pair.first = direction;
					pair.second = 0;
					pairs.push_back(pair);
				}
				robotMap.push_back(pairs);
				pairs.clear();
			}
			//loop through the vector to find the path
			while (!outOfBounds) {
				//if the visited marker - .second of the pair - is not increminted. go through the logic
				if (robotMap[position.x][position.y].second == 0) {
					if (robotMap[position.x][position.y].first == 'W') {
						if ((position.y - 1) < 0) {
							outOfBounds = true;
							instructionsCount++;
						}
						else {
							robotMap[position.x][position.y].second++;
							position.y = position.y--;
							instructionsCount++;
						}
					}
					else if (robotMap[position.x][position.y].first == 'E') {
						if ((position.y + 1) >= columns) {
							outOfBounds = true;
							instructionsCount++;
						}
						else {
							robotMap[position.x][position.y].second++;
							position.y = position.y++;
							instructionsCount++;
						}
					}
					else if (robotMap[position.x][position.y].first == 'N') {
						if ((position.x - 1) < 0) {
							outOfBounds = true;
							instructionsCount++;
						}
						else {
							robotMap[position.x][position.y].second++;
							position.x = position.x--;
							instructionsCount++;
						}
					}
					else if (robotMap[position.x][position.y].first == 'S') {
						if ((position.x + 1) >= rows) {
							outOfBounds = true;
							instructionsCount++;
						}
						else {
							robotMap[position.x][position.y].second++;
							position.x = position.x++;
							instructionsCount++;
						}
					}
				}
				//if you have been here before you are in a loop - do this logic
				else {
					loopStart.x = position.x;
					loopStart.y = position.y;
					while (robotMap[position.x][position.y].second == 1) {
						if (robotMap[position.x][position.y].first == 'W') {
								position.y = position.y--;
								robotMap[loopStart.x][loopStart.y].second++;
								loopCount++;
						}
						else if (robotMap[position.x][position.y].first == 'E') {
							position.y = position.y++;
							robotMap[loopStart.x][loopStart.y].second++;
							loopCount++;
						}
						else if (robotMap[position.x][position.y].first == 'N') {
							position.x = position.x--;
							robotMap[loopStart.x][loopStart.y].second++;
							loopCount++;
						}
						else if (robotMap[position.x][position.y].first == 'S') {
							position.x = position.x++;
							robotMap[loopStart.x][loopStart.y].second++;
							loopCount++;
						}
					}
					outOfBounds = true;
				}
			}
			//print results to the file
			if (loopCount == 0) {
				if (instructionsCount == 1) {
					fout << instructionsCount << " instruction before exit" << endl;
				}
				else {
					fout << instructionsCount << " instructions before exit" << endl;
				}
			}
			else {
				if (loopCount == instructionsCount) {
					instructionsCount = 0;
					fout << instructionsCount << " instructions before a loop of "  << loopCount << " instructions" << endl;
				}
				else {
					if (instructionsCount - loopCount  == 1) {
						fout << (instructionsCount - loopCount) << " instruction before a loop of " << loopCount << " instructions" << endl;
					}
					else {
						fout << (instructionsCount - loopCount) << " instructions before a loop of " << loopCount << " instructions" << endl;
					}
				}
			}
			pairs.clear();
			robotMap.clear();
			fin >> rows >> columns >> startX >> startY;
		}
		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}