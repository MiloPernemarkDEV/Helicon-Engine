#pragma once

#include "core/HcArray.h"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

class HcArrayTest {
public:

	static void testHcArrayPerformanceComparedToVector() {
		const size_t N = 10'000'000;

	    {
			std::vector<int> stdv;
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < N; ++i)
				stdv.push_back(i);
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << "std::vector push_back: "
				<< duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
		}

		{
			HcArray<int> hc;
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < N; ++i)
				hc.push_back(i);
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << "HcArray push_back: "
				<< duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
		}
	}

	static void testIfContainerContainsContent(const HcArray<std::string>& container)
	{
		HcArray<std::string> testStrings;
		std::string name = "Name";
		std::string description = "Bla bla bla bla bla bla bla bla bla bla bla bla bla bla";
		std::string health = "Good";
		testStrings.push_back(name);
		testStrings.push_back(description);
		testStrings.push_back(health);

		for (int index = 0; index < testStrings.size(); index++)
		{
			std::cout << testStrings[index] << "\n";
		}

	}

	static void testIfContainerWorksDynamically()
	{
		char input{};
		std::cout << "Enter a type: \n";
		std::cout << "1. int \n";
		std::cout << "2. string \n";
		std::cin >> input;

		if (input == '1') {
			HcArray<int32_t> int_container;
			int input;
			std::cout << "test push back, enter a number: \n";
			std::cin >> input;
			std::cout << int_container[0];
		}
		else if (input == '2') {
			HcArray<std::string> string_container;
			int input;
			std::cout << "test push back, enter a word: \n";
			std::cin >> input;
			for (int i = 0; i <= string_container.size(); i++) {
				std::cout << "\n\n" << string_container[i];
			}
		}
	}

	static void runTests() {

		testHcArrayPerformanceComparedToVector();
	}
};

