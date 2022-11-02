#include "board.h"
#include<cmath>
#include<chrono>


int main()
{
    int size;
    std::cout << "Size: ";
    std::cin >> size;
    int n = sqrt(size + 1);
    while(n * n != size + 1)
    {
        std::cout << "Please, input correct size: ";
        std::cin >> size;
        n = sqrt(size + 1);
    }
    int blankIndex;
    std::cout << "\nCorrect BlankIndex: ";
    std::cin >> blankIndex;
    while(blankIndex < -1 || blankIndex > size)
    {
        std::cout << "\nPlease, input correct blankIndex: ";
        std::cin >> blankIndex;
    }
    int input;
    int *m = new int[size+1];
    int i = 0;
    std::cout<<"\nInput vector: ";
    while (i != size+1)
    {
        std::cin >> input;
        m[i] = input;
        i++;
    }
    int blankRow = Board::findRow(m, size+1);
    int countInv = Board::countInversion(m,size+1);
    int part = sqrt(size+1);
    if ((countInv % 2 == 0 && part % 2 == 1) || ((countInv + blankRow) % 2 == 1 && part % 2 == 0))
    {
        Board b(m, size, blankIndex, ' ');
        auto start = std::chrono::steady_clock::now();
        Board::IDA(b, blankIndex);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    else
    {
        std::cout << "The board is unsolvable!\n";
    }

    return 0;
}