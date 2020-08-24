/**
 * This file is part of the Archicad GDL Add-on Example package.
 * <https://github.com/runxel/archicad-gdl-addon>
 * 
 * @file GDX-Template.cpp
 * @author runxel
 * @version 1.10 20-08-24
 * @license BOML
 */

#define		_GDXTEMPL_TRANSL_

#include	<stdio.h>

#if defined (_MSC_VER)
#include	<stdlib.h>
#endif

// This header **must** be set – always.
#include	"ACGDinc.h"

/***********************************************************************
 *  See also the supplied documentation by GS. 
 * <http://archicadapi.graphisoft.com/downloads/gdl-development-kit>
 ***********************************************************************/

/**
 * Provide info for this add-on.
 * Probably not needed to function correctly.
 */
GSErr __GDLEXT_CALL	GetAddonInfo (
						Int32, 					/* channel */
						const GS::UniString&, 	/* filename */ 
						const GS::UniString&,	/* paramstring */
						bool* isDeterministicAddOn)
{
	// This should be adjusted according to your *.RC resource file.
	*isDeterministicAddOn = false;

	return NoError;
}


/**
 * Called first when this extension is loaded.
 * Entry point for your Addon.
 * Init all global variables here.
 */
GSErr __GDLEXT_CALL	Initialize (void)
{	
	GSErr	err;
	err = NoError;

	char str[512];
	sprintf (str, "GDL Example Add-on has been loaded successfully.");
	// Use this function if you want to write into the Archicad protocol.
	AC_WriteReport (str, false, true);

	return err;
}


/**
 * Handle the opening or creating of a file.
 * Unused in our example case, but needs to be provided nontheless.
 */
GSErr __GDLEXT_CALL	OpenDataFile (
						Int32		/* channel */,
						const GS::UniString& /* fileName */,
						const GS::UniString& /* paramString */,
						GSHandle*	/* optionhdl */)
{
	return NoError;
}


/**
 * The core function.
 * `InputFromDataFile` yields back results to GDL via the `GDLRequestResult` parameter.
 */
GSErr __GDLEXT_CALL	InputFromDataFile (
						Int32		channel,
						const GS::UniString& recordID,
						const GS::UniString& fieldID,
						Int32 		nrvals, 		/* number of requested results */
						Int32 		*nrgotvals,		/* number of successful results yielded back from add-on */
						GDLRequestResult& values)
{
	// Declared but unused parameters have to be set to "unused".
	// Otherwise the .gdx won't compile.
	UNUSED_PARAMETER(channel);
	UNUSED_PARAMETER(recordID);
	UNUSED_PARAMETER(fieldID);

	if (nrgotvals == nullptr)
		return -1;

	GSErr	err = NoError;
	*nrgotvals = 0;

	char str[512];
	sprintf (str, "Requested the GDL Example Add-on with %d value(s)", nrvals);
	AC_WriteReport (str, false, true);

	values.AddString ("A string ought to be returned.");
	*nrgotvals = 1;

	// You can use `if`-structures to make adjustments.
	if (nrvals > 1)
	{
		values.AddDouble (1234.56);
		// Always make sure `nrgotvals` is set to the correct number of values you're yielding
		//  and update the number accordingly.
		*nrgotvals = 2;
	}

	return err;
}


/**
 * This function can be utilized to output some data into a file.
 * See "ReportGD" example by Graphisoft if you want to know how that works.
 * But what if you just want to do some calculations (= no writing to file needed)?
 * > Just init the function without any parameters and return `NoError`.
 */
GSErr __GDLEXT_CALL OutputToDataFile (
						Int32,
						const GS::UniString&,
						const GS::UniString&,
						const GDLRequestResult&)
{
	return NoError;
}


/**
 * Close the file identified by channel.
 */
GSErr __GDLEXT_CALL	CloseDataFile (Int32 channel)
{	
	GSErr	err = NoError;

	char str[512];
	sprintf(str, "CLOSE the channel %d to the Example Add-on.", channel);
	AC_WriteReport (str, false, true);

	return err;
}

/**
 * Free all own data structures you have allocated in the Initialize function.
 * `FreeData` is called when the extension is unloaded.
 */
GSErr __GDLEXT_CALL	FreeData (void)
{
	char str[512];
	sprintf (str, "Unloading the example GDL extension. Good Bye! ...");
	AC_WriteReport (str, false, true);

	/* Free local arrays etc. */

	return NoError;
}
