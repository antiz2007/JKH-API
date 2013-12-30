#pragma once
#include "api_public.h"
#include "curl/curl.h"
#include "curl/easy.h"
#include <map>
#include <string>

extern apiImport_t *ai;

typedef std::map<std::string, std::string>		postMap_t;
typedef std::pair<std::string, std::string>		postArg_t;

class ConnectionManager {
public:
	// -- Methods -- //
	static void Connect( int modId, const char *guid );
	static void Disconnect( void );
	static bool Login( char *plaintextUser, char *plaintextPassword );
	static void Logout( void );
private:
	// -- Properties -- //
	static CURL* ptConnection;

	// -- Methods -- //
	static void URL( std::string url );
	static std::string Perform( void );
	static void Post( std::string args );
friend class AchievementManager;
};

class AchievementManager {
public:
	// -- Methods -- //
	static void ProgressReport( int achieveId, int increment );
	static void UnlockAchieve( int achieveId );
};

struct APIList {
	// -- Methods -- //
	APIList& Add(std::string a, std::string b);
	std::string Serialize();
private:
	// -- Properties -- //
	postMap_t	z;
};