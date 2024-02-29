export module ucbl.cedilla:state_map.impl;
export import :state_map;

import :state;
import :common;

namespace cedilla
{
	fn StateMap::clone() const -> unique_ptr<StateMap>
	{
		auto out = make_unique<StateMap>();
		for (auto& item : *this)
			(*out)[item.first] = item.second->clone();
		return out;
	}

	fn StateMap::serialize() const -> string
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
