#include<bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<ctime>
using namespace std;
#define WIDTH 60
#define HEIGHT 25
int score;

class Snake
{
    private:
        COORD position;
        vector<COORD> body;
        int velocity,len;
        char dir;
        
    public:
        Snake(COORD position, int velocity);
        void grow();
        void move_snake();
        void change_direc(char dir);
        vector<COORD> get_body();
        bool collided();
        bool eaten(COORD meals);
        COORD get_position();
};

Snake::Snake(COORD position, int velocity)
{
    this->position = position;
    this->velocity = velocity;
    dir = 'n';
    len = 1;
    body.push_back(position);
}

void Snake::change_direc(char dir) { this->dir = dir; }
void Snake::grow() { len++; }
COORD Snake::get_position() { return position; }
vector<COORD> Snake::get_body() { return body; }

void Snake::move_snake()
{
    switch(dir)
    {
        case 'u': position.Y -= velocity; break;
        case 'd': position.Y += velocity; break;
        case 'l': position.X -= velocity; break;
        case 'r': position.X += velocity; break;
    }

    body.push_back(position);
    if(body.size() > len) body.erase(body.begin());
}

bool Snake::collided()
{
    if(position.X < 1 || position.X > WIDTH-2 || position.Y < 1 || position.Y > HEIGHT-2) return true;

    for(int i = 0; i < len-1; i++)
    {
        if(position.X == body[i].X && position.Y == body[i].Y) return true;
    }
    return false;
}

bool Snake::eaten(COORD meals)
{
    if(position.X == meals.X && position.Y == meals.Y) return true;
    return false;
}

class Meals
{
    private:
        COORD position;

    public:
        void genrate_meals();

        COORD get_position();
};
void Meals::genrate_meals()
{
    position.X = rand() % (WIDTH - 4) + 2;
    position.Y = rand() % (HEIGHT - 4) + 2;
}

COORD Meals::get_position() { return position; }

Snake snake({WIDTH/2, HEIGHT/2}, 1);
Meals meals;


void board()
{
    COORD snake_position = snake.get_position();
    COORD meals_position = meals.get_position();

    vector<COORD> snake_body = snake.get_body();

    cout << "SCORE : " << score << "\n";
    cout<<"Press\n'W' for UP."<<endl<<"'D' for RIGHT"<<endl<<"'A' for LEFT"<<endl<<"'S' for DOWN"<<endl;

    for(int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for(int j = 0; j < WIDTH - 2; j++)
        {
            if(i == 0 || i == HEIGHT-1) cout << '#';

            else if(i == snake_position.Y && j+1 == snake_position.X) cout << "0";
            else if(i == meals_position.Y && j+1 == meals_position.X) cout << '@';

            else
            {
                bool isBodyPart = false;
                for(int k = 0; k < snake_body.size()-1; k++)
                {
                    if(i == snake_body[k].Y && j+1 == snake_body[k].X)
                    {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }

                if(!isBodyPart) cout << ' ';
            }
        }
        cout << "#\n";
    }
}

int main()
{
    score = 0;
    srand(time(NULL));

    meals.genrate_meals();

    char game_over = false;

    while(!game_over)
    {
        board();

        if(kbhit())
        {
            switch(getch())
            {
                case 'w': snake.change_direc('u'); break;
                case 'a': snake.change_direc('l'); break;
                case 's': snake.change_direc('d'); break;
                case 'd': snake.change_direc('r'); break;
            }
        }

        if(snake.collided()) game_over = true;

        if(snake.eaten(meals.get_position()))
        {
            meals.genrate_meals();
            snake.grow();
            score = score + 10;
        }

        snake.move_snake();

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
}