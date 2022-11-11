#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <utility>
#include <chrono>

int N;
int M;
int sizeOfPopulation = 10;

struct Item
{
    int weight;
    int value;
};

// std::vector<Item> items{{7, 5}, {2, 4}, {1, 7}, {9, 2}};
// std::vector<Item> items{{90, 150}, {130, 35}, {1530, 200}, {500, 160}, {150, 60}, {680, 45}, {270, 60}, {390, 40}, {230, 30}, {520, 10}, {110, 70}};
// std::vector<Item> items{{5, 10}, {20, 28}, {31, 5}, {4, 10}, {7, 13}, {9, 81}, {11, 52}, {22, 17}, {1, 7}, {2, 6}, {53, 3}, {70, 32}, {13, 41}, {8, 5}, {101, 1}, {85, 4}};
// std::vector<Item> items{{10, 60}, {20, 100}, {30, 120}};//from internet 220solution
// std::vector<Item> items{{90, 150}, {130, 35}, {1530, 200}, {500, 160}, {150, 60}, {680, 45}, {270, 60}, {390, 40}, {230, 30}, {520, 10}, {110, 70}, {320, 30}, {240, 15}, {480, 10}, {730, 40}, {420, 70}, {430, 75}, {220, 80}, {70, 20}, {180, 12}, {40, 50}, {300, 10}, {900, 1}, {2000, 150}};
std::vector<Item> items;
int findFitness(std::vector<bool> chrom)
{
    int weightKnapsack = 0;
    int fitness = 0;
    for (int i = 0; i < N; i++)
    {
        fitness += chrom[i] * items[i].value;
        weightKnapsack += chrom[i] * items[i].weight;
    }
    if (weightKnapsack > M)
    {
        fitness = 0;
    }
    return fitness;
}

struct Chromosome
{
    std::vector<bool> chrom;
    int fitness;

    Chromosome() = default;
    Chromosome(std::vector<bool> chrom)
    {
        this->chrom = chrom;
        this->fitness = findFitness(chrom);
    }
    void print() const
    {
        for (int i = 0; i < chrom.size(); i++)
        {
            std::cout << chrom[i] << ' ';
        }
        std::cout << "\nFitness: " << fitness << '\n';
    }
    bool operator==(const Chromosome &other) const
    {
        return (this->chrom == other.chrom) && (this->fitness == other.fitness);
    }

    void swapp(int index1, int index2)
    {
        std::swap(chrom[index1], chrom[index2]);
        this->fitness = findFitness(chrom);
    }
};

struct greater
{
    bool operator()(Chromosome const &l, Chromosome const &r) const { return l.fitness > r.fitness; }
};

Chromosome generateChromosome()
{
    std::vector<bool> chrom;
    for (int i = 0; i < N; i++)
    {
        chrom.push_back(std::rand() % 2);
    }
    return Chromosome(chrom);
}

std::vector<Chromosome> gen_init_pop()
{
    std::vector<Chromosome> population;
    if (sizeOfPopulation > pow(2, N))
    {
        std::cout << "SizeOfPopulation > 2^N\n";
        return population;
    }
    while (population.size() != sizeOfPopulation)
    {
        Chromosome saver = generateChromosome();
        if (!std::count(population.begin(), population.end(), saver))
        {
            population.push_back(saver);
        }
    }
    return population;
}

/*std::pair<Chromosome, Chromosome> selection(std::vector<Chromosome> all)
{
    std::pair<Chromosome, Chromosome> parents;
    parents.first = all[std::rand() % N];
    parents.second = all[std::rand() % N];
    return parents;
}*/
std::pair<Chromosome, Chromosome> selection(std::vector<Chromosome> all)
{
    std::pair<Chromosome, Chromosome> parents;
    std::random_shuffle(std::begin(all), std::end(all));
    if (all.size() == 2 || all.size() == 3)
    {
        parents.first = all[0];
        parents.second = all[1];
    }
    else
    {
        if (all[0].fitness > all[1].fitness)
        {
            parents.first = all[0];
        }
        else
        {
            parents.first = all[1];
        }
        if (all[2].fitness > all[3].fitness)
        {
            parents.second = all[2];
        }
        else
        {
            parents.second = all[3];
        }
    }
    return parents;
}

std::pair<Chromosome, Chromosome> crossover(const Chromosome &p1, const Chromosome &p2)
{
    std::vector<bool> c1;
    std::vector<bool> c2;
    int index = std::rand() % (N - 1) + 1; //!=0
    for (int i = 0; i < index; i++)
    {
        c1.push_back(p1.chrom[i]);
        c2.push_back(p2.chrom[i]);
    }
    for (int i = index; i < N; i++)
    {
        c1.push_back(p2.chrom[i]);
        c2.push_back(p1.chrom[i]);
    }
    return {Chromosome(c1), Chromosome(c2)};
}

std::pair<Chromosome, Chromosome> mutation(Chromosome p1, Chromosome p2)
{
    std::pair<Chromosome, Chromosome> children = crossover(p1, p2);
    int index1;
    int index2;
    do
    {
        index1 = std::rand() % N;
        index2 = std::rand() % N;
    } while (index1 == index2);

    int fitnessC1 = children.first.fitness;
    int fitnessC2 = children.second.fitness;

    children.first.swapp(index1, index2);
    if (children.first.fitness < fitnessC1)
    {
        children.first.swapp(index1, index2);
    }

    children.second.swapp(index1, index2);
    if (children.second.fitness < fitnessC2)
    {
        children.second.swapp(index1, index2);
    }
    return children;
}

int main()
{
    std::cout << "M = ";
    std::cin >> M;
    std::cout << "N = ";
    std::cin >> N;

    for(int i = 0; i < N; i++)
    {
        int mi;
        int ci;
        std::cin>>mi;//weight
        std::cin>>ci;//value
        items.push_back({mi, ci});
    }

    std::srand(time(0));
    auto start = std::chrono::steady_clock::now();

    std::vector<Chromosome> pop = gen_init_pop();

    int t = 0;
    while (t < 1000)
    {
        std::vector<Chromosome> saver;
        std::pair<Chromosome, Chromosome> parents = selection(pop);
        std::pair<Chromosome, Chromosome> children = mutation(parents.first, parents.second);

        if (!std::count(pop.begin(), pop.end(), children.first))
        {
            pop.push_back(children.first);
        }
        if (!std::count(pop.begin(), pop.end(), children.second))
        {
            pop.push_back(children.second);
        }

        std::sort(pop.begin(), pop.end(), greater{});

        int i = 0;
        while (saver.size() != sizeOfPopulation)
        {
            if (!std::count(saver.begin(), saver.end(), pop[i]))
            {
                saver.push_back(pop[i]);
            }
            i++;
        }
        pop = saver;
        t++;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    pop[0].print();

    return 0;
}