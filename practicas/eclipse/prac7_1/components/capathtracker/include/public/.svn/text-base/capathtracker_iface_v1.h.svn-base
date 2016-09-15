#ifndef CAPATHTRACKER_H_
#define CAPATHTRACKER_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdpath_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/actuators_iface_v1.h>
#include <public/bprint_iface_v1.h>


/**
 * \class   CAPathTracker
 *
 */
class CAPathTracker: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCAPathTrackerSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCAPathTrackerSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							STrackPath, 
							SPathRequest, 
							SConfigPathTracker, 
							SStopTracking, 
							SStartTracking, 
							SConfigError, 
							SConfigOK };

	/**
	 * \class CAPathTracker::CEDROOMMemory
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

	//! TrackPath Component Port
	CEDROOMInterface	TrackPath;
	//! PathTrackerCtrl Component Port
	CEDROOMInterface	PathTrackerCtrl;


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
	CAPathTracker(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




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

	enum EDROOMCAPathTrackerSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, STrackPath, SPathRequest, SConfigPathTracker, SStopTracking, SStartTracking, SConfigError, SConfigOK };


		friend class CAPathTracker;

		CAPathTracker &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & TrackPath;
		CEDROOMInterface & PathTrackerCtrl;
		CEDROOMTimingInterface & Timer;

			enum edroomStateId{I, Idle, StandBy, TrackingPath, Pause};

			enum IdTrans{Init, NewPath, PathStep, PathStep_LastStep, PathStep_toNextStep, Config, Config_Error, Config_OK, Start, StopTrack, ResumePath, ToStandBy,  EDROOMMEMORIA };

		//Constants



		//Variables

		CDPath &VCurrentPath;
		TEDROOMUInt8 &VCurrentPathStep;
		TEDROOMUInt8 &VSimError;


		// Pools



		// CONSTRUCTORS

		EDROOMTopContext (CAPathTracker &act, CDPath & EDROOMpVarVCurrentPath, TEDROOMUInt8 & EDROOMpVarVCurrentPathStep, TEDROOMUInt8 & EDROOMpVarVSimError );

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
		void	FGetNewPatch();

		void	FGoToPathStep();

		/**
		 * \brief  
		 */
		void	FProgFirstTrackStep();

		/**
		 * \brief  
		 */
		void	FProgNextTrackStep();

		/**
		 * \brief  
		 */
		void	FReplyOK();

		/**
		 * \brief  
		 */
		void	FReplySimError();

		/**
		 * \brief  
		 */
		void	FSendPathRequest();

		TEDROOMBool	GLastStep();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:



		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		CDPath VCurrentPath;
		TEDROOMUInt8 VCurrentPathStep;
		TEDROOMUInt8 VSimError;


		// Pools



	public:

		// CONSTRUCTOR

		EDROOMTopState (CAPathTracker &act );


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

		// Leaf SubState StandBy

		// ***********************************************************************



		TEDROOMTransId EDROOMStandByllegada();

		// ***********************************************************************

		// Leaf SubState TrackingPath

		// ***********************************************************************



		TEDROOMTransId EDROOMTrackingPathllegada();

		// ***********************************************************************

		// Leaf SubState Pause

		// ***********************************************************************



		TEDROOMTransId EDROOMPausellegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
