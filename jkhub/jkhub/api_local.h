#pragma once
#include "api_public.h"
#include "curl/curl.h"
#include "curl/easy.h"
#include <list>
#include <string>

extern apiImport_t *ai;

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
	static void Post( std::list<std::pair<std::string, std::string>> args );
friend class AchievementManager;
};

class AchievementManager {
public:
	// -- Methods -- //
	static void ProgressReport( int achieveId, int increment );
	static void UnlockAchieve( int achieveId );
};