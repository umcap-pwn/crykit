#include "matrix.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>


std::pair<int, int> bestRectangle(int length) {
    int bestR = 1, bestC = length;
    int bestDiff = std::abs(bestR - bestC);
    for (int r = 1; r * r <= length + 10; ++r) {
        int c = (length + r - 1) / r;
        if (r * c >= length && std::abs(r - c) < bestDiff) {
            bestDiff = std::abs(r - c);
            bestR = r;
            bestC = c;
        }
    }
    return {bestR, bestC};
}

std::vector<int> generateKey(int r, int c) {
    std::vector<int> key(r * c);
    std::iota(key.begin(), key.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(key.begin(), key.end(), g);
    return key;
}


static std::vector<std::pair<int,int>> buildLocalOrder(const std::vector<int>& key,
                                                       int r, int c, int dr, int dc) {
    std::vector<int> order(key.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(),
              [&](int a, int b) { return key[a] < key[b]; });

    std::vector<std::pair<int,int>> localOrder(key.size());
    for (std::size_t k = 0; k < order.size(); ++k) {
        int idx = order[k];
        int baseRow = idx / c;
        int baseCol = idx % c;
        localOrder[k] = { (baseRow + dr) % r, (baseCol + dc) % c };
    }
    return localOrder;
}


static void applyBlockEncrypt(std::vector<char>& matrix, int R, int C,
                              int startRow, int startCol,
                              const std::vector<std::pair<int,int>>& localOrder,
                              int r, int c) {
    std::vector<char> buffer(r * c);

    for (int k = 0; k < r * c; ++k) {
        int lr = localOrder[k].first;
        int lc = localOrder[k].second;
        int gr = (startRow + lr) % R;
        int gc = (startCol + lc) % C;
        buffer[k] = matrix[gr * C + gc];
    }

    for (int lr = 0; lr < r; ++lr) {
        for (int lc = 0; lc < c; ++lc) {
            int gr = (startRow + lr) % R;
            int gc = (startCol + lc) % C;
            matrix[gr * C + gc] = buffer[lr * c + lc];
        }
    }
}


static void applyBlockDecrypt(std::vector<char>& matrix, int R, int C,
                              int startRow, int startCol,
                              const std::vector<std::pair<int,int>>& localOrder,
                              int r, int c) {
    std::vector<char> buffer(r * c);
    for (int lr = 0; lr < r; ++lr) {
        for (int lc = 0; lc < c; ++lc) {
            int gr = (startRow + lr) % R;
            int gc = (startCol + lc) % C;
            buffer[lr * c + lc] = matrix[gr * C + gc];
        }
    }
    
    for (int k = 0; k < r * c; ++k) {
        int lr = localOrder[k].first;
        int lc = localOrder[k].second;
        int gr = (startRow + lr) % R;
        int gc = (startCol + lc) % C;
        matrix[gr * C + gc] = buffer[k];
    }
}

std::vector<char> encrypt(const std::string& plain,
                          const std::vector<int>& key, int r, int c,
                          int dr, int dc,
                          int& outR, int& outC) {
    int L = plain.size();
    auto [R, C] = bestRectangle(L);
    outR = R; outC = C;

    std::vector<char> matrix(R * C, '\0');
    std::copy(plain.begin(), plain.end(), matrix.begin());

    auto localOrder = buildLocalOrder(key, r, c, dr, dc);


    for (int bi = 0; bi < R; bi += r) {
        for (int bj = 0; bj < C; bj += c) {
            applyBlockEncrypt(matrix, R, C, bi, bj, localOrder, r, c);
        }
    }
    return matrix;
}

std::string decrypt(std::vector<char>& matrix, int R, int C,
                    const std::vector<int>& key, int r, int c,
                    int dr, int dc, int originalLength) {
    auto localOrder = buildLocalOrder(key, r, c, dr, dc);


    std::vector<std::pair<int,int>> blocks;
    for (int bi = 0; bi < R; bi += r)
        for (int bj = 0; bj < C; bj += c)
            blocks.emplace_back(bi, bj);

    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
        applyBlockDecrypt(matrix, R, C, it->first, it->second, localOrder, r, c);
    }

    return std::string(matrix.begin(), matrix.begin() + originalLength);
}