#include "../../include/objects/barrelStack.h"

void BarrelStack::initialize()
{
	for (int height = 1; height < 6; height++)
	{
		for (int x = height; x < 12 - height; x++)
		{
			std::shared_ptr<CylindricObject> cylinder = std::make_shared<CylindricObject>(7, 2, 2, 10, 10, material);
			(*cylinder).setPosition(glm::vec3(1.18f * x + 0.5f * ((int)height % 2),
				1.02f * height - 0.5f, 0.0f));
			(*cylinder).setScale(glm::vec3(0.3f, 0.3f, 0.3f));

			addObject(cylinder);
		}

	}
}
