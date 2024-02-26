#include <cstdio>
#include <iostream>
#include <string>
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
	std::string password = "";
	size_t length = {};
	int count = {};
	int randomNum = {};
	char randomChar = {};

} data;

std::string
generate_password(data_t &data)
{
	/* ensuring that password is going to be reset before generating a new one
	 */
	data.password.clear();
	for (size_t i = 0; i < data.length; ++i)
	{
		do
		{
			/* print random char within ASCII range, 65-90, 97-122 */
			data.randomNum = rand() % (122 - 48 + 1) + 48;
			data.randomChar = static_cast<char>(data.randomNum);
		} while (data.randomChar < '0' ||
				 (data.randomChar > '9' && data.randomChar < 'A') ||
				 (data.randomChar > 'Z' && data.randomChar < 'a') ||
				 data.randomChar > 'z');

		data.password.push_back(data.randomChar);
	}
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
	scanf_s("%d", &data.count);
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
	scanf_s("%zu", &data.length);
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