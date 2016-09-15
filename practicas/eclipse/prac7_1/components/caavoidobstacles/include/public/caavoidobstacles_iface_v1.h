#ifndef CAAVOIDOBSTACLES_H_
#define CAAVOIDOBSTACLES_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Required software interfaces

#include <public/sensors_iface_v1.h>
#include <public/bprint_iface_v1.h>
#include <public/actuators_iface_v1.h>


/**
 * \class   CAAvoidObstacles
 *
 */
class CAAvoidObstacles: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCAAvoidObstaclesSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCAAvoidObstaclesSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SConfigAO, 
							SStart, 
							SObstacleDetected, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CAAvoidObstacles::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[3];
			//!Component Timing Service Timer Info Marks Memory
			TEDROOMBool TimerInfMarks[3];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[3];
			//!Component Timing Service TimeOut Messages Marks Memory
			TEDROOMBool TimeOutMsgsMarks[3];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;



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

	//! AvoidObstaclesSysCtrl Component Port
	CEDROOMInterface	AvoidObstaclesSysCtrl;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! Timer Timing Port
	CEDROOMTimingInterface	Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CAAvoidObstacles(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




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

	enum EDROOMCAAvoidObstaclesSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SConfigAO, SStart, SObstacleDetected, SConfigError, SConfigOK };


		friend class CAAvoidObstacles;

		CAAvoidObstacles &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & AvoidObstaclesSysCtrl;
		CEDROOMTimingInterface & Timer;

			enum edroomStateId{I, Idle, Ready};

			enum IdTrans{Init, Config, Start, CheackObstacles, CheackObstacles_ObsDetected, CheackObstacles_NoObstacle,  EDROOMMEMORIA };

		//Constants



		//Variables

		TEDROOMBool &VObsDetected;


		// Pools



		// CONSTRUCTORS

		EDROOMTopContext (CAAvoidObstacles &act, TEDROOMBool & EDROOMpVarVObsDetected );

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

		// User Defined Functions

		/**
		 * \brief  
		 */
		void	FCheckObstacles();

		/**
		 * \brief  
		 */
		void	FConfigOK();

		/**
		 * \brief  
		 */
		void	FHandleObstacle();

		/**
		 * \brief  
		 */
		void	FProgNextDetection();

		/**
		 * \brief  
		 */
		TEDROOMBool	GObstacleDetected();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		TEDROOMBool VObsDetected;


		// Pools



	public:

		// CONSTRUCTOR

		EDROOMTopState (CAAvoidObstacles &act );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

		// ***********************************************************************

		// Leaf SubState Idle

		// ***********************************************************************



		TEDROOMTransId EDROOMIdlellegada();

		// ***********************************************************************

		// Leaf SubState Ready

		// ***********************************************************************



		TEDROOMTransId EDROOMReadyllegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
