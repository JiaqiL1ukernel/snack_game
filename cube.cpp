#include "cube.h"
#include <cstdlib>
void Cube::Draw(void)
{
	fillrectangle(x, y, x + WIDTH, y + HEIGHT);

}

bool Cube::isCollide(const Cube& c)const
{
	if (x >= c.x && x <= c.x + WIDTH && y >= c.y && y <= c.y + HEIGHT)
		return true;
	else if (x + WIDTH >= c.x && x + WIDTH <= c.x + WIDTH && y >= c.y && y <= c.y + HEIGHT)
		return true;
	else if (x >= c.x && x <= c.x + WIDTH && y + HEIGHT >= c.y && y + HEIGHT <= c.y + HEIGHT)
		return true;
	else if (x + WIDTH >= c.x && x + WIDTH <= c.x + WIDTH && y + HEIGHT >= c.y && y + HEIGHT <= c.y + HEIGHT)
		return true;
	else
		return false;
}


void Snake::Draw(void)
{
	setfillcolor(color);
	for (int i = 0; i < body.size(); i++)
	{
		body[i].Draw();
	}

}

Snake::Snake(int a, int b, COLORREF c):Cube(a,b,c),dir(VK_RIGHT)
{
	body.push_back(Cube(a, b, c));
	body.push_back(Cube(a + WIDTH, b, c));
	body.push_back(Cube(a + 2 * WIDTH, b, c));
	body.push_back(Cube(a + 3 * WIDTH, b, c));
	body.push_back(Cube(a + 4 * WIDTH, b, c));
	body.push_back(Cube(a + 5 * WIDTH, b, c));
	body.push_back(Cube(a + 6 * WIDTH, b, c));
	body.push_back(Cube(a + 7 * WIDTH, b, c));
	body.push_back(Cube(a + 8 * WIDTH, b, c));
	body.push_back(Cube(a + 9 * WIDTH, b, c));

}



void Env::Run(Snake& s,Food &f)
{
	int times = 100;
	
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		Show_Border();
		s.Draw();
		f.Draw();
		EndBatchDraw();
		s.body_move();
		s.isEat(f);
		ExMessage msg;
		while (peekmessage(&msg, EX_KEY))
			OnMsg(msg, s);
		if (s.isLoop()|| s.isBorder())
			break;
		if (rand() % s.body.size() * 12 < 1)
			times -= 0.001;
		Sleep(times);
	}


}


bool Snake::isLoop()const
{
	for (int i = 0; i < body.size()-1; i++) {
		if (body[i].getX() == body[body.size() - 1].getX()
			&& body[i].getY() == body[body.size() - 1].getY())
			return true;
	}
	return false;
}

bool Snake::isBorder()const
{
	return (body[body.size() - 1].getX() >= 1000||
		body[body.size()-1].getY() >= 1000
		|| body[body.size() - 1].getY()<=0
		|| body[body.size() - 1].getX() <= 0);
}

void Snake::body_move()
{

	for (int i = 0; i < body.size()-1; i++)
	{
		body[i] = body[i + 1];
	}
	switch (dir)
	{
	case VK_DOWN:
		body[body.size() - 1].moveBy(0,HEIGHT);
		break;
	case VK_UP:
		body[body.size() - 1].moveBy(0, -HEIGHT);
		break;
	case VK_LEFT:
		body[body.size() - 1].moveBy(-WIDTH,0);
		break;
	case VK_RIGHT:
		body[body.size() - 1].moveBy(WIDTH,0);
		break;
	default:
		break;
	}
}

void Env::OnMsg(const ExMessage& msg,Snake &s)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == VK_UP || msg.vkcode == VK_DOWN
			|| msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT)
			if(s.dir+2!=msg.vkcode && s.dir-2!=msg.vkcode)
				s.dir = msg.vkcode;
		
	}
}


Food::Food()
{
	Cube f1((rand() % 940) + 21, (rand() % 940) + 21,GREEN);
	Cube f2((rand() % 940) + 21, (rand() % 940) + 21,GREEN);
	Cube f3((rand() % 940) + 21, (rand() % 940) + 21, GREEN);
	Cube f4((rand() % 940) + 21, (rand() % 940) + 21, GREEN);
	Cube f5((rand() % 940) + 21, (rand() % 940) + 21, GREEN);
	Cube f6((rand() % 940) + 21, (rand() % 940) + 21, GREEN);
	Cube f7((rand() % 940) + 21, (rand() % 940) + 21, GREEN);
	
	foods.push_back(f1);
	foods.push_back(f2);
	foods.push_back(f3);
	foods.push_back(f4);
	foods.push_back(f5);
	foods.push_back(f6);
	foods.push_back(f7);

}

void Food::Draw()
{
	for (int i = 0; i < foods.size(); i++)
	{
		setfillcolor(foods[i].get_color());
		foods[i].Draw();
	}

}

void Snake::grow()
{
	switch (dir)
	{
	case VK_DOWN:
		body.insert(body.begin(), Cube(body[0].getX(), body[0].getY() - HEIGHT));
		break;
	case VK_UP:
		body.insert(body.begin(),Cube(body[0].getX(), body[0].getY() + HEIGHT));
		break;
	case VK_LEFT:
		body.insert(body.begin(), Cube(body[0].getX()+WIDTH, body[0].getY()));
		break;
	case VK_RIGHT:
		body.insert(body.begin(), Cube(body[0].getX() - WIDTH, body[0].getY()));
		break;
	default:
		break;
	}
}

void Env::Show_Border()
{
	for (int i = 0; i < 1000; i+=21)
	{
		setfillcolor(WHITE);
		Cube c(i, 0);
		Cube c2(i, 980);
		c.Draw();
		c2.Draw();
	}
	for (int i = 1; i < 1000-1; i += 21)
	{
		setfillcolor(WHITE);
		Cube c(0, i);
		Cube c2(980, i);
		c.Draw();
		c2.Draw();
	}
}




bool Snake::isEat(Food &f)
{
	std::vector<Cube>::iterator it = f.foods.begin();
	for (int i = 0; i < f.foods.size(); i++)
	{
		if (body[body.size() - 1].isCollide(f.foods[i])) {
			f.foods.erase(it);
			f.create_food();
			grow();
			return true;
		}
		it++;
	}
	return false;
}


bool Cube::operator ==(const Cube& c)const
{
	return (x == c.x && y == c.y);
}

void Food::create_food()
{
	Cube f1((rand() % 900) + 50, (rand() % 900) + 50, GREEN);
	foods.push_back(f1);
}










