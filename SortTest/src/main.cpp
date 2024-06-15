#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <concepts>

#include <thread>
#include <chrono>

template <class T>
concept is_integral_or_floating_point_v = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <class T>
    requires is_integral_or_floating_point_v<T>
std::vector<T> generate_random_list(int const numItems, T const lowerBound, T const upperBound)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    const auto range = upperBound - lowerBound;
    std::vector<T> randomList(numItems);
    for (auto i = 0; i < numItems; ++i)
    {
        randomList[i] = lowerBound + static_cast<T>(gen() % range);
    }

    return randomList;
}

template <class T>
void comb_sort(std::vector<T> &v)
{
    const auto n = v.size();
    int h = n;
    bool has_swap = false;
    while (true)
    {
        h = std::max((int)(h / 1.3), 1);
        for (int i = 0; i < n - h; ++i)
        {
            const auto lhs = v[i];
            const auto rhs = v[i + h];

            if (lhs > rhs)
            {
                has_swap = true;
                std::swap(v[i], v[i + h]);
            }
        }

        if (!has_swap && h == 1)
        {
            break;
        }

        has_swap = false;
    }
}

int main()
{
    // リストは const で評価しません。
    auto list = generate_random_list(50, 0, 1000);
    comb_sort(list);
    for (auto &elm : list)
    {
        std::cout << elm << " ";
    }
    std::puts("");
    return 0;
}