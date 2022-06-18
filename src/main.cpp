#include <iostream>
#include <cmath>

#include "SDL2/SDL.h"

using namespace std;


SDL_Window   *window;
SDL_Renderer *renderer;

constexpr double pi()
{
    return std::atan(1) * 4;
}

struct Vector2d
{
    float x;
    float y;
    void add(Vector2d v2)
    {
        this->x += v2.x;
        this->y += v2.y;
    }
};

#include <Player.cpp>
#include <Wall.cpp>
#include <Bullet.cpp>

void scene_clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void setup()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        cout << "SDL cannot init" << endl;

    window = SDL_CreateWindow("sdl_bullethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 704, 704, SDL_WINDOW_OPENGL);
    if (window == nullptr)
        cout << "Window cannot be created" << endl;

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr)
        cout << "Renderer cannot init" << endl;
}

void render()
{

}

#include <vector>

int main(int argc, char *argv[])
{
    setup();

    std::vector<Wall> walls;

    std::vector<Bullet> bullets;
    for(int i = 0; i < 50; i++)
    {
        bullets.emplace_back(16 + 8 * i, 16 + 8 * i);
    }

    //DRAWING WALLS
    {
        for(int i = 0; i < 44; i++)
        {
            walls.emplace_back(16 * i, 0);
        }

        for(int i = 0; i < 44; i++)
        {
            walls.emplace_back(16 * i, 688);
        }

        for(int i = 0; i < 44; i++)
        {
            walls.emplace_back(0, 16 * i);
        }

        for(int i = 0; i < 44; i++)
        {
            walls.emplace_back(688, 16 * i);
        }
    }


    Player p1 = Player();

    bool mainLoop = true;
    SDL_Event event;
    while (mainLoop)
    {
        scene_clear();

        for(auto &w : walls)
        {
            w.draw();
        }

        for(auto &b : bullets)
        {
            b.chase(p1.getPos());
            b.draw();
            b.move();
        }

        p1.draw();

        SDL_RenderPresent(renderer);

        //
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if( (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
                && !(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) )
        {
            p1.accelerate(Player::direction::dir_right);
        }
        if((keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
                && !(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) )
        {
            p1.accelerate(Player::direction::dir_left);
        }

        if((keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
                && !(keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]))
        {
            p1.accelerate(Player::direction::dir_up);
        }
        if((keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
                && !(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]))
        {
            p1.accelerate(Player::direction::dir_down);
        }

        p1.move();
        
        if (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                mainLoop = false;
                break;
            }
        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
