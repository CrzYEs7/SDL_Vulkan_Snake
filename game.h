#ifndef GAME_H
#define GAME_H

#include <deque>
#include <vector>
#include <fstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "snake.h"
#include "fruit.h"
#include "text.h"

namespace game
{
	enum States { PAUSED, RUNNING, GAMEOVER , SAVESCORE};
}

struct vect_pair_sort
{
    bool operator()(std::pair<std::string, int> a, std::pair<std::string, int> b) const
    {
        return a.second > b.second;
    }
};

class Game
{
public:
	Game();
	~Game() = default;

public:
	Text start_text = Text((char*)"NovaSquare-Regular.ttf", (char*)"Press Enter to Start!", 46, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
	Text pause_text = Text((char*)"NovaSquare-Regular.ttf", (char*)"Paused, press Enter to play!", 46, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});   
    SDL_Rect rect;
	Snake _snake;
    int min_fruits = 1;
	std::vector<Fruit> fruit_vector;
    game::States state = game::GAMEOVER; 
	int score = 0;
    int number_scores_to_show = 10;

public:
	void Restart();
    void InputStateHandler(SDL_Event);

public:
	void Update(float delta);
	void Draw(SDL_Surface *surface);
	void Input(SDL_Event e);

private:
	float last_time = SDL_GetTicks();
	float current_step_time;
	float step_time;

    std::vector<std::pair<std::string,int>> score_board;
    std::string player_name;	

	std::deque<int> next_move_y;
	std::deque<int> next_move_x;

    vect_pair_sort scores_sort;

private:
    void SaveScore(std::string player_name);
    std::vector<std::pair<std::string,int>> LoadScores();
    void DrawScores(int n_of_scores, SDL_Surface* surface);
};

#endif
