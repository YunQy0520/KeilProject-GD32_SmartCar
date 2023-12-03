/* Includes ------------------------------------------------------------------*/
#include "communication.h"
#include "car.h"

/** @addtogroup Communication
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is sum check.
  * @param  const unsigned char *dat, unsigned char len
  * @retval None
  */
unsigned char Sum_Check(const unsigned char *dat, unsigned char len)
{
  unsigned char i, sum = 0;

  for (i = 0; i < len; i++) {
    sum += dat[i];
  }
  sum %= 0x100;

  return sum;
}

/**
  * @brief  Unpack the frame.
  * @param  *frame
  * @retval None
  */
void UnpackFrame(unsigned char *frame)
{
	switch (frame[2]) {
		case 0xA0:
			car_stop();
			break;
		case 0xA1:
			car_run(front, 4999);
			break;
		case 0xA2:
			car_run(back, 4999);
			break;
		case 0xA3:
			car_run(left, 4999);
			break;
		case 0xA4:
			car_run(right, 4999);
			break;
		default:
			break;
	}
}

/**
  * @brief  Framing.
  * @param  byte
  * @retval None
  */
void Framing(unsigned char byte)
{
  static unsigned char step = 0, cnt=0, buf[MAX_FRAME_LENGTH];

  switch (step) {
		/* Receive frame header byte */
    case 0:
      cnt = 0;
      if (byte == 0x5A) {
        step++;
        buf[cnt++] = byte;
      }
      break;
		/* Receive frame length byte */
    case 1:
      if (byte == 0 || byte > MAX_FRAME_LENGTH) {
        step = 0;
      } else {
        step++;
        buf[cnt++] = byte;
      }
      break;
		/* Receive the rest and end of frame */
    case 2:
      if (cnt < buf[1] - 1) {
        buf[cnt++] = byte;
      } else {
        if (byte == 0xA5) {
          buf[cnt] = byte;
//          flag_frameRx = 1;
          UnpackFrame(buf);
        }
        step = 0;
      }
      break;
    default:
      step=0;
  }
}

/**
  * @}
  */

/***** (C) YUNQY 2023 *****END OF FILE*****/
