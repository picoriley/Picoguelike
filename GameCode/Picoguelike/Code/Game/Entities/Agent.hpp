#pragma once
#include "Game/Entities/Entity.hpp"
#include "Game/Map/AStar.hpp"

class Agent : public Entity
{
public:
	//CONSTRUCTORS//////////////////////////////////////////////////////////////////////////
	Agent();
	virtual ~Agent();

	//FUNCTIONS//////////////////////////////////////////////////////////////////////////
	virtual void Update(float deltaSeconds) { Entity::Update(deltaSeconds); };
	virtual void Render() const;

	//MEMBER VARIABLES//////////////////////////////////////////////////////////////////////////
	int m_viewDistance;
	Path m_path;
};