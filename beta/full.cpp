#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

long bytes = 0;
std::mutex bytes_mutex;

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

void writeFiles(const std::string& dir, int n)
{
    std::string randomString = generateRandomString(n);
    std::string fileName = dir;
    fileName.append("/." + generateRandomString(10));
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
    std::lock_guard<std::mutex> lock(bytes_mutex);
    bytes += n;
}

int main(int argc, char *argv[])
{
    std::string dir = ".";
    int n = 100;
    if (argc >= 2)
        dir = argv[1];
    if (argc >= 3)
        n = std::stoi(argv[2]);

    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread([&] {
            while (true)
            {
                writeFiles(dir, n);
            }
        });
    }

    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    std::cout << "Total of " << bytes << " bytes written" << std::endl;
    return 0;
}
