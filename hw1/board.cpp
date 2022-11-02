#include "board.h"
#include <cmath>

int *Board::createGoalMat(int blankIndex) const
{
    int *b = new int[this->size + 1];
    if (blankIndex == -1)
    {
        blankIndex = this->size;
    }
    int i = 0;
    int k = 1;
    while (i <= this->size)
    {
        if (blankIndex == 0)
        {
            b[i] = 0;
        }
        else
        {
            b[i] = k;
            k++;
        }
        blankIndex--;
        i++;
    }
    return b;
}

int Board::manhattanDist(int blankIndex) const
{
    int *goal = createGoalMat(blankIndex);

    int *currX = new int[this->size + 1];
    int *currY = new int[this->size + 1];

    int *corrX = new int[this->size + 1];
    int *corrY = new int[this->size + 1];

    int part = sqrt(this->size + 1);

    for (int i = 0; i <= this->size; i++)
    {
        currX[this->m[i]] = i / part;
        currY[this->m[i]] = i % part;

        corrX[goal[i]] = i / part;
        corrY[goal[i]] = i % part;
    }
    int manh = 0;
    for (int i = 1; i <= this->size; i++)
    {
        manh += abs(corrX[i] - currX[i]) + abs(corrY[i] - currY[i]);
    }
    delete[] currX;
    delete[] currY;
    delete[] corrX;
    delete[] corrY;
    delete [] goal;
    return manh;
}

std::vector<Board> Board::generateBoards(int blankInd) const
{
    std::vector<Board> boards;
    int part = sqrt(this->size + 1);

    if (this->blankIndex % part != 0)
    {
        int *saver = new int[this->size + 1];
        for (int i = 0; i < this->size + 1; i++)
        {
            saver[i] = this->m[i];
        }
        std::swap(saver[this->blankIndex], saver[this->blankIndex - 1]);
        Board b1(saver, this->size, blankInd, 'r');
        boards.push_back(b1);
        delete[] saver;
    }
    if (this->blankIndex % part != part - 1)
    {
        int *saver = new int[this->size + 1];
        for (int i = 0; i < this->size + 1; i++)
        {
            saver[i] = this->m[i];
        }
        std::swap(saver[this->blankIndex], saver[this->blankIndex + 1]);
        Board b2(saver, this->size, blankInd, 'l');
        boards.push_back(b2);        
        delete [] saver;
    }
    if (this->blankIndex / part != 0)
    {
        int *saver = new int[this->size + 1];
        for (int i = 0; i < this->size + 1; i++)
        {
            saver[i] = this->m[i];
        }
        std::swap(saver[this->blankIndex], saver[this->blankIndex - part]);
        Board b3(saver, this->size, blankInd, 'd');
        boards.push_back(b3);
        delete[] saver;
    }
    if (this->blankIndex / part < part - 1)
    {
        int *saver = new int[this->size + 1];
        for (int i = 0; i < this->size + 1; i++)
        {
            saver[i] = this->m[i];
        }
        std::swap(saver[this->blankIndex], saver[this->blankIndex + part]);
        Board b4(saver, this->size, blankInd, 'u');
        boards.push_back(b4);
        delete[] saver;
    }
    
    return boards;
}

bool Board::IDAhelper(Board first, int threshold, int blankIndex, int g, std::vector<char> &v, std::vector<char> p)
{
    bool find = false;
    std::vector<Board> neighs = first.generateBoards(blankIndex);
    p.push_back(first.d);
    if (first.euristic == 0)
    {
        v = p;
        std::cout << g + first.euristic << '\n';
        for (char i : v)
        {
            if (i == 'l')
                std::cout << "left\n";
            if (i == 'r')
                std::cout << "right\n";
            if (i == 'u')
                std::cout << "up\n";
            if (i == 'd')
                std::cout << "down\n";
        }
        return true;
    }
    if (neighs.empty() || threshold < g + first.euristic)
    {
        return false;
    }
    for (Board x : neighs)
    {
        find = find || IDAhelper(x, threshold, blankIndex, g + 1, v, p);
    }
    return find;
}

Board::Board(int *mm, int size, int corrBlankIndex, char d)
{
    this->size = size;
    this->m = new int[size + 1];
    for (int i = 0; i < size + 1; i++)
    {
        this->m[i] = mm[i];
                if (this->m[i] == 0)
        {
            this->blankIndex = i;
        }
    }
    this->euristic = manhattanDist(corrBlankIndex);
    this->d = d;
}

Board::Board(const Board& other)
{
    this->size = other.size;
    this->m = new int[this->size + 1];
    for (int i = 0; i < this->size + 1; i++)
    {
        this->m[i] = other.m[i];
    }
    this->blankIndex = other.blankIndex;
    this->euristic = other.euristic;
    this->d = other.d;
}

Board::~Board()
{
    delete[] this->m;
}

/*void Board::print() const
{
    int parts = sqrt(this->size + 1);

    for (int i = 0; i < this->size + 1; i++)
    {
        std::cout << this->m[i] << ' ';
        if (i % parts == parts - 1)
        {
            std::cout << '\n';
        }
    }
    std::cout << "Size: " << this->size;
    std::cout << "\nBlankIndex: " << this->blankIndex;
    std::cout << "\nEuristic: " << this->euristic;
    std::cout<<"\nD: "<<this->d<<'\n';
}*/

int Board::countInversion(int *v, int size)
{
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (v[i] > v[j] && v[i] != 0 && v[j] != 0)
            {
                counter++;
            }
        }
    }
    return counter;
}

int Board::findRow(int *m, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (m[i] == 0)
        {
            return i / sqrt(size);
        }
    }
    return -1;
}

void Board::IDA(Board first, int blankIndex)
{
    std::vector<char> v;
    int threshold = first.euristic - 1;
    bool helper = false;
    while (!helper)
    {
        v.clear();
        helper = Board::IDAhelper(first, threshold++, blankIndex, 0, v, {});
    }
}


