module ucbl.cedilla;

import :common;

namespace cedilla
{
//    StateMap::StateMap(StateMap&& other) noexcept : StateMap::BaseType(std::move(other)) {}

	StateMap::StateMap(initializer_list<pair<const string, RrefCapture<unique_ptr<State>>>> init)
	{
		for (auto&& elem : init)
		{
			this->emplace(elem.first, std::move(elem.second));
		}
	}

	fn StateMap::clone() -> unique_ptr<StateMap>
	{
		//throw runtime_error("StateMap::clone() not implemented");
		auto out = make_unique<StateMap>();
		for (auto& item : *this)
			(*out)[item.first] = item.second->clone();
		return out;
	}

	fn StateMap::serialize() -> string
	{
		auto out = string("{");
		auto it = this->begin();
		const auto end = this->end();
		while (it != end)
		{
			out += format("\"{}\": {}", it->first, it->second->serialize());
			it = next(it);
			if (it == end)
				break ;
			out += ",";
		}
		out += "}";
		return out;
	}
}
