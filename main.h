//***********************************************************************************//
//*	Project:																		*//
//*																					*//
//*	File:		Main.h			 													*//
//*	Version:	1.0																	*//
//*																					*//
//*	Author:		Bob Marlowe															*//
//*	(C) 2016	Jörg Meier Software - Entwicklung briefe@jmeiersoftware.de			*//
//***********************************************************************************//
//***********************************************************************************//
//*																					*//
//*		Principles of Operation														*//
//*																					*//
//*		Standard include file for a project											*//
//*																					*//
//***********************************************************************************//

//***********************************************************************************//
//**************** Libraries ********************************************************//
//***********************************************************************************//
#include <project.h>

#ifndef Main_h
#define Main_h

//***********************************************************************************//
//**************** Definitions and Macros *******************************************//
//***********************************************************************************//
#define	FALSE					(0)											//	Define logical false and true values
#define	TRUE					(!FALSE)									//	
#define	forever					TRUE										//	I like that for infinite loops

//	Bit handling Macros
#define BitMask(BitNum)			(0x01ul << BitNum)							//	Generating a mask pattern with a set bit at required position
#define TestBit(Value,BitNum)	(Value & BitMask(BitNum))					//	Return bit at given position
#define IsBitSet(Value,Bit)		(TestBit(Value,BitNum)?TRUE:FALSE)			//	Return true or false when bit at position is set
#define SetBit(Value,BitNum)	(Value |=  BitMask(BitNum))					//	Set bit in variable at given position
#define ClrBit(Value,BitNum)	(Value &= ~BitMask(BitNum))					//	Clear bit in variable at given position

#define	Wait(x)																//	To increase readability
#define	ActiveHigh				TRUE
#define LEDOFF					!LEDON	
#define LEDON					ActiveHigh									//	LEDs are active high in this application

//***********************************************************************************//
//******************* Structs, Typedefs and Enums ***********************************//
//***********************************************************************************//
typedef uint8 Bool;

//***********************************************************************************//
//******************* External Data Area ********************************************//
//***********************************************************************************//
//	None yet

//***********************************************************************************//
//****************** Prototypes *****************************************************//
//***********************************************************************************//
//	None yet


    
    





#endif



