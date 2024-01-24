#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;
#define LIMIT 10000000
/*
This function checks if an integer n is prime.

Parameters:
n : int - integer to check

Returns true if n is prime, and false otherwise.
*/
bool check_prime(const int &n);
void getPrimes (int start, int end);
int count;
int innerlimit = LIMIT;
int nthread;
mutex primelock;
std::vector<int> primes;

int main() {
	std::vector<std::thread> threads;
	do {
	std::cout << "Enter N: " <<std::endl;
	cin >> innerlimit;
	if (innerlimit > LIMIT)
	{
		std::cout << "too big, try again" <<std::endl;
	}
	} while (innerlimit > LIMIT);
	std::cout << "Enter number of Threads: " <<std::endl;
	cin >> nthread;
	float increase = 1;
	float increasestart = 2;
	float increaseend = innerlimit/nthread;
	for (std::size_t i = 0; i < nthread; i++) {
	std::cout << "thread " << i << " start " << increasestart << " end " << increaseend <<std::endl;
	increase++;
    threads.emplace_back(getPrimes, increasestart, increaseend);
    increasestart = increaseend+1;
    increaseend = innerlimit*((increase)/nthread);
    
	}
	for (auto& thread : threads) {
    thread.join();
	}
  std::cout << primes.size() << " primes were found." << std::endl;

  return 0;
}

void getPrimes (int start, int end)
{
	for (int current_num = start; current_num <= end; current_num++) {
    if (check_prime(current_num)) {
      primelock.lock();
      primes.push_back(current_num);
      primelock.unlock();
    }
  }
}

bool check_prime(const int &n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}
