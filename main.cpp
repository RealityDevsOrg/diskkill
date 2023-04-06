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
    fileStream << randomString;
    fileStream.close();
    if (std::remove(fileName.c_str()) != 0)
    {
        std::cout << "Error removing file" << std::endl;
        return 1;
    }
    std::cout << "Total of " << bytes << " bytes written" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    while (true)
    {
        go(argc, argv);
    }
}