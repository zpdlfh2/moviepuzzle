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
		switch (i) {
		case 0:
			puzzles[i] = Object::create("images/part1.png", scene, arrX[i], arrY[i]);
			break;
		case 1:
			puzzles[i] = Object::create("images/part2.png", scene, arrX[i], arrY[i]);
			break;
		case 2:
			puzzles[i] = Object::create("images/part3.png", scene, arrX[i], arrY[i]);
			break;
		case 3:
			puzzles[i] = Object::create("images/part4.png", scene, arrX[i], arrY[i]);
			break;
		case 4:
			puzzles[i] = Object::create("images/part5.png", scene, arrX[i], arrY[i]);
			break;
		case 5:
			puzzles[i] = Object::create("images/part6.png", scene, arrX[i], arrY[i]);
			break;
		case 6:
			puzzles[i] = Object::create("images/part7.png", scene, arrX[i], arrY[i]);
			break;
		case 7:
			puzzles[i] = Object::create("images/part8.png", scene, arrX[i], arrY[i]);
			break;
		}
	}

	int mix[10][8] = {
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
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




	//puzzle 1

	puzzles[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[0] - 10 < part1X) && (arrY[0] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] - 10 < part1X) && (arrY[0] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] - 10 < part1X) && (arrY[0] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] == part1X + distance) && (arrY[0] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] + 10 > part1X + distance * 2) && (arrY[0] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] + 10 > part1X + distance * 2) && (arrY[0] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] + 10 > part1X + distance * 2) && (arrY[0] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		else if ((arrX[0] == part1X + distance) && (arrY[0] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[0] += distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[0] -= distance;
					puzzles[0]->locate(scene, arrX[0], arrY[0]);
				}
			}
		}
		return true;
		});


	//puzzle 2

	puzzles[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[1] - 10 < part1X) && (arrY[1] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] - 10 < part1X) && (arrY[1] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] - 10 < part1X) && (arrY[1] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] == part1X + distance) && (arrY[1] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] + 10 > part1X + distance * 2) && (arrY[1] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] + 10 > part1X + distance * 2) && (arrY[1] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] + 10 > part1X + distance * 2) && (arrY[1] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		else if ((arrX[1] == part1X + distance) && (arrY[1] - 11 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[1] += distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[1] -= distance;
					puzzles[1]->locate(scene, arrX[1], arrY[1]);
				}
			}
		}
		return true;
		});


	//puzzle 3

	puzzles[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[2] - 10 < part1X) && (arrY[2] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] - 10 < part1X) && (arrY[2] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] - 10 < part1X) && (arrY[2] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] == part1X + distance) && (arrY[2] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] + 10 > part1X + distance * 2) && (arrY[2] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] + 10 > part1X + distance * 2) && (arrY[2] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] + 10 > part1X + distance * 2) && (arrY[2] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		else if ((arrX[2] == part1X + distance) && (arrY[2] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[2] += distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[2] -= distance;
					puzzles[2]->locate(scene, arrX[2], arrY[2]);
				}
			}
		}
		return true;
		});


	//puzzle 4

	puzzles[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[3] - 10 < part1X) && (arrY[3] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] - 10 < part1X) && (arrY[3] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] - 10 < part1X) && (arrY[3] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] == part1X + distance) && (arrY[3] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] + 10 > part1X + distance * 2) && (arrY[3] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] + 10 > part1X + distance * 2) && (arrY[3] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] + 10 > part1X + distance * 2) && (arrY[3] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		else if ((arrX[3] == part1X + distance) && (arrY[3] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[3] += distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[3] -= distance;
					puzzles[3]->locate(scene, arrX[3], arrY[3]);
				}
			}
		}
		return true;
		});


	//puzzle 5

	puzzles[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[4] - 10 < part1X) && (arrY[4] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] - 10 < part1X) && (arrY[4] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] - 10 < part1X) && (arrY[4] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] == part1X + distance) && (arrY[4] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] + 10 > part1X + distance * 2) && (arrY[4] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] + 10 > part1X + distance * 2) && (arrY[4] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] + 10 > part1X + distance * 2) && (arrY[4] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		else if ((arrX[4] == part1X + distance) && (arrY[4] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[4] += distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[4] -= distance;
					puzzles[4]->locate(scene, arrX[4], arrY[4]);
				}
			}
		}
		return true;
		});


	//puzzle 6

	puzzles[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[5] - 10 < part1X) && (arrY[5] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] - 10 < part1X) && (arrY[5] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] - 10 < part1X) && (arrY[5] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] == part1X + distance) && (arrY[5] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] + 10 > part1X + distance * 2) && (arrY[5] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] + 10 > part1X + distance * 2) && (arrY[5] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] + 10 > part1X + distance * 2) && (arrY[5] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		else if ((arrX[5] == part1X + distance) && (arrY[5] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[5] += distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[5] -= distance;
					puzzles[5]->locate(scene, arrX[5], arrY[5]);
				}
			}
		}
		return true;
		});


	//puzzle 7

	puzzles[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[6] - 10 < part1X) && (arrY[6] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] - 10 < part1X) && (arrY[6] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] - 10 < part1X) && (arrY[6] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] == part1X + distance) && (arrY[6] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] + 10 > part1X + distance * 2) && (arrY[6] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] + 10 > part1X + distance * 2) && (arrY[6] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] + 10 > part1X + distance * 2) && (arrY[6] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		else if ((arrX[6] == part1X + distance) && (arrY[6] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[6] += distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[6] -= distance;
					puzzles[6]->locate(scene, arrX[6], arrY[6]);
				}
			}
		}
		return true;
		});


	//puzzle 8

	puzzles[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arrX[7] - 10 < part1X) && (arrY[7] - 10 < part1Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] - 10 < part1X) && (arrY[7] == part1Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] - 10 < part1X) && (arrY[7] + 10 > part1Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] == part1X + distance) && (arrY[7] + 10 > part1Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] + 10 > part1X + distance * 2) && (arrY[7] + 10 > part1Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] + 10 > part1X + distance * 2) && (arrY[7] == part1Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] + 10 > part1X + distance * 2) && (arrY[7] - 10 < part1Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		else if ((arrX[7] == part1X + distance) && (arrY[7] - 10 < part1Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y))
						n++;
				}
				if (n == 0) {
					arrY[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance * 2) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[7] += distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X) && (arrY[i] == part1Y - distance))
						n++;
				}
				if (n == 0) {
					arrX[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arrX[i] == part1X + distance) && (arrY[i] == part1Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arrY[7] -= distance;
					puzzles[7]->locate(scene, arrX[7], arrY[7]);
				}
			}
		}
		return true;
		});

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
		switch (i) {
		case 0:
			puzzle2[i] = Object::create("image2/part1.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 1:
			puzzle2[i] = Object::create("image2/part2.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 2:
			puzzle2[i] = Object::create("image2/part3.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 3:
			puzzle2[i] = Object::create("image2/part4.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 4:
			puzzle2[i] = Object::create("image2/part5.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 5:
			puzzle2[i] = Object::create("image2/part6.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 6:
			puzzle2[i] = Object::create("image2/part7.png", scene2, arr2X[i], arr2Y[i]);
			break;
		case 7:
			puzzle2[i] = Object::create("image2/part8.png", scene2, arr2X[i], arr2Y[i]);
			break;
		}
	}
	for (int i = 0; i < 8; i++) {
		puzzle2[i]->setScale(1.25f);
	}

	int mix2[10][8] = {
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
		{2, 3, 6, 1, 8, 9, 4, 7},
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





	//puzzle 1

	puzzle2[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[0] - 10 < part2X) && (arr2Y[0] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] - 10 < part2X) && (arr2Y[0] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] - 10 < part2X) && (arr2Y[0] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] == part2X + distance) && (arr2Y[0] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] + 10 > part2X + distance * 2) && (arr2Y[0] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] + 10 > part2X + distance * 2) && (arr2Y[0] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] + 10 > part2X + distance * 2) && (arr2Y[0] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		else if ((arr2X[0] == part2X + distance) && (arr2Y[0] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[0] += distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[0] -= distance;
					puzzle2[0]->locate(scene2, arr2X[0], arr2Y[0]);
				}
			}
		}
		return true;
		});


	//puzzle 2

	puzzle2[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[1] - 10 < part2X) && (arr2Y[1] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] - 10 < part2X) && (arr2Y[1] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] - 10 < part2X) && (arr2Y[1] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] == part2X + distance) && (arr2Y[1] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] + 10 > part2X + distance * 2) && (arr2Y[1] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] + 10 > part2X + distance * 2) && (arr2Y[1] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] + 10 > part2X + distance * 2) && (arr2Y[1] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		else if ((arr2X[1] == part2X + distance) && (arr2Y[1] - 11 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[1] += distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[1] -= distance;
					puzzle2[1]->locate(scene2, arr2X[1], arr2Y[1]);
				}
			}
		}
		return true;
		});


	//puzzle 3

	puzzle2[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[2] - 10 < part2X) && (arr2Y[2] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] - 10 < part2X) && (arr2Y[2] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] - 10 < part2X) && (arr2Y[2] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] == part2X + distance) && (arr2Y[2] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] + 10 > part2X + distance * 2) && (arr2Y[2] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] + 10 > part2X + distance * 2) && (arr2Y[2] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] + 10 > part2X + distance * 2) && (arr2Y[2] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		else if ((arr2X[2] == part2X + distance) && (arr2Y[2] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[2] += distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[2] -= distance;
					puzzle2[2]->locate(scene2, arr2X[2], arr2Y[2]);
				}
			}
		}
		return true;
		});


	//puzzle 4

	puzzle2[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[3] - 10 < part2X) && (arr2Y[3] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] - 10 < part2X) && (arr2Y[3] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] - 10 < part2X) && (arr2Y[3] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] == part2X + distance) && (arr2Y[3] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] + 10 > part2X + distance * 2) && (arr2Y[3] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] + 10 > part2X + distance * 2) && (arr2Y[3] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] + 10 > part2X + distance * 2) && (arr2Y[3] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		else if ((arr2X[3] == part2X + distance) && (arr2Y[3] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[3] += distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[3] -= distance;
					puzzle2[3]->locate(scene2, arr2X[3], arr2Y[3]);
				}
			}
		}
		return true;
		});


	//puzzle 5

	puzzle2[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[4] - 10 < part2X) && (arr2Y[4] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] - 10 < part2X) && (arr2Y[4] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] - 10 < part2X) && (arr2Y[4] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] == part2X + distance) && (arr2Y[4] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] + 10 > part2X + distance * 2) && (arr2Y[4] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] + 10 > part2X + distance * 2) && (arr2Y[4] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] + 10 > part2X + distance * 2) && (arr2Y[4] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		else if ((arr2X[4] == part2X + distance) && (arr2Y[4] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[4] += distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[4] -= distance;
					puzzle2[4]->locate(scene2, arr2X[4], arr2Y[4]);
				}
			}
		}
		return true;
		});


	//puzzle 6

	puzzle2[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[5] - 10 < part2X) && (arr2Y[5] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] - 10 < part2X) && (arr2Y[5] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] - 10 < part2X) && (arr2Y[5] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] == part2X + distance) && (arr2Y[5] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] + 10 > part2X + distance * 2) && (arr2Y[5] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] + 10 > part2X + distance * 2) && (arr2Y[5] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] + 10 > part2X + distance * 2) && (arr2Y[5] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		else if ((arr2X[5] == part2X + distance) && (arr2Y[5] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[5] += distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[5] -= distance;
					puzzle2[5]->locate(scene2, arr2X[5], arr2Y[5]);
				}
			}
		}
		return true;
		});


	//puzzle 7

	puzzle2[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[6] - 10 < part2X) && (arr2Y[6] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] - 10 < part2X) && (arr2Y[6] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] - 10 < part2X) && (arr2Y[6] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] == part2X + distance) && (arr2Y[6] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] + 10 > part2X + distance * 2) && (arr2Y[6] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] + 10 > part2X + distance * 2) && (arr2Y[6] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] + 10 > part2X + distance * 2) && (arr2Y[6] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		else if ((arr2X[6] == part2X + distance) && (arr2Y[6] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[6] += distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[6] -= distance;
					puzzle2[6]->locate(scene2, arr2X[6], arr2Y[6]);
				}
			}
		}
		return true;
		});


	//puzzle 8

	puzzle2[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if ((arr2X[7] - 10 < part2X) && (arr2Y[7] - 10 < part2Y - distance * 2)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] - 10 < part2X) && (arr2Y[7] == part2Y - distance)) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] - 10 < part2X) && (arr2Y[7] + 10 > part2Y)) {
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] == part2X + distance) && (arr2Y[7] + 10 > part2Y)) {          // 2번
			if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] + 10 > part2X + distance * 2) && (arr2Y[7] + 10 > part2Y)) {         // 3번
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] + 10 > part2X + distance * 2) && (arr2Y[7] == part2Y - distance)) {    // 6번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] + 10 > part2X + distance * 2) && (arr2Y[7] - 10 < part2Y - distance * 2)) {     // 9번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		else if ((arr2X[7] == part2X + distance) && (arr2Y[7] - 10 < part2Y - distance * 2)) {          // 8번
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}

		else {                                                                    // 5번 가운데
			if (action == MouseAction::MOUSE_DRAG_UP) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y))
						n++;
				}
				if (n == 0) {
					arr2Y[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance * 2) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[7] += distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_LEFT) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X) && (arr2Y[i] == part2Y - distance))
						n++;
				}
				if (n == 0) {
					arr2X[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
			else if (action == MouseAction::MOUSE_DRAG_DOWN) {
				int n = 0;
				for (int i = 0; i < 8; i++) {
					if ((arr2X[i] == part2X + distance) && (arr2Y[i] == part2Y - distance * 2))
						n++;
				}
				if (n == 0) {
					arr2Y[7] -= distance;
					puzzle2[7]->locate(scene2, arr2X[7], arr2Y[7]);
				}
			}
		}
		return true;
		});

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
				showMessage("미션 성공!! 당신은 <브론즈> 입니다!");
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