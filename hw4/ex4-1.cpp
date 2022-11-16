#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>

int eval(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'X')
            {
                return 1;
            }
            else if (board[i][0] == 'O')
            {
                return -1;
            }
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == 'X')
            {
                return 1;
            }
            else if (board[0][i] == 'O')
            {
                return -1;
            }
        }
    }
    if ((board[0][2] == board[1][1] && board[1][1] == board[2][0]) || (board[0][0] == board[1][1] && board[1][1] == board[2][2]))
    {
        if (board[1][1] == 'X')
        {
            return 1;
        }
        else if (board[1][1] == 'O')
        {
            return -1;
        }
    }
    return 0;
}

bool hasNoEmpty(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                return false;
            }
        }
    }
    return true;
}

struct Position
{
    int x;
    int y;
};

void printBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<Position> getAllPositions(char board[3][3])
{
    std::vector<Position> pos;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                pos.push_back({i, j});
            }
        }
    }
    return pos;
}

int miniMaxAlphaBeta(char board[3][3], int depth, char player, int alpha, int beta)
{
    int result = eval(board);
    int current;
    if ((result == 1) || (result == -1) || (result == 0 && hasNoEmpty(board)))
    {
        return result;
    }
    if (player == 'X')
    {
        int v = -1000000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = 'X';
                    current = miniMaxAlphaBeta(board, depth + 1, 'O', alpha, beta); // minValue
                    board[i][j] = '_';
                    v = std::max(current, v);
                    alpha = std::max(alpha, v);

                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return v;
    }
    else
    {
        int v = 1000000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = 'O';
                    current = miniMaxAlphaBeta(board, depth + 1, 'X', alpha, beta); // maxValue
                    board[i][j] = '_';
                    v = std::min(current, v);
                    beta = std::min(beta, v);

                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return v;
    }
}

Position getBestPosition(char board[3][3], char player)
{
    Position bestPos{-1, -1};
    int v;
    char oponent;
    if (player == 'X')
    {
        v = -10000;
        oponent = 'O';
    }
    else if (player == 'O')
    {
        v = 10000;
        oponent = 'X';
    }
    std::vector<Position> p = getAllPositions(board);
    for (int i = 0; i < p.size(); i++)
    {
        board[p[i].x][p[i].y] = player;
        int saver = miniMaxAlphaBeta(board, 0, oponent, -10000, 10000); // get all under root and then get max of them in 'v'!
        board[p[i].x][p[i].y] = '_';
        if (player == 'X' && saver > v)
        {
            bestPos.x = p[i].x;
            bestPos.y = p[i].y;
            v = saver;
        }
        else if (player == 'O' && saver < v)
        {
            bestPos.x = p[i].x;
            bestPos.y = p[i].y;
            v = saver;
        }
    }
    return bestPos;
}

bool canPut(char board[3][3], Position put)
{
    return board[put.x][put.y] == '_' && put.x < 3 && put.y < 3 && put.x >= 0 && put.y >= 0;
}

void printResult(char board[3][3])
{
    int utility = eval(board);
    if (utility == -1)
    {
        std::cout << "You win!\n";
    }
    else if (utility == 1)
    {
        std::cout << "You lost!\n";
    }
    else
    {
        std::cout << "There is no winner!\n";
    }
}

void playComputers()
{
    char board[3][3] =
        {
            {'_', '_', '_'},
            {'_', '_', '_'},
            {'_', '_', '_'}};

    auto start = std::chrono::steady_clock::now();
    board[std::rand() % 2][std::rand() % 2] = 'X';
    printBoard(board);
    while (!hasNoEmpty(board) && (eval(board) != 1 && eval(board) != -1))
    {
        Position player = getBestPosition(board, 'O');
        board[player.x][player.y] = 'O';
        printBoard(board);

        Position comp = getBestPosition(board, 'X');
        board[comp.x][comp.y] = 'X';
        printBoard(board);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    printResult(board);
}

void playWithPlayers()
{
    std::srand(time(0));
    char board[3][3] =
        {
            {'_', '_', '_'},
            {'_', '_', '_'},
            {'_', '_', '_'}};

    int x;
    std::cout << "Press (1) to start computer and (2) to start player: ";
    std::cin >> x;
    if (x == 1)
    {
        board[std::rand() % 2][std::rand() % 2] = 'X';
        printBoard(board);
    }
    int row;
    int col;
    while (!hasNoEmpty(board) && (eval(board) != 1 && eval(board) != -1))
    {
        do
        {
            std::cout << "Row and column: ";
            std::cin >> row >> col;
            std::cout << '\n';
        } while (!canPut(board, {row, col}));

        board[row][col] = 'O';
        printBoard(board);

        Position comp = getBestPosition(board, 'X');
        board[comp.x][comp.y] = 'X';
        printBoard(board);
    }
    printResult(board);
}

int main()
{
    // Computer - with X; Player - with O;
    // Computer-1; Player-2;

    playComputers();

    // playWithPlayers();

    return 0;
}
