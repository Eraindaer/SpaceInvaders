#pragma once
template <typename T, typename Q> bool CollisionAABB (T a, Q b) {
	if (a->dest.x + a->dest.w > b->dest.x  &&
		a->dest.x  < b->dest.x + b->dest.w  &&
		a->dest.y + a->dest.h > b->dest.y &&
		a->dest.y < b->dest.y + b->dest.h) 
		{
		return true;
	}
	return false;
}