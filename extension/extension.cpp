/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod SDKTools Extension
 * Copyright (C) 2004-2010 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"
#include "physnatives.h"
#include "physhandles.h"

/**
 * @file extension.cpp
 * @brief Implements SDK Tools extension code.
 */

SDKTools g_SdkTools;		/**< Global singleton for extension's main interface */

IServerGameEnts *servergameents = NULL;
IPhysics *iphysics = NULL;

CGlobalVars *gpGlobals;

IForward *g_pForwardObjectWake = NULL;
IForward *g_pForwardObjectSleep = NULL;

SMEXT_LINK(&g_SdkTools);

class CPhysicsObjectEvent: public IPhysicsObjectEvent
{
public:
	void ObjectWake(IPhysicsObject *pObject)
	{
		CBaseEntity *pEntity = static_cast<CBaseEntity *>(pObject->GetGameData());

		if (!pEntity)
			return;

		int entIndex = GetEntIndex(pEntity);

		g_pForwardObjectWake->PushCell(entIndex);
		g_pForwardObjectWake->Execute(NULL);
	}

	void ObjectSleep(IPhysicsObject *pObject)
	{
		CBaseEntity *pEntity = static_cast<CBaseEntity *>(pObject->GetGameData());

		if (!pEntity)
			return;

		int entIndex = GetEntIndex(pEntity);

		g_pForwardObjectSleep->PushCell(entIndex);
		g_pForwardObjectSleep->Execute(NULL);
	}
} *pPhysicsObjectEvent = new CPhysicsObjectEvent;

#if 0
class CPhysicsCollisionEvent: public IPhysicsCollisionEvent
{
	void PreCollision(vcollisionevent_t *pEvent ) { META_CONPRINT("PreCollision(...)\n"); }
	void PostCollision(vcollisionevent_t *pEvent ) { META_CONPRINT("PostCollision(...)\n"); }

	void Friction(IPhysicsObject *pObject, float energy, int surfaceProps, int surfacePropsHit, IPhysicsCollisionData *pData ) { META_CONPRINT("Friction(...)\n"); }

	void StartTouch(IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData ) { META_CONPRINT("StartTouch(...)\n"); }
	void EndTouch(IPhysicsObject *pObject1, IPhysicsObject *pObject2, IPhysicsCollisionData *pTouchData ) { META_CONPRINT("EndTouch(...)\n"); }

	void FluidStartTouch(IPhysicsObject *pObject, IPhysicsFluidController *pFluid ) { META_CONPRINT("FluidStartTouch(...)\n"); }
	void FluidEndTouch(IPhysicsObject *pObject, IPhysicsFluidController *pFluid ) { META_CONPRINT("FluidEndTouch(...)\n"); }

	void PostSimulationFrame() { /*META_CONPRINT("PostSimulationFrame(...)\n");*/ }

	void ObjectEnterTrigger(IPhysicsObject *pTrigger, IPhysicsObject *pObject ) { META_CONPRINT("ObjectEnterTrigger(...)\n"); }
	void ObjectLeaveTrigger(IPhysicsObject *pTrigger, IPhysicsObject *pObject ) { META_CONPRINT("ObjectLeaveTrigger(...)\n"); }
} *pPhysicsCollisionEvent = new CPhysicsCollisionEvent;

class CPhysicsConstraintEvent: public IPhysicsConstraintEvent
{
public:
	void ConstraintBroken( IPhysicsConstraint * ) { META_CONPRINT("ConstraintBroken(...)\n"); }
} *pPhysicsConstraintEvent = new CPhysicsConstraintEvent;
#endif

void SDKTools::OnLevelInit(const char *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background)
{
	IPhysicsEnvironment *pEnv = iphysics->GetActiveEnvironmentByIndex(0);
	if (pEnv)
	{
		//pEnv->SetCollisionEventHandler(pPhysicsCollisionEvent);
		pEnv->SetObjectEventHandler(pPhysicsObjectEvent);
		//pEnv->SetConstraintEventHandler(pPhysicsConstraintEvent);
	} else {
		g_pSM->LogError(myself, "IPhysicsEnvironment null.");
	}
}

bool SDKTools::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	sharesys->AddNatives(myself, g_PhysNatives);

	RegisterHandles();

	g_pForwardObjectWake = g_pForwards->CreateForward("Phys_OnObjectWake", ET_Ignore, 1, NULL, Param_Cell);
	g_pForwardObjectSleep = g_pForwards->CreateForward("Phys_OnObjectSleep", ET_Ignore, 1, NULL, Param_Cell);

	return true;
}

void SDKTools::SDK_OnUnload()
{
	g_pForwards->ReleaseForward(g_pForwardObjectWake);
	g_pForwards->ReleaseForward(g_pForwardObjectSleep);

	UnregisterHandles();
}

bool SDKTools::SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	GET_V_IFACE_CURRENT(GetServerFactory, servergameents, IServerGameEnts, INTERFACEVERSION_SERVERGAMEENTS);
	GET_V_IFACE_CURRENT(GetPhysicsFactory, iphysics, IPhysics, VPHYSICS_INTERFACE_VERSION);

	gpGlobals = g_SMAPI->GetCGlobals();

	g_SMAPI->AddListener(g_PLAPI, this);

	return true;
}

int GetEntIndex(CBaseEntity *pEntity)
{
	if(!pEntity)
		return -1;
	edict_t *pEdict = servergameents->BaseEntityToEdict(pEntity);

	if(!pEdict)
		return -1;

	return IndexOfEdict(pEdict);
}

CBaseEntity *GetBaseEntity(int iEntIndex)
{
	edict_t *pEdict = PEntityOfEntIndex(iEntIndex);
	if(!pEdict)
		return NULL;

	return servergameents->EdictToBaseEntity(pEdict);
}
