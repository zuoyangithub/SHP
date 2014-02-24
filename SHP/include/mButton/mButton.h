#define BUTTON_UP 		31		// GPIO PIN
#define BUTTON_DOWN 	22		// GPIO PIN
#define BUTTON_LEFT 	29		// GPIO PIN
#define BUTTON_RIGHT 	30		// GPIO PIN
#define BUTTON_SELECT 	28		// GPIO PIN

#define M_BUTTON_INIT_SUCCESS 	0
#define M_BUTTON_INIT_FAILED 		1

#define M_BUTTON_CLOSE_SUCCESS 	0
#define M_BUTTON_CLOSE_ERROR 		1

#define M_BUTTON_EVENT_SUCCESS 	0
#define M_BUTTON_EVENT_ERROR 		1

#define M_BUTTON_STATUS_SUCCESS 	0
#define M_BUTTON_STATUS_ERROR 		1

#define BUTTON_KEY 0

#define BUTTON_LOW 0
#define BUTTON_HIGH 1

extern int mButtonInit();

extern int mButtonEvent();

extern void mButtonClose();



