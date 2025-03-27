#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

namespace seneca {
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token;

		if (next_pos >= str.length()) {
			more = false;
			return "";
		}

		size_t pos_delimiter = str.find(m_delimiter, next_pos);
		if (pos_delimiter == next_pos) {
			more = false;
			next_pos++;
			throw std::runtime_error("Delimiter found at the next position");
		}

		if (pos_delimiter == std::string::npos) {
			token = str.substr(next_pos);
			next_pos = str.length();
			more = false;
		}
		else {
			token = str.substr(next_pos, pos_delimiter - next_pos);
			next_pos = pos_delimiter + 1;
			more = true;
		}

		size_t start = token.find_first_not_of("");
		size_t end = token.find_last_not_of("");
		token = (start == std::string::npos) ? "" : token.substr(start, end - start + 1);

		if (token.length() > m_widthField) {
			m_widthField = token.length();
		}

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}
