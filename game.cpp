#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include "game.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_surface.h"
#include "fruit.h"
#include "snake.h"
#include <deque>
#include <stdlib.h>
#include <time.h>
#include "text.h"

Game::Game()
{
    //if (TTF_Init() < 0) {
    //    printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
    //}

    //text = Text((char*)"NovaSquareRegular.ttf", (char*)"Press Enter to Start!", 46, SDL_Color{255,255,255,255}, SDL_Color{00,00,00,00});
    current_step_time = 0;
	last_time = 0;
	step_time = 120;

	next_move_y[0] = 1;
	next_move_x[0] = 0;

	rect = {_snake._x, _snake._y, CELL_SIZE, CELL_SIZE};
	srand(time(NULL));

    fruit_vector.reserve(41);

    for (int i = 0; i < 0; i++)
    {
        fruit_vector.emplace_back(Fruit(
            rand() % RESOLUTION * CELL_SIZE, 
            rand() % RESOLUTION * CELL_SIZE,1));
    }
	//text->CreateText("Press Enter!");
    score_board = LoadScores();
}

void Game::Draw(SDL_Surface *surface)
{
    
	if (state == game::GAMEOVER)
	{
		start_text.drawText(surface, 50, 50);
        DrawScores(10, surface);
        return;
    }

	_snake.draw(&rect, surface);	

    if (state == game::PAUSED)
    {
        pause_text.drawText(surface, 20, 10);
        DrawScores(10, surface);
    }
    else if (state == game::SAVESCORE)
    {
        Text enter_name((char*)"NovaSquare-Regular.ttf", (char*)"Please enter your name", 25, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
        enter_name.drawText(surface, SCREEN_SIZE / 2, SCREEN_SIZE / 2 + 100);

        Text name((char*)"NovaSquare-Regular.ttf", (char*)player_name.c_str(), 30, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
        name.drawText(surface, SCREEN_SIZE / 2, SCREEN_SIZE / 2 + 150);
    }

	for(Fruit fruit : fruit_vector)
	{
		fruit.draw(surface, &rect);
	}

    Text score_text((char*)"NovaSquare-Regular.ttf", (char*)std::to_string(score).c_str(), 20, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
    score_text.drawText(surface, SCREEN_SIZE - 50, 10);

}

void Game::Update(float delta)
{
    if (state != game::RUNNING)
        return;

    current_step_time += delta;
    
    // new fruit
    if (fruit_vector.size() < min_fruits)
    {
        fruit_vector.emplace_back(Fruit(
            rand() % RESOLUTION * CELL_SIZE, 
            rand() % RESOLUTION * CELL_SIZE,1));

        float chance = rand() % 10 * 1;
        // special fruit
        if (chance > 8)
        {
            fruit_vector.back().rate = 3;
            fruit_vector.back().lifespam = 250;
            fruit_vector.back().features.emplace_back(Fruit::feature::timer);
            fruit_vector.back().color = 0x00af8800;
        }
    }

    if (current_step_time >= step_time)
    {
        if (next_move_y.size() > 0)
        {	
            _snake.direction_y = next_move_y.front();
            _snake.direction_x = next_move_x.front();
            next_move_x.pop_front();
            next_move_y.pop_front();
        }

        _snake.move(delta);
        _snake.update(delta);

        if (_snake.state == _snake.DEAD)
        {
            player_name = "";
            SDL_StartTextInput();
            state = game::SAVESCORE;
        }
        for (int i = 0; i < fruit_vector.size(); i++)
        {
            if (fruit_vector[i].x == _snake._x && fruit_vector[i].y == _snake._y)
            {
                score += fruit_vector[i].rate;
                _snake.grow(fruit_vector[i].rate);
                fruit_vector.erase(fruit_vector.begin() + i);

            }
            else if (fruit_vector[i].hasFeature(Fruit::feature::timer))
            {
                if (fruit_vector[i].lifespam <= 0)
                {
                    fruit_vector.erase(fruit_vector.begin() + i);

                }
                fruit_vector[i].lifespam -= delta;
            }
        }

        current_step_time = 0;
    }
}

void Game::Input(SDL_Event e)
{

    Game::InputStateHandler(e);

    if (e.key.type == SDL_KEYDOWN)
    {
        if( e.key.keysym.sym == SDLK_UP )
        {
            next_move_y.emplace_back(-1);
            next_move_x.emplace_back(0);
        }
        if( e.key.keysym.sym == SDLK_DOWN )
        {
            next_move_y.emplace_back(1);
            next_move_x.emplace_back(0);
        }
        if( e.key.keysym.sym == SDLK_LEFT )
        {
            next_move_y.emplace_back(0);
            next_move_x.emplace_back(-1);
        }
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
            next_move_y.emplace_back(0);
            next_move_x.emplace_back(1);
        }
        // DEBUG
        if( e.key.keysym.sym == SDLK_SPACE )
            _snake.grow(1);
        //Handle backspace
        if( e.key.keysym.sym == SDLK_BACKSPACE && player_name.length() > 0
        && state == game::States::SAVESCORE )
        {
            player_name.pop_back();
        }
    }
    else if( e.type == SDL_TEXTINPUT )
    {
        player_name += e.text.text;
    }

}

void Game::Restart()
{
    score = 0;
	_snake.shrink(_snake._body.size() - 1);
	_snake._x = SCREEN_SIZE / 2;
	_snake._y = SCREEN_SIZE / 2;
	
	fruit_vector.clear();
	fruit_vector.emplace_back(Fruit(
		rand() % RESOLUTION * CELL_SIZE, 
		rand() % RESOLUTION * CELL_SIZE,1));
    for (int i = 0; i < 0; i++)
    {
        fruit_vector.emplace_back(Fruit(
            rand() % RESOLUTION * CELL_SIZE, 
            rand() % RESOLUTION * CELL_SIZE,1));
    }
	
	_snake.restart();
}

void Game::InputStateHandler(SDL_Event e)
{
    if (e.type != SDL_KEYDOWN)
        return;

    switch (state)
    {
        case game::PAUSED :
            if( e.key.keysym.sym == SDLK_RETURN)
            {
                state = game::RUNNING;
            }
            break;
        case game::RUNNING :
            if( e.key.keysym.sym == SDLK_p)
            {
                state = game::PAUSED;
            }
            break;
        case game::GAMEOVER :
            if( e.key.keysym.sym == SDLK_RETURN)
            {
                state = game::RUNNING;
                Restart();
                return;
            }
            break;
        case game::SAVESCORE :
            if (e.key.keysym.sym == SDLK_RETURN)
            {
                SaveScore(player_name);
                SDL_StopTextInput();
                score_board = LoadScores();
                state = game::GAMEOVER;
                return;
            }
            break;
    }
}

void Game::SaveScore(std::string player_name)
{
    std::ofstream scores;
    scores.open("scores.dat", std::ios::app);
    scores << player_name << ":" << score << "\n" ;
    //std::cout << "score saved :" << score << std::endl;
    scores.close();
}

std::vector<std::pair<std::string,int>> Game::LoadScores()
{
    std::ifstream file_scores;

    std::string name = "";
    int score;
    
    std::string temp;
    char c;

    std::vector<std::pair<std::string,int>> scores_vector;
    scores_vector.reserve(10);

    file_scores.open("scores.dat");

    while(file_scores.get(c)) 
    {
        temp += c;

        if ( c == ':')
        {
            temp.pop_back();
            name = temp;
            if ( name.empty() )
                name = "NoName";
            temp = "";
        }
        else if (c == '\n')
        {
            temp.pop_back();
            score = std::stoi(temp);
            std::pair<std::string, int> pair = {name, score};
            scores_vector.emplace_back(pair);
            temp = "";
        }
        //std::cout << scores << std::endl;
    }
    file_scores.close();
    std::sort(scores_vector.begin(), scores_vector.end(), scores_sort);
    return scores_vector;
}

void Game::DrawScores(int n_of_scores, SDL_Surface* surface)
{
    int line_pos_y = 0;
    int count = 0; 

    if (score_board.empty())
        return;

    for(auto _score : score_board)
    {
        if ( count > n_of_scores)
            break;

        std::string name = _score.first;
        std::string score = std::to_string(_score.second);
        std::string line = name + " : " + score;
        line_pos_y += 20;
        Text score_text((char*)"NovaSquare-Regular.ttf", (char*)line.c_str(), 15, SDL_Color{255,255,255,255}, SDL_Color{0,0,0,0});
        score_text.drawText(surface, SCREEN_SIZE - 200, line_pos_y);
        count++;
    }

}
