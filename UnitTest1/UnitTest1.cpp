#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include <vector>
#include "../lab11.4/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

void CreateTestFile(const char* filename, const vector<string>& lines) {
    ofstream fout(filename);
    for (const auto& line : lines) {
        fout << line << endl;
    }
    fout.close();
}

namespace UnitTestForFileProcessing
{
    TEST_CLASS(UnitTestForFileProcessing)
    {
    public:

        TEST_METHOD(TestProcessFile)
        {
            // Arrange
            const char* inputFile = "testF.txt";
            const char* outputFile = "testG.txt";
            string searchString = "Lviv";

            vector<string> inputLines = {
                "Kyiv;Lviv;123",
                "Lviv;Odessa;456",
                "Odessa;Kyiv;789",
                "Lviv;Dnipro;111"
            };

            vector<string> expectedOutputLines = {
                "Kyiv;Lviv;123",
                "Lviv;Odessa;456",
                "Lviv;Dnipro;111",
                "Number of matching lines: 3"
            };

            CreateTestFile(inputFile, inputLines);

            // Act
            ProcessFile(inputFile, outputFile, searchString);

            // Assert
            ifstream fin(outputFile);
            Assert::IsTrue(fin.is_open(), L"Output file could not be opened!");

            string line;
            vector<string> actualOutputLines;
            while (getline(fin, line)) {
                actualOutputLines.push_back(line);
            }
            fin.close();

            Assert::AreEqual(expectedOutputLines.size(), actualOutputLines.size(), L"Output file line count mismatch!");

            for (size_t i = 0; i < expectedOutputLines.size(); i++) {
                Assert::AreEqual(expectedOutputLines[i], actualOutputLines[i], L"Mismatch in file content!");
            }
        }
    };
}

