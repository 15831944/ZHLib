#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;


void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob,env;
        string pla, here;
        
        if (! me->query_temp("is_riding") && ! wizardp(me))
                return notify_fail("你还没有座骑！\n");
                
        if (! arg)
                return notify_fail("你要去哪里？\n");

      
        if (me->is_fighting())
                return notify_fail("你现在正在和人家动手， 哪能骑马走人呀。\n");
       if (me->query_temp("quest_biao"))
                return notify_fail("好好运镖,别乱跑.\n");

           env = environment(me); 
      //     if (! stringp(here = env->query("outdoors"))) 
      //          return notify_fail("在房间内不能骑马走人！\n");

       if (file_name(env)[0..5] == "/d/pk/") 
                return notify_fail("这里不能骑马走人！\n");        

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成，先等等吧。\n");

          else {
          message_vision(HIY
"$N骑在马上，大喝一声“走喽”，飞奔而去。。。\n"NOR, me);
}
          if(arg=="gc") pla = "/d/city/guangchang";
     else if(arg=="xingxiu") pla = "/d/xingxiu/xxh1";
     else if(arg=="mingjiao") pla = "/d/mingjiao/htping";
     else if(arg=="emei") pla = "/d/emei/huayanding";
     else if(arg=="henshan") pla = "/d/henshan/chidifeng";
     else if(arg=="shaolin") pla = "/d/shaolin/guangchang1";
     else if(arg=="lingjiu") pla = "/d/lingjiu/jian";
     else if(arg=="duanshi") pla = "/d/dali/wangfugate";
     else if(arg=="wudang") pla = "/d/wudang/jiejianyan";
     else if(arg=="huashan") pla = "/d/huashan/laojun";
     else if(arg=="quanzhen") pla = "/d/quanzhen/jiaobei";
     else if(arg=="xiaoyao") pla = "/d/xiaoyao/xiaodao4";
     else if(arg=="gumu") pla = "/d/gumu/mumen";
     else if(arg=="kunlun") pla = "/d/kunlun/shanmen";
     else if(arg=="xuedao") pla = "/d/xuedao/wangyougu";
     else if(arg=="tiezhang") pla = "/d/tiezhang/shanmen";
     else if(arg=="dalun") pla = "/d/xueshan/shanmen";
     else if(arg=="songshan") pla = "/d/songshan/dadian";
     else if(arg=="shenlong") pla = "/d/shenlong/damen";
     else if(arg=="xuanming") pla = "/d/xuanminggu/shanjiao";
     else if(arg=="kaifeng") pla = "/d/kaifeng/zhuque";
     else if(arg=="kunming") pla = "/d/kunming/jinrilou";
     else if(arg=="wudu") pla = "/d/wudu/damen";
     else if(arg=="hengshan") pla = "/d/hengshan/beiyuemiao";
     else if(arg=="xueshan") pla = "/d/lingxiao/shanya";
     else if(arg=="riyue") pla = "/d/heimuya/pingdingzhou";
     else if(arg=="murong") pla = "/d/yanziwu/bozhou";
     else if(arg=="ouyang") pla = "/d/baituo/damen";
     else if(arg=="jueqing") pla = "/d/jueqing/shanzhuang";
     else if(arg=="guanwai") pla = "/d/guanwai/jishi";
     else if(arg=="dali") pla = "/d/dali/center";
     else if(arg=="lsd") pla = "/d/mingjiao/lsd/anbian";
     else if(arg=="beijing") pla = "/d/beijing/tiananmen";
     else if(arg=="changan") pla = "/d/changan/bridge2";
     else if(arg=="chengdu") pla = "/d/city3/guangchang";
     else if(arg=="foshan") pla = "/d/foshan/street3";
     else if(arg=="fuzhou") pla = "/d/fuzhou/dongjiekou";
     else if(arg=="guiyun") pla = "/d/guiyun/damen";
     else if(arg=="hangzhou") pla = "/d/hangzhou/road9";
     else if(arg=="jingzhou") pla = "/d/jingzhou/guangchang";
     else if(arg=="lingzhou") pla = "/d/lingzhou/center";
     else if(arg=="luoyang") pla = "/d/luoyang/center";
     else if(arg=="quanzhou") pla = "/d/quanzhou/zhongxin";
     else if(arg=="suzhou") pla = "/d/suzhou/zhongxin";
     else if(arg=="zhongzhou") pla = "/d/zhongzhou/shizhongxin";
     else if(arg=="ruzhou") pla = "/d/ruzhou/ruzhou";
     else if(arg=="xiangyang") pla = "/quest/quest_jun/guangchang"; 
     else if(arg=="lanzhou") pla = "/d/lanzhou/guangchang"; 
     else if(arg=="lingxiao") pla = "/d/lingxiao/shanya";  
     else if(arg=="taohua") pla = "/d/taohua/damen";
     else if(arg=="baituo") pla = "/d/baituo/shijie";
     else if(arg=="shangjia") pla = "/d/shaolin/shang_men";
     else if(arg=="hujia") pla = "/d/guanwai/xiaoyuan";
     else if(arg=="wudie"
     && me->query("family/family_name") == "舞蝶仙") pla = "/d/wudie/wdt.c";     
     else if(arg=="meizhuang"
     && me->query("family/family_name") == "梅庄") pla = "/d/meizhuang/keting";
     else if(arg=="wugong") pla = "/d/quanzhen/zhongxin";             else {
               message_vision(HIR
"根本没有这个地方，怎么去呀！\n"NOR, me);
}
       me->move(pla);
  /*   if (me->move(pla)) {
       message_vision(HIC"\n到了！马儿稳稳的停了下来。\n"NOR,me);
           
 }              */
     return 1;
}


int help(object me)
{
        write(@HELP
指令格式 : rideto <地点>
这个指令可以骑在马上或者宠物上面到达某个地点.
可以到达的地点有：
星    宿<xingxiu>    明    教<mingjiao>    峨    嵋<emei>       少    林<shaolin>   
灵    鹫<lingjiu>    段    氏<duanshi>     武    当<wudang>     华    山<huashan>   
古    墓<gumu>       昆    仑<kunlun>      血 刀 门<xuedao>     铁    掌<tiezhang>  
嵩    山<songshan>   神    龙<shenlong>    玄 冥 谷<xuanming>   五    毒<wudu>      
雪    山<xueshan>    日    月<riyue>       全    真<quanzhen>   逍    遥<xiaoyao>
大    轮<dalun>      衡    山<henshan>     慕容世家<murong>     欧阳世家<ouyang>
绝 情 谷<jueqing>    归 云 庄<guiyun>      关    外<guanwai>    大 理 城<dali>
北    京<beijing>    成    都<chengdu>     佛    山<foshan>     福    州<fuzhou>
杭    州<hangzhou>   荆    州<jingzhou>    灵    州<lingzhou>   洛    阳<luoyang>
泉    州<quanzhou>   苏    州<suzhou>      中    州<zhongzhou>  扬州广场<gc>
襄    阳<xiangyang>  开    封<kaifeng>     昆    明<kunming>    兰    州<lanzhou>
汝    州<ruzhou>     武    功<wugong>      凌    霄<lingxiao>   桃     花<taohua>
梅    庄<meizhuang>  (仅限梅庄弟子使用）   商    家<shangjia>   胡     家<hujia>
恒    山<hengshan>   灵蛇岛<lsd>           舞    蝶<wudie>     (仅限舞蝶弟子使用）
 
HELP
    );
    return 1;
}


