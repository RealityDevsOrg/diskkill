#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long bytes = 0;

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

int go(int argc, char *argv[])
{

    if (!argv[1])
        argv[1] = ".";
    if (!argv[2])
        argv[2] = "100";
    int n = std::stoi(argv[2]);
    bytes += n;
    std::string randomString = generateRandomString(n);
    std::string fileName = argv[1];
    fileName.append("/." + generateRandomString(10));
    std::ofstream fileStream(fileName);
    if (!fileStream)
    {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::string str = "Hello World!";
    
    // Start time measurement
    auto start_time = std::chrono::high_resolution_clock::now();

    fileStream << randomString;
    fileStream.close();
    if (std::remove(fileName.c_str()) != 0)
    {
        std::cout << "Error removing file" << std::endl;
        return 1;
    }
    
    // End time measurement and calculate time taken
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Wrote " << n << " bytes in " << time_taken << "ms. Total of " << bytes << " bytes written" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    while (true)
    {
        go(argc, argv);
    }
}
