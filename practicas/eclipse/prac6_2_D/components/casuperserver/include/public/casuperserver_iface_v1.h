#ifndef CASUPERSERVER_H_
#define CASUPERSERVER_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

/**
 * \class   CASuperServer
 *
 */
class CASuperServer: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCASuperServerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCASuperServerSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SResAck, 
							SResNack, 
							SFreeRes, 
							SResReq };

	/**
	 * \class CASuperServer::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

		public:



			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, TEDROOMBool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, TEDROOMBool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! Service8 Component Port
	CEDROOMInterface	Service8;
	//! Service7 Component Port
	CEDROOMInterface	Service7;
	//! Service6 Component Port
	CEDROOMInterface	Service6;
	//! Service5 Component Port
	CEDROOMInterface	Service5;
	//! Service4 Component Port
	CEDROOMInterface	Service4;
	//! Service3 Component Port
	CEDROOMInterface	Service3;
	//! Service2 Component Port
	CEDROOMInterface	Service2;
	//! Service Component Port
	CEDROOMInterface	Service;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CASuperServer(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	TEDROOMBool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOMTopContext

	// ***********************************************************************



	class EDROOMTopContext {

	protected:

	enum EDROOMCASuperServerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SResAck, SResNack, SFreeRes, SResReq };


		friend class CASuperServer;

		CASuperServer &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & Service8;
		CEDROOMInterface & Service7;
		CEDROOMInterface & Service6;
		CEDROOMInterface & Service5;
		CEDROOMInterface & Service4;
		CEDROOMInterface & Service3;
		CEDROOMInterface & Service2;
		CEDROOMInterface & Service;

			enum edroomStateId{I};

			enum IdTrans{ EDROOMMEMORIA };

		//Constants



		//Variables



		// Pools



		// CONSTRUCTORS

		EDROOMTopContext (CASuperServer &act );

		EDROOMTopContext ( EDROOMTopContext &contex );

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		TEDROOMBool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage () { EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables



		// Pools



	public:

		// CONSTRUCTOR

		EDROOMTopState (CASuperServer &act );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
