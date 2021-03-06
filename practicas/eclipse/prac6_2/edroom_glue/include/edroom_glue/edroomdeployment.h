//##############################################################################
//###############     This file has been generated by EDROOM     ###############
//##############################################################################
 
#ifndef EDROOMDEPLOYMENT_H_
#define EDROOMDEPLOYMENT_H_
 
#include <edroom_glue/edroomdf.h>
#include <public/edroomsl_iface_v1.h>
 
 
//******************************************************************************
// include deployment edroom components
 
#include <public/caclient_iface_v1.h>
#include <public/caserver_iface_v1.h>
// ***********************************************************************
// class CEDROOMSystemMemory
// ***********************************************************************
 
class CEDROOMSystemMemory{
 
	//!Messages Memory of component comp2
	CEDROOMMessage	comp2Messages[10];
	TEDROOMBool	comp2MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp2QueueNodes[13];
	TEDROOMBool	comp2QueueNodesMarks[13];
 
	//!Messages Memory of component comp3
	CEDROOMMessage	comp3Messages[10];
	TEDROOMBool	comp3MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp3QueueNodes[13];
	TEDROOMBool	comp3QueueNodesMarks[13];
 
	//!Messages Memory of component comp4
	CEDROOMMessage	comp4Messages[10];
	TEDROOMBool	comp4MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp4QueueNodes[13];
	TEDROOMBool	comp4QueueNodesMarks[13];
 
	//!Messages Memory of component comp5
	CEDROOMMessage	comp5Messages[10];
	TEDROOMBool	comp5MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp5QueueNodes[14];
	TEDROOMBool	comp5QueueNodesMarks[14];
 
	//!Messages Memory of component comp6
	CEDROOMMessage	comp6Messages[10];
	TEDROOMBool	comp6MessagesMarks[10];
	CEDROOMQueue::CQueueNode	comp6QueueNodes[13];
	TEDROOMBool	comp6QueueNodesMarks[13];
 
	public:
 
	CAClient::CEDROOMMemory comp2Memory;
	CAClient::CEDROOMMemory comp3Memory;
	CAClient::CEDROOMMemory comp4Memory;
	CAServer::CEDROOMMemory comp5Memory;
	CAClient::CEDROOMMemory comp6Memory;
 
//!Set Memory
	void SetMemory();
};
 
class CEDROOMSystemCommSAP{
 
	 friend class CEDROOMSystemDeployment;
//!Communication Service Access Point
 
	CEDROOMLocalCommSAP m_localCommSAP;
 
 
//!Conections
 
	CEDROOMLocalConnection connections[4];
 
	CAClient   * mp_comp2;
	CAClient   * mp_comp3;
	CAClient   * mp_comp4;
	CAServer   * mp_comp5;
	CAClient   * mp_comp6;
 
 
//!Set Components
 
	void SetComponents(CAClient   *p_comp2,
							CAClient   *p_comp3,
							CAClient   *p_comp4,
							CAServer   *p_comp5,
							CAClient   *p_comp6);
 
 
//Signal Conversion
 
	static TEDROOMSignal C5Server_PpService4__C6Client4_PpServReq(TEDROOMSignal signal);
	static TEDROOMSignal C6Client4_PpServReq__C5Server_PpService4(TEDROOMSignal signal);
 
//Signal Conversion
 
	static TEDROOMSignal C4Client3_PpServReq__C5Server_PpService3(TEDROOMSignal signal);
	static TEDROOMSignal C5Server_PpService3__C4Client3_PpServReq(TEDROOMSignal signal);
 
//Signal Conversion
 
	static TEDROOMSignal C3Client2_PpServReq__C5Server_PpService2(TEDROOMSignal signal);
	static TEDROOMSignal C5Server_PpService2__C3Client2_PpServReq(TEDROOMSignal signal);
 
//Signal Conversion
 
	static TEDROOMSignal C2Client_PpServReq__C5Server_PpService1(TEDROOMSignal signal);
	static TEDROOMSignal C5Server_PpService1__C2Client_PpServReq(TEDROOMSignal signal);
 
 
//!Register Interfaces
	void RegisterInterfaces();
 
//!Set Local Connections
	void SetLocalConnections();
 
//!Set Remote Connections
	void SetRemoteConnections();
 
//!Set Connections
	void SetConnections();
 
};
 
class CEDROOMSystemDeployment{
 
//!Kernel
	Pr_Kernel	kernel;
 
#ifdef CONFIG_EDROOMDEPLOYMENT_NEED_TASK
 
//!Main Task
static Pr_TaskRV_t main_task(Pr_TaskP_t);
 
#endif
	CEDROOMSystemMemory   systemMemory;
	CEDROOMSystemCommSAP  systemCommSAP;
 
	CAClient   * mp_comp2;
	CAClient   * mp_comp3;
	CAClient   * mp_comp4;
	CAServer   * mp_comp5;
	CAClient   * mp_comp6;
 
	public:
 
	CEDROOMSystemDeployment();
 
//!Deployment Configuration
	void Config(CAClient   *p_comp2,
					CAClient   *p_comp3,
					CAClient   *p_comp4,
					CAServer   *p_comp5,
					CAClient   *p_comp6);
 
//!Deployment Start
	void Start();
 
//!StartComponents
	void StartComponents();
//!Config Components
 
	CAClient::CEDROOMMemory 		* GetComp2Memory(){return &systemMemory.comp2Memory;}
	CAClient::CEDROOMMemory 		* GetComp3Memory(){return &systemMemory.comp3Memory;}
	CAClient::CEDROOMMemory 		* GetComp4Memory(){return &systemMemory.comp4Memory;}
	CAServer::CEDROOMMemory 		* GetComp5Memory(){return &systemMemory.comp5Memory;}
	CAClient::CEDROOMMemory 		* GetComp6Memory(){return &systemMemory.comp6Memory;}
 
};
#endif
