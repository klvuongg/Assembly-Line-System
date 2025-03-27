#ifndef STATION_H
#define STATION_H
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
