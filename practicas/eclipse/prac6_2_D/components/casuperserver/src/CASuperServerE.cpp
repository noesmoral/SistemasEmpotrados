

#include <public/casuperserver_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



CASuperServer::CASuperServer(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )



		// ***************	Top State  *****************

		,edroomTopState(*this)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int CASuperServer::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int CASuperServer::EDROOMStart() {



		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void CASuperServer::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool CASuperServer::EDROOMIsComponentFinished() {


	return ( Server.EDROOMIsComponentFinished() && Server2.EDROOMIsComponentFinished() && CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void CASuperServer::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

