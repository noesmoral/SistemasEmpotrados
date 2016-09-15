//##############################################################################
//###############     This file has been generated by EDROOM     ###############
//##############################################################################
 
#ifndef EDROOMDEPLOYMENT_H_
#define EDROOMDEPLOYMENT_H_
 
#include <edroom_glue/edroomdf.h>
#include <public/edroomsl_iface_v1.h>
 
 
//******************************************************************************
// include deployment edroom components
 
#include <public/caserver_iface_v1.h>
#include <public/caclient_iface_v1.h>
 
 
class CEDROOMSystemMemory{
 
	CEDROOMMessage	comp2Messages[10];
	TEDROOMBool	comp2MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp2QueueNodes[14];
	TEDROOMBool	comp2QueueNodesMarks[14];
 
	CEDROOMMessage	comp3Messages[10];
	TEDROOMBool	comp3MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp3QueueNodes[15];
	TEDROOMBool	comp3QueueNodesMarks[15];
 
	CEDROOMMessage	comp4Messages[10];
	TEDROOMBool	comp4MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp4QueueNodes[15];
	TEDROOMBool	comp4QueueNodesMarks[15];
 
	CEDROOMMessage	comp5Messages[10];
	TEDROOMBool	comp5MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp5QueueNodes[15];
	TEDROOMBool	comp5QueueNodesMarks[15];
 
	CEDROOMMessage	comp6Messages[10];
	TEDROOMBool	comp6MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp6QueueNodes[15];
	TEDROOMBool	comp6QueueNodesMarks[15];
 
	public:
 
	CAServer::CEDROOMMemory comp2Memory;
	CAClient::CEDROOMMemory comp3Memory;
	CAClient::CEDROOMMemory comp4Memory;
	CAClient::CEDROOMMemory comp5Memory;
	CAClient::CEDROOMMemory comp6Memory;
 
	void SetMemory();
};
 
class CEDROOMSystemCommSAP{
 
	 friend class CEDROOMSystemDeployment;
	CEDROOMLocalCommSAP m_localCommSAP;
	CEDROOMLocalConnection connections[4];
 
	CAServer   * mp_comp2;
	CAClient   * mp_comp3;
	CAClient   * mp_comp4;
	CAClient   * mp_comp5;
	CAClient   * mp_comp6;
 
	void SetComponents(CAServer   *p_comp2,
							CAClient   *p_comp3,
							CAClient   *p_comp4,
							CAClient   *p_comp5,
							CAClient   *p_comp6);
 
	static TEDROOMSignal C6Client4_PpServReq__C2Server_PpService4(TEDROOMSignal signal);
	static TEDROOMSignal C2Server_PpService4__C6Client4_PpServReq(TEDROOMSignal signal);
	static TEDROOMSignal C5Client3_PpServReq__C2Server_PpService3(TEDROOMSignal signal);
	static TEDROOMSignal C2Server_PpService3__C5Client3_PpServReq(TEDROOMSignal signal);
	static TEDROOMSignal C4Client2_PpServReq__C2Server_PpService2(TEDROOMSignal signal);
	static TEDROOMSignal C2Server_PpService2__C4Client2_PpServReq(TEDROOMSignal signal);
	static TEDROOMSignal C3Client1_PpServReq__C2Server_PpService1(TEDROOMSignal signal);
	static TEDROOMSignal C2Server_PpService1__C3Client1_PpServReq(TEDROOMSignal signal);
 
	void RegisterInterfaces();
	void SetLocalConnections();
	void SetRemoteConnections();
	void SetConnections();
 
};
 
class CEDROOMSystemDeployment{
 
	Pr_Kernel	kernel;
 
	CEDROOMSystemMemory   systemMemory;
	CEDROOMSystemCommSAP  systemCommSAP;
 
	CAServer   * mp_comp2;
	CAClient   * mp_comp3;
	CAClient   * mp_comp4;
	CAClient   * mp_comp5;
	CAClient   * mp_comp6;
 
	public:
 
	CEDROOMSystemDeployment();
 
	void Config(CAServer   *p_comp2,
					CAClient   *p_comp3,
					CAClient   *p_comp4,
					CAClient   *p_comp5,
					CAClient   *p_comp6);
 
	void Start();
 
	CAServer::CEDROOMMemory 		* GetComp2Memory(){return &systemMemory.comp2Memory;}
	CAClient::CEDROOMMemory 		* GetComp3Memory(){return &systemMemory.comp3Memory;}
	CAClient::CEDROOMMemory 		* GetComp4Memory(){return &systemMemory.comp4Memory;}
	CAClient::CEDROOMMemory 		* GetComp5Memory(){return &systemMemory.comp5Memory;}
	CAClient::CEDROOMMemory 		* GetComp6Memory(){return &systemMemory.comp6Memory;}
 
};
#endif