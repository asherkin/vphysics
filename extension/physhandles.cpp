#include "physhandles.h"

// IPhysicsObject
HandleType_t g_IPhysicsObjectType = 0;	/* Holds the HandleType ID */

void IPhysicsObjectTypeHandler::OnHandleDestroy(HandleType_t type, void *object)
{
	return g_pSM->LogError(myself, "You shouldn't be calling this.");
}

/* Create an instance of the handler */
IPhysicsObjectTypeHandler g_IPhysicsObjectTypeHandler;

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
	/* Create default access rights */
	HandleAccess IPhysicsObjectRules;
	g_pHandleSys->InitAccessDefaults(NULL, &IPhysicsObjectRules);

	/* Restrict delete to only our identity */
	IPhysicsObjectRules.access[HandleAccess_Delete] = HANDLE_RESTRICT_IDENTITY;

	/* Register the type with our security permissions */
	g_IPhysicsObjectType = g_pHandleSys->CreateType("IPhysicsObject", 
		&g_IPhysicsObjectTypeHandler, 
		0, 
		NULL, 
		&IPhysicsObjectRules, 
		myself->GetIdentity(), 
		NULL);

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
	g_pHandleSys->RemoveType(g_IPhysicsObjectType, myself->GetIdentity());
	g_pHandleSys->RemoveType(g_IPhysicsSpringType, myself->GetIdentity());
	g_pHandleSys->RemoveType(g_IPhysicsConstraintType, myself->GetIdentity());
}