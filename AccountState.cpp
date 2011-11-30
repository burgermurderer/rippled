#include "AccountState.h"
#include "Serializer.h"

AccountState::AccountState(const std::vector<unsigned char>& v)
{
	Serializer s(v);
	mValid=false;
	if(!s.get160(mAccountID, 0)) return;
	if(!s.get64(mBalance, 20)) return;
	if(!s.get32(mAccountSeq, 28)) return;
	mValid=true;
}

AccountState::AccountState(const uint160& id) : mAccountID(id), mBalance(0), mAccountSeq(0), mValid(true)
{ ; }

std::vector<unsigned char> AccountState::getRaw() const
{ // 20-byte acct ID, 8-byte balance, 4-byte sequence
	Serializer s(32);
	s.add160(mAccountID);
	s.add64(mBalance);
	s.add32(mAccountSeq);
	return s.getData();
}
