#include <bangtal.h>
#include <ctime>

using namespace bangtal;
using namespace std;

class Puzzle {
public:
	int px, py;
	Puzzle(int x, int y) : px(x), py(y) {};
};

int main() {
	auto firstpage = Scene::create("MOVIE PUZZLE", "images/firstpage.png");
	auto secondpage = Scene::create("MOVIE PUZZLE", "images/secondpage.png");
	auto thirdpage = Scene::create("MOVIE PUZZLE", "images/thirdpage.png");
	auto fourthpage = Scene::create("MOVIE PUZZLE", "images/fourthpage.png");
	auto scene = Scene::create("STAGE 1", "images/blank.png");
	auto scene2 = Scene::create("STAGE 2", "images/blank.png");
	auto sound = Sound::create("audio/bgm.mp3");
	sound->play(true);

	auto firstPageButton = Object::create("images/next.png", firstpage, 585, 30);
	firstPageButton->setScale(0.1f);
	auto secondPageButton = Object::create("images/next.png", secondpage, 585, 30);
	secondPageButton->setScale(0.1f);
	auto thirdPageButton = Object::create("images/next.png", thirdpage, 585, 30);
	thirdPageButton->setScale(0.1f);
	auto fourthPageButton = Object::create("images/next.png", fourthpage, 585, 30);
	fourthPageButton->setScale(0.1f);

	firstPageButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		secondpage->enter();
		return true;
		});
	secondPageButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		thirdpage->enter();
		return true;
		});
	thirdPageButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		fourthpage->enter();
		return true;
		});
	fourthPageButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene->enter();
		return true;
		});

	auto part1X = 310, part1Y = 470, distance = 226;

	Puzzle first_puzzle_point[8] = {
		{part1X, part1Y},
		{part1X + distance, part1Y},
		{part1X + distance * 2, part1Y},
		{part1X , part1Y - distance},
		{part1X + distance, part1Y - distance},
		{part1X + distance * 2, part1Y - distance},
		{part1X, part1Y - distance * 2},
		{part1X + distance, part1Y - distance * 2},
	};

	ObjectPtr puzzles[8]; // auto 해서 사물 생성 하던거

	int arrX[8];
	int arrY[8];
	for (int i = 0; i < 8; i++) {
		arrX[i] = first_puzzle_point[i].px;
		arrY[i] = first_puzzle_point[i].py;
	}
	for (int i = 0; i < 8; i++) {
		string filename = "images/part" + to_string(i + 1) + ".png";
		puzzles[i] = Object::create(filename, scene, arrX[i], arrY[i]);
	}

	int mix[10][8] = {
		{9, 6, 5, 8, 3, 7, 4, 1},
		{6, 9, 8, 3, 1, 4, 2, 7},
		{6, 1, 4, 8, 7, 9, 3, 2},
		{5, 7, 9, 1, 3, 8, 6, 2},
		{7, 3, 8, 9, 4, 2, 1, 5},
		{4, 7, 9, 2, 6, 8, 5, 3},
		{5, 8, 2, 6, 3, 9, 1, 4},
		{2, 6, 7, 8, 4, 1, 9, 5},
		{2, 7, 1, 9, 6, 3, 5, 4},
		{2, 1, 8, 3, 6, 5, 7, 4},
	};

	auto startButton = Object::create("images/start.png", scene, 50, 450);
	startButton->setScale(0.1f);
	auto checkButton1 = Object::create("images/check.png", scene, 59, 250, false);
	checkButton1->setScale(0.092f);

	clock_t start;

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		int n = rand() % 10;
		for (int i = 0; i < 8; i++) {
			switch (mix[n][i]) {
			case 1:
				arrX[i] = part1X, arrY[i] = part1Y;
				break;
			case 2:
				arrX[i] = part1X + distance, arrY[i] = part1Y;
				break;
			case 3:
				arrX[i] = part1X + distance * 2, arrY[i] = part1Y;
				break;
			case 4:
				arrX[i] = part1X, arrY[i] = part1Y - distance;
				break;
			case 5:
				arrX[i] = part1X + distance, arrY[i] = part1Y - distance;
				break;
			case 6:
				arrX[i] = part1X + distance * 2, arrY[i] = part1Y - distance;
				break;
			case 7:
				arrX[i] = part1X, arrY[i] = part1Y - distance * 2;
				break;
			case 8:
				arrX[i] = part1X + distance, arrY[i] = part1Y - distance * 2;
				break;
			case 9:
				arrX[i] = part1X + distance * 2, arrY[i] = part1Y - distance * 2;
				break;
			}

		}
		for (int i = 0; i < 8; i++) {                  //퀴즈블록 랜덤 위치에 가져다놓음.
			puzzles[i]->locate(scene, arrX[i], arrY[i]);
		}
		checkButton1->show();
		start = clock();
		return true;
		});


	for (int k = 0; k < 8; k++) {
		puzzles[k]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)->bool {
			int j;
			for (j = 0; j < 8; j++) {
				if (puzzles[j] == object)
					break;
			}
			if ((arrX[j] == part1X) && (arrY[j] == part1Y - distance * 2)) {
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						m++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (m == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

			}
			else if ((arrX[j] == part1X) && (arrY[j] == part1Y - distance)) {
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						m++;
					else if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						l++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (m == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (l == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else if ((arrX[j] == part1X) && (arrY[j] == part1Y)) {
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
					else if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						m++;
				}
				if (n == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (m == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else if ((arrX[j] == part1X + distance) && (arrY[j] == part1Y)) {          // 2번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						m++;
					else if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						l++;
				}
				if (n == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (m == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (l == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else if ((arrX[j] == part1X + distance * 2) && (arrY[j] == part1Y)) {         // 3번
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						m++;
				}
				if (n == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

				else if (m == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else if ((arrX[j] == part1X + distance * 2) && (arrY[j] == part1Y - distance)) {    // 6번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
					else if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						m++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						l++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (m == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (l == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}

			}
			else if ((arrX[j] == part1X + distance * 2) && (arrY[j] == part1Y - distance * 2)) {     // 9번
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						m++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (m == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else if ((arrX[j] == part1X + distance) && (arrY[j] == part1Y - distance * 2)) {          // 8번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
					else if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						m++;
					else if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						l++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (m == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (l == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			else  if ((arrX[j] == part1X + distance) && (arrY[j] == part1Y - distance)) {                                       // 5번 가운데
				int n = 0; int m = 0; int l = 0; int o = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
					else if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						m++;
					else if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						l++;
					else if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						o++;
				}
				if (n == 0) {
					arrY[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (m == 0) {
					arrX[j] += distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (l == 0) {
					arrX[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
				else if (o == 0) {
					arrY[j] -= distance;
					puzzles[j]->locate(scene, arrX[j], arrY[j]);
				}
			}
			return true;
			});
	}

	int match = 0;
	int level = 0;
	checkButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		for (int i = 0; i < 8; i++) {
			if ((arrX[i] == first_puzzle_point[i].px) && (arrY[i] == first_puzzle_point[i].py)) {
				match++;
			}
		}
		if (match == 8) {
			int endTime = (float)(clock() - start) / CLOCKS_PER_SEC;
			if (endTime <= 60) {
				showMessage("1분 이내 성공! 다음 단계로 넘어갑니다!");
				level += 4;
			}
			else if (endTime <= 120 && endTime > 60) {
				showMessage("2분 이내 성공! 다음 단계로 넘어갑니다!");
				level += 3;
			}
			else if (endTime <= 180 && endTime > 120) {
				showMessage("3분 이내 성공! 다음 단계로 넘어갑니다!");
				level += 2;
			}
			else if (endTime <= 240 && endTime > 180) {
				showMessage("4분 이내 성공! 다음 단계로 넘어갑니다!");
				level += 1;
			}
			else {
				showMessage("4분 초과 성공! 다음 단계로 넘어갑니다!");
			}
			scene2->enter();
		}

		return true;
		});



	// 장면 2

	auto part2X = 310, part2Y = 470;
	Puzzle second_puzzle_point[8] = {
		{part2X, part2Y},
		{part2X + distance, part2Y},
		{part2X + distance * 2, part2Y},
		{part2X , part2Y - distance},
		{part2X + distance, part2Y - distance},
		{part2X + distance * 2, part2Y - distance},
		{part2X, part2Y - distance * 2},
		{part2X + distance, part2Y - distance * 2},
	};

	ObjectPtr puzzle2[8];

	int arr2X[8];
	int arr2Y[8];
	for (int i = 0; i < 8; i++) {
		arr2X[i] = second_puzzle_point[i].px;
		arr2Y[i] = second_puzzle_point[i].py;
	}

	for (int i = 0; i < 8; i++) {
		string filename2 = "image2/part" + to_string(i + 1) + ".png";
		puzzle2[i] = Object::create(filename2, scene2, arr2X[i], arr2Y[i]);
	}
	for (int i = 0; i < 8; i++) {
		puzzle2[i]->setScale(1.25f);
	}

	int mix2[10][8] = {
		{9, 6, 5, 8, 3, 7, 4, 1},
		{6, 9, 8, 3, 1, 4, 2, 7},
		{6, 1, 4, 8, 7, 9, 3, 2},
		{5, 7, 9, 1, 3, 8, 6, 2},
		{7, 3, 8, 9, 4, 2, 1, 5},
		{4, 7, 9, 2, 6, 8, 5, 3},
		{5, 8, 2, 6, 3, 9, 1, 4},
		{2, 6, 7, 8, 4, 1, 9, 5},
		{2, 7, 1, 9, 6, 3, 5, 4},
		{2, 1, 8, 3, 6, 5, 7, 4},
	};

	auto startButton2 = Object::create("images/start.png", scene2, 50, 450);
	startButton2->setScale(0.1f);
	auto checkButton2 = Object::create("image2/check.png", scene2, 59, 250, false);
	checkButton2->setScale(0.092f);
	auto endButton = Object::create("images/end.png", scene2, 63, 50, false);
	endButton->setScale(1.6f);

	clock_t start2;

	startButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		int n = rand() % 10;
		for (int i = 0; i < 8; i++) {
			switch (mix2[n][i]) {
			case 1:
				arr2X[i] = part2X, arr2Y[i] = part2Y;
				break;
			case 2:
				arr2X[i] = part2X + distance, arr2Y[i] = part2Y;
				break;
			case 3:
				arr2X[i] = part2X + distance * 2, arr2Y[i] = part2Y;
				break;
			case 4:
				arr2X[i] = part2X, arr2Y[i] = part2Y - distance;
				break;
			case 5:
				arr2X[i] = part2X + distance, arr2Y[i] = part2Y - distance;
				break;
			case 6:
				arr2X[i] = part2X + distance * 2, arr2Y[i] = part2Y - distance;
				break;
			case 7:
				arr2X[i] = part2X, arr2Y[i] = part2Y - distance * 2;
				break;
			case 8:
				arr2X[i] = part2X + distance, arr2Y[i] = part2Y - distance * 2;
				break;
			case 9:
				arr2X[i] = part2X + distance * 2, arr2Y[i] = part2Y - distance * 2;
				break;
			}
		}
		for (int i = 0; i < 8; i++) {                  //퀴즈블록 랜덤 위치에 가져다놓음.
			puzzle2[i]->locate(scene2, arr2X[i], arr2Y[i]);
		}
		checkButton2->show();
		start2 = clock();

		return true;
		});


	for (int k = 0; k < 8; k++) {
		puzzle2[k]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)->bool {
			int j;
			for (j = 0; j < 8; j++) {
				if (puzzle2[j] == object)
					break;
			}
			if ((arr2X[j] == part2X) && (arr2Y[j] == part2Y - distance * 2)) {
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						m++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (m == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

			}
			else if ((arr2X[j] == part2X) && (arr2Y[j] == part2Y - distance)) {
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						m++;
					else if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						l++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (m == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (l == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else if ((arr2X[j] == part2X) && (arr2Y[j] == part2Y)) {
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
					else if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						m++;
				}
				if (n == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (m == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else if ((arr2X[j] == part2X + distance) && (arr2Y[j] == part2Y)) {          // 2번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						m++;
					else if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						l++;
				}
				if (n == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (m == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (l == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else if ((arr2X[j] == part2X + distance * 2) && (arr2Y[j] == part2Y)) {         // 3번
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						m++;
				}
				if (n == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

				else if (m == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else if ((arr2X[j] == part2X + distance * 2) && (arr2Y[j] == part2Y - distance)) {    // 6번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
					else if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						m++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						l++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (m == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (l == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}

			}
			else if ((arr2X[j] == part2X + distance * 2) && (arr2Y[j] == part2Y - distance * 2)) {     // 9번
				int n = 0; int m = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						m++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (m == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else if ((arr2X[j] == part2X + distance) && (arr2Y[j] == part2Y - distance * 2)) {          // 8번
				int n = 0; int m = 0; int l = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
					else if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						m++;
					else if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						l++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (m == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (l == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			else  if ((arr2X[j] == part2X + distance) && (arr2Y[j] == part2Y - distance)) {                                       // 5번 가운데
				int n = 0; int m = 0; int l = 0; int o = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
					else if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						m++;
					else if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						l++;
					else if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						o++;
				}
				if (n == 0) {
					arr2Y[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (m == 0) {
					arr2X[j] += distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (l == 0) {
					arr2X[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
				else if (o == 0) {
					arr2Y[j] -= distance;
					puzzle2[j]->locate(scene2, arr2X[j], arr2Y[j]);
				}
			}
			return true;
			});
	}

	int match2 = 0;

	checkButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		for (int i = 0; i < 8; i++) {
			if ((arr2X[i] == second_puzzle_point[i].px) && (arr2Y[i] == second_puzzle_point[i].py)) {
				match2++;
			}
		}
		if (match2 == 8) {
			int endTime = (float)(clock() - start2) / CLOCKS_PER_SEC;
			if (endTime <= 60) {
				level += 4;
			}
			else if (endTime <= 120 && endTime > 60) {
				level += 3;
			}
			else if (endTime <= 180 && endTime > 120) {
				level += 2;
			}
			else if (endTime <= 240 && endTime > 180) {
				level += 1;
			}

			switch (level) {
			case 8:
				showMessage("미션 성공!! 당신의 레벨은 <그랜드마스터> 입니다!");
				break;
			case 7:
				showMessage("미션 성공!! 당신의 레벨은 <마스터> 입니다!");
				break;
			case 6:
				showMessage("미션 성공!! 당신의 레벨은 <다이아> 입니다!");
				break;
			case 5:
				showMessage("미션 성공!! 당신의 레벨은 <플래티넘> 입니다!");
				break;
			case 4:
				showMessage("미션 성공!! 당신의 레벨은 <골드> 입니다!");
				break;
			case 3:
				showMessage("미션 성공!! 당신의 레벨은 <실버> 입니다!");
				break;
			default:
				showMessage("미션 성공!! 당신의 레벨은 <브론즈> 입니다!");
				break;
			}
			endButton->show();
		}

		return true;
		});

	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		sound->stop();
		endGame();
		return true;
		});
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	startGame(firstpage);


	return 0;
}