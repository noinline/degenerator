#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

/* colors >~< */
#define RESET	  "\u001b[0m"
#define RED(s)	  "\u001b[1;31m" s RESET
#define GREEN(s)  "\u001b[1;32m" s RESET
#define YELLOW(s) "\u001b[1;33m" s RESET
#define CYAN(s)	  "\u001b[1;36m" s RESET
#define WHITE(s)  "\u001b[37;1m" s RESET

struct data_t
{
	std::string input = "";
	std::string password = "";
	size_t length = {};
	int count = {};
	char minChar = {};
	char maxChar = {};
	std::vector<char> vecPassword;
} data;

std::string
generate_password(data_t &data)
{
	data.vecPassword.resize(data.length);
	for (size_t i = 0; i < data.length; ++i)
	{
		data.minChar = 'a';
		data.maxChar = 'z';
		if (rand() % 2 == 0)
		{ /* 50% chance to include uppercase letters */
			data.minChar = 'A';
			data.maxChar = 'Z';
		}
		if (rand() % 2 == 0)
		{ /* 50% chance to include digits */
			data.minChar = '0';
			data.maxChar = '9';
		}
		/* assign a random char within ASCII range, 65-90, 97-122 */
		data.vecPassword[i] = static_cast<char>(
			rand() % (data.maxChar - data.minChar + 1) + data.minChar);
	}
	data.password =
		std::string(data.vecPassword.begin(), data.vecPassword.end());
	return data.password;
}

int
main(void)
{
	/* seed the random number generator with the current time */
	srand(static_cast<unsigned int>(time(0)));
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetConsoleTitleA("password degenerator :3");
	std::printf("How many"
				" " CYAN("passwords") " "
									  "do you want to generate?: ");
	std::getline(std::cin, data.input);
	data.count = std::stoi(data.input);
	/* ensuring that password count is not less than one :lol: */
	if (data.count < 1)
	{
		std::printf(RED("Invalid") " " CYAN(
			"password") " "
						"count. Please enter a"
						" " GREEN("valid") " " WHITE("number") "! "
															   "\n");
		return 1;
	}
	std::printf(
		"How many"
		" " WHITE("characters") " "
								"in each"
								" " CYAN("password") "? "
													 "(up to"
													 " " WHITE("32") "): ");
	std::getline(std::cin, data.input);
	data.length = std::stoull(data.input);
	/* ensuring that password length is not exceeded */
	if (data.length < 1 || data.length > 32)
	{
		std::printf(RED("Invalid") " " CYAN(
			"password") " "
						"length. Please enter a"
						" " WHITE("number") " "
											"between"
											" " WHITE("1") " "
														   "and"
														   " " WHITE(
															   "32") ". "
																	 "\n");
		return 1;
	}
	std::printf(YELLOW("Generating") " " WHITE("%i") " " CYAN(
					"passwords") " "
								 "of length"
								 " " WHITE("%zu") " "
												  "each: \n",
				data.count, data.length);
	std::setvbuf(stdout, NULL, _IOFBF, 1024 * 16);
	for (int i = 0; i < data.count; ++i)
	{
		data.password = generate_password(data);
		std::printf(CYAN("Password") " " WHITE("%i") ": %s \n", (i + 1),
					data.password.c_str());
	}
	std::cout << std::flush;
	std::printf(GREEN("Successfully") " "
									  "generated " WHITE("%i") " " CYAN(
										  "passwords") " "
													   "of length"
													   " " WHITE("%zu") ". \n",
				data.count, data.length);
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	return 0;
}