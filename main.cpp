#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

// TODO: remove global declaration
SDL_Window   *window;
SDL_Renderer *renderer;


// TODO: rewrite vector as class with functions like "rotate", "vector addition"
struct Vector2d
{
    int x;
    int y;
};

class Player
{
    // TODO:
    // add renderer variable
    // SDL_Renderer *renderer;


    int health = 100;
    Vector2d pos = { 350, 350 };        // position
    Vector2d vel = { 10, 10 };          // velocity

    SDL_Texture *texture;               // player sprite texture

public:
    enum direction { dir_up, dir_down, dir_left, dir_right };

    Player()
    {
        SDL_Surface *surface = SDL_LoadBMP("textures/player.bmp");
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        std::cout<<"texture loaded\n";
    }

    void draw()
    {
        SDL_Rect sprite_pos = {this->pos.x, this->pos.y, 14, 14}; // MOVE AWAY


        SDL_RenderCopy(renderer, this->texture, NULL, &sprite_pos);
    }

    void move(direction direction)
    {
        //TODO add test for colission

        switch(direction)
        {
        case dir_up:
            this->pos.y += this->vel.y;
            break;
        case dir_down:
            this->pos.y -= this->vel.y;
            break;
        case dir_left:
            this->pos.x -= this->vel.x;
            break;
        case dir_right:
            this->pos.x += this->vel.x;
            break;
        }
    }


};

void scene_clear()
{
    //TODO: color as variable
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



    scene_clear();
}

void render()
{

}

int main(int argc, char *argv[])
{

    setup();

    Player p1 = Player();

    //Brick walls texture
    SDL_Surface *bitmapSurface = SDL_LoadBMP("textures/brick.bmp");
    SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);

    bool mainLoop = true;
    SDL_Event event;
    while (mainLoop)
    {
        scene_clear();

        // # TEST AREA
        // DRAW WALLS

        SDL_Rect brick_rect;

        for (int i = 0; i < 44; ++i)
        {
            brick_rect.x = 16 * i;
            brick_rect.y = 0;
            brick_rect.h = 16;
            brick_rect.w = 16;
            SDL_RenderCopy(renderer, bitmapTex, NULL, &brick_rect);
        }

        for (int i = 0; i < 50; ++i)
        {
            brick_rect.x = 16 * i;
            brick_rect.y = 688;
            brick_rect.h = 16;
            brick_rect.w = 16;
            SDL_RenderCopy(renderer, bitmapTex, NULL, &brick_rect);
        }


        for (int i = 0; i < 50; ++i)
        {
            brick_rect.y = 16 * i;
            brick_rect.x = 0;
            brick_rect.h = 16;
            brick_rect.w = 16;
            SDL_RenderCopy(renderer, bitmapTex, NULL, &brick_rect);
        }

        for (int i = 0; i < 50; ++i)
        {
            brick_rect.y = 16 * i;
            brick_rect.x = 688;
            brick_rect.h = 16;
            brick_rect.w = 16;
            SDL_RenderCopy(renderer, bitmapTex, NULL, &brick_rect);
        }
        p1.draw();
        p1.move(Player::direction::dir_down);

        SDL_RenderPresent(renderer);

        // END-TEST AREA #

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                mainLoop = false;
                break;

            case SDL_KEYDOWN:
                // key event
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
