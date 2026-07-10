# SA Mobile Integration

A lightweight include for SA:MP / open.mp servers to detect and read data from players using the **SA Mobile** client.

This include communicates with the **SA Mobile Integration** filterscript via `CallRemoteFunction`. No source code is shared, only the compiled filterscript (`samobile.amx`) and this include (`samobile.inc`) are required.

---

## Requirements

- The `samobile.amx` filterscript must be loaded on your server (via `server.cfg` / `config.json`).
- If the filterscript is **not** loaded, all functions safely return `0` / `false` — no errors, no problem at all.

---

## Installation

1. Place `samobile.inc` in your server's `pawno/include` (or `qawno/include`) folder.
2. Place `samobile.amx` in your server's `filterscripts` folder.
3. Add `samobile` to your `filterscripts` line in `server.cfg`, or your `filterscripts` array in `config.json`.
4. In your gamemode or filterscript:
```pawn
#include <samobile>
```

---

## Functions

| Function | Return Type | Description |
|---|---|---|
| `SAMobile_GetVersion(playerid)` | `int` | Client version (e.g. `12` = v1.2). Returns `0` if unavailable. |
| `SAMobile_GetNetworkVersion(playerid)` | `E_SAMOBILE_NETWORK` | Network version. See enum below. |
| `SAMobile_GetNetworkVersionName(playerid, dest[], size)` | `-` | Writes the network version as a readable string into `dest`. |
| `SAMobile_HasMonetLoader(playerid)` | `bool` | `true` if MonetLoader is enabled. |
| `SAMobile_HasAML(playerid)` | `bool` | `true` if AML (Android Mod Loader) is enabled. |
| `SAMobile_HasCleo(playerid)` | `bool` | `true` if CLEO is enabled. |

### `E_SAMOBILE_NETWORK` enum

```pawn
enum E_SAMOBILE_NETWORK
{
	SAMOBILE_NETWORK_UNKNOWN,
	SAMOBILE_NETWORK_LEGACY,   // 0.3.7
	SAMOBILE_NETWORK_ADVANCE   // 0.3.DL
}
```

---

## Example

```pawn
#include <samobile>

public OnPlayerSpawn(playerid)
{
	new version = SAMobile_GetVersion(playerid);

	if (version > 0)
	{
		new major = version / 10;
		new minor = version % 10;

		new szNetVer[16];
		SAMobile_GetNetworkVersionName(playerid, szNetVer);

		new szMsg[128];
		format(szMsg, sizeof(szMsg), "Detected client v%d.%d (Network: %s)", major, minor, szNetVer);
		SendClientMessage(playerid, -1, szMsg);

		if (SAMobile_HasCleo(playerid))
		{
			SendClientMessage(playerid, 0xFF0000FF, "Warning: CLEO detected.");
		}

		if (SAMobile_HasMonetLoader(playerid) || SAMobile_HasAML(playerid))
		{
			SendClientMessage(playerid, 0xFF0000FF, "Warning: Mod loader detected.");
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Player is not using SA Mobile, or data isn't available yet.");
	}
	return 1;
}
```

---

## Notes

- Detection happens automatically when a player connects (`OnPlayerConnect` in the filterscript). Data may take a moment to arrive after connecting, a version of `0` simply means it isn't available (yet, or at all).
- These functions work regardless of whether the calling script is the gamemode or another filterscript, as long as `samobile.amx` is loaded somewhere on the server.
