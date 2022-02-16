//#include<reg51.h>
#include "STC15.h"
//#include"lcd1602.h"

void delay(int z)
{
	int x,y;
	for(x = z;x > 0;x--)
	for(y = 110;y > 0;y--);
}

code const unsigned int music_scale[] = {62477,58078,58781,59418,59995,60517,
    60991,61419,61807,62159,64507,65252,65190,64692,63263,64771,64843,64909,
    64151,64968,65021,65070,65303,65279,64281,64400,62766,63478,64604,63672,
    64007,65222,63027,65154,63847,65114
};

/*
乐谱结构体声明
BPM：演奏速率，每分钟的节拍数
name：曲目名称
music：乐谱的字符串表示
*/
struct Music{
    unsigned char BPM;
    unsigned char *name;
    unsigned char  *music;
};

struct Music mymusics[] = {
 {110,"JvCiLangDeXiaTian","====6_0_ e__=__0__=__|\
4_8_ q__=__8__=__|5_9_ w__=__9__=__|8_w_ t__=__w__=__\
|= o__s__d__f__|\
d_s__ s-|= o__s__d__f__|d_s__d_f_f__-|o__s__d__f__|\
d_s__ s-|= o__s__d__f__|d_s__d_f_f__-|f_g|\
h_h__h_h_|h_f__s_f___g__|h_h__h_h_|h_f__s_s___d__|\
f_f__f_f_|f_j_ j__f___d___s_|d p_p__p__|p_a__=__ o__s__d__f__|\
d_s__ s-|= o__s__d__f__|d_s__d_f_f__-|o__s__d__f__|\
d_s__ s-|= o__s__d__f__|d_s__d_f_f__-|f_g|\
h_h__h_h_|h_f__s_f___g__|h_h__h_h_|h_f__s_s___d__|"},
 {130,"HuanLeDouDiZhu","====op_s_|h_ h_j__h_f_hv__b__v_|s_s__d__s_p_ ov__b__v_|p_p__o__p_s_d_s_d_f_|\
h_h__j__h_f_db__v__z_|h_h__j__h_f_hb__v__|d_d__f__d_s_pz__x__b__|o_p_s_d_f_j_f_h_|\
d_d__f__d_p_s=|j_j__h__f_h_jf_|h_h__j__h_f_h=|d_d__f__d_s_p_o_|\
dsf=|j_j__h__f_h_jf_|h_h__j__h_f_h=|d_d__f__d_s_d_s_p_o_|s=l__h__f__-|"},
{150,"QiFengLe","====tyutp_4__o__8__p_q_- t_a__5__p__9__\
a_w_- a_3_p__7__a_0_us__6__d_s__0__a_p_e_o\
p_4_o__8__p_q_o_p_o_ p_5_o__9__y_w_o u_1_580 t_w_yu_0_t\
p_4_o__8__p_q_-t_ a_5_p__9__a_w_- a_3_p__7__a_0_us__6__d\
_s__0__a_p_e_o p_4_f__8__f_q_op_5_f__9__f_w_o p_6_3680-"},
{160,"DaYu","====uyup uyua uyus a-o  uyup uyua-o-\
uyup uyua uyus a-o  yue-yuewe-\
ety-te- ety-tu-uop pouy t-y-u-\
ety-te- ety-tu-yue-yuewe-\
uos-au-uyt-tyu-uyt-psapoy u-\
uos-au-uyt-tyu-yue-yuewe-"},
{170,"ZhiAiLiSi","uyuyuryte 80er 0wrt 0uyuyuyte 80er 0tre\
e rtyuwiyyquyt0yte80er0wrt0 uyuyuryte 80er\
0wrt e rty uwiu yquy t0yt r0ufxfuyuyuyuyuyuryte"},
{90,"WoHeWoDeZuGuo","====o_p_o_i_u_y_|t.w.|t_u_s_a_p_.u__|\
o~|p_a_p_o_i_u_|y.e.|r_e_w_o_t_.y__|u~|o_p_o_i_u_y_|t.w.|\
t_u_s_a_d_.s__|p~|s_a_p_o.|p_o_i_u.|re_wy_|t~|"},
{90,"MengZhongDeHunLi","====_.j__|j__k__k__l__l__k__k__j__\
j__f__f__s__s__p__p__h__|h__g__g__f__g__h__g.|=__g__g__\
h__h__j__j__k__k__h__h__d__d__g__|g__f__f__d__f__g__f.|f_ \
p__s__f__d__ f_ p__s__f__d__ f_ p__s__g__f__ |g_ g__f__g__\
G__ h_ h__j__h__j__f.|x_ j__l__x__z__ x_ j__l__x__z__ x_ j\
__l__c__x__ |c_ c__x__c__C__ v_ v__b__v__b__x.|l_.f__f__g__\
g_.d__d__k__ k_.d__d__f__ f_s__s__j__h__|j_.s__s__d__ d_.a__\
f__d__f.|l_.l__l__z__z_.l__k__j__h_.h__j__h__f.|l_l__l__l__z__\
z_.l__k__j__ h_.h__j__h__|j---|"},
{170,"TianKongZhiCheng","====pas-as-f-a---\
up-op-s-o---\
ui-uis---\
sa-IIs-s-\
p-j-jh-h--\
s-d-sd-h-f---\
s-j-jh-h--\
s-d-sd-a-p---\
pas-as-f-a---\
u-p-op-s-o---\
ui-s-fs--\
sa-p-a-O-p--"},
};

//每分钟节拍数
unsigned int current_freq=60000;
//空拍标志位
bit stop_beat = 1;
//切歌标志位
bit next_music = 0;

//暂停标志位
bit pause_music = 0;

sbit speaker = P3^4;

void play(const struct Music *m)
{
    //计算一个拍的时间
    unsigned int beat_time_ms = 1000/ m->BPM *600;
    unsigned char p,i,isbeat;
    //指针
    unsigned int music_p=0;
    stop_beat = 1;
//    lcd_clear();
//    lcd_write_str(m->name,0,0);
    //开始进入音乐循环
    while(m->music[music_p] != '\0')    
    {
        while(pause_music);
        stop_beat = 1;
        if(next_music){
            //如果切歌标志位置位，立即切歌
            next_music = 0;
            return;
        }
        isbeat = 1;
        p = m->music[music_p];
        
        //节拍字符
        if(p>='a' && p<='z')
        {
            stop_beat = 0;
            current_freq = music_scale[p-'a'+10];
        }
        else if(p>='0' && p<='9')
        {
            stop_beat = 0;
            current_freq = music_scale[p-'0'];
        }
        else if(p=='=')
        {
            //空拍
            stop_beat = 1;
        }
        else if(p=='|')
        {
            //分节符,空一个四分音符
            stop_beat = 1;
            delay(beat_time_ms/8);
            isbeat = 0;
        }
        else
        {
            isbeat = 0;
        }
        music_p++;

        //节拍延时
        if(isbeat)
        {
            for(i=0;m->music[music_p]=='_';i++)
                music_p++;
            //连音符处理,一个'-'播放一拍
            while(m->music[music_p] == '-')
            {
                music_p++;
                delay(beat_time_ms);
            }
            if(i==0)
                //四分音符
                delay(beat_time_ms);
            else if(i==1)
                //八分音符
                delay(beat_time_ms/2);
            else if(i==2)
                //十六分音符
                delay(beat_time_ms/4);
            else if(i>=3)
                //三十二分音符
                delay(beat_time_ms/8);
        }
        stop_beat = 1;
        delay(beat_time_ms/8);
    }
    
}

void main()
{
    unsigned char current_music = 0;
    code const unsigned int music_count =sizeof(mymusics)/7 ;
    //初始化计数器0
    TMOD = 0x01;
    TH0 = 0x00;
    TL0 = 0x00;
    ET0 = 1;
    TR0 = 1;
    //开启外部中断，下降沿触发
    EX0 = 1;
    IT0 = 1;
    EX1 = 1;
    IT1 = 1;
    //使能中断开关
    EA = 1;
    //初始化lcd1602
//    lcd_init();
    while(1)
	{
        play(&(mymusics[current_music]));
        current_music++;
        if(current_music>music_count-1)
            current_music = 0;
	}
}

void timer0() interrupt 1
{
    TH0=current_freq/256;
    TL0=current_freq%256;
    if(stop_beat)
        ;
    else
        speaker = ~speaker;
}

void exit0() interrupt 0
{
    pause_music = ~pause_music;
}

void exit1() interrupt 3
{
    next_music = 1;
}

