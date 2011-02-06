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
#include "physhandles.h"

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
#if SOURCE_ENGINE > SE_DARKMESSIAH
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
#if SOURCE_ENGINE > SE_DARKMESSIAH
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
#if SOURCE_ENGINE > SE_DARKMESSIAH
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
#if SOURCE_ENGINE > SE_DARKMESSIAH
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

static cell_t SetMaterialIndex(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	m_pPhysicsObject->SetMaterialIndex(params[2]);

	return 1;
}

static cell_t GetMaterialIndex(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsObject *m_pPhysicsObject = GetPhysicsObject(params[1]);

	if (!m_pPhysicsObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	return m_pPhysicsObject->GetMaterialIndex();
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

static cell_t LocalToWorld(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[3], &addr);

	Vector inputVec = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));
	Vector outputVec;

	pObject->LocalToWorld(&outputVec, inputVec);

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[2], &addr2);
	addr2[0] = sp_ftoc(outputVec.x);
	addr2[1] = sp_ftoc(outputVec.y);
	addr2[2] = sp_ftoc(outputVec.z);

	return 1;
}

static cell_t WorldToLocal(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[3], &addr);

	Vector inputVec = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));
	Vector outputVec;

	pObject->WorldToLocal(&outputVec, inputVec);

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[2], &addr2);
	addr2[0] = sp_ftoc(outputVec.x);
	addr2[1] = sp_ftoc(outputVec.y);
	addr2[2] = sp_ftoc(outputVec.z);

	return 1;
}

static cell_t CalculateForceOffset(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	Vector forceVector = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[3], &addr2);
	Vector worldPosition = Vector(sp_ctof(addr2[0]), sp_ctof(addr2[1]), sp_ctof(addr2[2]));

	Vector centerForce;
	AngularImpulse centerTorque;

	pObject->CalculateForceOffset(forceVector, worldPosition, &centerForce, &centerTorque);

	cell_t *addr3;
	pContext->LocalToPhysAddr(params[3], &addr3);
	addr3[0] = sp_ftoc(centerForce.x);
	addr3[1] = sp_ftoc(centerForce.y);
	addr3[2] = sp_ftoc(centerForce.z);

	cell_t *addr4;
	pContext->LocalToPhysAddr(params[3], &addr4);
	addr4[0] = sp_ftoc(centerTorque.x);
	addr4[1] = sp_ftoc(centerTorque.y);
	addr4[2] = sp_ftoc(centerTorque.z);

	return 1;
}

static cell_t CalculateVelocityOffset(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	Vector forceVector = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[3], &addr2);
	Vector worldPosition = Vector(sp_ctof(addr2[0]), sp_ctof(addr2[1]), sp_ctof(addr2[2]));

	Vector centerVelocity;
	AngularImpulse centerAngularVelocity;

	pObject->CalculateVelocityOffset(forceVector, worldPosition, &centerVelocity, &centerAngularVelocity);

	cell_t *addr3;
	pContext->LocalToPhysAddr(params[3], &addr3);
	addr3[0] = sp_ftoc(centerVelocity.x);
	addr3[1] = sp_ftoc(centerVelocity.y);
	addr3[2] = sp_ftoc(centerVelocity.z);

	cell_t *addr4;
	pContext->LocalToPhysAddr(params[3], &addr4);
	addr4[0] = sp_ftoc(centerAngularVelocity.x);
	addr4[1] = sp_ftoc(centerAngularVelocity.y);
	addr4[2] = sp_ftoc(centerAngularVelocity.z);

	return 1;
}

static cell_t ApplyForceCenter(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	Vector forceVector = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	pObject->ApplyForceCenter(forceVector);

	return 1;
}

static cell_t ApplyTorqueCenter(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	AngularImpulse torque = AngularImpulse(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	pObject->ApplyTorqueCenter(torque);

	return 1;
}

static cell_t AddVelocity(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	Vector velocity = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[3], &addr2);
	AngularImpulse angularVelocity = AngularImpulse(sp_ctof(addr2[0]), sp_ctof(addr2[1]), sp_ctof(addr2[2]));
	
	pObject->AddVelocity(&velocity, &angularVelocity);

	return 1;
}

static cell_t SetVelocity(IPluginContext *pContext, const cell_t *params)
{
	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return pContext->ThrowNativeError("IPhysicsEnvironment null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	Vector velocity = Vector(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));

	cell_t *addr2;
	pContext->LocalToPhysAddr(params[3], &addr2);
	AngularImpulse angularVelocity = AngularImpulse(sp_ctof(addr2[0]), sp_ctof(addr2[1]), sp_ctof(addr2[2]));

	if (params[3] > 0)
	{
		pObject->SetVelocityInstantaneous(&velocity, &angularVelocity);
	} else {
		pObject->SetVelocity(&velocity, &angularVelocity);
	}

	return 1;
}

///////////////////////////////////////////

static cell_t IsPhysicsObject(IPluginContext *pContext, const cell_t *params)
{
	return (GetPhysicsObject(params[1]))?1:0;
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

#if SOURCE_ENGINE > SE_DARKMESSIAH
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

static cell_t CreateSpring(IPluginContext *pContext, const cell_t *params)
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

	IPhysicsObject *pObjectStart = GetPhysicsObject(params[1]);

	if (!pObjectStart)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	IPhysicsObject *pObjectEnd = GetPhysicsObject(params[2]);

	if (!pObjectEnd)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[2]);
	}

	springparams_t spring;

	cell_t *cellStartPos;
	pContext->LocalToPhysAddr(params[3], &cellStartPos);
	spring.startPosition = Vector(sp_ctof(cellStartPos[0]), sp_ctof(cellStartPos[1]), sp_ctof(cellStartPos[2]));

	cell_t *cellEndPos;
	pContext->LocalToPhysAddr(params[4], &cellEndPos);
	spring.endPosition = Vector(sp_ctof(cellEndPos[0]), sp_ctof(cellEndPos[1]), sp_ctof(cellEndPos[2]));

	spring.useLocalPositions = (params[5] > 0)?true:false;

	spring.naturalLength = sp_ctof(params[6]);

	spring.constant = sp_ctof(params[7]);
	spring.damping = sp_ctof(params[8]);
	spring.relativeDamping = sp_ctof(params[9]);

	spring.onlyStretch = (params[10] > 0)?true:false;

	IPhysicsSpring *pSpring = pPhysicsEnvironment->CreateSpring(pObjectStart, pObjectEnd, &spring);

	RETURN_NEW_HANDLE(Spring, pSpring);
}

static cell_t CreateFixedConstraint(IPluginContext *pContext, const cell_t *params)
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

	IPhysicsObject *pReferenceObject = GetPhysicsObject(params[1]);

	if (!pReferenceObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	IPhysicsObject *pAttachedObject = GetPhysicsObject(params[2]);

	if (!pAttachedObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[2]);
	}

	IPhysicsConstraintGroup *pConstraintGroup = NULL;
	GET_POINTER_FROM_HANDLE(ConstraintGroup, 3, pConstraintGroup);

	constraint_fixedparams_t fixedconstraint;

	fixedconstraint.InitWithCurrentObjectState(pReferenceObject, pAttachedObject);

	fixedconstraint.constraint.strength = sp_ctof(params[4]);
	fixedconstraint.constraint.forceLimit = sp_ctof(params[5]);
	fixedconstraint.constraint.torqueLimit = sp_ctof(params[6]);

	fixedconstraint.constraint.bodyMassScale[0] = sp_ctof(params[7]);
	fixedconstraint.constraint.bodyMassScale[1] = sp_ctof(params[8]);

	fixedconstraint.constraint.isActive = (params[9] > 0)?true:false;

	IPhysicsConstraint *pConstraint = pPhysicsEnvironment->CreateFixedConstraint(pReferenceObject, pAttachedObject, pConstraintGroup, fixedconstraint);

	RETURN_NEW_HANDLE(Constraint, pConstraint);
}

static cell_t CreateLengthConstraint(IPluginContext *pContext, const cell_t *params)
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

	IPhysicsObject *pReferenceObject = GetPhysicsObject(params[1]);

	if (!pReferenceObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	IPhysicsObject *pAttachedObject = GetPhysicsObject(params[2]);

	if (!pAttachedObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[2]);
	}

	IPhysicsConstraintGroup *pConstraintGroup = NULL;
	GET_POINTER_FROM_HANDLE(ConstraintGroup, 3, pConstraintGroup);

	constraint_lengthparams_t lengthconstraint;

	cell_t *refPosition;
	pContext->LocalToPhysAddr(params[4], &refPosition);
	//pReferenceObject->WorldToLocal(&lengthconstraint.objectPosition[0], Vector(sp_ctof(refPosition[0]), sp_ctof(refPosition[1]), sp_ctof(refPosition[2])));
	lengthconstraint.objectPosition[0] = Vector(sp_ctof(refPosition[0]), sp_ctof(refPosition[1]), sp_ctof(refPosition[2]));

	cell_t *attachedPosition;
	pContext->LocalToPhysAddr(params[5], &attachedPosition);
	//pAttachedObject->WorldToLocal(&lengthconstraint.objectPosition[1], Vector(sp_ctof(attachedPosition[0]), sp_ctof(attachedPosition[1]), sp_ctof(attachedPosition[2])));
	lengthconstraint.objectPosition[1] = Vector(sp_ctof(attachedPosition[0]), sp_ctof(attachedPosition[1]), sp_ctof(attachedPosition[2]));

	lengthconstraint.totalLength = sp_ctof(params[6]);
	lengthconstraint.minLength = sp_ctof(params[7]);

	lengthconstraint.constraint.strength = sp_ctof(params[8]);
	lengthconstraint.constraint.forceLimit = sp_ctof(params[9]);
	lengthconstraint.constraint.torqueLimit = sp_ctof(params[10]);

	lengthconstraint.constraint.bodyMassScale[0] = sp_ctof(params[11]);
	lengthconstraint.constraint.bodyMassScale[1] = sp_ctof(params[12]);

	lengthconstraint.constraint.isActive = (params[13] > 0)?true:false;

	IPhysicsConstraint *pConstraint = pPhysicsEnvironment->CreateLengthConstraint(pReferenceObject, pAttachedObject, pConstraintGroup, lengthconstraint);

	RETURN_NEW_HANDLE(Constraint, pConstraint);
}

static cell_t CreateHingeConstraint(IPluginContext *pContext, const cell_t *params)
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

	IPhysicsObject *pReferenceObject = GetPhysicsObject(params[1]);

	if (!pReferenceObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	IPhysicsObject *pAttachedObject = GetPhysicsObject(params[2]);

	if (!pAttachedObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[2]);
	}

	IPhysicsConstraintGroup *pConstraintGroup = NULL;
	GET_POINTER_FROM_HANDLE(ConstraintGroup, 3, pConstraintGroup);

	constraint_hingeparams_t hingeconstraint;

	cell_t *worldPosition;
	pContext->LocalToPhysAddr(params[4], &worldPosition);
	hingeconstraint.worldPosition = Vector(sp_ctof(worldPosition[0]), sp_ctof(worldPosition[1]), sp_ctof(worldPosition[2]));

	cell_t *worldAxisDirection;
	pContext->LocalToPhysAddr(params[5], &worldAxisDirection);
	hingeconstraint.worldAxisDirection = Vector(sp_ctof(worldAxisDirection[0]), sp_ctof(worldAxisDirection[1]), sp_ctof(worldAxisDirection[2]));

	hingeconstraint.hingeAxis.minRotation = sp_ctof(params[6]);
	hingeconstraint.hingeAxis.maxRotation = sp_ctof(params[7]);
	hingeconstraint.hingeAxis.angularVelocity = sp_ctof(params[8]);
	hingeconstraint.hingeAxis.torque = sp_ctof(params[9]);

	hingeconstraint.constraint.strength = sp_ctof(params[10]);
	hingeconstraint.constraint.forceLimit = sp_ctof(params[11]);
	hingeconstraint.constraint.torqueLimit = sp_ctof(params[12]);

	hingeconstraint.constraint.bodyMassScale[0] = sp_ctof(params[13]);
	hingeconstraint.constraint.bodyMassScale[1] = sp_ctof(params[14]);

	hingeconstraint.constraint.isActive = (params[15] > 0)?true:false;

	IPhysicsConstraint *pConstraint = pPhysicsEnvironment->CreateHingeConstraint(pReferenceObject, pAttachedObject, pConstraintGroup, hingeconstraint);

	RETURN_NEW_HANDLE(Constraint, pConstraint);
}

///////////////////////////////////////////

static cell_t CreateConstraintGroup(IPluginContext *pContext, const cell_t *params)
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

	constraint_groupparams_t constraintgroup;

	constraintgroup.additionalIterations = params[1];
	constraintgroup.minErrorTicks = params[2];
	constraintgroup.errorTolerance = sp_ctof(params[3]);

	IPhysicsConstraintGroup *pConstraintGroup = pPhysicsEnvironment->CreateConstraintGroup(constraintgroup);

	RETURN_NEW_HANDLE(ConstraintGroup, pConstraintGroup);
}

///////////////////////////////////////////

static cell_t CreateFrictionSnapshot(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	IPhysicsObject *pObject = GetPhysicsObject(params[1]);

	if (!pObject)
	{
		return pContext->ThrowNativeError("IPhysicsObject for entity %d null.", params[1]);
	}

	IPhysicsFrictionSnapshot *pSnapshot = pObject->CreateFrictionSnapshot();

	FrictionSnapshotHandle *fsh = new FrictionSnapshotHandle;
	fsh->pObject = pObject;
	fsh->pSnapshot = pSnapshot;

	RETURN_NEW_HANDLE(FrictionSnapshot, fsh);
}

static cell_t IsFrictionSnapshotValid(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	FrictionSnapshotHandle *fsh = NULL;
	GET_POINTER_FROM_HANDLE(FrictionSnapshot, 1, fsh);

	return fsh->pSnapshot->IsValid();
}

static cell_t NextFrictionData(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	FrictionSnapshotHandle *fsh = NULL;
	GET_POINTER_FROM_HANDLE(FrictionSnapshot, 1, fsh);

	fsh->pSnapshot->NextFrictionData();

	return 1;
}

static cell_t GetTouchingEntity(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	FrictionSnapshotHandle *fsh = NULL;
	GET_POINTER_FROM_HANDLE(FrictionSnapshot, 1, fsh);

	IPhysicsObject *pOther = fsh->pSnapshot->GetObject(1);
	CBaseEntity *pOtherEntity = static_cast<CBaseEntity *>(pOther->GetGameData());

	return GetEntIndex(pOtherEntity);
}

static cell_t GetContactPoint(IPluginContext *pContext, const cell_t *params)
{
	if (!iphysics)
	{
		return pContext->ThrowNativeError("IPhysics null.");
	}

	FrictionSnapshotHandle *fsh = NULL;
	GET_POINTER_FROM_HANDLE(FrictionSnapshot, 1, fsh);

	Vector contactPoint;

	fsh->pSnapshot->GetContactPoint(contactPoint);

	cell_t *addr;
	pContext->LocalToPhysAddr(params[2], &addr);
	addr[0] = sp_ftoc(contactPoint.x);
	addr[1] = sp_ftoc(contactPoint.y);
	addr[2] = sp_ftoc(contactPoint.z);

	return 1;
}

///////////////////////////////////////////

static cell_t GetIndexOfMaterial(IPluginContext *pContext, const cell_t *params)
{
	if (!surfaceprops)
	{
		return pContext->ThrowNativeError("IPhysicsSurfaceProps null.");
	}

	char *materialName;
	pContext->LocalToString(params[1], &materialName);

	return surfaceprops->GetSurfaceIndex(materialName);
}

static cell_t GetMaterialName(IPluginContext *pContext, const cell_t *params)
{
	if (!surfaceprops)
	{
		return pContext->ThrowNativeError("IPhysicsSurfaceProps null.");
	}

	char *materialName = new char[params[3]];
	int numbytes = g_pSM->Format(materialName, params[3], "%s", surfaceprops->GetString(params[1]));
	pContext->StringToLocal(params[2], numbytes, materialName);
	return numbytes;
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
	ADD_NATIVE(Phys, SetMaterialIndex)
	ADD_NATIVE(Phys, GetMaterialIndex)
	ADD_NATIVE(Phys, BecomeHinged)
	ADD_NATIVE(Phys, RemoveHinged)
	ADD_NATIVE(Phys, IsPhysicsObject)
	ADD_NATIVE(Phys, GetEnvironmentGravity)
	ADD_NATIVE(Phys, SetEnvironmentGravity)
	ADD_NATIVE(Phys, GetEnvironmentAirDensity)
	ADD_NATIVE(Phys, SetEnvironmentAirDensity)
	ADD_NATIVE(Phys, CreateSpring)
	ADD_NATIVE(Phys, LocalToWorld)
	ADD_NATIVE(Phys, WorldToLocal)
	ADD_NATIVE(Phys, CalculateForceOffset)
	ADD_NATIVE(Phys, CalculateVelocityOffset)
	ADD_NATIVE(Phys, CreateFixedConstraint)
	ADD_NATIVE(Phys, ApplyForceCenter)
	ADD_NATIVE(Phys, ApplyTorqueCenter)
	ADD_NATIVE(Phys, AddVelocity)
	ADD_NATIVE(Phys, CreateLengthConstraint)
	ADD_NATIVE(Phys, CreateHingeConstraint)
	ADD_NATIVE(Phys, SetVelocity)
	ADD_NATIVE(Phys, CreateConstraintGroup)
	ADD_NATIVE(Phys, CreateFrictionSnapshot)
	ADD_NATIVE(Phys, IsFrictionSnapshotValid)
	ADD_NATIVE(Phys, NextFrictionData)
	ADD_NATIVE(Phys, GetTouchingEntity)
	ADD_NATIVE(Phys, GetContactPoint)
	ADD_NATIVE(Phys, GetIndexOfMaterial)
	ADD_NATIVE(Phys, GetMaterialName)
END_NATIVES()
