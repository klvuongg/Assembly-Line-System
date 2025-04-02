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
#include <iostream>
#include <iomanip>
#include "Workstation.h"
using namespace std;

namespace seneca {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (!m_orders.empty()) {
			CustomerOrder& order = m_orders.front();
			if (order.isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					*m_pNextStation += std::move(order);
				}
				else {
					if (order.isOrderFilled()) {
						g_completed.push_back(std::move(order));
					}
					else {
						g_incomplete.push_back(std::move(order));
					}
				}
				m_orders.pop_front();
				return true;
			}
		}
		return false;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> " << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << "\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}

