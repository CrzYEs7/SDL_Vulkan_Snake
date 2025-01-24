#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
	Snake(int size, int x, int y);
	int _y = 0;
	int _x = 0;
	int direction_x = 0;
	int direction_y = 0;
	int _speed = 1;

public:
	void move_to(int x, int y);
	void move(int x, int y, float delta);
	int get_speed();
	void set_speed(int new_speed);
	int get_size();
	void set_sizes(int new_size);

private:
	int _size = 1;
};

#endif
