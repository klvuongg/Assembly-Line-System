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
#include <fstream>
#include <algorithm>
#include <sstream>
#include "LineManager.h"
using namespace std;

namespace seneca {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream fin(file);
		if (!fin) {
			throw std::runtime_error("Unable to open file");
		}

		std::string line, currentStation, nextStation;
		std::vector<std::pair<std::string, std::string>> stationPair;

		while (std::getline(fin, line)) {
			std::istringstream rec(line);
			std::getline(rec, currentStation, '|');
			if (!std::getline(rec, nextStation, '|')) {
				nextStation.clear();
			};
			stationPair.emplace_back(currentStation, nextStation);
		}
		fin.close();
		
		auto findStation = [&stations](const std::string& name) {
			return *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
				return station->getItemName() == name;
			});
		};

		std::for_each(stationPair.begin(), stationPair.end(), [&](const auto& pair) {
			Workstation* currStation = findStation(pair.first);
			Workstation* nxtStation = pair.second.empty() ? nullptr : findStation(pair.second);
			currStation->setNextStation(nxtStation);
			m_activeLine.push_back(currStation);
		});

		auto getFirstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
			return std::none_of(stationPair.begin(), stationPair.end(), [&](const auto& pair) {
				return pair.second == station->getItemName();
			});
		});

		m_firstStation = (getFirstStation != stations.end()) ? *getFirstStation : nullptr;
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations()
	{
		std::vector<Workstation*> orderedStations;
		Workstation* curr = m_firstStation;

		while (curr) {
			orderedStations.push_back(curr);
			curr = curr->getNextStation();
		}

		m_activeLine = std::move(orderedStations);
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t cnt = 1;

		os << "Line Manager Iteration: " << cnt++ << endl;

		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
			station->fill(os);
		});

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
			station->attemptToMoveOrder();
		});

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}

	void LineManager::display(std::ostream& os) const
	{
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
			station->display(os);
		});
	}
}
