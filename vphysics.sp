#include <sourcemod>
#include <sdktools>

#include <vphysics>

public OnPluginStart() {
	RegAdminCmd("sm_freeze", Command_Freeze, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_unfreeze", Command_UnFreeze, ADMFLAG_CHEATS, "");
	
	RegAdminCmd("sm_nograv", Command_NoGrav, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_grav", Command_Grav, ADMFLAG_CHEATS, "");
	
	RegAdminCmd("sm_freeze_all", Command_FreezeAll, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_unfreeze_all", Command_UnFreezeAll, ADMFLAG_CHEATS, "");
	
	RegAdminCmd("sm_nograv_all", Command_NoGravAll, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_grav_all", Command_GravAll, ADMFLAG_CHEATS, "");
	
	RegAdminCmd("sm_pivot", Command_Pivot, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_stoppivot", Command_RemPivot, ADMFLAG_CHEATS, "");

	RegAdminCmd("sm_flip", Command_Flip, ADMFLAG_CHEATS, "");
}

public Action:Command_Flip(client, args)
{
	new Float:gravity[3];

	Phys_GetEnvironmentGravity(gravity);
	
	gravity[0] *= -1;
	gravity[1] *= -1;
	gravity[2] *= -1;
	
	Phys_SetEnvironmentGravity(gravity);
	
	new max = GetMaxEntities();
	for (new i = MaxClients; i < max; i++)
	{
		if (IsValidEntity(i) && Phys_IsPhysicsObject(i))
			Phys_Wake(i);
	}
	
	return Plugin_Handled;
}

public Action:Command_Pivot(client, args)
{
	new String:arg1[32];
	GetCmdArg(1, arg1, 32);

	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_BecomeHinged(ent, StringToInt(arg1));
	
	return Plugin_Handled;
}

public Action:Command_RemPivot(client, args)
{
	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_RemoveHinged(ent);
	
	return Plugin_Handled;
}

public Action:Command_FreezeAll(client, args)
{
	new max = GetMaxEntities();
	for (new i = MaxClients; i < max; i++)
	{
		if (IsValidEntity(i) && Phys_IsPhysicsObject(i))
			Phys_EnableMotion(i, false);
	}
	
	return Plugin_Handled;
}

public Action:Command_UnFreezeAll(client, args)
{
	new max = GetMaxEntities();
	for (new i = MaxClients; i < max; i++)
	{
		if (IsValidEntity(i) && Phys_IsPhysicsObject(i))
			Phys_EnableMotion(i, true);
	}
	
	return Plugin_Handled;
}

public Action:Command_NoGravAll(client, args)
{
	new max = GetMaxEntities();
	for (new i = MaxClients; i < max; i++)
	{
		if (IsValidEntity(i) && Phys_IsPhysicsObject(i))
			Phys_EnableGravity(i, false);
	}
	
	return Plugin_Handled;
}

public Action:Command_GravAll(client, args)
{
	new max = GetMaxEntities();
	for (new i = MaxClients; i < max; i++)
	{
		if (IsValidEntity(i) && Phys_IsPhysicsObject(i))
			Phys_EnableGravity(i, true);
	}
	
	return Plugin_Handled;
}

public Action:Command_Freeze(client, args)
{
	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_EnableMotion(ent, false);
	
	return Plugin_Handled;
}

public Action:Command_UnFreeze(client, args)
{
	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_EnableMotion(ent, true);
	
	return Plugin_Handled;
}

public Action:Command_NoGrav(client, args)
{
	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_EnableGravity(ent, false);
	
	return Plugin_Handled;
}

public Action:Command_Grav(client, args)
{
	new ent = GetClientAimTarget(client, false);
	if (IsValidEntity(ent))
		Phys_EnableGravity(ent, true);
	
	return Plugin_Handled;
}