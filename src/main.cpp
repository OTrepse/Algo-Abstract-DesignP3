#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<char, int> readCharacterWeights(int countEntries) {
    unordered_map<char, int> weights;
    for (int entry = 0; entry < countEntries; entry++) {
        char symbol;
        int weight;
        cin >> symbol >> weight;
        weights[symbol] = weight;
    }
    return weights;
}

int getCharacterWeight(char symbol, const unordered_map<char, int>& weights) {
    auto it = weights.find(symbol);
    return it != weights.end() ? it->second : 0;
}

vector<vector<int>> computeWeightedLCS(const string& firstString,
                                       const string& secondString,
                                       const unordered_map<char, int>& weights) {
    int firstLength = firstString.size();
    int secondLength = secondString.size();
    vector<vector<int>> scoreTable(firstLength + 1, vector<int>(secondLength + 1, 0));

    for (int i = 1; i <= firstLength; i++) {
        for (int j = 1; j <= secondLength; j++) {
            scoreTable[i][j] = max(scoreTable[i - 1][j], scoreTable[i][j - 1]);
            if (firstString[i - 1] == secondString[j - 1]) {
                int letterWeight = getCharacterWeight(firstString[i - 1], weights);
                scoreTable[i][j] = max(scoreTable[i][j], scoreTable[i - 1][j - 1] + letterWeight);
            }
        }
    }

    return scoreTable;
}

string reconstructWeightedLCS(const string& firstString,
                              const string& secondString,
                              const unordered_map<char, int>& weights,
                              const vector<vector<int>>& scoreTable) {
    string subsequence;
    int i = firstString.size();
    int j = secondString.size();

    while (i > 0 && j > 0) {
        if (firstString[i - 1] == secondString[j - 1]) {
            int letterWeight = getCharacterWeight(firstString[i - 1], weights);
            if (scoreTable[i][j] == scoreTable[i - 1][j - 1] + letterWeight) {
                subsequence.push_back(firstString[i - 1]);
                i--;
                j--;
                continue;
            }
        }

        if (scoreTable[i][j] == scoreTable[i - 1][j]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(subsequence.begin(), subsequence.end());
    return subsequence;
}

int main() {
    int weightCount;
    cin >> weightCount;

    unordered_map<char, int> characterWeights = readCharacterWeights(weightCount);
    string firstString;
    string secondString;
    cin >> firstString >> secondString;

    vector<vector<int>> scoreTable = computeWeightedLCS(firstString, secondString, characterWeights);
    string bestSubsequence = reconstructWeightedLCS(firstString, secondString, characterWeights, scoreTable);

    cout << scoreTable[firstString.size()][secondString.size()] << endl;
    cout << bestSubsequence << endl;

    return 0;
}