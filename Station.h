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

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
namespace seneca {
	class Station {
		int id{};
		std::string item_name{};
		std::string desc{};
		size_t serial_num{};
		size_t quantity{};
		static size_t m_widthField;
		static size_t id_generator;
	public: 
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif
