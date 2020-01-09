#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <algorithm>

bool is_this_prime_number(const int &);
void create_prime_map(std::multimap<int, int> &, std::vector<int> &, const int &);
void generate_N_numbers_in_the_vector(std::vector<int> &, int &, const int &);
void check_vector_elements(std::vector<int> &, std::multimap<int, int> &);
void print(std::multimap<int,int>&);


int main()
{
    int M, N;
    std::cout << "Generate N values from 0 to M ";
    std::cin>>N >> M;
    std::vector<int> vec;
    std::multimap<int, int> mmap;
    generate_N_numbers_in_the_vector(vec, M, N);
    check_vector_elements(vec, mmap);
    std::cout<<"\n Prime random numbers, where prime is a divisor of values: \n";
    print(mmap);


    return 0;
}

bool is_this_prime_number(const int &number)
{
    if (number < 2)
        return false;
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

void generate_N_numbers_in_the_vector(std::vector<int> &vec, int &M, const int &N)
{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> distribution(0, M);
    vec.resize(N);

    std::generate(vec.begin(), vec.end(), [&]() { return distribution(gen); });
}

void check_vector_elements(std::vector<int> &vec, std::multimap<int, int> &mmap)
{
    
    std::sort(vec.begin(), vec.end());
    auto last =  std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    int vector_size = vec.size();


    for (int i = 0; i < vector_size; i++)
    {

        auto search = mmap.find(i);
        if (search == mmap.end() )
        {
            if(is_this_prime_number(vec[i]))
            create_prime_map(mmap, vec, vec[i]);
        }
      
    }
}

void create_prime_map(std::multimap<int, int> &mmap, std::vector<int> &vec, const int &prime_number)
{

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] % prime_number == 0)
            mmap.emplace(prime_number, vec[i]);
    }

}

void print(std::multimap<int,int>&mmap)
{
    auto start = std::begin(mmap);

    while(start != std::end(mmap))
    {
        auto finish = mmap.upper_bound(start ->first);

        std::cout<<start->first << " = { ";
        std::for_each(start, finish, [](const auto& i){std::cout<< i.second << " ,";});
        std::cout<<'\b' <<  "}" << std::endl;
        start = finish;
    }
}