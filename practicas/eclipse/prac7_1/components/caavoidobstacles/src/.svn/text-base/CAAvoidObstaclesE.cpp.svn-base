

#include <public/caavoidobstacles_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



CAAvoidObstacles::CAAvoidObstacles(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )

		// *********** Timing service access point *********

		,EDROOMtimingSAP(this, 3,&pActorMemory->TimingMemory)


		// *******************  Timers  ********************

		,Timer(&EDROOMtimingSAP, 2 )




		// ***************	Top State  *****************

		,edroomTopState(*this)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int CAAvoidObstacles::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int CAAvoidObstacles::EDROOMStart() {



		//****************** Timing Task Start**********************

	EDROOMtimingSAP.Start();

		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void CAAvoidObstacles::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool CAAvoidObstacles::EDROOMIsComponentFinished() {


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void CAAvoidObstacles::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);

		TimingMemory.SetMemory(3,TimerInf,&TimerInfMarks[0],TimeOutMsgs,&TimeOutMsgsMarks[0]);


}

