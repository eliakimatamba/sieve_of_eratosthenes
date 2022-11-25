#include<iostream>
#include<vector>
#include<climits>
bool is_prime(unsigned int check){
	//iterate through the integers from 2 to check,
	for(int i=2; i*i<=check; i++){
		//test if each integer is divisible by any of the other integers in the loop.
		if(check%i==0){
			//If it is, then it will return false;
            return false;
		}
	}
	//otherwise, it will return true.
	return true;
}

std::vector<unsigned int> sieve_of_eratosthens(unsigned int min, unsigned int max){
	// create primes vector
    std::vector<unsigned int> primes;
	// generate positive integers
	if(min <2 )
		min=2;
	//MAXIMUM UNSIGNED INT
	
	for(unsigned int gen=min; gen <=max; gen++)
	//of the generated integers check for it's prime state
	//if not, strike through and continue
	    if(is_prime(gen)){
			//if the prime state is true, push the integer into prime vector container
			primes.push_back(gen);
		}
	
	return primes;
}
//drive code

int main(char arg, char** argv){
	unsigned int minimum, maximum;
	
	std::cout<<"Minimum: ";
  std::cout<<"Maximum: ";
	std::cin>>minimum>>maximum;
	
	auto prime_numbers = sieve_of_eratosthens(minimum,maximum);

	std::cout<<"{ ";
	for(auto prime: prime_numbers)
		std::cout<<prime<<",";
	std::cout<<" }\n";

	return 0;
}
