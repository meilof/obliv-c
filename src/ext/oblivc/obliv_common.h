#ifndef OBLIV_COMMON_H
#define OBLIV_COMMON_H

#include<obliv_types.h>

// Because I am evil and I do not like 
// Java-style redundant "say the type twice" practice
#define CAST(p) ((void*)p)

void gcryDefaultLibInit(void);

// Convenience functions
static inline int orecv(ProtocolDesc* pd,int s,void* p,size_t n)
  { return pd->trans->recv(pd->trans,s,p,n); }
static inline int osend(ProtocolDesc* pd,int d,const void* p,size_t n)
  { return pd->trans->send(pd->trans,d,p,n); }

// Maybe these 5 lines should move to bcrandom.h
#define DHCurveName "secp192r1"
#define DHEltBits 192
#define DHEltSerialBytes (((DHEltBits+7)/8+2)*2)

void dhRandomInit(void);
void dhRandomFinalize(void);

static inline void otSenderRelease(OTsender* sender)
  { sender->release(sender->sender); }
static inline void otRecverRelease(OTrecver* recver)
  { recver->release(recver->recver); }

struct NpotSender* npotSenderNew(int nmax,ProtocolDesc* pd,int destParty);
void npotSenderRelease(struct NpotSender* s);
OTsender npotSenderAbstract(struct NpotSender* s);
struct NpotRecver* npotRecverNew(int nmax,ProtocolDesc* pd,int srcParty);
void npotRecverRelease(struct NpotRecver* r);
OTrecver npotRecverAbstract(struct NpotRecver* r);

void npotSend1Of2Once(struct NpotSender* s,const char* opt0,const char* opt1,
    int n,int len);
void npotRecv1Of2Once(struct NpotRecver* r,char* dest
                     ,unsigned mask,int n,int len);
void npotSend1Of2(struct NpotSender* s,const char* opt0,const char* opt1,
    int n,int len,int batchsize);
void npotRecv1Of2(struct NpotRecver* r,char* dest,const bool* sel,int n,int len,
    int batchsize);

struct HonestOTExtRecver* honestOTExtRecverNew(ProtocolDesc* pd,int srcparty);
void honestOTExtRecverRelease(struct HonestOTExtRecver* recver);
void honestOTExtRecv1Of2(struct HonestOTExtRecver* r,char* dest,const bool* sel,
    int n,int len);
OTrecver honestOTExtRecverAbstract(struct HonestOTExtRecver* r);

struct HonestOTExtSender* honestOTExtSenderNew(ProtocolDesc* pd,int destparty);
void honestOTExtSenderRelease(struct HonestOTExtSender* sender);
void honestOTExtSend1Of2(struct HonestOTExtSender* s,
    const char* opt0,const char* opt1,int n,int len);
OTsender honestOTExtSenderAbstract(struct HonestOTExtSender* s);

struct MaliciousOTExtRecver* maliciousOTExtRecverNew(ProtocolDesc* pd,int srcparty);
void maliciousOTExtRecverRelease(struct MaliciousOTExtRecver* recver);
bool maliciousOTExtRecv1Of2(struct MaliciousOTExtRecver* r,char* dest,const bool* sel,
    int n,int len);
OTrecver maliciousOTExtRecverAbstract(struct MaliciousOTExtRecver* r);

struct MaliciousOTExtSender* maliciousOTExtSenderNew(ProtocolDesc* pd,int destparty);
void maliciousOTExtSenderRelease(struct MaliciousOTExtSender* sender);
bool maliciousOTExtSend1Of2(struct MaliciousOTExtSender* s,
    const char* opt0,const char* opt1,int n,int len);
OTsender maliciousOTExtSenderAbstract(struct MaliciousOTExtSender* s);

// Overrides ypd so that we are not using semi-honest OT
void yaoUseNpot(ProtocolDesc* pd,int me);
void yaoReleaseOt(ProtocolDesc* pd,int me); // Used with yaoUseNpot
#endif
