#include "api_local.h"

using namespace std;

string sessionHash = "";			// used for this particular game session
string userSessionHash = "";		// used for the logged in user

CURL* ConnectionManager::ptConnection = NULL;

bool ConnectionManager::Connect( int modId, const char *guid ) {
	// sets up the initial connection to the game
	ptConnection = curl_easy_init();
	if(!ptConnection) {
		ai->Error(0, "Could not init cURL");
		return false;
	}

	// set url
	string temp = SITE_URL;
	temp += "init.php?m=" + modId;
	URL(temp);

	// set post data
	APIList postData;
	Post(postData.Add("guid", guid).Serialize());

	// now actually do it
	sessionHash = Perform();
	if(sessionHash != "0")
		return true;
	return false;
}

void ConnectionManager::Disconnect( ) {
	// dump the session hash, we don't need it anymore
	sessionHash = "";

	// dump the user hash too in case that isn't already dumped
	userSessionHash = "";

	// kill cURL
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

void ConnectionManager::Post( string postData ) {
	curl_easy_setopt(ptConnection, CURLOPT_POSTFIELDS, postData.c_str());
}

string ConnectionManager::Perform( void ) {

	if(curl_easy_perform(ptConnection) != CURLE_OK) {
		ai->Error(0, "ConnectionManager::Perform: curl_easy_perform != CURLE_OK");
		return "";
	}
	
	// Loop and receive all the data from the page (POTENTIAL BOTTLENECK)
	CURLcode last;
	string allData = "";

	while(1) {
		size_t numRead;
		char buffer[512] = {0};

		last = curl_easy_recv(ptConnection, buffer, 512, &numRead);

		if(numRead == 0) // closed connection
			break;
		else if(last == CURLE_AGAIN) { // have some data in buffer but need to call again and receive more
			allData += buffer;
			continue;
		}
		else if(last == CURLE_OK){ // have received all data in the buffer
			allData += buffer;
			break;
		}
		else 
			break;
	}

	// If we encountered an error, now would be a good time to Com_Error I think
	if(last != CURLE_OK) {
		switch(last) {
			case CURLE_UNSUPPORTED_PROTOCOL:
				ai->Error(0, "ConnectionManager::Perform: Unsupported protocol.");
				return "";
				break;
		}
	}

	return allData;
}