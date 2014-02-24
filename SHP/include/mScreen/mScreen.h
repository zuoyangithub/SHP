#define M_SCREEN_INIT_SUCCESS 	0
#define M_SCREEN_INIT_FAILED 		1

#define M_SCREEN_CLOSE_SUCCESS 	0
#define M_SCREEN_CLOSE_ERROR 		1

#define M_SCREEN_EVENT_SUCCESS 	0
#define M_SCREEN_EVENT_ERROR 		1

#define M_SCREEN_STATUS_SUCCESS 	0
#define M_SCREEN_STATUS_ERROR 		1

#define SCREEN_KEY 0

// PIN Setup
#define PIN_DIN  10
#define PIN_SCLK 11
#define PIN_DC   23
#define PIN_RST  24
#define PIN_CS   8
#define PIN_LIGHT 18

// LCD contrast
#define LCD_CONTRAST 70

// LCD Light
#define LCD_LIGHT_ON 1
#define LCD_LIGHT_OFF 0

extern int mScreenInit();

extern int mScreenEvent();

extern void mScreenClose();

extern void mScreenDrawstring(int, int, char*);

extern void mScreenDisplay(void);

extern void mScreenSetLight(int);

extern void mScreenSetCursor(int, int);


extern void mScreenClear(void);


