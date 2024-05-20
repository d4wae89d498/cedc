module ucbl.cedilla;

import :common;

namespace cedilla
{
	StateArray::StateArray(initializer_list<RrefCapture<unique_ptr<State>>> init)
	{
		for (auto&& elem : init)
		{
			this->emplace_back(std::move(elem));
		}
	}

	fn StateArray::clone() -> unique_ptr<StateArray>
	{
		throw runtime_error("StateArray::clone() not implemented");
		auto out = make_unique<StateArray>();
		for (auto& item : *this)
			out->push_back(item->clone());
		return out;
	}

	fn StateArray::serialize() -> string
	{
		throw runtime_error("StateArray::serialize() not implemented");
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
