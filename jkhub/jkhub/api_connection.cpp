#include "api_local.h"

using namespace std;
void ConnectionManager::Connect( int modId, const char *guid ) {
	ptConnection = curl_easy_init();
	if(!ptConnection) {
		ai->Error(0, "Could not init cURL");
		return;
	}

	// set url and post data
	string temp = "http://apitest.jkhub.org/api/init.php?m=" + modId;
	URL(temp);
	Post(

	if(curl_easy_perform(ptConnection) != CURLE_OK) {
		ai->Error(0, "ConnectionManager::Connect: could not perform");
		return;
	}
	char buffer[128];

}

void ConnectionManager::Disconnect( ) {
	curl_easy_cleanup(ptConnection);
	curl_global_cleanup();
}

bool ConnectionManager::Login( char *plaintextUser, char *plaintextPassword ) {

	return false;
}

void ConnectionManager::Logout( ) {

}

void ConnectionManager::URL( string url ) {
	curl_easy_setopt(ptConnection, CURLOPT_URL, url.c_str()); // set the URL
	curl_easy_setopt(ptConnection, CURLOPT_FOLLOWLOCATION, 1L); // make sure we follow any sorta redirects (not foreseen but possible)
}

string ConnectionManager::Perform( void ) {

	if(curl_easy_perform(ptConnection) != CURLE_OK) {
		ai->Error(0, "ConnectionManager::Perform: curl_easy_perform != CURLE_OK");
		return "";
	}
	
	// Loop and receive all the data from the page (POTENTIAL BOTTLENECK)
	int x = 0;
	CURLcode last;
	while(x != -1) {
		last = curl_easy_recv(
	}
}