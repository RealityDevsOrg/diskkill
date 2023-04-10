#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

std::string generateRandomString(int length)
{
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string randomString = "";
    int charactersLength = characters.length();

    srand(time(0)); // Set the random seed to the current time

    for (int i = 0; i < length; i++)
    {
        randomString += characters[rand() % charactersLength];
    }

    return randomString;
}

void writeRandomFile(int n, const std::string& dirPath)
{
    std::string randomString = generateRandomString(n);
    std::string fileName = dirPath + "/." + generateRandomString(10);

    std::ofstream fileStream(fileName);
    if (!fileStream)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    fileStream << randomString;
    fileStream.close();

    if (std::remove(fileName.c_str()) != 0)
    {
        std::cout << "Error removing file" << std::endl;
        return;
    }
}

int main(int argc, char *argv[])
{
    const std::string dirPath = argc > 1 ? argv[1] : ".";
    const int n = argc > 2 ? std::stoi(argv[2]) : 100;

    long long totalBytes = 0;
    const int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; i++)
    {
        threads.emplace_back([n, &dirPath, &totalBytes] {
            while (true)
            {
                writeRandomFile(n, dirPath);
                totalBytes += n;
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "Total of " << totalBytes << " bytes written" << std::endl;

    return 0;
}
