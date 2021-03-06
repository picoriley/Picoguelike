#pragma once
#include "Engine/Input/XMLUtils.hpp"
#include <string>

class NPC;

class NPCFactory
{
public:
	//CONSTRUCTORS//////////////////////////////////////////////////////////////////////////
	NPCFactory(const XMLNode& npcBlueprintNode);

	//STATIC FUNCTIONS//////////////////////////////////////////////////////////////////////////
	static void LoadAll();
	static NPC* CreateByName(const std::string& name);

	//FUNCTIONS//////////////////////////////////////////////////////////////////////////
	NPC* Create();

private:
	//HELPER FUNCTIONS//////////////////////////////////////////////////////////////////////////
	void PopulateFromXMLNode(const XMLNode& npcBlueprintNode);
	
	//MEMBER VARIABLES//////////////////////////////////////////////////////////////////////////
	NPC* m_templateNPC;
};