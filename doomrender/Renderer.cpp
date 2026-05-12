#include "Renderer.h"

#define DRAW_DISTANCE 15.0f
#define RAYCAST_STEP 0.01f
#define FOV 90.0f
#define THREAD_COUNT 1

Renderer::Renderer(int w, int h, CharMap* mapC, std::vector<Entity*> * enList)
	: screenWidth(w < 1 ? 1 : w),
	screenHeight(h < 1 ? 1 : h),
	map(mapC),
	entityList(enList)

{
	renderBuffer.resize(screenWidth * screenHeight);
	renderBuffer.assign(screenWidth * screenHeight, ' ');
	zBuffer.resize(screenWidth);
	zBuffer.assign(screenWidth * screenHeight, 100);
}

void Renderer::Render() {
	//Clear buffers
	renderBuffer.assign(screenWidth * screenHeight, ' ');

	//Tracing the z distance of walls from map
	for (int i = 0; i < screenWidth; i++) {
		zBuffer.at(i) = TraceMap(xLoc, yLoc, (rotation - i * FOV / (screenWidth - 1) + FOV / 2) * M_PI / 180.0f);
		if (zBuffer.at(i) < DRAW_DISTANCE) {
		zBuffer.at(i) = zBuffer.at(i) * std::cosf((i * FOV / (screenWidth - 1) - FOV / 2) * M_PI / 180.0f);
		}
	}
	//Filling the renderBuffer with walls (this function was created for multithreading)
	FillColumns(0, screenWidth - 1);

	//Sorting entity array, so there is no need in creating z-buffer for them
	std::sort(entityList->begin(), entityList->end(), [this](Entity* a, Entity* b) {
		float dxA = a->getX() - this->xLoc;
		float dyA = a->getY() - this->yLoc;
		float dsA = dxA * dxA + dyA * dyA;

		float dxB = b->getX() - this->xLoc;
		float dyB = b->getY() - this->yLoc;
		float dsB = dxB * dxB + dyB * dyB;

		return dsA > dsB;
		});

	//Drawing entities
	for (Entity * e : *entityList) {
		float dx = e->getX() - xLoc;
		float dy = e->getY() - yLoc;
		float d = std::sqrt(dx * dx + dy * dy);
		if (d > 0) {
			float angle = std::atan2f(dy, dx);
			float screenAngle = angle - rotation * M_PI / 180;
			screenAngle = std::atan2f(std::sinf(screenAngle), std::cosf(screenAngle));
			if (std::abs(screenAngle) > FOV * M_PI / 360) {
				continue;
			}
			d = d * std::cos(screenAngle);
			int screenX = screenWidth / 2 - screenAngle * screenWidth / (FOV * M_PI / 180);
			int spriteWidth = d > 0 ? 20 / d : 0;

			int filler = -1;
			for (int i = screenX - spriteWidth; i <= screenX + spriteWidth; i++) {
				
				if (i < 0 || i >= screenWidth) {
					continue;
				}
				if (zBuffer.at(i) > d) {
					char ch;
					if (e->getFill() == 'j') {
						std::vector<char> text = { 'j', 'o', 'b', ' ', 'a', 'p', 'p', 'l', 'i', 'c', 'a', 't', 'i', 'o', 'n',};

						int progress = (i - screenX + spriteWidth) * (text.size()-1) / (2 * spriteWidth);

						if (progress > filler) {
							filler = progress;
							ch = text.at(progress >= 0 && progress < text.size() ? progress % text.size() : 0);
						}
						else
						{
							ch = ' ';
						}
						
					}
					else {
						ch = e->getFill();
					}
					FillColumn(i, screenHeight / 2 - 20 / d, screenHeight / 2 + screenHeight / 3 / d, ':');
					int labelHeight = static_cast<int>(screenHeight / 2 - 4 / d) * screenWidth + i;
					if (labelHeight < 0 || labelHeight >= renderBuffer.size()) {
						continue;
					}
					renderBuffer.at(labelHeight) = ch;
				}
			}
		}
	}
}

//Outputting renderBuffer to console
void Renderer::Draw() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacterA(
		hConsole,
		renderBuffer.data(),
		screenWidth*screenHeight,
		{0,0},
		&dwBytesWritten);

}

//Tracing the distance to the wall in the given direction
float Renderer::TraceMap(float startX, float startY, float rot) {
	float xComp = std::cosf(rot) * RAYCAST_STEP;
	float yComp = std::sinf(rot) * RAYCAST_STEP;
	float z{ 0 };

	float x{ startX };
	float y{ startY };

	while (z <= DRAW_DISTANCE) {
		if (map->getPoint(static_cast<int>(x), static_cast<int>(y)) != ' ') {
			return z;
		}
		x += xComp;
		y += yComp;
		z += RAYCAST_STEP;
	}
	return DRAW_DISTANCE;
}

//Filling the renderBuffer with walls (this function was created for multithreading)
void Renderer::FillColumns(int start, int end) {
	
	for (int i = start; i < end; i++) {
		int ceiling = screenHeight / 2 - screenHeight / 2 / zBuffer.at(i);
		int floor = screenHeight / 2 + screenHeight / 3 / zBuffer.at(i);

		char shade;


		if (zBuffer.at(i) < 0.25f) { shade = '@'; }
		else if (zBuffer.at(i) < 0.5f) { shade = '#'; }
		else if (zBuffer.at(i) < 0.75f) { shade = '%'; }
		else if (zBuffer.at(i) < 1.0f) { shade = '*'; }
		else if (zBuffer.at(i) < 1.5f) { shade = '+'; }
		else if (zBuffer.at(i) < 2.0f) { shade = '='; }
		else if (zBuffer.at(i) < 3.0f) { shade = '-'; }
		else if (zBuffer.at(i) < 4.5f) { shade = ':'; }
		else if (zBuffer.at(i) < DRAW_DISTANCE-1) { shade = '.'; }
		else { shade = ' '; }

		FillColumn(i, ceiling, floor, shade);
	}
}

//Fill one column of the renderBuffer
void Renderer::FillColumn(int x, int ceiling, int floor, char ch) {
	if (x < 0 || x >= screenWidth ) {
		return;
	}
		for (int j = 0; j < screenHeight; j++) {
			if (j > ceiling && j < floor) {
				renderBuffer.at(j * screenWidth + x) = ch;
			}
		}
}

//Function to resize console buffer for correct visualization
void Renderer::ResizeWindow() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT rect = {0, 0, 1, 1};
	SetConsoleWindowInfo(hConsole, TRUE, &rect);

	COORD coord = { screenWidth, screenHeight + 10 };
	SetConsoleScreenBufferSize(hConsole, coord);

	rect.Right = screenWidth - 1;
	rect.Bottom = screenHeight - 1 + 10;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}