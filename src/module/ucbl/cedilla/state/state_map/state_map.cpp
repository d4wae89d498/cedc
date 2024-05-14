module ucbl.cedilla;

import :common;

namespace cedilla
{
	fn StateMap::clone() const -> unique_ptr<StateMap>
	{
		throw runtime_error("not implemented");
		auto out = make_unique<StateMap>();
		for (auto& item : *this)
			(*out)[item.first] = item.second->clone();
		return out;
	}

	fn StateMap::serialize() const -> string
	{
		throw runtime_error("not implemented");
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
