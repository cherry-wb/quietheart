/********************************************************
 * @file  Fr_diabloverup.h
 * @brief Interface for diablo spi flash driver..
 * @date  2011-11-29
 * @author lv-k@neusoft.com
 追加Diablo比较好，能直接通过函数名知道升级对象：
 例　SPI_VerupStart  -> SPI_DiabloVersionUpStart
 *******************************************************/

#ifndef __FR_DIABLOVERUP_H__
#define __FR_DIABLOVERUP_H__

 /**
 * @brief nothing now.
 * @param[OUT] 		none
 * @param[IN]		none
 * @return 		      state value
 */
int SPI_DiabloVerupInit(void);

 /**
 * @brief nothing now.
 * @param[OUT] 		none
 * @param[IN]		none
 * @return 		      state value
 */
int SPI_DiabloVerupStart(unsigned int uiAddr, unsigned int uiSize);

 /**
 * @brief Write data.
 * @param[IN] ulWrAdrs data address to write.
 * @param[IN] pucBuf data pointer to write.
 * @param[IN] ulRemSize size of data (byte) to write.
 * @return length of data be written.
 */
int SPI_DiabloVerupWrite(unsigned int ulWrAdrs, unsigned char *pucBuf, unsigned long ulRemSize);

 /**
 * @brief  			
 * @param[OUT] 		none
 * @param[IN]		none
 * @return 		      state value
 */
int SPI_DiabloVerupEnd(void);

 /**
 * @brief Read data.
 * @param[IN] ulRdAdrs data offset to be read.
 * @param[IN] ulSize data length to be read.
 * @param[OUT] pucBuf buffer which used for store read data.
 * @return none
 */
void SPI_DiabloReadDataBytes(unsigned int ulRdAdrs,unsigned long ulSize, unsigned char *pucBuf);
#endif //__FR_DIABLOVERUP_H__
