#if defined _vphysics_included
  #endinput
#endif
#define _vphysics_included

native bool Phys_IsPhysicsObject(int entity);

native bool Phys_IsStatic(int entity);
native bool Phys_IsAsleep(int entity);
native bool Phys_IsHinged(int entity);
native bool Phys_IsCollisionEnabled(int entity);
native bool Phys_IsGravityEnabled(int entity);
native bool Phys_IsDragEnabled(int entity);
native bool Phys_IsMotionEnabled(int entity);
native void Phys_EnableCollisions(int entity, bool enable);
native void Phys_EnableGravity(int entity, bool enable);
native void Phys_EnableDrag(int entity, bool enable);
native void Phys_EnableMotion(int entity, bool enable);
native void Phys_Wake(int entity);
native void Phys_Sleep(int entity);
native void Phys_SetMass(int entity, float mass);
native float Phys_GetMass(int entity);
native void Phys_SetMaterialIndex(int entity, int materialIndex);
native int Phys_GetMaterialIndex(int entity);
native void Phys_BecomeHinged(int entity, int axis);
native void Phys_RemoveHinged(int entity);
native void Phys_LocalToWorld(int entity, float worldPosition[3], const float localPosition[3]);
native void Phys_WorldToLocal(int entity, float localPosition[3], const float worldPosition[3]);

native void Phys_CalculateForceOffset(int entity, const float forceVector[3], const float worldPosition[3], float centerForce[3], float centerTorque[3]);
native void Phys_CalculateVelocityOffset(int entity, const float forceVector[3], const float worldPosition[3], float centerVelocity[3], float centerAngularVelocity[3]);
native void Phys_ApplyForceCenter(int entity, const float forceVector[3]);
native void Phys_ApplyTorqueCenter(int entity, const float torque[3]);
native void Phys_AddVelocity(int entity, const float velocity[3], const float angularVelocity[3]);
native void Phys_SetVelocity(int entity, const float velocity[3], const float angularVelocity[3], bool instantaneous = false);

native void Phys_GetEnvironmentGravity(float gravity[3]);
native void Phys_SetEnvironmentGravity(const float gravity[3]);
native float Phys_GetEnvironmentAirDensity();
native void Phys_SetEnvironmentAirDensity(float density);

native Handle Phys_CreateConstraintGroup(int additionalIterations = 0, int minErrorTicks = 15, float errorTolerance = 3.0);

native Handle Phys_CreateSpring(int startObject, int endObject, const float startPos[3], const float endPos[3], bool useLocalPositions, float naturalLength, float constant, float damping, float relativeDamping, bool onlyStretch);

native Handle Phys_CreateFixedConstraint(int referenceObject, int attachedObject, Handle constraintGroup, float strength = 1.0, float forceLimit = 0.0, float torqueLimit = 0.0, float bodyMassScaleRef = 1.0, float bodyMassScaleAttached = 1.0, bool isActive = true);
native Handle Phys_CreateLengthConstraint(int referenceObject, int attachedObject, Handle constraintGroup, const float refPosition[3], const float attachedPosition[3], float totalLength, float minLength = 0.0, float strength = 1.0, float forceLimit = 0.0, float torqueLimit = 0.0, float bodyMassScaleRef = 1.0, float bodyMassScaleAttached = 1.0, bool isActive = true);
native Handle Phys_CreateHingeConstraint(int referenceObject, int attachedObject, Handle constraintGroup, const float worldPosition[3], const float worldAxisDirection[3], float minRotation = 0.0, float maxRotation = 0.0, float angularVelocity = 0.0, float torque = 0.0, float strength = 1.0, float forceLimit = 0.0, float torqueLimit = 0.0, float bodyMassScaleRef = 1.0, float bodyMassScaleAttached = 1.0, bool isActive = true);

native Handle Phys_CreateFrictionSnapshot(int entity);
native bool Phys_IsFrictionSnapshotValid(Handle snapshot);
native bool Phys_NextFrictionData(Handle snapshot);
native int Phys_GetTouchingEntity(Handle snapshot);
native void Phys_GetContactPoint(Handle snapshot, float contactPoint[3]);

native int Phys_GetIndexOfMaterial(const char[] material);

forward void Phys_OnObjectWake(int entity);
forward void Phys_OnObjectSleep(int entity);

stock void Phys_ApplyForceOffset(int entity, const float forceVector[3], const float worldPosition[3])
{
	float centerForce[3];
	float centerTorque[3];

	Phys_CalculateForceOffset(entity, forceVector, worldPosition, centerForce, centerTorque);

	Phys_ApplyForceCenter(entity, centerForce);
	Phys_ApplyTorqueCenter(entity, centerTorque);
}

stock void Phys_AddVelocityOffset(int entity, const float forceVector[3], const float worldPosition[3])
{
	float centerVelocity[3];
	float centerAngularVelocity[3];

	Phys_CalculateVelocityOffset(entity, forceVector, worldPosition, centerVelocity, centerAngularVelocity);

	Phys_AddVelocity(entity, centerVelocity, centerAngularVelocity);
}

stock bool Phys_IsTouchingEntity(int entity, int other)
{
	Handle snapshot = Phys_CreateFrictionSnapshot(entity);

	bool touching = false;

	while (Phys_IsFrictionSnapshotValid(snapshot))
	{
		if (Phys_GetTouchingEntity(snapshot) == other)
		{
			touching = true;
			break;
		}

		Phys_NextFrictionData(snapshot);
	}

	delete snapshot;

	return touching;
}

/**
 * Do not edit below this line!
 */
public Extension __ext_vphysics = 
{
	name = "VPhysics",
	file = "vphysics.ext",
	autoload = 1,
	#if defined REQUIRE_EXTENSIONS
		required = 1,
	#else
		required = 0,
	#endif
}

#if !defined REQUIRE_EXTENSIONS
public void __ext_vphysics_SetNTVOptional()
{
	MarkNativeAsOptional("Phys_IsPhysicsObject");
	MarkNativeAsOptional("Phys_IsStatic");
	MarkNativeAsOptional("Phys_IsAsleep");
	MarkNativeAsOptional("Phys_IsHinged");
	MarkNativeAsOptional("Phys_IsCollisionEnabled");
	MarkNativeAsOptional("Phys_IsGravityEnabled");
	MarkNativeAsOptional("Phys_IsDragEnabled");
	MarkNativeAsOptional("Phys_IsMotionEnabled");
	MarkNativeAsOptional("Phys_EnableCollisions");
	MarkNativeAsOptional("Phys_EnableGravity");
	MarkNativeAsOptional("Phys_EnableDrag");
	MarkNativeAsOptional("Phys_EnableMotion");
	MarkNativeAsOptional("Phys_Wake");
	MarkNativeAsOptional("Phys_Sleep");
	MarkNativeAsOptional("Phys_SetMass");
	MarkNativeAsOptional("Phys_GetMass");
	MarkNativeAsOptional("Phys_SetMaterialIndex");
	MarkNativeAsOptional("Phys_GetMaterialIndex");
	MarkNativeAsOptional("Phys_BecomeHinged");
	MarkNativeAsOptional("Phys_RemoveHinged");
	MarkNativeAsOptional("Phys_LocalToWorld");
	MarkNativeAsOptional("Phys_WorldToLocal");
	MarkNativeAsOptional("Phys_CalculateForceOffset");
	MarkNativeAsOptional("Phys_CalculateVelocityOffset");
	MarkNativeAsOptional("Phys_ApplyForceCenter");
	MarkNativeAsOptional("Phys_ApplyTorqueCenter");
	MarkNativeAsOptional("Phys_AddVelocity");
	MarkNativeAsOptional("Phys_SetVelocity");
	MarkNativeAsOptional("Phys_GetEnvironmentGravity");
	MarkNativeAsOptional("Phys_SetEnvironmentGravity");
	MarkNativeAsOptional("Phys_GetEnvironmentAirDensity");
	MarkNativeAsOptional("Phys_SetEnvironmentAirDensity");
	MarkNativeAsOptional("Phys_CreateConstraintGroup");
	MarkNativeAsOptional("Phys_CreateSpring");
	MarkNativeAsOptional("Phys_CreateFixedConstraint");
	MarkNativeAsOptional("Phys_CreateLengthConstraint");
	MarkNativeAsOptional("Phys_CreateHingeConstraint");
	MarkNativeAsOptional("Phys_CreateFrictionSnapshot");
	MarkNativeAsOptional("Phys_IsFrictionSnapshotValid");
	MarkNativeAsOptional("Phys_NextFrictionData");
	MarkNativeAsOptional("Phys_GetTouchingEntity");
	MarkNativeAsOptional("Phys_GetContactPoint");
	MarkNativeAsOptional("Phys_GetIndexOfMaterial");
}
#endif
