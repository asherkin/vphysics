/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod SDKTools Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
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

#ifndef _INCLUDE_SDKTOOLS_PHYSHANDLES_H_
#define _INCLUDE_SDKTOOLS_PHYSHANDLES_H_

#include "extension.h"

void RegisterHandles();
void UnregisterHandles();

#define STRINGIFY(string) #string

#define DECL_HANDLE(name) \
class IPhysics##name##TypeHandler : public IHandleTypeDispatch \
	{ \
	public: \
		void OnHandleDestroy(HandleType_t type, void *object); \
	}; \
	extern HandleType_t g_IPhysics##name##Type; \
	extern IPhysics##name##TypeHandler g_IPhysics##name##TypeHandler;

#define CHECK_ENV(name) \
	if (!iphysics) \
	{ \
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysics" #name " called while IPhysics interface is null."); \
	} \
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0); \
	if (!pPhysicsEnvironment) \
	{ \
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysics" #name " called while IPhysicsEnvironment pointer is null."); \
	}

#define START_HANDLER(name) \
	HandleType_t g_IPhysics##name##Type = 0; \
	void IPhysics##name##TypeHandler::OnHandleDestroy(HandleType_t type, void *object) \
	{

#define END_HANDLER(name) \
	} \
	IPhysics##name##TypeHandler g_IPhysics##name##TypeHandler;

#define SIMPLE_HANDLER(name) \
	START_HANDLER(name) \
		CHECK_ENV(name); \
		pPhysicsEnvironment->Destroy##name((IPhysics##name *)object); \
	END_HANDLER(name)

/* Register the type with default security permissions */
#define CREATE_TYPE(name) \
	g_IPhysics##name##Type = g_pHandleSys->CreateType(STRINGIFY(Physics##name), \
	&g_IPhysics##name##TypeHandler, \
	0, \
	NULL, \
	NULL, \
	myself->GetIdentity(), \
	NULL);

/* Remove the type on shutdown */
#define REMOVE_TYPE(name) \
	g_pHandleSys->RemoveType(g_IPhysics##name##Type, myself->GetIdentity());

#define RETURN_NEW_HANDLE(name, var) \
	if (var) \
{ \
	return g_pHandleSys->CreateHandle(g_IPhysics##name##Type, \
	var, \
	pContext->GetIdentity(), \
	myself->GetIdentity(), \
	NULL); \
} else { \
	return BAD_HANDLE; \
}

#define GET_POINTER_FROM_HANDLE(name, param, var) \
	Handle_t name##Handle = static_cast<Handle_t>(params[param]); \
	if (name##Handle != BAD_HANDLE) \
	{ \
		HandleSecurity sec; \
		sec.pOwner = NULL; \
		sec.pIdentity = myself->GetIdentity(); \
		g_pHandleSys->ReadHandle(name##Handle, g_IPhysics##name##Type, &sec, (void **)&var); \
	}

struct FrictionSnapshotHandle {
	IPhysicsObject *pObject;
	IPhysicsFrictionSnapshot *pSnapshot;
};

DECL_HANDLE(Spring);
DECL_HANDLE(Constraint);
DECL_HANDLE(ConstraintGroup);
DECL_HANDLE(FrictionSnapshot);

#endif //_INCLUDE_SDKTOOLS_PHYSHANDLES_H_
