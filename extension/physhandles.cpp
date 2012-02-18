#include "physhandles.h"

SIMPLE_HANDLER(Spring);
SIMPLE_HANDLER(Constraint);
SIMPLE_HANDLER(ConstraintGroup);

START_HANDLER(FrictionSnapshot)
	CHECK_ENV(FrictionSnapshot);

	IPhysicsObject *pObject = ((FrictionSnapshotHandle *)object)->pObject;
	IPhysicsFrictionSnapshot *pSnapshot = ((FrictionSnapshotHandle *)object)->pSnapshot;

	pObject->DestroyFrictionSnapshot(pSnapshot);

	delete (FrictionSnapshotHandle *)object;
END_HANDLER(FrictionSnapshot)

void RegisterHandles()
{
	CREATE_TYPE(Spring);
	CREATE_TYPE(Constraint);
	CREATE_TYPE(ConstraintGroup);
	CREATE_TYPE(FrictionSnapshot);
}

void UnregisterHandles()
{
	REMOVE_TYPE(Spring);
	REMOVE_TYPE(Constraint);
	REMOVE_TYPE(ConstraintGroup);
	REMOVE_TYPE(FrictionSnapshot);
}
