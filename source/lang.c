#include "lang.h"

char* gl_init_error;
char* gl_power_off;
char* gl_init_ok;
char* gl_Loading;
char* gl_file_overflow;

char* gl_menu_btn;
char* gl_lastest_game;

char* gl_writing;

char* gl_time;
char* gl_Mon;
char* gl_Tues;
char* gl_Wed;
char* gl_Thur;
char* gl_Fri;
char* gl_Sat;
char* gl_Sun;

char* gl_addon;
char* gl_reset;
char* gl_rts;
char* gl_sleep;
char* gl_cheat;

char* gl_hot_key;
char* gl_hot_key2;

char* gl_language;
char* gl_en_lang;
char* gl_zh_lang;
char* gl_set_btn;
char* gl_ok_btn;

char* gl_formatnor_info;

char* gl_check_sav;
char* gl_make_sav;

char* gl_check_RTS;
char* gl_make_RTS;

char* gl_check_pat;
char* gl_make_pat;

char* gl_loading_game;

char* gl_engine;
char* gl_use_engine;

char*  gl_recently_play;

char* gl_START_help;
char* gl_SELECT_help;
char* gl_L_A_help;
char* gl_LSTART_help;
char* gl_online_manual;

char* gl_no_game_played;

char* gl_ingameRTC;
//char* gl_offRTC_powersave;
char* gl_ingameRTC_open;
char* gl_ingameRTC_close;

char* gl_error_0;
char* gl_error_1;
char* gl_error_2;
char* gl_error_3;
char* gl_error_4;
char* gl_error_5;
char* gl_error_6;
//--
char**  gl_rom_menu;
char**  gl_nor_op;


//����
const char zh_init_error[]="TF����ʼ��ʧ��";
const char zh_power_off[]="�ػ�";
const char zh_init_ok[]="TF����ʼ���ɹ�";
const char zh_Loading[]="������...";
const char zh_file_overflow[]="�ļ�̫��,���ܼ���";

const char zh_menu_btn[]=" [B]ȡ��    [A]ȷ��";
const char zh_writing[]="����д...";
const char zh_lastest_game[]="��ѡ�����һ����Ϸ";

const char zh_time[] ="     ʱ��";
const char zh_Mon[]="һ";
const char zh_Tues[]="��";
const char zh_Wed[]="��";
const char zh_Thur[]="��";
const char zh_Fri[]="��";
const char zh_Sat[]="��";
const char zh_Sun[]="��";

const char zh_addon[]="     ����";
const char zh_reset[]="����λ";
const char zh_rts[]="��ʱ�浵";
const char zh_sleep[]="˯��";
const char zh_cheat[]="����ָ";

const char zh_hot_key[]=" ˯���ȼ�";
const char zh_hot_key2[]=" �˵��ȼ�";

const char zh_language[]=" LANGUAGE";
const char zh_lang[]=" ����";

const char zh_set_btn[]="����";
const char zh_ok_btn[]="����";
const char zh_formatnor_info[]="ȷ��?��Լ4����";

const char zh_check_sav[]="���SAV�ļ�";
const char zh_make_sav[]="����SAV�ļ�";

const char zh_check_RTS[]="���RTS�ļ�";
const char zh_make_RTS[]="����RTS�ļ�";

const char zh_check_pat[]="���PAT�ļ�";
const char zh_make_pat[]="����PAT�ļ�";

const char zh_loading_game[]="������Ϸ";

const char zh_engine[]="     ����";
const char zh_use_engine[]="���ٲ�������";

const char zh_recently_play[]="�����Ϸ�б�";

const char zh_START_help[]="�������Ϸ�б�";
const char zh_SELECT_help[]="����ͼ����";
const char zh_L_A_help[]="������";
const char zh_LSTART_help[]="ɾ���ļ�";
const char zh_online_manual[]="  ����˵����";

const char zh_no_game_played[]="��û�����Ϸ";

const char zh_ingameRTC[]=" ��Ϸʱ��";
//const char zh_offRTC_powersave[]=" ";
const char zh_ingameRTC_open[]="��";
const char zh_ingameRTC_close[]="�ر�";//TURNOFF TO POWER SAVE

const char zh_error_0[]="�ļ��д���";
const char zh_error_1[]="�ļ�����";
const char zh_error_2[]="SAVER����";
const char zh_error_3[]="�浵����";
const char zh_error_4[]="��ȡ�浵����";
const char zh_error_5[]="�����浵����";
const char zh_error_6[]="RTS�ļ�����";

const char *zh_rom_menu[]={
	"ֱ������",
	"����������",
	"��¼��NOR",
	"��¼��NOR������",
	"�浵����",
	"����ָ",
};
const char *zh_nor_op[3]={
	"ֱ������",
	"ɾ��",
	"ȫ����ʽ��",
};



//Ӣ��
const char en_init_error[]="Micro SD card initial error";
const char en_power_off[]="Power off";
const char en_init_ok[]="Micro SD card initial OK";
const char en_Loading[]="Loading...";
const char en_file_overflow[]="The file overflow";

const char en_menu_btn[]="[B]CANCEL    [A]OK";
const char en_writing[]="WRITING...";
const char en_lastest_game[]="SELECT THE LASTEST";

const char en_time[]="     TIME";
const char en_Mon[]="MON";
const char en_Tues[]="TUE";
const char en_Wed[]="WED";
const char en_Thur[]="THU";
const char en_Fri[]="FRI";
const char en_Sat[]="SAT";
const char en_Sun[]="SUN";

const char en_addon[]="    ADDON";
const char en_reset[]="RESET";
const char en_rts[]="SAVESTATE";
const char en_sleep[]="SLEEP";
const char en_cheat[]="CHEAT";

const char en_hot_key[] ="SLEEP KEY";
const char en_hot_key2[]=" MENU KEY";

const char en_language[]=" LANGUAGE";
const char en_lang[]="ENGLISH";
const char en_set_btn[]="SET";
const char en_ok_btn[]=" OK";

const char en_formatnor_info[]="SURE?about 4 mins";

const char en_check_sav[]="CHECKING SAV FILE";
const char en_make_sav[] ="CREATING SAV FILE";

const char en_check_RTS[]="CHECKING RTS FILE";
const char en_make_RTS[] ="CREATING RTS FILE";

const char en_check_pat[]="CHECKING PAT FILE";
const char en_make_pat[] ="CREATING PAT FILE";

const char en_loading_game[]="LOADING GAME";

const char en_engine[]="   ENGINE";
const char en_use_engine[]="FAST PATCH ENGINE";

const char en_recently_play[]="RECENT PLAYED";

const char en_START_help[]="Open recently played list";
const char en_SELECT_help[]="Thumbnail toggle";
const char en_L_A_help[]="Multiboot";
const char en_LSTART_help[]="Delete file";
const char en_online_manual[]="Online manual";

const char en_no_game_played[]="No game played yet";

const char en_ingameRTC[]=" GAME RTC";
const char en_ingameRTC_open[]="OPEN";
const char en_ingameRTC_close[]="CLOSE";//TURNOFF TO POWER SAVE

const char en_error_0[]="Folder error";
const char en_error_1[]="File error";
const char en_error_2[]="SAVER error";
const char en_error_3[]="Save error";
const char en_error_4[]="Read save error";
const char en_error_5[]="Make save error";
const char en_error_6[]="RTS file error";

const char *en_rom_menu[] = {
	"START GAME",
	"START WITH ADDONS",
	"COPY TO NOR",
	"Copy to NOR Addon",
	"SAVEING",
	"CHEAT",
};
const char *en_nor_op[3]={
	"START GAME",
	"DELETE FILE",
	"FORMAT",
};	

//---------------------------------------------------------------------------------
void LoadChinese(void)
{
	gl_init_error = (char*)zh_init_error;
	gl_power_off = (char*)zh_power_off;
	gl_init_ok = (char*)zh_init_ok;
	gl_Loading = (char*)zh_Loading;
	gl_file_overflow = (char*)zh_file_overflow;

	gl_menu_btn = (char*)zh_menu_btn;
	gl_writing = (char*)zh_writing;
	gl_lastest_game = (char*)zh_lastest_game;
	
	
	gl_time = (char*)zh_time;	
	gl_Mon = (char*)zh_Mon;
	gl_Tues = (char*)zh_Tues;
	gl_Wed = (char*)zh_Wed;
	gl_Thur = (char*)zh_Thur;
	gl_Fri = (char*)zh_Fri;
	gl_Sat = (char*)zh_Sat;
	gl_Sun = (char*)zh_Sun;

	gl_addon = (char*)zh_addon;
	gl_reset = (char*)zh_reset;
	gl_rts = (char*)zh_rts;
	gl_sleep = (char*)zh_sleep;
	gl_cheat = (char*)zh_cheat;	
	
	gl_hot_key = (char*)zh_hot_key;
	gl_hot_key2 = (char*)zh_hot_key2;

	gl_language =  (char*)zh_language;
	gl_en_lang = (char*)en_lang;
	gl_zh_lang = (char*)zh_lang;;
	gl_set_btn = (char*)zh_set_btn;
	gl_ok_btn = (char*)zh_ok_btn;
	gl_formatnor_info = (char*)zh_formatnor_info;

	gl_check_sav = (char*)zh_check_sav;
	gl_make_sav = (char*)zh_make_sav;
		
	gl_check_RTS = (char*)zh_check_RTS;
	gl_make_RTS = (char*)zh_make_RTS;
	
	gl_check_pat = (char*)zh_check_pat;
	gl_make_pat = (char*)zh_make_pat;
	
	gl_loading_game = (char*)zh_loading_game;
	gl_engine = (char*)zh_engine;
	gl_use_engine = (char*)zh_use_engine;
	
	gl_recently_play = (char*)zh_recently_play;

	gl_START_help = (char*)zh_START_help;
	gl_SELECT_help = (char*)zh_SELECT_help;
	gl_L_A_help = (char*)zh_L_A_help;
	gl_LSTART_help = (char*)zh_LSTART_help;
	gl_online_manual = (char*)zh_online_manual;
	
	gl_no_game_played = (char*)zh_no_game_played;
	
	gl_ingameRTC = (char*)zh_ingameRTC;
	//gl_offRTC_powersave = (char*)zh_offRTC_powersave;
	gl_ingameRTC_open = (char*)zh_ingameRTC_open;
	gl_ingameRTC_close = (char*)zh_ingameRTC_close;
	
	gl_error_0 = (char*)zh_error_0;
	gl_error_1 = (char*)zh_error_1;
	gl_error_2 = (char*)zh_error_2;
	gl_error_3 = (char*)zh_error_3;
	gl_error_4 = (char*)zh_error_4;
	gl_error_5 = (char*)zh_error_5;
	gl_error_6 = (char*)zh_error_6;
	
	//
	gl_rom_menu = (char**)zh_rom_menu;
	gl_nor_op = (char**)zh_nor_op;

}
//---------------------------------------------------------------------------------
void LoadEnglish(void)
{
	gl_init_error = (char*)en_init_error;
	gl_power_off = (char*)en_power_off;
	gl_init_ok = (char*)en_init_ok;
	gl_Loading = (char*)en_Loading;
	gl_file_overflow = (char*)en_file_overflow;

	gl_menu_btn = (char*)en_menu_btn;
	gl_writing = (char*)en_writing;
	gl_lastest_game = (char*)en_lastest_game;
	
	gl_time = (char*)en_time;	
	gl_Mon = (char*)en_Mon;
	gl_Tues = (char*)en_Tues;
	gl_Wed = (char*)en_Wed;
	gl_Thur = (char*)en_Thur;
	gl_Fri = (char*)en_Fri;
	gl_Sat = (char*)en_Sat;
	gl_Sun = (char*)en_Sun;
	gl_addon = (char*)en_addon;
	gl_reset = (char*)en_reset;
	gl_rts = (char*)en_rts;
	gl_sleep = (char*)en_sleep;
	gl_cheat = (char*)en_cheat;	
	
	gl_hot_key = (char*)en_hot_key;
	gl_hot_key2 = (char*)en_hot_key2;
	
	gl_language =  (char*)en_language;
	gl_en_lang = (char*)en_lang;
	gl_zh_lang = (char*)zh_lang;;
	gl_set_btn = (char*)en_set_btn;
	gl_ok_btn = (char*)en_ok_btn;
	gl_formatnor_info = (char*)en_formatnor_info;

	gl_check_sav = (char*)en_check_sav;
	gl_make_sav = (char*)en_make_sav;
		
	gl_check_RTS = (char*)en_check_RTS;
	gl_make_RTS = (char*)en_make_RTS;
	
	gl_check_pat = (char*)en_check_pat;
	gl_make_pat = (char*)en_make_pat;
	
	gl_loading_game = (char*)en_loading_game;
	
	gl_engine = (char*)en_engine;
	gl_use_engine = (char*)en_use_engine;
	
	gl_recently_play = (char*)en_recently_play;
	
	gl_START_help = (char*)en_START_help;
	gl_SELECT_help = (char*)en_SELECT_help;
	gl_L_A_help = (char*)en_L_A_help;
	gl_LSTART_help = (char*)en_LSTART_help;
	gl_online_manual = (char*)en_online_manual;
	
	gl_no_game_played = (char*)en_no_game_played;
	
	gl_ingameRTC = (char*)en_ingameRTC;
	//gl_offRTC_powersave = (char*)en_offRTC_powersave;
	gl_ingameRTC_open = (char*)en_ingameRTC_open;
	gl_ingameRTC_close = (char*)en_ingameRTC_close;
	
	gl_error_0 = (char*)en_error_0;
	gl_error_1 = (char*)en_error_1;
	gl_error_2 = (char*)en_error_2;
	gl_error_3 = (char*)en_error_3;
	gl_error_4 = (char*)en_error_4;
	gl_error_5 = (char*)en_error_5;
	gl_error_6 = (char*)en_error_6;
	//
	gl_rom_menu = (char**)en_rom_menu;
	gl_nor_op = (char**)en_nor_op;
}
