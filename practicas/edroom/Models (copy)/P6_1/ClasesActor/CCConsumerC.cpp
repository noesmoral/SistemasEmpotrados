#include <public/ccconsumer_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCConsumer::EDROOMTopContext::EDROOMTopContext (CCConsumer &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,PIn(EDROOMcomponent.PIn)
	,Timer(EDROOMcomponent.Timer)
 {

}

CCConsumer::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,PIn(contex.PIn)
	,Timer(contex.Timer)
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCConsumer::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CCConsumer::EDROOMTopContext::FConReady()

{

   PIn.send(SConReady); 
}



void	CCConsumer::EDROOMTopContext::FProgDelay()

{
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	//interval = Pr_Time(X,Y); // interval of X sec + Y microsec
	interval=Pr_Time(1,0);
   Timer.InformIn( interval ); 
}



void	CCConsumer::EDROOMTopContext::FShowData()

{
  TEDROOMByte & varSData = *(TEDROOMByte *)Msg->data;
	
		// Data access
	
	// ... =varSData;
	printf ("Data =%c\n", varSData);

}



void	CCConsumer::EDROOMTopContext::FShowTime()

{

	Pr_Time aux;
	aux.GetTime();
	printf("Current Time = %i\n",(uint32_t)aux.Secns());

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCConsumer::EDROOMTopState::EDROOMTopState (CCConsumer &act ):
	  EDROOMTopContext( act  )
{

}

	//***************************** EDROOMBehaviour ********************************

void CCConsumer::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans = EDROOMIllegada();

	do{

		switch(edroomCurrentTrans.localId){

			case(Init):
				edroomNextState = Ready;
				break;
			case(ShowData):
				FShowData();
				edroomNextState = HandleData;
				break;
			case(EndHandling):
				FShowTime();
				edroomNextState = Ready;
				break;
		}

		switch(edroomNextState){

			case(I):
				edroomCurrentTrans=EDROOMIllegada();
				break;

			case(Ready):
				FConReady();
				edroomCurrentTrans=EDROOMReadyllegada();
				break;

			case(HandleData):
				edroomCurrentTrans=EDROOMHandleDatallegada();
				FProgDelay();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CCConsumer::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCConsumer::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCConsumer::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SData): 

				 if ( *Msg->GetPInterface() == PIn) {

					edroomCurrentTrans.localId= ShowData;
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

	// Leaf SubState  HandleData

	// ***********************************************************************



TEDROOMTransId CCConsumer::EDROOMTopState::EDROOMHandleDatallegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= EndHandling;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



