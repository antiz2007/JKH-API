#pragma once

#define API_VERSION		0x01
#define SITE_URL		"http://apitest.jkhub.org/api"

typedef struct {
	void	(*Print)			( const char *msg, ... );
	void	(*Error)			( int level, const char *msg, ... );
	int		(*Milliseconds)		(  );
	void	(*TrueMalloc)		( void **ptr, int size );
	void	(*TrueFree)			( void **ptr );
} apiImport_t;

typedef struct {
	bool	(*Connect)			( int modId, const char *hash );
	void	(*Disconnect)		( void );
	bool	(*Login)			( char *plaintextUser, char *plaintextPassword );
	void	(*Logout)			( void );
	
	void	(*ProgressReport)	( int achieveId, int increment );
	void	(*UnlockAchieve)	( int achieveId );
} apiExport_t;

// Linker love
#ifdef _WIN32
#define CURL_STATICLIB			// no extra .dll required
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "..\\libraries\\libcurl\\lib\\libeay32.lib")
#pragma comment(lib, "..\\libraries\\libcurl\\lib\\openldap.lib")
#pragma comment(lib, "..\\libraries\\libcurl\\lib\\ssleay32.lib")
#pragma warning(disable: 4099)
#endif