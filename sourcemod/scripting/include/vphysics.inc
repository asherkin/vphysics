#if defined _sdktools_phys_included
  #endinput
#endif
#define _sdktools_phys_included

native bool:Phys_IsStatic(entity);
native bool:Phys_IsAsleep(entity);
native bool:Phys_IsHinged(entity);
native bool:Phys_IsCollisionEnabled(entity);
native bool:Phys_IsGravityEnabled(entity);
native bool:Phys_IsDragEnabled(entity);
native bool:Phys_IsMotionEnabled(entity);
native Phys_EnableCollisions(entity, bool:enable);
native Phys_EnableGravity(entity, bool:enable);
native Phys_EnableDrag(entity, bool:enable);
native Phys_EnableMotion(entity, bool:enable);
native Phys_Wake(entity);
native Phys_Sleep(entity);
native Phys_SetMass(entity, Float:mass);
native Float:Phys_GetMass(entity);
native Phys_BecomeHinged(entity, axis);
native Phys_RemoveHinged(entity);
native Phys_IsPhysicsObject(entity);
native Phys_GetEnvironmentGravity(Float:gravity[3]);
native Phys_SetEnvironmentGravity(const Float:gravity[3]);
native Float:Phys_GetEnvironmentAirDensity();
native Phys_SetEnvironmentAirDensity(Float:density);

/**
 * Do not edit below this line!
 */
public Extension:__ext_vphysics = 
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