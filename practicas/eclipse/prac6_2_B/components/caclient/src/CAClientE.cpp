

#include <public/caclient_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



CAClient::CAClient(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )

		// *********** Timing service access point *********

		,EDROOMtimingSAP(this, 3,&pActorMemory->TimingMemory)


		// *******************  Timers  ********************

		,Timer(&EDROOMtimingSAP, 2 )




		// ***************	Top State  *****************

		,edroomTopState(*this,pActorMemory)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int CAClient::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int CAClient::EDROOMStart() {



		//****************** Timing Task Start**********************

	EDROOMtimingSAP.Start();

		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void CAClient::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool CAClient::EDROOMIsComponentFinished() {


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void CAClient::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);

		TimingMemory.SetMemory(3,TimerInf,&TimerInfMarks[0],TimeOutMsgs,&TimeOutMsgsMarks[0]);


}

