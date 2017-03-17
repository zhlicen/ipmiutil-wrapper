#ifndef WRAPPER_IPMI_UTIL_MAP_TABLE_H
#define WRAPPER_IPMI_UTIL_MAP_TABLE_H

#include <functional>
#include <exception>
#include <map>
#include <mutex>


namespace wrapper {
namespace utils {

template<typename KEY, typename VAL, typename REGISTER>
class MapTable {
public:
	using ThisClass = MapTable<KEY, VAL, REGISTER>;
	using AddFunc = std::function<void(const KEY&, const VAL&)>;
	static ThisClass* get_instance() {
		std::lock_guard<std::recursive_mutex> lock(m_mutex_instance);
		static MapTable *table = NULL;
		if (nullptr == table) {
			table = new ThisClass;
		}
		return table;
	}

	// Load value from file - not implemented.
	virtual void Load(const std::string& file) {
		throw std::runtime_error("Not Implemented");
	}

	VAL look_up(const KEY& key) const {
		std::lock_guard<std::recursive_mutex> lock(m_mutex_data);
		auto iter = m_data.find(key);
		if (iter == m_data.end()) {
			throw std::runtime_error("Not Found");
		}
		return iter->second;
	}

protected:
	MapTable() {
		register_vals();
	}

	virtual ~MapTable() {
	}

	void add_val(const KEY& key, const VAL& val) {
		m_data[key] = val;
	}

	void register_vals() {
		std::lock_guard<std::recursive_mutex> lock(m_mutex_data);
		AddFunc add_func = std::bind(&ThisClass::add_val, 
			this, std::placeholders::_1, std::placeholders::_2);
		REGISTER regiter(add_func);
	}
protected:
	std::map<KEY, VAL> m_data;
	mutable std::recursive_mutex m_mutex_data;
	static std::recursive_mutex m_mutex_instance;
};

template<typename KEY, typename VAL, typename REGISTER>
std::recursive_mutex MapTable<KEY, VAL, REGISTER>::m_mutex_instance;

}
}


#endif