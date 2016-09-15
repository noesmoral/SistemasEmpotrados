#include <public/caclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAClient::EDROOMTopContext::EDROOMTopContext (CAClient &act
	, TEDROOMUInt8 & EDROOMpVarVresId
	, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,Timer(EDROOMcomponent.Timer)
	, VresId ( EDROOMpVarVresId )
	, EDROOMPoolTEDROOMUInt8 ( EDROOMpPoolTEDROOMUInt8 )
 {

}

CAClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,Timer(contex.Timer)
	, VresId ( contex.VresId )
	, EDROOMPoolTEDROOMUInt8 ( contex.EDROOMPoolTEDROOMUInt8 )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CAClient::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	CAClient::EDROOMTopContext::FFreeRes()

{
  TEDROOMUInt8 * pSFreeRes_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSFreeRes_Data=VresId;
   pServReq.send(SFreeRes, pSFreeRes_Data, &EDROOMPoolTEDROOMUInt8); 
}



void	CAClient::EDROOMTopContext::FProgRequest()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(3,0);
	printf("%s is sleeping\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWait()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval=Pr_Time(1,0);
	printf("%s is waiting\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWorking()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
 
	interval =Pr_Time(2,0);
	printf("%s is working\n", EDROOMcomponent.EDROOMName);
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FResRequest()

{

   MsgBack=pServReq.invoke(SResReq); 
}



TEDROOMBool	CAClient::EDROOMTopContext::GIsAck()

{

	return (MsgBack->signal==SResAck);

}



void	CAClient::EDROOMTopContext::FGetResId()

{
  TEDROOMUInt8 & varSResAck = *(TEDROOMUInt8 *)MsgBack->data;
	
		// Data access
	
	VresId=varSResAck;

	printf("%s get ResId %i\n", EDROOMcomponent.EDROOMName, VresId);
 
}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CAClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount, TEDROOMUInt8* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMUInt8)){;}

TEDROOMUInt8 *	CAClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::AllocData(){
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAClient::EDROOMTopState::EDROOMTopState (CAClient &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VresId
		, EDROOMPoolTEDROOMUInt8 )
	, EDROOMPoolTEDROOMUInt8 ( 10, pEDROOMMemory->poolTEDROOMUInt8, pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CAClient::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(ReqRes):
				FResRequest();
				if( GIsAck() ){
					FGetResId();
					edroomCurrentTrans.localId = ReqRes_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = ReqRes_Nack;
					edroomNextState = Wait;
				 } 
				break;
			case(TryAgain):
				FResRequest();
				if( GIsAck() ){
					FGetResId();
					edroomCurrentTrans.localId = TryAgain_Ack;
					edroomNextState = Working;
				 } 
				else{
					edroomCurrentTrans.localId = TryAgain_Nack;
					edroomNextState = Wait;
				 } 
				break;
			case(FreeRes):
				FFreeRes();
				edroomNextState = Idle;
				break;
			case(Init):
				edroomNextState = Idle;
				break;
		}

		switch(edroomNextState){

			case(I):
				edroomCurrentTrans=EDROOMIllegada();
				break;

			case(Idle):
				FProgRequest();
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

			case(Working):
				FProgWorking();
				edroomCurrentTrans=EDROOMWorkingllegada();
				break;

			case(Wait):
				FProgWait();
				edroomCurrentTrans=EDROOMWaitllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CAClient::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId = ReqRes;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Working

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMWorkingllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= FreeRes;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Wait

	// ***********************************************************************



TEDROOMTransId CAClient::EDROOMTopState::EDROOMWaitllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId = TryAgain;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



