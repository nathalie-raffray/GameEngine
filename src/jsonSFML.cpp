#include "jsonSFML.h"

namespace sf
{
	void to_json(json& j, const IntRect& p)
	{
		j = json{ p.left, p.top, p.width, p.height };
	}

	void from_json(const json& j, IntRect& p)
	{
		p.left = j[0];
		p.top = j[1];
		p.width = j[2];
		p.height = j[3];
	}
}