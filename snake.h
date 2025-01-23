#ifndef SNAKE_H
#define SNAKE_H

class Snake(Uint32 size, int x, int y)
{
public:
	void move_to(int x, int y);
	int get_speed();
	int set_speed(float new_speed);
	Uint32 get_size();
	Uint32 set_sizes(Uint32 new_size);
private:
	float _speed = 1;
	Uint32 _size = size;
	int x = 0;
	int y = 0;
}

#endif
