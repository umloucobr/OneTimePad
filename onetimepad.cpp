#include <iostream>
#include <string>
#include <random>

std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution randomIntCharAscii{ 0, 25 };

int encrypt() {
	std::string input{};
	std::string text{};
	std::string key{};
	std::string finalResult{};
	do
	{
		std::cout << "Do you want a (r)andom key or a (c)ustom key?";
		std::cin >> input;
	}while (input != "r" && input != "random" && input != "c" && input != "custom");

	if (input == "r" || input == "random")
	{
		//Gets input from user and copy it in a string without whitespaces.
		std::cout << "What's the text you want to encrypt?\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text, '\n');
		text.erase(remove(text.begin(), text.end(), ' '), text.end());

		for (int i = 0; i < text.length(); i++)
		{
			char randomToChar{static_cast<char>(randomIntCharAscii(mt) + 97)};
			key.push_back(randomToChar);
		}

		for (int i = 0; i < text.length(); i++)
		{
			int keyToInt{ static_cast<int>(key[i] - 97) };
			int textToInt{ static_cast<int>(text[i] - 97) };

			int operationEncrypt{ keyToInt + textToInt };
			operationEncrypt = operationEncrypt % 26;

			char operationEncryptToChar{ static_cast<char>(operationEncrypt + 97) };
			finalResult.push_back(operationEncryptToChar);
		}

		std::cout << "Your text was encrypted using the key: " << key << ", and the final result was: " << finalResult << ".\n";
	}
	else
	{
		//Gets input from user and copy it in a string without whitespaces.
		std::cout << "What's the text you want to encrypt?";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text, '\n');
		text.erase(remove(text.begin(), text.end(), ' '), text.end());

		std::cout << "What is the key to encrypt it?\n";
		std::cin >> key;
		if (key.length() < text.length())
		{
			std::cerr << "Key doesn't have the same length as the text.\n";
			return 1;
		}

		for (int i = 0; i < text.length(); i++)
		{
			int keyToInt{ static_cast<int>(key[i] - 97) };
			int textToInt{ static_cast<int>(text[i] - 97) };

			int operationEncrypt{ keyToInt + textToInt };
			operationEncrypt = operationEncrypt % 26;

			char operationEncryptToChar{ static_cast<char>(operationEncrypt + 97) };
			finalResult.push_back(operationEncryptToChar);
		}

		std::cout << "Your text was encrypted using the key: " << key << ", and the final result was: " << finalResult << ".\n";
	}
}

int decrypt() {
	std::string text{};
	std::string key{};
	std::string finalResult{};

	std::cout << "What is the text to decrypt?\n";
	std::cin >> text;
	std::cout << "What is the key to decrypt?\n";
	std::cin >> key;
	if (key.length() < text.length())
	{
		std::cerr << "Key doesn't have the same length as the text.\n";
		return 1;
	}

	for (int i = 0; i < text.length(); i++)
	{
		int keyToInt{ static_cast<int>(key[i] - 97) };
		int textToInt{ static_cast<int>(text[i] - 97) };

		int operationDecrypt{ textToInt - keyToInt };
		if (operationDecrypt < 0)
		{
			//I have no idea what this does, but C++ can't do modulo operation with negative numbers.
			operationDecrypt = (26 >= 0 ? 26 : -26) - 1 + (operationDecrypt + 1) % 26;
		}

		char operationDecryptToChar{ static_cast<char>(operationDecrypt + 97) };
		finalResult.push_back(operationDecryptToChar);
	}

	std::cout << "Your text was decrypted using the key: " << key << ", and the final result was: " << finalResult << ".\n";
}

void mainProgram() {
	int input{};
	do
	{
		std::cout << "What do you want to do? \n" << "1 - Encrypt something. \n" << "2 - Decrypt something. \n";
		std::cin >> input;
	}while (input != 1 && input != 2);

	if (input == 1)
	{
		encrypt();
	}
	else 
	{
		decrypt();
	}
}

int main() {
	std::string choice{};
	mainProgram();

	do
	{
		std::cout << "Go again?(y/n)\n";
		std::cin >> choice;
	} while (choice != "y" && choice != "yes" && choice != "n" && "no");

	if (choice == "y" || choice == "yes")
	{
		main();
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	return 0;
}