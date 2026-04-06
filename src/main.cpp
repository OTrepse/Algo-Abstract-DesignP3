#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct HVLCSResult {
    int maxValue;
    string subsequence;
};

HVLCSResult solveHVLCS(istream& inputStream) {
    int weightCount;
    inputStream >> weightCount;

    unordered_map<char, int> characterWeights;
    for (int entry = 0; entry < weightCount; entry++) {
        char symbol;
        int weight;
        inputStream >> symbol >> weight;
        characterWeights[symbol] = weight;
    }

    string firstString;
    string secondString;
    inputStream >> firstString >> secondString;

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

    return {scoreTable[firstString.size()][secondString.size()], bestSubsequence};
}

int main() {
    cin.tie(nullptr);

    int mode;
    cout << "Enter 1 for manual input, 2 for single file input, or 3 for benchmark mode: ";
    cin >> mode;

    if (mode == 1) {
        auto startTime = high_resolution_clock::now();
        HVLCSResult result = solveHVLCS(cin);
        auto endTime = high_resolution_clock::now();

        double runtimeMs = duration<double, milli>(endTime - startTime).count();

        cout << result.maxValue << '\n';
        cout << result.subsequence << '\n';
        cout << fixed << setprecision(3);
        cout << "Runtime (ms): " << runtimeMs << '\n';
    }
    else if (mode == 2) {
        string inputFileName;
        cout << "Enter input file name: ";
        cin >> inputFileName;

        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cerr << "Error: could not open input file.\n";
            return 1;
        }

        auto startTime = high_resolution_clock::now();
        HVLCSResult result = solveHVLCS(inputFile);
        auto endTime = high_resolution_clock::now();

        double runtimeMs = duration<double, milli>(endTime - startTime).count();

        cout << result.maxValue << '\n';
        cout << result.subsequence << '\n';
        cout << fixed << setprecision(3);
        cout << "Runtime (ms): " << runtimeMs << '\n';
    }
    else if (mode == 3) {
        int fileCount;
        cout << "Enter number of benchmark files: ";
        cin >> fileCount;

        vector<string> fileNames(fileCount);
        for (int index = 0; index < fileCount; index++) {
            cout << "Enter file " << index + 1 << ": ";
            cin >> fileNames[index];
        }

        cout << fixed << setprecision(3);
        cout << "\nBenchmark Results\n";
        cout << "-----------------\n";

        for (const string& fileName : fileNames) {
            ifstream inputFile(fileName);
            if (!inputFile.is_open()) {
                cout << fileName << " -> Error opening file\n";
                continue;
            }

            auto startTime = high_resolution_clock::now();
            HVLCSResult result = solveHVLCS(inputFile);
            auto endTime = high_resolution_clock::now();

            double runtimeMs = duration<double, milli>(endTime - startTime).count();

            cout << fileName
                 << " -> Value: " << result.maxValue
                 << ", Subsequence: " << result.subsequence
                 << ", Runtime (ms): " << runtimeMs << '\n';
        }
    }
    else {
        cerr << "Error: invalid mode.\n";
        return 1;
    }

    return 0;
}