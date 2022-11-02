#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

int findAllConflicts(int *nQueens, int N)
{
    int *queensPerRow = new int[N]{0};
    int *queensPerD1 = new int[2 * N - 1]{0};
    int *queensPerD2 = new int[2 * N - 1]{0};

    for (int i = 0; i < N; i++) // columns
    {
        queensPerRow[nQueens[i]]++;
        queensPerD1[i - nQueens[i] + N - 1]++;
        queensPerD2[nQueens[i] + i]++;
    }
    int sum = 0;
    // Completed graph --> number of edges = (N*(N-1))/2 = number of conflicts;
    for (int i = 0; i < 2 * N - 1; i++)
    {
        if (i < N)
        {
            sum += (queensPerRow[i] * (queensPerRow[i] - 1)) / 2;
        }
        sum += (queensPerD1[i] * (queensPerD1[i] - 1)) / 2;
        sum += (queensPerD2[i] * (queensPerD2[i] - 1)) / 2;
    }
    delete[] queensPerRow;
    delete[] queensPerD1;
    delete[] queensPerD2;

    return sum;
}

bool hasConflicts(int *nQueens, int N)
{
    return findAllConflicts(nQueens, N) != 0;
}

int *init(int N)
{
    int *nQueens = new int[N];

    int *queensPerRow = new int[N]{0};
    int *queensPerD1 = new int[(2 * N) - 1]{0};
    int *queensPerD2 = new int[(2 * N) - 1]{0};

    std::vector<int> minConfRows;
    int minConflicts = N * N;
    int conf;

    srand(time(0));
    int x = rand() % N;
    nQueens[x] = 0;

    queensPerRow[nQueens[x]]++;
    queensPerD1[x + N - 1]++;
    queensPerD2[x]++;

    for (int i = 0; i < N; i++) // column
    {
        if (i != x)
        {
            minConfRows.clear();
            minConflicts = N * N;
            conf = 0;
            for (int j = 0; j < N; j++) // rows
            {
                conf = queensPerRow[j] + queensPerD1[i - j + N - 1] + queensPerD2[i + j] - 3;

                if (conf < minConflicts)
                {
                    minConflicts = conf;
                    minConfRows.clear();
                    minConfRows.push_back(j);
                }
                else if (conf == minConflicts)
                {
                    minConfRows.push_back(j);
                }
            }

            nQueens[i] = minConfRows[rand() % minConfRows.size()];

            queensPerRow[nQueens[i]]++;
            queensPerD1[i - nQueens[i] + N - 1]++;
            queensPerD2[nQueens[i] + i]++;
        }
    }
    delete[] queensPerRow;
    delete[] queensPerD1;
    delete[] queensPerD2;

    return nQueens;
}

void print(int *nQueens, int N)
{
    for (int i = 0; i < N; i++) // rows
    {
        for (int j = 0; j < N; j++) // columns
        {
            if (nQueens[j] == i)
            {
                std::cout << " * ";
            }
            else
            {
                std::cout << " _ ";
            }
        }
        std::cout << '\n';
    }
}

int getColWithQueenWithMaxConf(int *nQueens, int N)
{
    int *queensPerRow = new int[N]{0};
    int *queensPerD1 = new int[2 * N - 1]{0};
    int *queensPerD2 = new int[2 * N - 1]{0};

    std::vector<int> maxConf;
    int max = 0;
    int conf;

    for (int i = 0; i < N; i++) // columns
    {
        queensPerRow[nQueens[i]]++;
        queensPerD1[i - nQueens[i] + N - 1]++;
        queensPerD2[nQueens[i] + i]++;
    }
    for (int i = 0; i < N; i++) // columns
    {
        conf = queensPerRow[nQueens[i]] + queensPerD1[i - nQueens[i] + N - 1] + queensPerD2[i + nQueens[i]] - 3;
        if (conf > max)
        {
            max = conf;
            maxConf.clear();
            maxConf.push_back(i);
        }
        else if (conf == max)
        {
            maxConf.push_back(i);
        }
    }
    delete[] queensPerRow;
    delete[] queensPerD1;
    delete[] queensPerD2;

    return maxConf[rand() % maxConf.size()];
}

int getRowWithMinConflict(int column, int *nQueens, int N)
{
    int *queensPerRow = new int[N]{0};
    int *queensPerD1 = new int[2 * N - 1]{0};
    int *queensPerD2 = new int[2 * N - 1]{0};

    std::vector<int> minConf;
    int min = N * N;
    int conf;

    for (int i = 0; i < N; i++) // columns
    {
        queensPerRow[nQueens[i]]++;
        queensPerD1[i - nQueens[i] + N - 1]++;
        queensPerD2[nQueens[i] + i]++;
    }
    for (int i = 0; i < N; i++) // rows
    {
        conf = queensPerRow[i] + queensPerD1[column - i + N - 1] + queensPerD2[column + i];
        if (conf < min)
        {
            min = conf;
            minConf.clear();
            minConf.push_back(i);
        }
        else if (conf == min)
        {
            minConf.push_back(i);
        }
    }
    delete[] queensPerRow;
    delete[] queensPerD1;
    delete[] queensPerD2;

    return minConf[rand() % minConf.size()];
}

void solve(int N)
{
    int *nQueens = init(N);

    int iter = 0;
    while (iter++ <= 10 * N && hasConflicts(nQueens, N))
    {
        int col = getColWithQueenWithMaxConf(nQueens, N);
        int row = getRowWithMinConflict(col, nQueens, N);
        nQueens[col] = row;
    }
    if (hasConflicts(nQueens, N))
    {
        delete[] nQueens;
        solve(N);
    }
    else
    {
        if (N <= 20)
        {
            print(nQueens, N);
        }
        delete[] nQueens;
    }
}

int main()
{
    int N;
    std::cout << "N = ";
    std::cin >> N;
    if (N < 4)
    {
        std::cout << "No solution!!!\n";
		return -1;
    }
    else
    {
        auto start = std::chrono::steady_clock::now();
        solve(N);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    return 0;
}