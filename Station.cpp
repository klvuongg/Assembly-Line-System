#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string& record)
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
		os << setw(3) << setfill('0') << id << " | " << left << setw(m_widthField) << setfill(' ') << item_name << " | " << right << setw(6) << setfill('0') << serial_num << " | ";
		
		if (full) {
			os << setw(4) << setfill(' ') << quantity << " | " << desc;
		}

		os << endl;
	}
}