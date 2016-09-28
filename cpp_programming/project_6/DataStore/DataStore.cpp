#include "DataStore.h"

DataStore::DataStore(Crypto *crypto) {
	myCrypto = crypto;
}

DataStore::~DataStore() {
	if (myCrypto)
	{
		myCrypto = NULL;
		delete myCrypto;
	}
}

bool DataStore::decrypt(std::string &myString) {
	if (myCrypto != NULL) {
		myCrypto->decrypt(myString);
	}
	return true;
}

bool DataStore::encrypt(std::string &myString) {
	if (myCrypto != NULL) {
		myCrypto->encrypt(myString);
	}
	return true;
}