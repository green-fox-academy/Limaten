/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SOCKET_CLIENT_H
#define __SOCKET_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery_ts.h"
#include "socket_server.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void socket_client_thread(void const *argument);

#endif /* __SOCKET_CLIENT_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
