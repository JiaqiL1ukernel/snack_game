#ifndef _CUBE_H_
#define _CUBE_H_
#include <easyx.h>
#include <vector>

class Cube
{
protected:
	enum { WIDTH = 20 , HEIGHT = 20};
	int x;
	int y;
	COLORREF color;
public:
	Cube(int a = 0, int b = 0, COLORREF c = RED) :x(a), y(b), color(c) {};
	Cube(const Cube& c) { x = c.x; y = c.y; color = c.color; }
	virtual ~Cube(){};
	virtual void Draw(void);
	void moveBy(int a, int b) { x += a; y += b; }
	int getX()const { return x; }
	int getY()const { return y; }
	COLORREF get_color()const { return color; }
	bool operator ==(const Cube& c)const;
	bool isCollide(const Cube& c)const;
};

class Food :public Cube
{
private:
public:
	std::vector<Cube> foods;
	Food();
	void Draw();
	void create_food();
};
class Snake : public Cube
{
private:
	std::vector<Cube> body;
	int dir;
public:
	friend class Env;
	Snake(int a = 0, int b = 0, COLORREF c = RED);
	void Draw(void);
	void body_move();
	~Snake() {}
	bool isLoop()const;
	bool isBorder()const;
	bool isEat(Food &f);
	void grow();
};


class Env
{
private:
	int score;
	int max_score;

public:
	Env() :score(0), max_score(0) {}
	void Show_Border();
	void Run(Snake &s,Food &f);
	int get_score()const { return score; }
	int get_max_score()const { return max_score; }
	void OnMsg(const ExMessage& msg,Snake &s);

};


#endif




