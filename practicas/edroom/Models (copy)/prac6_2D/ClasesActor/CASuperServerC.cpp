#include <public/casuperserver_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CASuperServer::EDROOMTopContext::EDROOMTopContext (CASuperServer &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,Service8(EDROOMcomponent.Service8)
	,Service7(EDROOMcomponent.Service7)
	,Service6(EDROOMcomponent.Service6)
	,Service5(EDROOMcomponent.Service5)
	,Service4(EDROOMcomponent.Service4)
	,Service3(EDROOMcomponent.Service3)
	,Service2(EDROOMcomponent.Service2)
	,Service(EDROOMcomponent.Service)
 {

}

CASuperServer::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,Service8(contex.Service8)
	,Service7(contex.Service7)
	,Service6(contex.Service6)
	,Service5(contex.Service5)
	,Service4(contex.Service4)
	,Service3(contex.Service3)
	,Service2(contex.Service2)
	,Service(contex.Service)
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CASuperServer::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

CASuperServer::EDROOMTopState::EDROOMTopState (CASuperServer &act ):
	  EDROOMTopContext( act  )
{

}

	//***************************** EDROOMBehaviour ********************************

void CASuperServer::EDROOMTopState::EDROOMBehaviour(){

}



	// Inicio**********************************************

void CASuperServer::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CASuperServer::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	edroomCurrentTrans.localId= 0;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



