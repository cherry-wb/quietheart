	/************************************************************************
	*																		*
	*		VisualOn, Inc. Confidential and Proprietary, 2003-2009			*
	*																		*
	************************************************************************/
/*******************************************************************************
	File:		voMP3.h

	Contains:	Video type and function define header file

	Written by:	Bangfei Jin

	Change History (most recent first):
	2009-03-10		JBF			Create file

*******************************************************************************/

#ifndef __voMP3_H__
#define __voMP3_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <voAudio.h>



/* MP3 Param ID */
#define VO_PID_MP3_Mdoule				0x42221000



/* MP3 decoder error ID */
#define VO_ERR_MP3_Mdoule				0x82220000
#define VO_ERR_MP3_INVHEADER			VO_ERR_MP3_Mdoule | 0x0001
#define VO_ERR_MP3_INVFRAME				VO_ERR_MP3_Mdoule | 0x0002


/**
 * Get Audio codec API interface
 * \param pDecHandle [out] Return the MP3 Decoder handle.
 * \retval VO_ERR_OK Succeeded.
 */
VO_S32 VO_API voGetMP3DecAPI (VO_AUDIO_CODECAPI * pDecHandle);

/**
 * Get audio codec API interface
 * \param pEncHandle [out] Return the MP3 Encoder handle.
 * \retval VO_ERR_OK Succeeded.
 */
VO_S32 VO_API voGetMP3EncAPI (VO_AUDIO_CODECAPI * pEncHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __voAAC_H__
