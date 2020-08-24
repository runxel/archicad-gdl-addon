/*==========================================================================**
**								GDLExtDefs.h								**
**																			**
**					PUBLIC HEADER FILE OF THE GDL EXTENSION MANAGER			**
**==========================================================================*/

#ifndef	_GDLExtDefs_H_
#define	_GDLExtDefs_H_

#pragma once


/* methodVers */
#define 	Vers_IoGDLMethod		9
				/*	1:	 96.01.08 - AC5.0 development version								*/
				/*	2:	 96.02.13 - WOA->WA, WOO->WO										*/
				/* --------- AC5.00 --------- 												*/
				/*  3:	 97.02.26 - powerC alignment										*/
				/* --------- ACTW B --------- 												*/
				/* --------- ACTW B2 -------- 												*/
				/* --------- ACTW ----------- 												*/
				/*  4:	 98.02.18 - Options of the GDL I/O extensions						*/
				/*  5:   98.03.10 - __GDLEXT_CALL											*/
				/*  6:   98.04.01 - OptionHdl int OpenProc									*/
				/* --------- Minarik B4 ----------- 										*/
				/* --------- Minarik B7 ----------- 										*/
				/* --------- Minarik GM ----------- 										*/
				/*  7:   00.01.15 - New input parameters									*/
				/*  8:   02.01.07 - gen2DData												*/
				/*  9:   15.03.24 - expList.getaddoninfo									*/

/* methodInIndex */

/* methodFlags */

#define		KeepAsOpened			1
#define		DeterministicResult		2
#define		PersistentFunction		4
#define		MultiThreadingEnabled	8

/* platform */
#define		MacIntel				0x0002
#define		Winx64					0x0008

#ifdef macintosh
	#define PlatformCode			MacIntel
#endif
#if defined (WINDOWS)
	#define	PlatformCode			Winx64
#endif

/* method */
#define		IoGDLMethod				3

/* acnfVers */
#define		ACNF_VERSION			22


#endif
