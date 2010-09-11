#include <sourcemod>
#include <sdktools>

#include <vphysics>

public OnPluginStart() {
	RegAdminCmd("sm_weld", Command_Weld, ADMFLAG_CHEATS, "");
	RegAdminCmd("sm_rope", Command_Rope, ADMFLAG_CHEATS, "");
}

public Action:Command_Weld(client, args)
{
	static tempEntIndex = 0;
	
	if (!tempEntIndex)
	{
		new entity = GetClientAimTarget(client, false);
		if (IsValidEntity(entity) && Phys_IsPhysicsObject(entity))
		{
			tempEntIndex = entity;
			ReplyToCommand(client, "[VPhys] Set reference entity to %d", tempEntIndex);
		} else {
			ReplyToCommand(client, "[VPhys] Target entity invalid, try again.");
		}
	} else {
		new entity = GetClientAimTarget(client, false);
		if (IsValidEntity(entity) && Phys_IsPhysicsObject(entity))
		{
			Phys_CreateFixedConstraint(tempEntIndex, entity);
			ReplyToCommand(client, "[VPhys] Welded entities %d and %d, reset reference entity.", tempEntIndex, entity);
		} else {
			ReplyToCommand(client, "[VPhys] Target entity invalid, reset reference entity.");
		}
		tempEntIndex = 0;
	}
	
	return Plugin_Handled;
}

public Action:Command_Rope(client, args)
{
	static tempEntIndex = 0;
	static Float:tempEntHitPos[3];
	
	new Float:eyePos[3];
	new Float:eyeAng[3];
	
	GetClientEyePosition(client, eyePos);
	GetClientEyeAngles(client, eyeAng);
	
	new Handle:trace = TR_TraceRayFilterEx(eyePos, eyeAng, MASK_SHOT, RayType_Infinite, TraceEntityFilterOnlyVPhysics);
	
	if (!tempEntIndex)
	{
		if(TR_DidHit(trace) && TR_GetEntityIndex(trace))
		{
			new Float:tempEntHitPosWorld[3];
			TR_GetEndPosition(tempEntHitPosWorld, trace);
			tempEntIndex = TR_GetEntityIndex(trace);
			Phys_WorldToLocal(tempEntIndex, tempEntHitPos, tempEntHitPosWorld);
			
			ReplyToCommand(client, "[VPhys] Set reference entity to %d", tempEntIndex);
		} else {
			ReplyToCommand(client, "[VPhys] Target entity invalid, try again.");
			return Plugin_Handled;
		}
	} else {
		if(TR_DidHit(trace) && TR_GetEntityIndex(trace))
		{
			new entIndex = TR_GetEntityIndex(trace);
			new Float:hitPosWorld[3];
			TR_GetEndPosition(hitPos, trace);
			new Float:hitPos[3];
			Phys_WorldToLocal(tempEntIndex, hitPos, hitPosWorld);
			
			new Float:distVec[3];
			MakeVectorFromPoints(tempEntHitPos, hitPos, distVec);
			
			Phys_CreateLengthConstraint(tempEntIndex, entIndex, tempEntHitPos, hitPos, GetVectorLength(distVec));
			ReplyToCommand(client, "[VPhys] Roped entities %d and %d, reset reference entity.", tempEntIndex, entIndex);
		} else {
			ReplyToCommand(client, "[VPhys] Target entity invalid, reset reference entity.");
		}
		
		tempEntIndex = 0;
	}
	
	CloseHandle(trace);
	
	return Plugin_Handled;
}

public bool:TraceEntityFilterOnlyVPhysics(entity, contentsMask)
{
    return ((entity > MaxClients) && Phys_IsPhysicsObject(entity));
}