#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;
#define LIMIT 10000
/*
This function checks if an integer n is prime.

Parameters:
n : int - integer to check

Returns true if n is prime, and false otherwise.
*/
bool check_prime(const int &n);
void getPrimes (int start, int end);
int count;
mutex primelock;

int main() {
  std::cout << LIMIT/2 <<std::endl;
  std::cout << LIMIT/2+1<<std::endl;
  std::cout << LIMIT<<std::endl;
  std:: thread t1 (getPrimes, 2,(LIMIT/2));
  std:: thread t2 (getPrimes, (LIMIT/2)+1,LIMIT);
  t1.join();
  t2.join();
  std::cout << count << " primes were found." << std::endl;

  return 0;
}

void getPrimes (int start, int end)
{
	for (int current_num = start; current_num <= end; current_num++) {
    if (check_prime(current_num)) {
      primelock.lock();
      count++;
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
