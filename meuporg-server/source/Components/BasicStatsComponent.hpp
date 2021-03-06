#ifndef BASICSTATSCOMPONENT_HPP_INCLUDED
#define BASICSTATSCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	BasicStatsComponent class.
	Component : holds the hp, strength, agility and resistance.
*/
class BasicStatsComponent : public kantan::Component
{
	public:
		// Ctor.
		BasicStatsComponent(unsigned int ownerId);

		// Attribute.
		bool isDead;

		float hp;
		float maxhp;

		float strength;
		float agility;
		float resistance;
};

#endif // BASICSTATSCOMPONENT_HPP_INCLUDED
