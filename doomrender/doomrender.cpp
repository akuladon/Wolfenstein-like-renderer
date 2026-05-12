// doomrender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <Windows.h>

#include "CharMap.h"
#include "Renderer.h"
#include "Entity.h"
#include "Enemy.h"
#include "Follower.h"


float moveSpeed = 1.0f;
float rotSpeed = 180.0f;


int main()
{
    //creating The map
    CharMap map(10, 10);
    #pragma region "MapFill"

    //bottomwall
    map.setPoint(0, 0, '#');
    map.setPoint(1, 0, '#');
    map.setPoint(2, 0, '#');
    map.setPoint(3, 0, '#');
    map.setPoint(4, 0, '#');
    map.setPoint(5, 0, '#');
    map.setPoint(6, 0, '#');
    map.setPoint(7, 0, '#');
    map.setPoint(8, 0, '#');
    map.setPoint(9, 0, '#');

    map.setPoint(0, 1, '#');
    map.setPoint(0, 2, '#');
    map.setPoint(0, 4, '#');
    map.setPoint(0, 5, '#');
    map.setPoint(0, 6, '#');
    map.setPoint(0, 7, '#');
    map.setPoint(0, 8, '#');
    map.setPoint(0, 9, '#');

    map.setPoint(2, 1, '#');
    map.setPoint(1, 3, '#');
    map.setPoint(2, 3, '#');

    map.setPoint(0, 9, '#');
    map.setPoint(1, 9, '#');
    map.setPoint(2, 9, '#');
    map.setPoint(3, 9, '#');
    map.setPoint(4, 9, '#');
    map.setPoint(5, 9, '#');

    #pragma endregion

    std::vector<Entity*> EntityList;


    Renderer rend(180, 50, &map, &EntityList);

    //startPoint
    rend.xLoc = 1.5f;
    rend.yLoc = 1.5f;
    rend.rotation = 45;

    //Creating entities
    Enemy e1(5.0f, 5.0f, 'E', 1.0f);
    Enemy e2(3.5f, 3.0f, 'E', 0.0f);
    Follower e3(10.0f, 10.0f, &rend);
    EntityList.push_back(&e1);
    EntityList.push_back(&e2);
    EntityList.push_back(&e3);

    //Waiting for input
    std::cout << "Resize the window to full screen and press enter\nIf you have troubles with visualization, try pressing R\n";
    std::getchar();
    rend.ResizeWindow();

	//Capturing the time for deltaTime calculation
    std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();

    //Game loop
    while (true) {
		//Delta time calculation
        std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float deltaTime = elapsedTime.count();

		//Input handling
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            rend.rotation += rotSpeed * deltaTime;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            rend.rotation -= rotSpeed * deltaTime;
        }

        if (GetAsyncKeyState('W') & 0x8000) {
            rend.xLoc += std::cosf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
            rend.yLoc += std::sinf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            rend.xLoc -= std::cosf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
            rend.yLoc -= std::sinf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
        }
        if (GetAsyncKeyState('A') & 0x8000) {
            rend.xLoc -= std::sinf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
            rend.yLoc += std::cosf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            rend.xLoc += std::sinf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
            rend.yLoc -= std::cosf(rend.rotation * M_PI / 180.0f) * moveSpeed * deltaTime;
        }
        if (GetAsyncKeyState('R') & 0x8000) {
            rend.ResizeWindow();
        }

		//Updating entities
        for (Entity* e : EntityList) {
            e->Update(deltaTime);
        }

		//Rendering and visualization
        rend.Render();
        rend.Draw();

        //Debug data rendering
        if (deltaTime != 0) {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD pos = { 0, 50 };
            SetConsoleCursorPosition(hOut, pos);
           std::cout << "FPS: " << 1 / deltaTime << " X: " << rend.xLoc << " Y: " << rend.yLoc;
        }

    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
