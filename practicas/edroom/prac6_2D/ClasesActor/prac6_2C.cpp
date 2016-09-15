#include <public/prac6_2_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

prac6_2::EDROOMTopContext::EDROOMTopContext (prac6_2 &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
 {

}

prac6_2::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool prac6_2::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

prac6_2::EDROOMTopState::EDROOMTopState (prac6_2 &act ):
	  EDROOMTopContext( act  )
{

}

	//***************************** EDROOMBehaviour ********************************

void prac6_2::EDROOMTopState::EDROOMBehaviour(){

}



	// Inicio**********************************************

void prac6_2::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId prac6_2::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId= 0;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



