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

#include "extension.h"
#include "vphysics_interface.h"
#include "vphysics/constraints.h"

#include "physnatives.h"

////////////////////////////////////////////////////////

static cell_t IsStatic(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return m_pPhysicsObject->IsStatic();
}

static cell_t IsAsleep(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return m_pPhysicsObject->IsAsleep();
}

static cell_t IsHinged(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return m_pPhysicsObject->IsHinged();
}

static cell_t IsCollisionEnabled(IPluginContext *pContext, const cell_t *params)
{
#if SOURCE_ENGINE > SE_EPISODEONE
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return m_pPhysicsObject->IsCollisionEnabled();
#else
	return pContext->ThrowNativeError("%s not supported by this engine.", "IsCollisionEnabled");
#endif
}

static cell_t IsGravityEnabled(IPluginContext *pContext, const cell_t *params)
{
#if SOURCE_ENGINE > SE_EPISODEONE
		IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);
	
		if (!m_pPhysicsObject)
		{
			return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
		}
	
		return m_pPhysicsObject->IsGravityEnabled();
#else
	return pContext->ThrowNativeError("%s not supported by this engine.", "IsGravityEnabled");
#endif
}

static cell_t IsDragEnabled(IPluginContext *pContext, const cell_t *params)
{
#if SOURCE_ENGINE > SE_EPISODEONE
		IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);
	
		if (!m_pPhysicsObject)
		{
			return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
		}
	
		return m_pPhysicsObject->IsDragEnabled();
#else
	return pContext->ThrowNativeError("%s not supported by this engine.", "IsDragEnabled");
#endif
}

static cell_t IsMotionEnabled(IPluginContext *pContext, const cell_t *params)
{
#if SOURCE_ENGINE > SE_EPISODEONE
		IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);
	
		if (!m_pPhysicsObject)
		{
			return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
		}
	
		return m_pPhysicsObject->IsMotionEnabled();
#else
	return pContext->ThrowNativeError("%s not supported by this engine.", "IsMotionEnabled");
#endif
}

///////////////////////////////////////////////////////

static cell_t EnableCollisions(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->EnableCollisions((params[2] > 0)?true:false);

	return 1;
}

static cell_t EnableGravity(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->EnableGravity((params[2] > 0)?true:false);

	return 1;
}

static cell_t EnableDrag(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->EnableDrag((params[2] > 0)?true:false);

	return 1;
}

static cell_t EnableMotion(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->EnableMotion((params[2] > 0)?true:false);

	return 1;
}

/////////////////////////////////////////

static cell_t Wake(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->Wake();

	return 1;
}

static cell_t Sleep(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->Sleep();

	return 1;
}

///////////////////////////////////////////

static cell_t SetMass(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->SetMass(sp_ctof(params[2]));

	return 1;
}

static cell_t GetMass(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return sp_ftoc(m_pPhysicsObject->GetMass());
}

///////////////////////////////////////////

static cell_t BecomeHinged(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->BecomeHinged(params[2]);

	return 1;
}

static cell_t RemoveHinged(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->RemoveHinged();

	return 1;
}

///////////////////////////////////////////

static cell_t IsPhysicsObject(IPluginContext *pContext, const cell_t *params)
{
	if (GetPhysicsObject(params[1]))
	{
		return 1;
	} else {
		return 0;
	}
}

///////////////////////////////////////////

static cell_t GetEnvironmentGravity(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	Vector envGravity;

#if SOURCE_ENGINE > SE_EPISODEONE
	pPhysicsEnvironment->GetGravity(&envGravity);
#else
	pPhysicsEnvironment->GetGravity(envGravity);
#endif

	cell_t *addr;
	pContext->LocalToPhysAddr(params[1], &addr);
	addr[0] = sp_ftoc(envGravity.x);
	addr[1] = sp_ftoc(envGravity.y);
	addr[2] = sp_ftoc(envGravity.z);

	return 1;
}

static cell_t SetEnvironmentGravity(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[1], &addr);

	Vector newGrav = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	pPhysicsEnvironment->SetGravity(newGrav);

	return 1;
}

static cell_t GetEnvironmentAirDensity(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	float density = pPhysicsEnvironment->GetAirDensity();

	return sp_ftoc(density);
}

static cell_t SetEnvironmentAirDensity(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	pPhysicsEnvironment->SetAirDensity(sp_ctof(params[1]));

	return 1;
}

///////////////////////////////////////////

IPhysicsObject *GetPhysicsObject(int iEntityIndex)
{
	CBaseEntity *pEntity = PEntityOfEntIndex(iEntityIndex)->GetUnknown()->GetBaseEntity();

	if (pEntity)
	{
		return GetPhysicsObject(pEntity);
	} else {
		 return NULL;
	}
}

IPhysicsObject *GetPhysicsObject(CBaseEntity *pEntity)
{
	datamap_t *data = gamehelpers->GetDataMap(pEntity);

	if (!data) 
	{
		return NULL;
	}

	typedescription_t *type = gamehelpers->FindInDataMap(data, "m_pPhysicsObject");

	if (!type)
	{
		return NULL;
	}

#if SOURCE_ENGINE >= SE_LEFT4DEAD
	return *(IPhysicsObject **)((char *)pEntity + type->fieldOffset);
#else
	return *(IPhysicsObject **)((char *)pEntity + type->fieldOffset[TD_OFFSET_NORMAL]);
#endif
}

BEGIN_NATIVES(Phys)
	ADD_NATIVE(Phys, IsStatic)
	ADD_NATIVE(Phys, IsAsleep)
	ADD_NATIVE(Phys, IsHinged)
	ADD_NATIVE(Phys, IsCollisionEnabled)
	ADD_NATIVE(Phys, IsGravityEnabled)
	ADD_NATIVE(Phys, IsDragEnabled)
	ADD_NATIVE(Phys, IsMotionEnabled)
	ADD_NATIVE(Phys, EnableCollisions)
	ADD_NATIVE(Phys, EnableGravity)
	ADD_NATIVE(Phys, EnableDrag)
	ADD_NATIVE(Phys, EnableMotion)
	ADD_NATIVE(Phys, Wake)
	ADD_NATIVE(Phys, Sleep)
	ADD_NATIVE(Phys, SetMass)
	ADD_NATIVE(Phys, GetMass)
	ADD_NATIVE(Phys, BecomeHinged)
	ADD_NATIVE(Phys, RemoveHinged)
	ADD_NATIVE(Phys, IsPhysicsObject)
	ADD_NATIVE(Phys, GetEnvironmentGravity)
	ADD_NATIVE(Phys, SetEnvironmentGravity)
	ADD_NATIVE(Phys, GetEnvironmentAirDensity)
	ADD_NATIVE(Phys, SetEnvironmentAirDensity)
END_NATIVES()
