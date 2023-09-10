#include <bits/stdc++.h>
using namespace std;

const int N = 26;

/*
Type
0 -> blank
1 -> Ladder bottom
2 -> Snake head
*/

// Abstract class
class Cell
{
public:
    int destination;
    virtual void addDestination(int destination) = 0;
    virtual int getDestination() = 0;
    virtual int getType() = 0;
};

class LadderCell : public Cell
{
public:
    void addDestination(int destination)
    {
        this->destination = destination;
    }
    int getDestination()
    {
        return this->destination;
    }
    int getType()
    {
        return 1;
    }
};

class SnakeCell : public Cell
{
public:
    void addDestination(int destination)
    {
        this->destination = destination;
    }
    int getDestination()
    {
        return this->destination;
    }
    int getType()
    {
        return 2;
    }
};

class NormalCell : public Cell
{
public:
    void addDestination(int destination)
    {
        this->destination = destination;
    }
    int getDestination()
    {
        return this->destination;
    }
    int getType()
    {
        return 0;
    }
};

class Board
{
protected:
    vector<Cell *> matrix;

public:
    Board(int n)
    {
        matrix.resize(n + 1);
        for (int i = 1; i < n; i++)
        {
            matrix[i] = new NormalCell();
        }
    }

    void addLadder(int x, int y)
    { // y > x
        matrix[x] = new LadderCell();
        matrix[x]->addDestination(y);
    }

    void addSnake(int x, int y)
    {
        // x > y
        matrix[x] = new SnakeCell();
        matrix[x]->addDestination(y);
    }

    Cell *getCell(int x)
    {
        return matrix[x];
    }
};

class Dice
{
public:
    int rollDice()
    {
        int face = (rand() % 6) + 1;
        return face;
    }
};

class Player
{
private:
    int position;

public:
    Player()
    {
        position = 1;
    }

    void updatePosition(int position)
    {
        this->position = position;
    }

    int getPosition()
    {
        return position;
    }
};

signed main()
{
    srand(time(0));
    Board *board = new Board(N);

    board->addLadder(2, 12);
    board->addLadder(8, 14);
    board->addLadder(18, 23);

    board->addSnake(22, 1);
    board->addSnake(24, 13);
    board->addSnake(6, 4);

    Player *yash = new Player();
    Player *suyog = new Player();

    Dice *dice = new Dice();

    int chance = 0;

    while (1)
    {
        int playerPosition;
        Cell *finalCell;
        int value = dice->rollDice();

        if (chance == 0)
        {
            playerPosition = yash->getPosition();
            cout << "Yash is on " << playerPosition << ", ";
            cout << "Yash Got " << value << ", ";
            playerPosition += value;
            finalCell = board->getCell(playerPosition);

            if (playerPosition > N-1)
            {
                cout << '\n';
                goto end;
            }

            if (finalCell->getType() == 4 || finalCell->getType() == 2)
            {
                cout << "He moved to " << playerPosition << ", ";
                if (finalCell->getType() == 1)
                {
                    cout << "He Found Ladder, ";
                }
                else
                {
                    cout << "He Found Snake, ";
                }
                playerPosition = finalCell->getDestination();
            }

            cout << "He moved to " << playerPosition << "\n";
            yash->updatePosition(playerPosition);
        }
        else
        {
            playerPosition = suyog->getPosition();
            cout << "Suyog is on " << playerPosition << ", ";
            cout << "Suyog Got " << value << ", ";
            playerPosition += value;
            finalCell = board->getCell(playerPosition);

            if (playerPosition > N-1)
            {
                cout << '\n';
                goto end;
            }

            if (finalCell->getType() == 1 || finalCell->getType() == 2)
            {
                cout << "He moved to " << playerPosition << ", ";
                if (finalCell->getType() == 1)
                {
                    cout << "He Found Ladder, ";
                }
                else
                {
                    cout << "He Found Snake, ";
                }
                playerPosition = finalCell->getDestination();
            }
            cout << "He moved to " << playerPosition << "\n";
            suyog->updatePosition(playerPosition);
        }

        if (yash->getPosition() == N - 1)
        {
            cout << "YAAyy, Yash WON!!\n";
            break;
        }
        if (suyog->getPosition() == N - 1)
        {
            cout << "Hurray, Suyog WON!!\n";
            break;
        }

    end:
        chance ^= 1;
    }
    return 0;
}