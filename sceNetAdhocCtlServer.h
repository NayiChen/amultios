#pragma once
#include <time.h>
#include <string>
#include "packet.h"
//Server Configuration
#define CTL_SERVER_BACKLOG 128
#define CTL_SERVER_MAX_USER 1024
#define CTL_SERVER_TIMEOUT 15
#define CTL_SERVER_DATABASE "amultios"
#define CTL_SERVER_SHUTDOWN_MESSAGE "Game Server Shutting Down Report to Admin.."
//User State 
#define CTL_USER_WAITING 0
#define CTL_USER_LOGGED_IN 1
#define CTL_USER_TIMED_OUT 2


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif

#define IsMatch(buf1, buf2)	(memcmp(&buf1, &buf2, sizeof(buf1)) == 0)

typedef struct db_crosslink {
	char id_from[PRODUCT_CODE_LENGTH + 1]; //SceNetAdhocctlProductCode id_from;
	char id_to[PRODUCT_CODE_LENGTH + 1]; //SceNetAdhocctlProductCode id_to;
} db_crosslink;

typedef struct db_productid {
	char id[PRODUCT_CODE_LENGTH + 1]; //SceNetAdhocctlProductCode id;
	char name[ADHOCCTL_NICKNAME_LEN]; //Title name
} db_productid;

typedef struct db_groupname {
	char groupid[ADHOCCTL_GROUPNAME_LEN + 1]; //SceNetAdhocctlProductCode id;
	std::string name;
} db_groupname;

// PSP Resolver Information
typedef struct
{
	// PSP MAC Address
	SceNetEtherAddr mac;

	// PSP Hotspot IP Address
	uint32_t ip;
	uint16_t port;
	// PSP Player Name
	SceNetAdhocctlNickname name;
} SceNetAdhocctlResolverInfo;

// Type Prototypes
typedef struct SceNetAdhocctlGameNode SceNetAdhocctlGameNode;
typedef struct SceNetAdhocctlGroupNode SceNetAdhocctlGroupNode;

// Double-Linked User List
typedef struct SceNetAdhocctlUserNode {
	// Next Element
	struct SceNetAdhocctlUserNode * next;

	// Previous Element
	struct SceNetAdhocctlUserNode * prev;

	// Next Element (Group)
	struct SceNetAdhocctlUserNode * group_next;

	// Previous Element
	struct SceNetAdhocctlUserNode * group_prev;

	// Resolver Information
	SceNetAdhocctlResolverInfo resolver;

	// Game Link
	SceNetAdhocctlGameNode * game;

	// Group Link
	SceNetAdhocctlGroupNode * group;

	// TCP Socket
	int stream;
	uint8_t dbState;

	// Last Ping Update
	time_t last_recv;

	// RX Buffer
	uint8_t rx[1024];
	uint32_t rxpos;

	uint8_t role;
} SceNetAdhocctlUserNode;

// Double-Linked Game List
struct SceNetAdhocctlGameNode {
	// Next Element
	struct SceNetAdhocctlGameNode * next;

	// Previous Element
	struct SceNetAdhocctlGameNode * prev;

	// PSP Game Product Code
	SceNetAdhocctlProductCode game;

	// Number of Players
	uint32_t playercount;

	// Number of Groups
	uint32_t groupcount;

	// Double-Linked Group List
	SceNetAdhocctlGroupNode * group;
};

// Double-Linked Group List
struct SceNetAdhocctlGroupNode {
	// Next Element
	struct SceNetAdhocctlGroupNode * next;

	// Previous Element
	struct SceNetAdhocctlGroupNode * prev;

	// Game Link
	SceNetAdhocctlGameNode * game;

	// PSP Adhoc Group Name
	SceNetAdhocctlGroupName group;

	// Number of Players
	uint32_t playercount;

	// Double-Linked Player List
	SceNetAdhocctlUserNode * player;
};