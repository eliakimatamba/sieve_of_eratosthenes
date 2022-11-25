#include <iostream>
#include <vector>
#include <climits>
#include <math.h>
#include <assert.h>
#include <chrono>
#include <fstream>

// make changes to vary output
bool legal_rules()
{
	// TODO
	// true by default
	return true;
}

auto start_timer()
{
	return std::chrono::steady_clock::now();
}

auto stop_timer()
{
	return std::chrono::steady_clock::now();
}

auto run_time(std::chrono::_V2::steady_clock::time_point end, std::chrono::_V2::steady_clock::time_point start)
{

	return std::chrono::duration<double, std::milli>(end - start).count() / 1000.0;
}

unsigned int reverse_number(unsigned int number)
{
	unsigned int reversed = 0, remainder = 0;
	// get total value of number
	int total_value = 0;
	for (int i = 10; i < number; i *= 10)
	{
		total_value += 1;
	}

	while (total_value >= 0)
	{
		remainder = fmod(number, 10);
		reversed += remainder * pow(10, total_value);
		number /= 10;
		total_value--;
	}
	return reversed;
}

bool is_prime(unsigned int check)
{
	// iterate through the integers from 2 to check,
	for (int i = 2; i * i <= check; i++)
	{
		// test if each integer is divisible by any of the other integers in the loop.
		if (check % i == 0)
		{
			// If it is, then it will return false;
			return false;
		}
	}
	// otherwise, it will return true.
	return true;
}

std::vector<unsigned int> emirp_finder(std::vector<unsigned int> gen_primes)
{

	std::vector<unsigned int> emirps;
	for (auto prime_number : gen_primes)
		if (is_prime(reverse_number(prime_number)))
			if (prime_number > 10)
				emirps.push_back(prime_number);
	return emirps;
}

std::vector<unsigned int> palindromic_emirps(std::vector<unsigned int> gen_primes)
{
	std::vector<unsigned int> palindrome;

	for (auto prime_number : gen_primes)
	{
		assert(is_prime(prime_number));
		if (prime_number == reverse_number(prime_number))
			palindrome.push_back(prime_number);
	}
	return palindrome;
}

std::vector<unsigned int> sieve_of_eratosthenes(unsigned int min, unsigned int max)
{

	std::vector<unsigned int> primes;
	// generate positive integers
	if (min < 2)
		min = 2;
	// MAXIMUM UNSIGNED INT
	if (max > UINT_MAX || max < min)
		max = UINT_MAX;

	for (unsigned int gen = min; gen <= max; gen++)
		// of the generated integers check for it's prime state
		// if not, strike through and continue
		if (is_prime(gen))
		{
			// if the prime state is true, push the integer into prime vector container
			primes.push_back(gen);
		}

	return primes;
}

// driver code
int main()
{
	unsigned int minimum, maximum;
	std::vector<double> rtimes;
	int count = 0;

	std::cout << "Minimum: ";
	std::cin >> minimum;
	std::cout << "Maximum: ";
	std::cin >> maximum;

	auto start = start_timer();
	std::vector<unsigned int> eratosthenes_primes = sieve_of_eratosthenes(minimum, maximum);
	auto end = stop_timer();
	rtimes.push_back(run_time(end, start));

	start = start_timer();
	std::vector<unsigned int> emirp_primes = emirp_finder(eratosthenes_primes);
	end = stop_timer();
	rtimes.push_back(run_time(end, start));

	start = start_timer();
	std::vector<unsigned int> emirp_palindrome = palindromic_emirps(emirp_primes);
	end = stop_timer();
	rtimes.push_back(run_time(end, start));

	// check rules
	assert(legal_rules());

	std::cout << std::endl
			  << "Generating Primes in range " << minimum << "-" << maximum << std::endl;
	std::cout << "{ \n";
	count = 0;
	for (auto prime : eratosthenes_primes)
	{
		std::cout << prime << ",";
		if (count % 15 == 0)
			std::cout << std::endl;
		count++;
	}
	std::cout << " \n}\n";
	std::cout << "Took " << rtimes[0] << " sec" << std::endl;

	std::cout << std::endl
			  << "Finding Emirps in the Primes " << std::endl;
	std::cout << "{ \n";
	count = 0;

	for (auto emirp : emirp_primes)
	{
		std::cout << emirp << ",";
		if (count % 15 == 0)
			std::cout << std::endl;
		count++;
	}
	std::cout << " \n}\n";
	std::cout << "Took " << rtimes[1] << " sec" << std::endl;

	std::cout << std::endl
			  << "Finding Palindromes in the Primes " << std::endl;
	std::cout << "{ \n";
	count = 0;
	for (auto palindrome : emirp_palindrome)
	{
		std::cout << palindrome << ",";
		if (count % 15 == 0)
			std::cout << std::endl;
		count++;
	}
	std::cout << " \n}\n";
	std::cout << "Took " << rtimes[2] << " sec" << std::endl;
	std::ofstream ofile("run_times.txt", std::ios::in | std::ios::app);

	// writing run times into a file
	ofile << std::endl
		  << std::endl
		  << "Using Sieve of Eratosthenes to Generate Primes" << std::endl
		  << "Generating Primes in range " << minimum << "-" << maximum
		  << std::endl
		  << "Run time: " << rtimes[0]
		  << std::endl
		  << std::endl
		  << "Finding Emirps in the Primes "
		  << std::endl
		  << "Run time: " << rtimes[1]
		  << std::endl
		  << std::endl
		  << "Finding Palindromes in the Primes "
		  << std::endl
		  << "Run time: " << rtimes[1] << std::endl;

	return 0;
}
