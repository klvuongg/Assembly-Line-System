/*
* Name: Kaitlyn Vuong
* Email: klvuong@myseneca.ca
* Student ID: 165190224
* Date: April 2, 2025
*
* I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& record) : id(++id_generator)
	{
		Utilities utilities;
		size_t next_pos = 0;
		bool more = true;

		item_name = utilities.extractToken(record, next_pos, more);
		serial_num = std::stoul(utilities.extractToken(record, next_pos, more));
		quantity = std::stoul(utilities.extractToken(record, next_pos, more));

		if (utilities.getFieldWidth() > m_widthField) {
			m_widthField = utilities.getFieldWidth();
		}
		desc = utilities.extractToken(record, next_pos, more);
	}
	const std::string& Station::getItemName() const
	{
		return item_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return serial_num++;
	}

	size_t Station::getQuantity() const
	{
		return quantity;
	}

	void Station::updateQuantity()
	{
		quantity--;
		if (quantity < 0) {
			quantity = 0;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os.fill(' ');
		os.unsetf(ios::adjustfield);

		os << std::right << std::setw(3) << std::setfill('0') << id << " | "
			<< std::left << std::setw(m_widthField) << std::setfill(' ') << item_name << " | "
			<< std::right << std::setw(6) << std::setfill('0') << serial_num << " | ";

		if (full) {
			os << std::right << std::setw(4) << std::setfill(' ') << quantity << " | " << std::left << desc;
		}

		os << std::endl;
	}
}