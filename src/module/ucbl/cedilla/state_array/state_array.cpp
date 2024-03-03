module ucbl.cedilla;

import :common;

namespace cedilla
{
	fn StateArray::clone() const -> unique_ptr<StateArray>
	{
		auto out = make_unique<StateArray>();
		for (auto& item : *this)
			out->push_back(item->clone());
		return out;
	}

	fn StateArray::serialize() const -> string
	{
		auto out = string("[");
		auto it = this->begin();
		const auto end = this->end();
		while (1)
		{
			out += format("{}", it->get()->serialize());
			it = next(it);
			if (it == end)
				break ;
			out += ",";
		}
		out += "]";
		return out;
	}
}
