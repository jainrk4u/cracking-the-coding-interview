#include <iostream>
#include <iomanip>
#include <algorithm>	/* std::rotate */
#include <cassert>

/**
 * @brief solution which checks if str2 appears in (str1 + str1)
 * @return true if str2 is a rotation of str1, false otherwise
 * @note complexity: O(n) in both time and space, where n is the length of
 *       the strings (if not the same, one cannot be a rotation of the other)
 */
bool is_rotation_1(const std::string& str1, const std::string& str2)
{
	if (str1.size() != str2.size())
	{
		return false;
	}

	return (str1 + str1).find(str2) != std::string::npos;
}

/**
 * @brief brute-force solution: compares str2 with all rotations of str1
 * @return true if str2 is a rotation of str1, false otherwise
 * @note complexity: O(n²) in time, O(n) in space
 */
bool is_rotation_2(std::string str1, const std::string& str2)
{
	if (str1.size() != str2.size())
	{
		return false;
	}

	bool result = (str1 == str2);

	for (size_t j = 0; j+1 < str1.size() && result == false; ++j)
	{
		std::rotate(str1.begin(), str1.begin()+1, str1.end());

		result = (str1 == str2);
	}

	return result;
}

/**
 * @brief generates a random ASCII string of length n and characters in [a-c]
 * @note complexity: O(n) in both space and time
 */
std::string random_string(size_t n)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution< int > distribution(0,2);

	std::string str;

	while (n > 0)
	{
		char letter = 'a' + distribution(generator);
		str.push_back(letter);
		--n;
	}

	return str;
}

int main()
{
	for (size_t n = 0; n <= 20; ++n)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::string str1 = random_string(n);
			std::string str2 = random_string(n);

			assert(is_rotation_1(str1, str2) == is_rotation_2(str1, str2));

			for (size_t j = 0; j < n; ++j)
			{
				std::string str1_rot = str1;
				std::rotate(str1_rot.begin(), str1_rot.begin()+j, str1_rot.end());

				assert(is_rotation_1(str1, str1_rot) == true);
				assert(is_rotation_2(str1, str1_rot) == true);
			}
		}

		std::cout << "passed random tests for strings of length " << n << std::endl;
	}

	return 0;
}