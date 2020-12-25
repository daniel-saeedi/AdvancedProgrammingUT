#include "XOREncryption.hpp"

std::string XOREncryption::encrypt_decrypt(std::string text)
{
	char key = 'k';
	std::string output = text;
	for (int i = 0; i < text.size(); i++)
		output[i] = text[i] ^ key;
	return output;
}