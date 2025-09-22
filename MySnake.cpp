#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include "LinkedList.h"

#define UP_KEY 38
#define DOWN_KEY 40
#define RIGHT_KEY 39
#define LEFT_KEY 37

int Get_Random_Number(int max)
{
    static std::random_device rd;
    // Use Mersenne Twister engine seeded with rd
    static std::mt19937 gen(rd());
    // Define the range
    std::uniform_int_distribution<> dist(0, max);
    // Generate and return a random number in [min, max]
    return dist(gen);
}
class SNAKE
{
private:
    int random_x = Get_Random_Number(100);
    int random_y = Get_Random_Number(50);
    void Move_Snake_Right(LinkedList &, int);
    void Move_Snake_Left(LinkedList &, int);
    void Move_Snake_Up(LinkedList &, int);
    void Move_Snake_Down(LinkedList &, int);
    void Display_Snake(LinkedList &);

public:
    int user_score = 0;
    void Update_UserScore(void);
    int Run_Game(void);
};

void Update_UserInput(int &ruui)
{

    WORD type_event;
    HANDLE handle_screen = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD input_array;
    DWORD length = 1;
    DWORD number_of_input;

    while (true)
    {

        if (ReadConsoleInput(handle_screen, &input_array, length, &number_of_input))
        {
            type_event = input_array.EventType;
            switch (type_event)
            {
            case KEY_EVENT:
                if (input_array.Event.KeyEvent.bKeyDown)
                {

                    ruui = input_array.Event.KeyEvent.wVirtualKeyCode;
                }
                break;
            default:
                break;
            }
        }
        else
        {
            GetLastError();
        }
    }
}

void SNAKE::Move_Snake_Right(LinkedList &a, int x)
{

    if (x <= a.Get_Head()->c.x)
    {
        a.update_head(coordinate{0, a.Get_Head()->c.y});
        // a.remove_tail();
        return;
    }
    a.update_head(coordinate{a.Get_Head()->c.x + 1, a.Get_Head()->c.y});
    // a.remove_tail();
}

void SNAKE::Move_Snake_Left(LinkedList &a, int x)
{
    if (a.Get_Head()->c.x == 0)
    {
        a.update_head(coordinate{x, a.Get_Head()->c.y});
        // a.remove_tail();
        return;
    }
    a.update_head(coordinate{a.Get_Head()->c.x - 1, a.Get_Head()->c.y});
    // a.remove_tail();
}

void SNAKE::Move_Snake_Down(LinkedList &a, int y)
{
    if (a.Get_Head()->c.y >= y)
    {
        a.update_head(coordinate{a.Get_Head()->c.x, 0});
        //   a.remove_tail();
        return;
    }
    a.update_head(coordinate{a.Get_Head()->c.x, a.Get_Head()->c.y + 1});
    // a.remove_tail();
}

void SNAKE::Display_Snake(LinkedList &s)
{
    DWORD num0;
    char n0[] = {'A'};
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleOutputCharacter(h, n0, 1, COORD{random_x, random_y}, &num0);

    DWORD num1;
    char space[] = {' '};
    WriteConsoleOutputCharacter(h, space, 1, COORD{s.Get_Tail()->c.x, s.Get_Tail()->c.y}, &num1);
    if (s.Get_Head()->c.x != random_x && s.Get_Head()->c.y != random_y)
    {
        s.remove_tail();
    }
    else
    {
        random_x = Get_Random_Number(100);
        random_y = Get_Random_Number(100);
    }

    Node *tail = s.Get_Tail();

    char n1[] = {'O'};
    DWORD num;
    for (Node *move = tail; move != NULL; move = move->prev)
        WriteConsoleOutputCharacter(h, n1, 1, COORD{move->c.x, move->c.y}, &num);
}

void SNAKE::Move_Snake_Up(LinkedList &a, int y)
{
    if (a.Get_Head()->c.y == 0)
    {
        a.update_head(coordinate{a.Get_Head()->c.x, y});
        // a.remove_tail();
        return;
    }
    a.update_head(coordinate{a.Get_Head()->c.x, a.Get_Head()->c.y - 1});
    // a.remove_tail();
}

int SNAKE::Run_Game()
{

    enum DIRECTION
    {
        XP = 0,
        XN,
        YP,
        YN
    };
    SNAKE snake;
    int user_input_value = RIGHT_KEY;
    LinkedList my_snake;
    my_snake.AddNode(Node{coordinate{6, 0}});
    my_snake.AddNode(Node{coordinate{5, 0}});
    my_snake.AddNode(Node{coordinate{4, 0}});
    my_snake.AddNode(Node{coordinate{3, 0}});
    my_snake.AddNode(Node{coordinate{2, 0}});
    my_snake.AddNode(Node{coordinate{1, 0}});
    my_snake.AddNode(Node{coordinate{0, 0}});
    Node *head = my_snake.Get_Head();
    enum DIRECTION snake_direction = XP;
    // Update_UserInput(user_input_value);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int x;
    int y;
    std::thread t(Update_UserInput, std::ref(user_input_value));

    while (true)
    {

        GetConsoleScreenBufferInfo(handle, &csbi);
        x = csbi.dwMaximumWindowSize.X;
        y = csbi.dwMaximumWindowSize.Y;
        switch (user_input_value)
        {
        case RIGHT_KEY:
            if (snake_direction != XN)
            {
                Move_Snake_Right(my_snake, x);
                snake_direction = XP;
            }
            else
            {
                Move_Snake_Left(my_snake, x);
            }
            break;
        case LEFT_KEY:
            if (snake_direction != XP)
            {
                Move_Snake_Left(my_snake, x);
                snake_direction = XN;
            }
            else
            {
                Move_Snake_Right(my_snake, x);
            }

            break;
        case DOWN_KEY:
            if (snake_direction != YP)
            {
                Move_Snake_Down(my_snake, y);
                snake_direction = YN;
            }
            else
            {
                Move_Snake_Up(my_snake, y);
            }
            break;
        case UP_KEY:
            if (snake_direction != YN)
            {
                Move_Snake_Up(my_snake, y);
                snake_direction = YP;
            }
            else
            {
                Move_Snake_Down(my_snake, y);
            }
            break;
        default:
            break;
        }
        Display_Snake(my_snake);
        // my_snake.print_linkedList();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // std::system("cls");
    }
}

inline void SNAKE::Update_UserScore()
{
    user_score++;
}

int main()
{
    // lab controlled code
    SNAKE checkmySNAKE;
    checkmySNAKE.Update_UserScore();
    std::cout << checkmySNAKE.user_score << std::endl;
    checkmySNAKE.Run_Game();
    // implmentaioonn for Update_UserScore is complete

    return 0;
}
