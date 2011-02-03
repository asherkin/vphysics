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

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

/**
 * @file extension.h
 * @brief SDK Tools extension code header.
 */

#include "smsdk_ext.h"
#include <vphysics_interface.h>
#include <datamap.h>

/**
 * @brief Implementation of the SDK Tools extension.
 * Note: Uncomment one of the pre-defined virtual functions in order to use it.
 */
class SDKTools: public SDKExtension, public IMetamodListener
{
public: //public SDKExtension
	virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
	virtual void SDK_OnUnload();
	//virtual void SDK_OnAllLoaded();
	//virtual void SDK_OnPauseChange(bool paused);
	//virtual bool QueryRunning(char *error, size_t maxlength);
	//virtual bool QueryInterfaceDrop(SMInterface *pInterface);
	//virtual void NotifyInterfaceDrop(SMInterface *pInterface);
	//virtual void OnCoreMapStart(edict_t *pEdictList, int edictCount, int clientMax);
	//const char *GetExtensionVerString();
	//const char *GetExtensionDateString();
public:
#if defined SMEXT_CONF_METAMOD
	virtual bool SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	//virtual bool SDK_OnMetamodUnload(char *error, size_t maxlen);
	//virtual bool SDK_OnMetamodPauseChange(bool paused, char *error, size_t maxlen);
#endif
public: //IMetamodListener
	void OnLevelInit(char const *pMapName, 
		char const *pMapEntities, 
		char const *pOldLevel, 
		char const *pLandmarkName, 
		bool loadGame, 
		bool background);
};

extern SDKTools g_SdkTools;
extern CGlobalVars *gpGlobals;
/* Interfaces from engine or gamedll */
extern IPhysics *iphysics;

#if SOURCE_ENGINE >= SE_LEFT4DEAD
inline int IndexOfEdict(const edict_t *pEdict)
{
	return (int)(pEdict - gpGlobals->pEdicts);
}
inline edict_t *PEntityOfEntIndex(int iEntIndex)
{
	if (iEntIndex >= 0 && iEntIndex < gpGlobals->maxEntities)
	{
		return (edict_t *)(gpGlobals->pEdicts + iEntIndex);
	}
	return NULL;
}
#else
inline int IndexOfEdict(const edict_t *pEdict)
{
	return engine->IndexOfEdict(pEdict);
}
inline edict_t *PEntityOfEntIndex(int iEntIndex)
{
	return engine->PEntityOfEntIndex(iEntIndex);
}
#endif //SOURCE_ENGINE >= SE_LEFT4DEAD

int GetEntIndex(CBaseEntity *pEntity);
CBaseEntity *GetBaseEntity(int iEntIndex);

#endif //_INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
