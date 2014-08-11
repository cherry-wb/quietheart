	/************************************************************************
	*																		*
	*		VisualOn, Inc. Confidential and Proprietary, 2003-2009			*
	*																		*
	************************************************************************/
/*******************************************************************************
	File:		voADPCM.h

	Contains:	Video type and function define header file

	Written by:	Bangfei Jin

	Change History (most recent first):
	2009-03-10		JBF			Create file

*******************************************************************************/

#ifndef __voADPCM_H__
#define __voADPCM_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <voAudio.h>
	
/*!
 * the special process that the decoder supports 
 */
typedef enum {
	WAVE_FORMAT_MS_ADPCM				= 0x0002,		/* Microsoft ADPCM */
	WAVE_FORMAT_ALAW					= 0x0006,		/* Microsoft A-Law */
	WAVE_FORMAT_MULAW					= 0x0007,		/* Microsoft u-Law */
	WAVE_FORMAT_IMA_ADPCM				= 0x0011,		/* Intel Corporation */
	WAVE_FORMAT_ITU_G726				= 0x0045,	
	WAVE_FORMAT_MAX						= VO_MAX_ENUM_VALUE,
} VOADPCMTYPE;	


/* ADPCM Param ID */
#define VO_PID_ADPCM_Mdoule				0x422A1000
#define VO_PID_ADPCM_FMTCHUNK			(VO_PID_ADPCM_Mdoule | 0x0001)
#define VO_PID_ADPCM_GETBLOCKSIZE		(VO_PID_ADPCM_Mdoule | 0x0002)		

/* ADPCM decoder error ID */
#define VO_ERR_ADPCM_Mdoule				0x822A0000


/**
 * Get Audio codec API interface
 * \param pDecHandle [out] Return the ADPCM Decoder handle.
 * \retval VO_ERR_OK Succeeded.
 */
VO_S32 VO_API voGetADPCMDecAPI (VO_AUDIO_CODECAPI * pDecHandle);

/**
 * Get audio codec API interface
 * \param pEncHandle [out] Return the ADPCM Encoder handle.
 * \retval VO_ERR_OK Succeeded.
 */
VO_S32 VO_API voGetADPCMEncAPI (VO_AUDIO_CODECAPI * pEncHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __voADPCM_H__
