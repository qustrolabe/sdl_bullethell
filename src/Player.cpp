class Player
{
    // TODO:
    // add renderer variable
    // SDL_Renderer *renderer;


    int health = 100;

    Vector2d pos = { 16, 600 };        // position
    Vector2d vel = { 0, 0 };          // velocity

    SDL_Texture *texture;               // player sprite texture

public:
    enum direction { dir_up, dir_down, dir_left, dir_right };

    Player()
    {
        SDL_Surface *surface = SDL_LoadBMP("textures/player.bmp");
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        std::cout << "Player texture loaded\n";
    }

    void draw()
    {
        SDL_Rect sprite_pos = {(int) this->pos.x, (int) this->pos.y, 16, 16};
        SDL_RenderCopy(renderer, this->texture, NULL, &sprite_pos);
    }

    void accelerate(direction dir)
    {

        switch(dir)
        {
        case dir_up:
            // this->vel.y -= 1;
            this->vel.y = -2;
            break;
        case dir_down:
            // this->vel.y += 1;
            this->vel.y = 2;
            break;
        case dir_left:
            // this->vel.x -= 1;
            this->vel.x = -2;
            break;
        case dir_right:
            this->vel.x = 2;
            // this->vel.x += 1;
            break;
        }

    }

    void move()
    {
        this->pos.add(this->vel);

        this->vel.x *= 0.97;
        this->vel.y *= 0.97;

        if(this->pos.x > (688 - 16))
        {
            this->pos.x = 688 - 16;
        }
        if(this->pos.x < 16)
        {
            this->pos.x = 16;
        }

        if(this->pos.y > (688 - 16))
        {
            this->pos.y = 688 - 16;
        }
        if(this->pos.y < 16)
        {
            this->pos.y = 16;
        }
    }

    Vector2d getPos()
    {
        return this->pos;
    }


};