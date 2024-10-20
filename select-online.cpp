#include "select-online.hpp"

// Find the approximate median value.
template <typename T, size_t SmallArraySize, class ForwardIt>
T median_of_medians(ForwardIt first, ForwardIt last)
{
    auto const size{std::distance(first, last)};
    if (size <= SmallArraySize)
    {
        std::array<T, SmallArraySize> v;
        std::copy(first, last, std::begin(v));
        std::sort(std::begin(v), std::begin(v) + size);
        size_t const median_index{static_cast<size_t>(size / 2)};
        return v.at(median_index);
    }
    std::vector<T> medians;
    for (auto it{first}; it < last; it += SmallArraySize)
    {
        auto const sub_last{std::min(it + SmallArraySize, last)};
        medians.push_back(median_of_medians<T, SmallArraySize>(it, sub_last));
    }
    return median_of_medians<T, SmallArraySize>(medians.begin(), medians.end());
}

template <typename T, class ForwardIt>
T custom_selection_algorithm(ForwardIt first, ForwardIt last, size_t i)
{
    auto const size{std::distance(first, last)};
    // Check if the size is large or equal to the order statistics index.
    if (size < i)
    {
        throw std::out_of_range{"The order statistics is out of range."};
    }
    // Find the approximate median value.
    auto const pivot{median_of_medians<T, 5>(first, last)};
    // Partition the elements around the pivot.
    auto const partition_it{
        std::partition(first, last, [pivot](T const n) { return n < pivot; })};
    // Calculate the number of elements less than the pivot.
    auto const num_less_than_pivot{std::distance(first, partition_it)};
    // Check if the pivot is the order statistics.
    if (num_less_than_pivot == i)
    {
        return pivot;
    }
    // Check if the pivot is less than the order statistics.
    else if (num_less_than_pivot < i)
    {
        return custom_selection_algorithm<T>(partition_it, last,
                                             i - num_less_than_pivot);
    }
    // Check if the pivot is greater than the order statistics.
    else
    {
        return custom_selection_algorithm<T>(first, partition_it, i);
    }
}

template <typename T, class ForwardIt>
T custom_selection(ForwardIt first, ForwardIt last, size_t i)
{
    // Copy the elements to a vector.
    std::vector<T> v;
    v.reserve(std::distance(first, last));
    std::copy(first, last, std::back_inserter(v));
    // Call the custom selection algorithm.
    return custom_selection_algorithm<T>(v.begin(), v.end(), i);
}

template <typename T, class ForwardIt>
T sorting_selection(ForwardIt first, ForwardIt last, size_t i)
{
    auto const size{std::distance(first, last)};
    if (size < i)
    {
        throw std::out_of_range{"The order statistics is out of range."};
    }
    std::vector<T> v;
    v.reserve(size);
    std::copy(first, last, std::back_inserter(v));
    std::sort(v.begin(), v.end());
    return v.at(i);
}

int online_selection(std::vector<int> const v)
{
    std::copy(std::begin(v), std::end(v),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    auto const order_statistics_index{v.size() / 2};

    auto const median_of_medians_selection_result{custom_selection<int>(
        std::begin(v), std::end(v), order_statistics_index)};
    auto const sorting_selection_result{sorting_selection<int>(
        std::begin(v), std::end(v), order_statistics_index)};
}