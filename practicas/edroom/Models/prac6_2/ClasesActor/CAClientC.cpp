#include <public/caclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CAClient::EDROOMTopContext::EDROOMTopContext (CAClient &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,Timer(EDROOMcomponent.Timer)
 {

}

CAClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,Timer(contex.Timer)
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

   //Send message 
   pServReq.send(SFreeRes); 
}



void	CAClient::EDROOMTopContext::FProgRequest()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(3,0); // interval of X sec + Y microsec
	printf("%s is sleeping\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWait()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(1,0); // interval of X sec + Y microsec
	printf("%s is waiting\n",EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FProgWorking()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(2,0); // interval of X sec + Y microsec
	printf("%s is working\n",EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CAClient::EDROOMTopContext::FResRequest()

{

   //Invoke synchronous communication 
   MsgBack=pServReq.invoke(SResReq); 
}



TEDROOMBool	CAClient::EDROOMTopContext::GIsAck()

{

return(MsgBack->signal==SResAck);

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CAClient::EDROOMTopState::EDROOMTopState (CAClient &act ):
	  EDROOMTopContext( act  )
{

}

	//***************************** EDROOMBehaviour ********************************

void CAClient::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//To Choice Point BranchTryAgain
			case(TryAgain):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Nack;

				//Next State is Wait
					edroomNextState = Wait;
				 } 
				break;
			//To Choice Point BranchReqRes
			case(ReqRes):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){

				//Next Transition is ReqRes
					edroomCurrentTrans.localId = ReqRes_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is ReqRes
					edroomCurrentTrans.localId = ReqRes_Nack;

				//Next State is Wait
					edroomNextState = Wait;
				 } 
				break;
			//Next Transition is FreeRes
			case(FreeRes):
				//Send Asynchronous Message 
				FFreeRes();
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Init
			case(Init):
				//Next State is Idle
				edroomNextState = Idle;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state I
			case(I):
				//Entry into the State I
				edroomCurrentTrans=EDROOMIllegada();
				break;

				//Go to the state Wait
			case(Wait):
				//Execute Entry Action 
				FProgWait();
				//Entry into the State Wait
				edroomCurrentTrans=EDROOMWaitllegada();
				break;

				//Go to the state Working
			case(Working):
				//Execute Entry Action 
				FProgWorking();
				//Entry into the State Working
				edroomCurrentTrans=EDROOMWorkingllegada();
				break;

				//Go to the state Idle
			case(Idle):
				//Execute Entry Action 
				FProgRequest();
				//Entry into the State Idle
				edroomCurrentTrans=EDROOMIdlellegada();
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

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
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

					//Next transition is  TryAgain
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

					//Next transition is  ReqRes
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



