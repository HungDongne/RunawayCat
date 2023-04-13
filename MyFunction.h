#ifndef MYFUNCTION__H_
#define MYFUNCTION__H_

#include "Global.h"
#include "Constant.h"

bool init();
bool loadMedia();
void close();
bool checkCollision(LTexture& a, Enermy& b);
bool checkCollision(LTexture& a, Food& b);
void Push_Calculator();
void initialize();

#endif // !MYFUNCTION__H_
