#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    cin.tie(nullptr);

    int mode;
    cout << "Enter 1 for manual input or 2 for file input:  ";
    cin >> mode;

    istream* inputStream = &cin;
    ifstream inputFile;

    if (mode == 2) {
        string inputFileName;
        cout << "Enter input file name:  ";
        cin >> inputFileName;
        inputFile.open(inputFileName);

        if (!inputFile.is_open()) {
            cerr << "Error: could not open input file.\n";
            return 1;
        }

        inputStream = &inputFile;
    }

    int weightCount;
    (*inputStream) >> weightCount;

    unordered_map<char, int> characterWeights;
    for (int entry = 0; entry < weightCount; entry++) {
        char symbol;
        int weight;
        (*inputStream) >> symbol >> weight;
        characterWeights[symbol] = weight;
    }

    string firstString;
    string secondString;
    (*inputStream) >> firstString >> secondString;

    int firstLength = firstString.size();
    int secondLength = secondString.size();
    vector<vector<int>> scoreTable(firstLength + 1, vector<int>(secondLength + 1, 0));

    for (int i = 1; i <= firstLength; i++) {
        for (int j = 1; j <= secondLength; j++) {
            scoreTable[i][j] = max(scoreTable[i - 1][j], scoreTable[i][j - 1]);
            if (firstString[i - 1] == secondString[j - 1]) {
                auto it = characterWeights.find(firstString[i - 1]);
                int letterWeight = (it != characterWeights.end()) ? it->second : 0;
                scoreTable[i][j] = max(scoreTable[i][j], scoreTable[i - 1][j - 1] + letterWeight);
            }
        }
    }

    string bestSubsequence;
    int i = firstString.size();
    int j = secondString.size();

    while (i > 0 && j > 0) {
        if (firstString[i - 1] == secondString[j - 1]) {
            auto it = characterWeights.find(firstString[i - 1]);
            int letterWeight = (it != characterWeights.end()) ? it->second : 0;
            if (scoreTable[i][j] == scoreTable[i - 1][j - 1] + letterWeight) {
                bestSubsequence.push_back(firstString[i - 1]);
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

    reverse(bestSubsequence.begin(), bestSubsequence.end());

    cout << scoreTable[firstString.size()][secondString.size()] << '\n';
    cout << bestSubsequence << '\n';

    return 0;
}