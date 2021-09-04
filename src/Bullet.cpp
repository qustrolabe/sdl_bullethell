class Bullet
{
    Vector2d pos;

    double speed = 1;
    double rotateSpeed = 0.5;

    double rotation = 0;

    SDL_Texture *texture;

public:
    Bullet(float x, float y, double rotation = 0)
    {
        this->pos.x = x;
        this->pos.y = y;

        this->rotation = rotation;

        SDL_Surface *surface = SDL_LoadBMP("textures/bullet.bmp");
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    };

    void draw()
    {
        SDL_Rect sprite_pos = {(int) this->pos.x, (int) this->pos.y, 16, 10}; // MOVE AWAY
        SDL_RenderCopyEx(renderer, this->texture, NULL, &sprite_pos, rotation, NULL, SDL_FLIP_NONE);
    }

    void rotate(double ang)
    {

        this->rotation += ang;

        if(this->rotation >= 180)
        {
            this->rotation -= 360;
        }

        if(this->rotation < -180)
        {
            this->rotation += 360;
        }
    }

    void chase(Vector2d target_pos)
    {
        Vector2d bp = {target_pos.x - this->pos.x, target_pos.y - this->pos.y};


        double chaseAngle = std::atan2(bp.y, bp.x) * 180.0 / pi();
        double angle = this->rotation;

        double delta = (chaseAngle - angle);

        if((delta < 0 && (fabs(delta) <= 180.0))
                || (delta > 0 && (fabs(delta) >= 180.0)))
            this->rotate(- this->rotateSpeed);
        else
            this->rotate(+ this->rotateSpeed);
    }

    void move()
    {
        this->pos.x += std::cos((rotation) * 2 * pi() / 360) * speed;
        this->pos.y += std::sin((rotation) * 2 * pi() / 360) * speed;
    }


};
