#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;
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
	do{
		std::cout << "Enter number of Threads: " <<std::endl;
		cin >> nthread;
		if (nthread < 1)
		{
			std::cout << "Threads cannot be less than 1 " <<std::endl;
		}
	} while (nthread < 1);
	
	auto start = high_resolution_clock::now();
	
	float cthread = 1;
	float increasestart = 2;
	float increaseend = innerlimit/nthread;
	
	for (int i = 0; i < nthread; i++) {
	//std::cout << "thread " << i << " start " << increasestart << " end " << increaseend <<std::endl;
	cthread++;
    threads.emplace_back(getPrimes, increasestart, increaseend);
    increasestart = increaseend+1;
    increaseend = innerlimit*(cthread/nthread);
	}
	for (auto& thread : threads) {
    thread.join();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
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
