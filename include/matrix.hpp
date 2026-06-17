#pragma once
#include <string>
#include <vector>
#include <utility>

std::pair<int, int> bestRectangle(int length);

std::vector<int> generateKey(int r, int c);

std::vector<char> encrypt(const std::string& plain,
                          const std::vector<int>& key, int r, int c,
                          int dr, int dc,
                          int& outR, int& outC);

std::string decrypt(std::vector<char>& matrix, int R, int C,
                    const std::vector<int>& key, int r, int c,
                    int dr, int dc, int originalLength);