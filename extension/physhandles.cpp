#include "physhandles.h"

// IPhysicsSpring
HandleType_t g_IPhysicsSpringType = 0;	/* Holds the HandleType ID */

void IPhysicsSpringTypeHandler::OnHandleDestroy(HandleType_t type, void *object)
{
	if (!iphysics)
	{
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysicsSpring called while IPhysics interface is null.");
	}

	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysicsSpring called while IPhysicsEnvironment pointer is null.");
	}

	pPhysicsEnvironment->DestroySpring((IPhysicsSpring *)object);
}

/* Create an instance of the handler */
IPhysicsSpringTypeHandler g_IPhysicsSpringTypeHandler;

// IPhysicsConstraint
HandleType_t g_IPhysicsConstraintType = 0;	/* Holds the HandleType ID */

void IPhysicsConstraintTypeHandler::OnHandleDestroy(HandleType_t type, void *object)
{
	if (!iphysics)
	{
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysicsConstraint called while IPhysics interface is null.");
	}

	IPhysicsEnvironment *pPhysicsEnvironment = iphysics->GetActiveEnvironmentByIndex(0);

	if (!pPhysicsEnvironment)
	{
		return g_pSM->LogError(myself, "OnHandleDestroy handler for IPhysicsConstraint called while IPhysicsEnvironment pointer is null.");
	}

	pPhysicsEnvironment->DestroyConstraint((IPhysicsConstraint *)object);
}

/* Create an instance of the handler */
IPhysicsConstraintTypeHandler g_IPhysicsConstraintTypeHandler;

void RegisterHandles()
{
	/* Register the type with default security permissions */
	g_IPhysicsSpringType = g_pHandleSys->CreateType("IPhysicsSpring", 
		&g_IPhysicsSpringTypeHandler, 
		0, 
		NULL, 
		NULL, 
		myself->GetIdentity(), 
		NULL);

	/* Register the type with default security permissions */
	g_IPhysicsConstraintType = g_pHandleSys->CreateType("IPhysicsConstraint", 
		&g_IPhysicsConstraintTypeHandler, 
		0, 
		NULL, 
		NULL, 
		myself->GetIdentity(), 
		NULL);
}

void UnregisterHandles()
{
	/* Remove the type on shutdown */
	g_pHandleSys->RemoveType(g_IPhysicsSpringType, myself->GetIdentity());
	g_pHandleSys->RemoveType(g_IPhysicsConstraintType, myself->GetIdentity());
}