class Wall
{
    Vector2d pos;

    SDL_Texture *texture;

public:
    Wall(float x, float y)
    {
        this->pos.x = x;
        this->pos.y = y;

        SDL_Surface *surface = SDL_LoadBMP("textures/brick.bmp");
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    }

    void draw()
    {
        SDL_Rect sprite_pos = {(int) this->pos.x, (int) this->pos.y, 16, 16}; // MOVE AWAY
        SDL_RenderCopy(renderer, this->texture, NULL, &sprite_pos);
    }

};