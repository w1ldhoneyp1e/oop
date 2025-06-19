#pragma once

#include <vector>
#include <string>
#include <numeric>

template <typename T>
T ArraySum(const std::vector<T>& arr)
{
	return std::accumulate(arr.begin(), arr.end(), T{});
}
