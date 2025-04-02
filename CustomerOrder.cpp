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
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities utilities;
		size_t next_pos = 0;
		bool more = true;

		m_name = utilities.extractToken(str, next_pos, more);
		m_product = utilities.extractToken(str, next_pos, more);
		std::vector<std::string> items;
		while (more) {
			items.push_back(utilities.extractToken(str, next_pos, more));
		}
		m_cntItem = items.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(items[i]);
		}

		if (utilities.getFieldWidth() > m_widthField) {
			m_widthField = utilities.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw std::runtime_error("Copy operations are not allowed for CustomerOrder objects.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept 
	{
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
				}
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "] " << endl;
				return;
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< setfill(' ') << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - "
				<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}

}