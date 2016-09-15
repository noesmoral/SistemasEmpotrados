

#include <public/ccproducer_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



CCProducer::CCProducer(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )



		// ***************	Top State  *****************

		,edroomTopState(*this,pActorMemory)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int CCProducer::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int CCProducer::EDROOMStart() {



		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void CCProducer::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool CCProducer::EDROOMIsComponentFinished() {


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void CCProducer::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

