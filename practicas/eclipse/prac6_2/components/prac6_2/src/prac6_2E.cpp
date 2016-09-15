

#include <public/prac6_2_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



prac6_2::prac6_2(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )



		// ***************	Top State  *****************

		,edroomTopState(*this)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int prac6_2::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int prac6_2::EDROOMStart() {



		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void prac6_2::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool prac6_2::EDROOMIsComponentFinished() {


	return ( Client.EDROOMIsComponentFinished() && Client2.EDROOMIsComponentFinished() && Client3.EDROOMIsComponentFinished() && Server.EDROOMIsComponentFinished() && Client4.EDROOMIsComponentFinished() && CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void prac6_2::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

