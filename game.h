#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_mixer.h>
#include <deque>
#include <vector>
#include <fstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_surface.h"
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
	Game(SDL_Surface* _window_surface);
	~Game() = default;

public:
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
    SDL_Surface* window_surface;

	float last_time = SDL_GetTicks();
	float current_step_time;
	float step_time;

    std::vector<std::pair<std::string,int>> score_board;
    std::string player_name;	

	std::deque<int> next_move_y;
	std::deque<int> next_move_x;

    vect_pair_sort scores_sort;

    Mix_Chunk* get_fruit_sound;
    Mix_Music* music; 

    SDL_Color font_color = {200,200,200,255};

    Text* large_text;
	Text* medium_text;
    Text* small_text;

private:
    void SaveScore(std::string player_name);
    std::vector<std::pair<std::string,int>> LoadScores();
    void DrawScores(int n_of_scores, SDL_Surface* surface);
};

#endif
