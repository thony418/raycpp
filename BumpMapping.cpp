#include "BumpMapping.h"

/*
	Used to compute the normal on the impact point to make the surface "bump"
	If the impacted object exists and has a bump map, will get the color value of this point on the map
	Then, will compute and return the normal depending on the color found
	Else, will return the standard normal
*/
Vec3 BumpMapping::computeBump(const pair<Vec3, SceneObject*> impactedObject) const {
	Vec3 res = Vec3();
	if (impactedObject.second) {	// Check if the object exist

		// TODO : check if the object has a bump map

		Vec3 objectPosition = impactedObject.second->getPosition();	// Store the position of the object
		Vec3 positionImpact = impactedObject.first - objectPosition; // Store the position of the impact in the object base

		// TODO : get the matching point on the texture

		// TODO : compute the new normal
	}
	return Vec3();
}