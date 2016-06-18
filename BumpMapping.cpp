#include "BumpMapping.h"

/*
	Used to compute the normal on the impact point to make the surface "bump"
	If the impacted object has a bump map, it will get the color value of this point on the map
	Then, it will compute the normal depending on the color found
	Finally, it will return that value
*/
Vec3 BumpMapping::computeBump(const pair<Vec3, SceneObject*> impactedObject) const {
	return Vec3();
}