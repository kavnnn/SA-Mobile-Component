#if defined _INC_SAMOBILE_INTEG
	#endinput
#endif
#define _INC_SAMOBILE_INTEG

#tryinclude <open.mp>

#if !defined _INC_open_mp
	#include <a_samp>
#endif

// Enums
enum E_SAMOBILE_NETWORK
{
	SAMOBILE_NETWORK_UNKNOWN,
	SAMOBILE_NETWORK_LEGACY,
	SAMOBILE_NETWORK_ADVANCE
}

/**
 * SA Mobile Server Integration - Include
 *
 * Requires the "SA Mobile Integration" filterscript to be loaded
 * on the server for these functions to return real data.
 * If the filterscript isn't loaded, all functions return 0/false.
 */

/**
 * Gets the player's SA Mobile client version.
 *
 * @param playerid  Player ID.
 * @return          Client version as an integer (e.g. 12 = v1.2).
 *                  Returns 0 if filterscript not loaded or player not on SA Mobile.
 */
stock SAMobile_GetVersion(playerid)
{
	return CallRemoteFunction("SAMobile_GetVersion", "d", playerid);
}

/**
 * Gets the player's network protocol version.
 *
 * @param playerid  Player ID.
 * @return          SAMOBILE_NETWORK_UNKNOWN, SAMOBILE_NETWORK_LEGACY,
 *                  or SAMOBILE_NETWORK_ADVANCE.
 */
stock E_SAMOBILE_NETWORK:SAMobile_GetNetworkVersion(playerid)
{
	return E_SAMOBILE_NETWORK:CallRemoteFunction("SAMobile_GetNetworkVersion", "d", playerid);
}

/**
 * Gets the player's network protocol version as a readable string.
 *
 * @param playerid  Player ID.
 * @param dest      Destination string buffer.
 * @param size      Size of the destination buffer (use sizeof(dest)).
 */
stock SAMobile_GetNetworkVersionName(playerid, dest[], size = sizeof(dest))
{
	switch (SAMobile_GetNetworkVersion(playerid))
	{
		case SAMOBILE_NETWORK_LEGACY:  strcat(dest, "Legacy", size);
		case SAMOBILE_NETWORK_ADVANCE: strcat(dest, "Advance", size);
		default:                       strcat(dest, "Unknown", size);
	}
	return 1;
}

/**
 * Checks if the player has MonetLoader installed.
 *
 * @param playerid  Player ID.
 * @return          true if detected, false otherwise.
 */
stock bool:SAMobile_HasMonetLoader(playerid)
{
	return bool:CallRemoteFunction("SAMobile_HasMonetLoader", "d", playerid);
}

/**
 * Checks if the player has AML (Android Mod Loader) installed.
 *
 * @param playerid  Player ID.
 * @return          true if detected, false otherwise.
 */
stock bool:SAMobile_HasAML(playerid)
{
	return bool:CallRemoteFunction("SAMobile_HasAML", "d", playerid);
}

/**
 * Checks if the player has CLEO installed.
 *
 * @param playerid  Player ID.
 * @return          true if detected, false otherwise.
 */
stock bool:SAMobile_HasCleo(playerid)
{
	return bool:CallRemoteFunction("SAMobile_HasCleo", "d", playerid);
}
