#include <iostream>
#include <vector>

class Board
{
private:
    int *m;
    int size;
    int blankIndex;
    int euristic;
    char d;

    int *createGoalMat(int blankIndex) const;

    int manhattanDist(int blankIndex) const;

    std::vector<Board> generateBoards(int blankIndex) const;

    static bool IDAhelper(Board first, int threshold, int blankIndex, int g, std::vector<char> &v, std::vector<char> p);

public:
    Board(int *mm, int size, int corrBlankIndex, char d);
    Board(const Board &other);
    ~Board();
    // void print() const;
    static int countInversion(int *v, int size);
    static int findRow(int *m, int size);

    static void IDA(Board first, int blankIndex);
};
