#pragma once
#include <vector>
bool tryAdd(int m,
            const std::vector<std::vector<int>>& A,
            const std::vector<double>& costs,
            std::vector<int>& sol);
bool tryRemove(int m,
               const std::vector<std::vector<int>>& A,
               const std::vector<double>& costs,
               std::vector<int>& sol);
bool trySwap(int m,
             const std::vector<std::vector<int>>& A,
             const std::vector<double>& costs,
             std::vector<int>& sol);
