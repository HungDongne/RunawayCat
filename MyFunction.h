#ifndef MYFUNCTION__H_
#define MYFUNCTION__H_

#include "Global.h"
#include "Constant.h"

bool init();
bool loadMedia();
void close();
bool checkCollision(LTexture& a, Enermy& b);
bool checkCollision(LTexture& a, Food& b);
void Bullet_calculator();
void initialize();
double getAngle(double x, double y, double x0, double y0);
void gamecalculator();
void gamerender();
bool checkCollision(int& mousex, int& mousey, LTexture& tmp);

#endif // !MYFUNCTION__H_
