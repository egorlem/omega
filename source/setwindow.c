#include <gba_systemcalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <gba_base.h>
#include <gba_input.h>


#include "lang.h"
#include "ezkernel.h"
#include "RTC.h"
#include "draw.h"
#include "Ezcard_OP.h"

extern const unsigned char __attribute__((aligned(4)))gImage_SET[76800];
extern u16 gl_select_lang;
extern u16 gl_engine_sel;
extern u16 gl_show_Thumbnail;
extern u16 gl_ingame_RTC_open_status;

u16 SET_info_buffer [0x200]EWRAM_BSS;

#define	K_A		 	 (0)
#define	K_B		 	 (1)
#define	K_SELECT (2)
#define	K_START  (3)
#define	K_RIGHT	 (4)
#define	K_LEFT	 (5)
#define	K_UP		 (6)
#define	K_DOWN	 (7)
#define	K_R		   (8)
#define	K_L		 	 (9)

u8* str_A      = (u8*)"   A  ";
u8*	str_B		   = (u8*)"   B  ";
u8* str_SELECT = (u8*)"SELECT";
u8*	str_START	 = (u8*)"START ";
u8*	str_RIGHT	 = (u8*)"RIGHT ";
u8*	str_LEFT	 = (u8*)" LEFT ";
u8* str_UP		 = (u8*)"  UP  ";
u8*	str_DOWN	 = (u8*)" DOWN ";
u8* str_R		   = (u8*)"   R  ";
u8* str_L		   = (u8*)"   L  ";


/* MENU SETTINGS AREA LIST */

#define TIME_AREA 0 
#define ADDON_AREA 1
#define ENGINE_AREA 2
#define SLEEP_AREA 3
#define MENU_AREA 4 
#define RTC_AREA 5

u16 v_reset;
u16 v_rts;
u16 v_sleep;
u16 v_cheat;
// u16 language_sel;	
u16 engine_sel;
u8 edit_sleephotkey[3]={0};
u8 edit_rtshotkey[3]={0};
//---------------------------------------------------------------------------------
void Show_ver(void) {
	char msg[20];
	char *ver="v 021011";
	u16 FPGAver = Read_FPGA_ver();
	sprintf(msg,"FW:%d %s",FPGAver&0xFF,ver);
	DrawHZText12(msg, 0, 160, 3, gl_color_text, 1);	
}
//---------------------------------------------------------------------------------
void Draw_select_icon(u32 X,u32 Y,u32 mode) {
	Clear(X + 2, Y + 2, 8, 8, gl_color_text, 1);
	Clear(X + 3, Y + 3, 6, 6, RGB(4,8,12), 1);
	if (mode) { 
		Clear(X+4, Y+4, 4, 4, gl_color_selected, 1);
	}
}
//---------------------------------------------------------------------------------
u32 Setting_window(void) {
	u16 isKeyDown;
	u16 isKeyDownRepeat;
	u32 line;
	u32 select;
	u32 Set_OK=0;
	u32 Set_OK_line=0;
	
	u8 edit_pos=0;
	//u32 i; 
	u32 currstate=0;
	
	char msg[128];
	u16 clean_color;
	u16 menuButtonColor;
	u16 clean_pos;
	u16 clean_w;
	u32 re_show=1;

	u32 addon_sel=2;
	
	u8 sleep_pos=0;
	u8 rtshotkey_pos=0;
	
	u8 engine_pos = 1;			
	 
	u8 datetime[7];
	u8 edit_datetime[7]={0};
	
	u8 RTC_pos = 1;

	u8 *str0;
	u8 *str1;
	u8 *str2;
	
	Show_ver();
	
	select = 0;
	u32 y_offset = 24;
	u32 set_offset = 1;
	u32 x_offset = set_offset+9*6+3;
	
	u32 line_x = 17;
	
	// TASK-ZH		
	// 0xE1E1 = ENG
	// if(gl_select_lang == 0xE1E1) {
	// 	language_sel = 0;
	// } else {
	// 	language_sel = 1;
	// }	

	// language_sel = 0;
	
	v_reset = Read_SET_info(1);
	v_rts = 	Read_SET_info(2);
	v_sleep = Read_SET_info(3);
	v_cheat = Read_SET_info(4);

	if( (v_reset != 0x0) && (v_reset != 0x1)) {
		v_reset = 0x0;
	}
	
	if( (v_rts != 0x0) && (v_rts != 0x1)) {
		v_rts = 0x0;
	}

	if( (v_sleep != 0x0) && (v_sleep != 0x1)) {
		v_sleep = 0x0;
	}

	if( (v_cheat != 0x0) && (v_cheat != 0x1)) {
		v_cheat = 0x0;
	}
	
	engine_sel = gl_engine_sel;

	
	while(1) {
		VBlankIntrWait(); 	
		
		if (re_show) {	
			// TIME SECTION
			sprintf(msg, "%s", gl_time);
			DrawHZText12(msg, 0, set_offset, y_offset, gl_color_selected, 1);	
			VBlankIntrWait();
			// ADDON SECTION
			sprintf(msg, "%s", gl_addon);
			DrawHZText12(msg, 0, set_offset, y_offset + line_x, gl_color_selected, 1);	
			Draw_select_icon(x_offset, y_offset + line_x, v_reset);
			// ADDON ITEMS
			// ITEM 1
			sprintf(msg,"%s", gl_reset);
			DrawHZText12(msg,0,x_offset + 15, y_offset + line_x, (addon_sel == 0) ? gl_color_selected : gl_color_text, 1);	
			Draw_select_icon(x_offset + 12 * 6, y_offset + line_x, v_rts );
			// ITEM 2
			sprintf(msg, "%s", gl_rts);
			DrawHZText12(msg,0,x_offset+12*6+15,y_offset+line_x,(addon_sel==1)?gl_color_selected:gl_color_text,1);
			// VBlankIntrWait();	
			// ITEM 3
			Draw_select_icon(x_offset,y_offset+line_x*2,v_sleep);
			sprintf(msg,"%s",gl_sleep);
			DrawHZText12(msg,0,x_offset+15,y_offset + line_x * 2,(addon_sel==3) ? gl_color_selected:gl_color_text,1);	
			// ITEM 4
			Draw_select_icon(x_offset+12*6,y_offset + line_x *2,v_cheat);
			sprintf(msg,"%s",gl_cheat);
			DrawHZText12(msg,0,x_offset+12*6+15,y_offset+line_x*2,(addon_sel==4)?gl_color_selected:gl_color_text,1);
			// VBlankIntrWait();		
			// ENGINE SECTION
			// VBlankIntrWait();			
			sprintf(msg, "%s", gl_engine);
			DrawHZText12(msg, 0, set_offset,y_offset + line_x * 3,gl_color_selected,1);
			Draw_select_icon(x_offset,y_offset+line_x * 3,(engine_sel == 0x1));
			sprintf(msg,"%s",gl_use_engine);
			DrawHZText12(msg,0,x_offset+15,y_offset+line_x * 3,(engine_pos == 0) ? gl_color_selected : gl_color_text, 1);	

			if ((v_rts == 1) && (v_cheat == 0) && (v_reset == 0) && (v_sleep == 0)) {
				sprintf(msg,"%s"," SAVE KEY");					
				DrawHZText12(msg,0,set_offset,y_offset + line_x * 4,gl_color_selected,1);	
				
				sprintf(msg,"%s"," LOAD KEY");
				DrawHZText12(msg,0,set_offset,y_offset + line_x * 5,gl_color_selected,1);	
			} else {						
				sprintf(msg,"%s",gl_hot_key);
				DrawHZText12(msg,0,set_offset,y_offset + line_x * 4,gl_color_selected,1);	
				
				sprintf(msg,"%s",gl_hot_key2);
				DrawHZText12(msg,0,set_offset,y_offset + line_x * 5,gl_color_selected,1);		
			}

			//RTC
			sprintf(msg,"%s", gl_ingameRTC);
			DrawHZText12(msg,0,set_offset,y_offset + line_x * 6,gl_color_selected,1);			
			Draw_select_icon(x_offset,y_offset + line_x * 6, (gl_ingame_RTC_open_status == 0x1));
			// sprintf(msg,"%s",gl_offRTC_powersave);
			ClearWithBG((u16*)gImage_SET, x_offset + 15, y_offset + line_x * 6, 6 * 6, 13, 1);
			if(gl_ingame_RTC_open_status){
				sprintf(msg,"%s",gl_ingameRTC_open);
			} else {
				sprintf(msg,"%s",gl_ingameRTC_close);
			}			
			DrawHZText12(msg,0,x_offset+15,y_offset + line_x * 6,(RTC_pos==0)?gl_color_selected:gl_color_text,1);	
	

			/* BUTTON BACKGROUND */
			u32 offsety;
			for (line = 0; line < 6; line++) {
				if(Set_OK == 1) {
					if((line == select) && (select == TIME_AREA) && (edit_pos == 7))
						clean_color = deepGreen;					
					else if((line == select) && (select == ADDON_AREA) && (addon_sel == 2)) 
						clean_color = deepGreen;	
					else if((line == select) && (select == ENGINE_AREA) && (engine_pos == 1)) 
						clean_color = deepGreen;	
					else if((line == select) && (select == SLEEP_AREA) && (sleep_pos == 3)) 	
						clean_color = deepGreen;	
					else if((line == select) && (select == MENU_AREA) && (rtshotkey_pos == 3)) 	
						clean_color = deepGreen;		
					else if((line == select) && (select == RTC_AREA) && (RTC_pos == 1)) 
						clean_color = deepGreen;	
					else 
						clean_color = gray100; 
				}	else {
					if (line == select)
						clean_color = deepGreen; 
					else 
						clean_color = gray100; // seaGreen
					}	

				offsety = y_offset + line * line_x;
				if (line > 1) offsety += line_x; 
					
				Clear(202, offsety - 2, 30, 14, clean_color, 1);	
				
				/* BUTTON TEXT */
				if (Set_OK == 1) {
					menuButtonColor = gray75;
				} else {
					menuButtonColor = baseWhite;
				}

				if (Set_OK && (line == Set_OK_line)){
					sprintf(msg, "%s", gl_ok_btn);
					DrawHZText12(msg, 0, 200 + 5, offsety, baseWhite, 1);
				} else {
					sprintf(msg, "%s", gl_set_btn);
					DrawHZText12(msg, 0, 200 + 5, offsety, menuButtonColor, 1);
				}
				// VBlankIntrWait();		
			}						
		}		
			
		currstate = Set_OK;		
		switch(currstate) {
			case 0: //initial state
				//get date and time 	
				VBlankIntrWait();
				rtc_enable();
				rtc_get(datetime);
				rtc_disenable();				
				char* wkday;
				switch(UNBCD(datetime[3]&0x7)) {
					case 0:wkday = gl_Sun;break;
					case 1:wkday = gl_Mon;break;
					case 2:wkday = gl_Tues;break;
					case 3:wkday = gl_Wed;break;
					case 4:wkday = gl_Thur;break;
					case 5:wkday = gl_Fri;break;
					case 6:wkday = gl_Sat;break;	
					default:wkday = gl_Sun;break;	
				}
				
				u8 HH = UNBCD(datetime[4]&0x3F);
				u8 MM = UNBCD(datetime[5]&0x7F);
				u8 SS = UNBCD(datetime[6]&0x7F);

				if (HH >23) HH = 0;
				if (MM >59) MM = 0;
				if (SS >59) SS = 0;

				/* Display date. Read binded key */
				sprintf(msg,"%u/%02u/%02u %02d:%02d:%02d %s",UNBCD(datetime[0])+2000,UNBCD(datetime[1]&0x1F),UNBCD(datetime[2]&0x3F),HH,MM,SS, wkday);
				ClearWithBG((u16*)gImage_SET,x_offset, y_offset, 22 * 6, 13, 1);	
				DrawHZText12(msg, 0, x_offset, y_offset, gl_color_text, 1);	
			

				u16 read5 = Read_SET_info(5); 
				u16 read6 = Read_SET_info(6); 
				u16 read7 = Read_SET_info(7); 

				switch(read5) {
					case 0:str0 = str_A;break;
					case 1:str0 = str_B;break;
					case 2:str0 = str_SELECT;break;
					case 3:str0 = str_START;break;
					case 4:str0 = str_RIGHT;break;
					case 5:str0 = str_LEFT;break;
					case 6:str0 = str_UP;break;	
					case 7:str0 = str_DOWN;break;
					case 8:str0 = str_R;break;
					case 9:str0 = str_L;break;
					default:str0 = str_L;break;							
				}	
				
				switch(read6) {
					case 0:str1 = str_A;break;
					case 1:str1 = str_B;break;
					case 2:str1 = str_SELECT;break;
					case 3:str1 = str_START;break;
					case 4:str1 = str_RIGHT;break;
					case 5:str1 = str_LEFT;break;
					case 6:str1 = str_UP;break;	
					case 7:str1 = str_DOWN;break;
					case 8:str1 = str_R;break;
					case 9:str1 = str_L;break;
					default:str1 = str_R;break;										
				}	
				
				switch(read7) {
					case 0:str2 = str_A;break;
					case 1:str2 = str_B;break;
					case 2:str2 = str_SELECT;break;
					case 3:str2 = str_START;break;
					case 4:str2 = str_RIGHT;break;
					case 5:str2 = str_LEFT;break;
					case 6:str2 = str_UP;break;	
					case 7:str2 = str_DOWN;break;
					case 8:str2 = str_R;break;
					case 9:str2 = str_L;break;	
					default:str2 = str_SELECT;break;										
				}	

				/* Display sleep hotkey. Read binded key */
				sprintf(msg,"%s %s  %s", str0, str1, str2); 
				DrawHZText12(msg, 0, x_offset + 10, y_offset + line_x * 4, menuButtonColor, 1);
				
				u16 read8 = Read_SET_info(8); 
				u16 read9 = Read_SET_info(9); 
				u16 read10 = Read_SET_info(10); 
				
				switch(read8) {
					case 0:str0 = str_A;break;
					case 1:str0 = str_B;break;
					case 2:str0 = str_SELECT;break;
					case 3:str0 = str_START;break;
					case 4:str0 = str_RIGHT;break;
					case 5:str0 = str_LEFT;break;
					case 6:str0 = str_UP;break;	
					case 7:str0 = str_DOWN;break;
					case 8:str0 = str_R;break;
					case 9:str0 = str_L;break;		
					default:str0 = str_L;break;							
				}	

				switch(read9) {
					case 0:str1 = str_A;break;
					case 1:str1 = str_B;break;
					case 2:str1 = str_SELECT;break;
					case 3:str1 = str_START;break;
					case 4:str1 = str_RIGHT;break;
					case 5:str1 = str_LEFT;break;
					case 6:str1 = str_UP;break;	
					case 7:str1 = str_DOWN;break;
					case 8:str1 = str_R;break;
					case 9:str1 = str_L;break;	
					default:str1 = str_R;break;									
				}	
				
				switch(read10) {
					case 0:str2 = str_A;break;
					case 1:str2 = str_B;break;
					case 2:str2 = str_SELECT;break;
					case 3:str2 = str_START;break;
					case 4:str2 = str_RIGHT;break;
					case 5:str2 = str_LEFT;break;
					case 6:str2 = str_UP;break;	
					case 7:str2 = str_DOWN;break;
					case 8:str2 = str_R;break;
					case 9:str2 = str_L;break;	
					default:str2 = str_START;break;									
				}	

				/* Display menu hot key */
				sprintf(msg,"%s %s  %s",str0,str1,str2);
				DrawHZText12(msg, 0, x_offset + 10, y_offset + line_x * 5, gl_color_text,1);
				

				/* Keys behavior in settings screen */
				scanKeys();
				isKeyDown = keysDown();
				
				/* Keys actions. Логика при выбранной линии */
				// set 
				if (isKeyDown & KEY_A) {
					Set_OK_line = select;
					Set_OK = 1; // !Set_OK;
					re_show = 1;
					
					// ????????
					edit_datetime[_HOUR] 	= HH;//UNBCD(datetime[_HOUR]&0x3F);
					edit_datetime[_MIN]		= MM;//UNBCD(datetime[_MIN]&0x7F);
					edit_datetime[_SEC] 	= SS;//UNBCD(datetime[_SEC]&0x7F);
					edit_datetime[_DAY] 	= UNBCD(datetime[_DAY]&0x3F);
					edit_datetime[_MONTH] = UNBCD(datetime[_MONTH]&0x1F);
					edit_datetime[_YEAR] 	= UNBCD(datetime[_YEAR]);
					edit_datetime[_WKD] 	= UNBCD(datetime[_WKD]&0x7);	
	
					if (select == TIME_AREA) {
						edit_pos = 0;
					} else if (select == ADDON_AREA) {
						addon_sel = 0;
					} else if (select == ENGINE_AREA) {
						engine_pos = 0;
					} else if (select == SLEEP_AREA) {
						sleep_pos = 0;
					}	else if (select == MENU_AREA) {
						rtshotkey_pos = 0;
					}	else if ((select == RTC_AREA) && (RTC_pos != 1)) {
						RTC_pos = 0;
					}

					// ??????
					
					edit_sleephotkey[0] = (read5 > 10) ? K_L : read5;
					edit_sleephotkey[1] = (read6 > 10) ? K_R : read6;
					edit_sleephotkey[2] = (read7 > 10) ? K_SELECT : read7;
					edit_rtshotkey[0] = (read8 > 10) ? K_L : read8;
					edit_rtshotkey[1] = (read9 > 10) ? K_R : read9;
					edit_rtshotkey[2] = (read10 > 10) ? K_START : read10;

				} else if (isKeyDown & KEY_DOWN) {  
						// Подумать как это пререписать
					if(select < 5){
						select++;		
						re_show = 1;
					} 
				} else if (isKeyDown & KEY_UP) {
					// Подумать как это пререписать
					if(select){
						select--;
						re_show = 1;
					} 
				} else if(isKeyDown & KEY_L) {
					return 0;
				} else if(isKeyDown & KEY_R) {
					return 1;
				}			
				break	;
			case 1: // edit state	
				//if(Set_OK_line==0) {														
					if(re_show) {																
						if(select == TIME_AREA){
							ClearWithBG((u16*)gImage_SET,x_offset, y_offset, 23 * 6, 13, 1);	
							switch(edit_pos) {
								case 0:clean_pos = x_offset;
									clean_w = 24;
									break;
								case 1:clean_pos = x_offset+6*5;
									clean_w = 12;
									break;
								case 2:clean_pos = x_offset+6*8;
									clean_w = 12;
									break;
								case 3:clean_pos = x_offset+6*11;
									clean_w = 12;
									break;
								case 4:clean_pos = x_offset+6*14;
									clean_w = 12;
									break;
								case 5:clean_pos = x_offset+6*17;
									clean_w = 12;
									break;
								case 6:clean_pos = x_offset+6*20;
									clean_w = 18;
									break;	
															
							}
							if(	edit_pos < 7)	
								Clear(clean_pos, y_offset, clean_w, 13, gl_color_btn_clean, 1);
								
							char* wkday;
							switch(edit_datetime[_WKD])
							{
								case 0:wkday = gl_Sun;break;
								case 1:wkday = gl_Mon;break;
								case 2:wkday = gl_Tues;break;
								case 3:wkday = gl_Wed;break;
								case 4:wkday = gl_Thur;break;
								case 5:wkday = gl_Fri;break;
								case 6:wkday = gl_Sat;break;	
								default:wkday = gl_Sun;break;	
							}						
							sprintf(msg,"20%02d/%02d/%02d %02d:%02d:%02d %s",edit_datetime[_YEAR],edit_datetime[_MONTH],edit_datetime[_DAY],edit_datetime[_HOUR],edit_datetime[_MIN],edit_datetime[_SEC] ,wkday);
							DrawHZText12(msg,0,x_offset,y_offset,gl_color_text,1);	
						}
						else if(select == SLEEP_AREA) {
							ClearWithBG((u16*)gImage_SET,x_offset, y_offset+line_x * 4, 23 * 6, 13, 1);	
							switch(sleep_pos) {
								case 0:clean_pos = x_offset + 10;
									break;
								case 1:clean_pos = x_offset + 10 + 6 * 6 + 6;
									break;
								case 2:clean_pos = x_offset + 10 + 6 * 12 + 18;
									break;						
								}
							// TODO
							if (sleep_pos < 3)	
								Clear(clean_pos, y_offset + line_x * 4, 36, 13, gl_color_btn_clean, 1);
							
							//DEBUG_printf("%x %x %x", edit_sleephotkey[0], edit_sleephotkey[1], edit_sleephotkey[2]);
							switch(edit_sleephotkey[0]) {
								case 0:str0 = str_A;break;
								case 1:str0 = str_B;break;
								case 2:str0 = str_SELECT;break;
								case 3:str0 = str_START;break;
								case 4:str0 = str_RIGHT;break;
								case 5:str0 = str_LEFT;break;
								case 6:str0 = str_UP;break;	
								case 7:str0 = str_DOWN;break;
								case 8:str0 = str_R;break;
								case 9:str0 = str_L;break;									
							}	

							switch(edit_sleephotkey[1]) {
								case 0:str1 = str_A;break;
								case 1:str1 = str_B;break;
								case 2:str1 = str_SELECT;break;
								case 3:str1 = str_START;break;
								case 4:str1 = str_RIGHT;break;
								case 5:str1 = str_LEFT;break;
								case 6:str1 = str_UP;break;	
								case 7:str1 = str_DOWN;break;
								case 8:str1 = str_R;break;
								case 9:str1 = str_L;break;									
							}	

							switch(edit_sleephotkey[2]) {
								case 0:str2 = str_A;break;
								case 1:str2 = str_B;break;
								case 2:str2 = str_SELECT;break;
								case 3:str2 = str_START;break;
								case 4:str2 = str_RIGHT;break;
								case 5:str2 = str_LEFT;break;
								case 6:str2 = str_UP;break;	
								case 7:str2 = str_DOWN;break;
								case 8:str2 = str_R;break;
								case 9:str2 = str_L;break;									
							}	

							sprintf(msg, "%s %s  %s", str0, str1, str2);
							DrawHZText12(msg, 0, x_offset + 10, y_offset + line_x * 4, gl_color_text, 1);
						} else if(select == MENU_AREA) {
							ClearWithBG((u16*)gImage_SET, x_offset, y_offset + line_x * 5, 23 * 6, 13, 1);	
							switch(rtshotkey_pos) {
								case 0:clean_pos = x_offset+10;
									break;
								case 1:clean_pos = x_offset+10+6*6+6;
									break;
								case 2:clean_pos = x_offset+10+6*12+18;
									break;								
								}
								if(	rtshotkey_pos < 3)	
									Clear(clean_pos, y_offset + line_x * 5, 36, 13, gl_color_btn_clean, 1);
								//DEBUG_printf("%x %x %x", edit_rtshotkey[0],edit_rtshotkey[1],edit_rtshotkey[2]);	
								switch(edit_rtshotkey[0]) {
									case 0:str0 = str_A;break;
									case 1:str0 = str_B;break;
									case 2:str0 = str_SELECT;break;
									case 3:str0 = str_START;break;
									case 4:str0 = str_RIGHT;break;
									case 5:str0 = str_LEFT;break;
									case 6:str0 = str_UP;break;	
									case 7:str0 = str_DOWN;break;
									case 8:str0 = str_R;break;
									case 9:str0 = str_L;break;									
								}	

								switch(edit_rtshotkey[1]) {
									case 0:str1 = str_A;break;
									case 1:str1 = str_B;break;
									case 2:str1 = str_SELECT;break;
									case 3:str1 = str_START;break;
									case 4:str1 = str_RIGHT;break;
									case 5:str1 = str_LEFT;break;
									case 6:str1 = str_UP;break;	
									case 7:str1 = str_DOWN;break;
									case 8:str1 = str_R;break;
									case 9:str1 = str_L;break;									
								}	
								switch(edit_rtshotkey[2]) {
									case 0:str2 = str_A;break;
									case 1:str2 = str_B;break;
									case 2:str2 = str_SELECT;break;
									case 3:str2 = str_START;break;
									case 4:str2 = str_RIGHT;break;
									case 5:str2 = str_LEFT;break;
									case 6:str2 = str_UP;break;	
									case 7:str2 = str_DOWN;break;
									case 8:str2 = str_R;break;
									case 9:str2 = str_L;break;									
								}	

								sprintf(msg,"%s %s  %s", str0, str1, str2);
								DrawHZText12(msg, 0, x_offset + 10, y_offset + line_x * 5, gl_color_text, 1);
						}	
					}

					re_show = 0;		
					/* Keys behavior in settings item area */
					// setRepeat(10, 1);	
					scanKeys();
					isKeyDown = keysDown();
					isKeyDownRepeat = keysDownRepeat();
					
					/* Keys actions логика редактирования */
					if (isKeyDownRepeat & KEY_UP) {
						if (select == TIME_AREA) {
							switch(edit_pos) {
								case 2:
									//day
									switch(edit_datetime[_MONTH]) {
										case 1: case 3: case 5: case 7: case 8: case 10: case 12:
											if(edit_datetime[_DAY]==31) {edit_datetime[_DAY]=1;} else {edit_datetime[_DAY]++;}
										break;
										case 4: case 6: case 9: case 11:
											if(edit_datetime[_DAY]==30) {edit_datetime[_DAY]=1;} else {edit_datetime[_DAY]++;}
										break;
										case 2:
											if((edit_datetime[_YEAR]%4==0 && edit_datetime[_DAY]==9) || (edit_datetime[_YEAR]%4>0 && edit_datetime[_DAY]==28)) {edit_datetime[_DAY]=1;} else {edit_datetime[_DAY]++;}
										break;
									}
								break;
								case 1:
									//month
									if(edit_datetime[_MONTH]==12) {edit_datetime[_MONTH]=1;} else {edit_datetime[_MONTH]++;}
								break;
								case 0:
									//year
									if(edit_datetime[_YEAR]==99) {edit_datetime[_YEAR]=0;} else {edit_datetime[_YEAR]++;}
								break;
								case 6:
									//week day
									if(edit_datetime[_WKD]==6) {edit_datetime[_WKD]=0;} else {edit_datetime[_WKD]++;}
								break;
								case 3:
									//hour
									if(edit_datetime[_HOUR]==23) {edit_datetime[_HOUR]=0;} else {edit_datetime[_HOUR]++;}
								break;
								case 4:
									//minute
									if(edit_datetime[_MIN]==59) {edit_datetime[_MIN]=0;} else {edit_datetime[_MIN]++;}
								break;
								case 5:
									//second
									if(edit_datetime[_SEC]==59) {edit_datetime[_SEC]=0;} else {edit_datetime[_SEC]++;}
								break;			
							}
											
						} else if (select == ADDON_AREA) {
							if (addon_sel > 2) {
								addon_sel -= 3;
							}
						}
						else if(select == SLEEP_AREA){
							switch(sleep_pos) {
								case 0:
									if(edit_sleephotkey[0] == 9) 
										{edit_sleephotkey[0]=0;} 
									else{edit_sleephotkey[0]++;}
										
									if(edit_sleephotkey[0]==edit_sleephotkey[1])
									{
										edit_sleephotkey[0]++;
										if(edit_sleephotkey[0]==edit_sleephotkey[2])
											edit_sleephotkey[0]++;
									}		
									else if(edit_sleephotkey[0]==edit_sleephotkey[2])
									{
										edit_sleephotkey[0]++;
										if(edit_sleephotkey[0]==edit_sleephotkey[1])
											edit_sleephotkey[0]++;
									}						
									break;
								case 1:
									if(edit_sleephotkey[1]==9) 
										{edit_sleephotkey[1]=0;} 
									else {edit_sleephotkey[1]++;}
										
									if(edit_sleephotkey[1]==edit_sleephotkey[0])
									{
										edit_sleephotkey[1]++;
										if(edit_sleephotkey[1]==edit_sleephotkey[2])
											edit_sleephotkey[1]++;
									}	
									else if(edit_sleephotkey[1]==edit_sleephotkey[2])
									{
										edit_sleephotkey[1]++;
										if(edit_sleephotkey[1]==edit_sleephotkey[0])
											edit_sleephotkey[1]++;
									}	
									break;
								case 2:
									if(edit_sleephotkey[2]==9) 
										{edit_sleephotkey[2]=0;} 
									else {edit_sleephotkey[2]++;}
										
									if(edit_sleephotkey[2]==edit_sleephotkey[0])
									{
										edit_sleephotkey[2]++;
										if(edit_sleephotkey[2]==edit_sleephotkey[1])
											edit_sleephotkey[2]++;
									}	
									else if(edit_sleephotkey[2]==edit_sleephotkey[1])
									{
										edit_sleephotkey[2]++;
										if(edit_sleephotkey[2]==edit_sleephotkey[0])
											edit_sleephotkey[2]++;
									}			
									break;
							}
						}
						else if(select == MENU_AREA){
							switch(rtshotkey_pos) {
								case 0:
									if(edit_rtshotkey[0]==9) 
										{edit_rtshotkey[0]=0;} 
									else {edit_rtshotkey[0]++;}
										
									if(edit_rtshotkey[0]==edit_rtshotkey[1])
									{
										edit_rtshotkey[0]++;
										if(edit_rtshotkey[0]==edit_rtshotkey[2])
											edit_rtshotkey[0]++;
									}		
									else if(edit_rtshotkey[0]==edit_rtshotkey[2])
									{
										edit_rtshotkey[0]++;
										if(edit_rtshotkey[0]==edit_rtshotkey[1])
											edit_rtshotkey[0]++;
									}	
									break;
								case 1:
									if(edit_rtshotkey[1]==9) 
										{edit_rtshotkey[1]=0;} 
									else {edit_rtshotkey[1]++;}
										
									if(edit_rtshotkey[1]==edit_rtshotkey[0])
									{
										edit_rtshotkey[1]++;
										if(edit_rtshotkey[1]==edit_rtshotkey[2])
											edit_rtshotkey[1]++;
									}	
									else if(edit_rtshotkey[1]==edit_rtshotkey[2])
									{
										edit_rtshotkey[1]++;
										if(edit_rtshotkey[1]==edit_rtshotkey[0])
											edit_rtshotkey[1]++;
									}	
									break;
								case 2:
									if(edit_rtshotkey[2]==9) 
										{edit_rtshotkey[2]=0;} 
									else {edit_rtshotkey[2]++;}
										
									if(edit_rtshotkey[2]==edit_rtshotkey[0])
									{
										edit_rtshotkey[2]++;
										if(edit_rtshotkey[2]==edit_rtshotkey[1])
											edit_rtshotkey[2]++;
									}	
									else if(edit_rtshotkey[2]==edit_rtshotkey[1])
									{
										edit_rtshotkey[2]++;
										if(edit_rtshotkey[2]==edit_rtshotkey[0])
											edit_rtshotkey[2]++;
									}	
									break;
							}
						}					
						re_show = 1;								
					} else if (isKeyDownRepeat & KEY_DOWN) {
						if (select == TIME_AREA) {
							switch(edit_pos) {
								case 2:
									switch(edit_datetime[_MONTH]) {
										case 1: case 3: case 5: case 7: case 8: case 10: case 12:
											if(edit_datetime[_DAY]==1) 
											{
												edit_datetime[_DAY]=31;
											} 
											else 
											{
												//if(edit_datetime[_DAY] > 1)
													edit_datetime[_DAY]--;
											}
										break;
										case 4: case 6: case 9: case 11:
											if(edit_datetime[_DAY]==1) 
											{
												edit_datetime[_DAY]=30;
											} 
											else 
											{
												//if(edit_datetime[_DAY] > 1)
													edit_datetime[_DAY]--;
											}
										break;
										case 2:
											if(edit_datetime[_DAY]==1) {
												if(edit_datetime[_YEAR]%4==0) {
													edit_datetime[_DAY]=29;
												} else {
													edit_datetime[_DAY]=28;
												}
											} else {
												edit_datetime[_DAY]--;
											}
										break;
									}
								break;
								case 1:
									if(edit_datetime[_MONTH]==1) {edit_datetime[_MONTH]=12;} else {edit_datetime[_MONTH]--;}
								break;
								case 0:
									if(edit_datetime[_YEAR]==0) {edit_datetime[_YEAR]=99;} else {edit_datetime[_YEAR]--;}
								break;
								case 6:
									//week day
									if(edit_datetime[_WKD]==0) {edit_datetime[_WKD]=6;} else {edit_datetime[_WKD]--;}
								break;
								case 3:
									//hour
									if(edit_datetime[_HOUR]==0) {edit_datetime[_HOUR]=23;} else {edit_datetime[_HOUR]--;}
								break;
								case 4:
									//minute
									if(edit_datetime[_MIN]==0) {edit_datetime[_MIN]=59;} else {edit_datetime[_MIN]--;}
								break;
								case 5:
									//second
									if(edit_datetime[_SEC]==0) {edit_datetime[_SEC]=59;} else {edit_datetime[_SEC]--;}
								break;
							
							}
						}
						else if (select == ADDON_AREA) {
							if(addon_sel < 2){
								addon_sel += 3;
							}
						}
						else if (select == SLEEP_AREA) {
							switch(sleep_pos) {
								case 0:
									if(edit_sleephotkey[0]==0) 
										{edit_sleephotkey[0]=9;} 
									else{	edit_sleephotkey[0]--;}
										
										
									if(edit_sleephotkey[0]==edit_sleephotkey[1])
									{
										if(edit_sleephotkey[0]==0) 
											{edit_sleephotkey[0]=9;} 
										else{	edit_sleephotkey[0]--;}
											
										if(edit_sleephotkey[0]==edit_sleephotkey[2])
											edit_sleephotkey[0]--;
									}		
									else if(edit_sleephotkey[0]==edit_sleephotkey[2])
									{
										if(edit_sleephotkey[0]==0) 
											{edit_sleephotkey[0]=9;} 
										else{	edit_sleephotkey[0]--;}
											
										if(edit_sleephotkey[0]==edit_sleephotkey[1])
											edit_sleephotkey[0]--;
									}																			
									break;
								case 1:
									if(edit_sleephotkey[1]==0) 
										{edit_sleephotkey[1]=9;} 
									else {edit_sleephotkey[1]--;}
									if(edit_sleephotkey[1]==edit_sleephotkey[0])
									{
										if(edit_sleephotkey[1]==0) 
											{edit_sleephotkey[1]=9;} 
										else{	edit_sleephotkey[1]--;}
											
										if(edit_sleephotkey[1]==edit_sleephotkey[2])
											edit_sleephotkey[1]--;
									}	
									else if(edit_sleephotkey[1]==edit_sleephotkey[2])
									{
										if(edit_sleephotkey[1]==0) 
											{edit_sleephotkey[1]=9;} 
										else{	edit_sleephotkey[1]--;}
											
										if(edit_sleephotkey[1]==edit_sleephotkey[0])
											edit_sleephotkey[1]--;
									}																					
									break;
								case 2:
									if(edit_sleephotkey[2]==0) 
										{edit_sleephotkey[2]=9;} 
									else{edit_sleephotkey[2]--;}
										
									if(edit_sleephotkey[2]==edit_sleephotkey[0])
									{
										if(edit_sleephotkey[2]==0) 
											{edit_sleephotkey[2]=9;} 
										else{	edit_sleephotkey[2]--;}
											
										if(edit_sleephotkey[2]==edit_sleephotkey[1])
											edit_sleephotkey[2]--;
									}	
									else if(edit_sleephotkey[2]==edit_sleephotkey[1])
									{
										if(edit_sleephotkey[2]==0) 
											{edit_sleephotkey[2]=9;} 
										else{	edit_sleephotkey[2]--;}
											
										if(edit_sleephotkey[2]==edit_sleephotkey[0])
											edit_sleephotkey[2]--;
									}														
									break;
							}
						}
						else if (select == MENU_AREA) {
							switch(rtshotkey_pos) {
								case 0:
									if(edit_rtshotkey[0]==0) 
										{edit_rtshotkey[0]=9;} 
									else{edit_rtshotkey[0]--;}	
										
									if(edit_rtshotkey[0]==edit_rtshotkey[1])
									{
										if(edit_rtshotkey[0]==0) 
											{edit_rtshotkey[0]=9;} 
										else{	edit_rtshotkey[0]--;}
											
										if(edit_rtshotkey[0]==edit_rtshotkey[2])
											edit_rtshotkey[0]--;
									}		
									else if(edit_rtshotkey[0]==edit_rtshotkey[2])
									{
										if(edit_rtshotkey[0]==0) 
											{edit_rtshotkey[0]=9;} 
										else{	edit_rtshotkey[0]--;}
											
										if(edit_rtshotkey[0]==edit_rtshotkey[1])
											edit_rtshotkey[0]--;
									}																				
									break;
								case 1:
									if(edit_rtshotkey[1]==0) 
										{edit_rtshotkey[1]=9;} 
									else 
										{edit_rtshotkey[1]--;}
											
									if(edit_rtshotkey[1]==edit_rtshotkey[0])
									{
										if(edit_rtshotkey[1]==0) 
											{edit_rtshotkey[1]=9;} 
										else{	edit_rtshotkey[1]--;}
											
										if(edit_rtshotkey[1]==edit_rtshotkey[2])
											edit_rtshotkey[1]--;
									}	
									else if(edit_rtshotkey[1]==edit_rtshotkey[2])
									{
										if(edit_rtshotkey[1]==0) 
											{edit_rtshotkey[1]=9;} 
										else{	edit_rtshotkey[1]--;}
											
										if(edit_rtshotkey[1]==edit_rtshotkey[0])
											edit_rtshotkey[1]--;
									}									
									break;
								case 2:
									if(edit_rtshotkey[2]==0) 
										{edit_rtshotkey[2]=9;} 
									else{edit_rtshotkey[2]--;}
										
									if(edit_rtshotkey[2]==edit_rtshotkey[0])
									{
										if(edit_rtshotkey[2]==0) 
											{edit_rtshotkey[2]=9;} 
										else{	edit_rtshotkey[2]--;}
											
										if(edit_rtshotkey[2]==edit_rtshotkey[1])
											edit_rtshotkey[2]--;
									}	
									else if(edit_rtshotkey[2]==edit_rtshotkey[1])
									{
										if(edit_rtshotkey[2]==0) 
											{edit_rtshotkey[2]=9;} 
										else{	edit_rtshotkey[2]--;}
											
										if(edit_rtshotkey[2]==edit_rtshotkey[0])
											edit_rtshotkey[2]--;
									}																	
									break;
							}
						}
						re_show = 1;	
					} else if(isKeyDownRepeat & KEY_RIGHT) {
						if (select == TIME_AREA) {
							if (edit_pos == 7) {
								edit_pos = 0;
							} else {
								edit_pos++;
							}
						} else if(select == ADDON_AREA) {
							if(addon_sel == 3){
								addon_sel ++;
							}else if (addon_sel < 2) {
								addon_sel ++;
							}
						} else if (select == ENGINE_AREA) {
								engine_pos = 1;
						} else if	(select == SLEEP_AREA) {
							if (sleep_pos < 3) {
								sleep_pos ++;
							}
						} else if	(select == MENU_AREA) {
							if(rtshotkey_pos<3){
								rtshotkey_pos ++;
							}
						} else if(select == RTC_AREA) {
								RTC_pos = 1;
						}
						re_show = 1;	
					} else if(isKeyDownRepeat & KEY_LEFT) {
						if (select == TIME_AREA) {
							if (edit_pos == 0) {
								edit_pos = 7;
							} else {
								edit_pos--;
							}
						} else if (select == ADDON_AREA) {
							if (addon_sel == 4) {
								addon_sel --;
							}	else if ((addon_sel > 0) && (addon_sel < 3)){
								addon_sel --;
							}		
						} else if (select == ENGINE_AREA) {
								engine_pos = 0;
						} else if (select == SLEEP_AREA) {
							if (sleep_pos) {
								sleep_pos--;
							}	
						}	else if(select == MENU_AREA) {
							if (rtshotkey_pos) {
								rtshotkey_pos--;
							}		
						}	else if(select == RTC_AREA) {
								RTC_pos = 0;
						}
						re_show = 1;	
					} else if(isKeyDown & KEY_A) {
						if ((select == TIME_AREA) && (edit_pos == 7)){
							rtc_enable();
							rtc_set(edit_datetime);
							rtc_disenable();
							delay(0x200);
							Set_OK = 0;//!Set_OK;
						} else if(select == ADDON_AREA)  {
							switch(addon_sel) {
								case 0:v_reset = !v_reset;break;
								case 1:v_rts   = !v_rts;break;
								case 3:v_sleep = !v_sleep;break;
								case 4:v_cheat = !v_cheat;break;	
								case 2:
									{
										save_set_info();
										CheckSwitch(); //read again  
										Set_OK = 0;	
										break;							
									}
							}	
						} else if (select == ENGINE_AREA) {
							switch(engine_pos)
							{
								case 0:engine_sel = !engine_sel;break;
								case 1:
									{
										save_set_info();
										Set_OK = 0;	
										gl_engine_sel = Read_SET_info(11);
										if( (gl_engine_sel != 0x0) && (gl_engine_sel != 0x1))
										{
											gl_engine_sel = 0x1;
										}
										break;							
									}
							}	
						} else if ((select == SLEEP_AREA) && (sleep_pos == 3)) {
							save_set_info();
							Set_OK = 0;
						}	else if ((select == MENU_AREA)  && (rtshotkey_pos == 3)) {
							save_set_info();
							Set_OK = 0;	
						}	else if (select == RTC_AREA) {
							switch(RTC_pos) {
								case 0:gl_ingame_RTC_open_status = !gl_ingame_RTC_open_status;break;
								case 1:
									{
										save_set_info();
										Set_OK = 0;	
										gl_ingame_RTC_open_status = Read_SET_info(13);
										if( (gl_ingame_RTC_open_status != 0x0) && (gl_ingame_RTC_open_status != 0x1))
										{
											gl_ingame_RTC_open_status = 0x1;
										}
										break;							
									}
							}	
						}			
						re_show = 1;
		
					} else if(isKeyDown & KEY_B) { 
						if ((select == TIME_AREA) && (edit_pos != 7)) {
							edit_pos = 7;
						} else if ((select == ADDON_AREA) && (addon_sel != 3)) {
							addon_sel = 3;
						} else if ((select == ENGINE_AREA) && (engine_pos != 1)) {
							engine_pos = 1;
						} else if ((select == SLEEP_AREA) && (sleep_pos != 3)) {
							sleep_pos = 3;
						}	else if ((select == MENU_AREA) && (rtshotkey_pos != 3)) {
							rtshotkey_pos = 3;
						}	else if ((select == RTC_AREA) && (RTC_pos != 1)) {
							RTC_pos = 1;
						}
						re_show = 1;
					}
				break	;			
		}//end switch 		
	} //end while(1)
}

/* SETTINGS STATE */
void save_set_info(void) {
	/* 0xE2E2 = ZH	0xE1E1 = ENG */
	SET_info_buffer[0] = 0xE1E1;
	SET_info_buffer[1] = v_reset;
	SET_info_buffer[2] = v_rts;
	SET_info_buffer[3] = v_sleep;
	SET_info_buffer[4] = v_cheat;	
	
	SET_info_buffer[5] = edit_sleephotkey[0];
	SET_info_buffer[6] = edit_sleephotkey[1];	
	SET_info_buffer[7] = edit_sleephotkey[2];	
	SET_info_buffer[8] = edit_rtshotkey[0];
	SET_info_buffer[9] = edit_rtshotkey[1];	
	SET_info_buffer[10] = edit_rtshotkey[2];	
	
	SET_info_buffer[11] = engine_sel;	
	
	SET_info_buffer[12] = gl_show_Thumbnail;	
	
	SET_info_buffer[13] = gl_ingame_RTC_open_status;
						
	//save to nor 
	Save_SET_info(SET_info_buffer, 0x200);
}