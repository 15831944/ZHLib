// 女娲庙/九天玄女解谜地点

#include <ansi.h> 
inherit ROOM;

#define XUANYIN    "/u/yuchang/special/xuannv/xuanyin.h"
#define XUANNVJIAN       "/u/yuchang/special/xuannv/xuannvjian.h"
#define SPECIAL     "/data/item/"

void create()
{
	set("short", "女娲庙");
	set("long", @LONG
此处供奉的是天神女娲。相传盘古开天辟地后，女娲用泥土
捏制人形，吹入仙气，生者无数，后世世人皆由此而来。当年女
娲更以五彩石贴补天之缺口，世间方免遭生灵涂炭之劫。所以历
代世人无不景仰女娲造人补天之德，特造此庙以示敬意。相传受
女娲庇护之人在此虔心叩拜(ketou)会有至福。
LONG );
	set("exits", ([		
		"south"        : "/d/changan/road6",
	]));
	set("objects",([	
             __DIR__"statue" : 1,
	]));
       set("no_fight",1);	
	setup();	
}

void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

int do_ketou()
{
     object me, xuanyin, xuannvjian;
     string fn, fc, answer;     

     me = this_player();
    
     if (me->is_busy() || me->is_fighting())
     {
            write("你忙完了再说吧！\n");
            return 1;
     }
     if (me->query("jing") < 20)
     {
            write("你精力不足！\n");
            return 1;
     }
     if (me->query("jing") > 20) 
          me->add("jing", -20);
     else me->set("jing", 1);

     me->start_busy(2 + random(2));

     message_vision(HIC "只见$N" HIC "面朝女娲神像，跪在地上恭恭敬敬磕了三个响头。\n\n"
                    NOR, me);

     message_vision(HIC "磕头完毕，$N缓缓站起身来。\n\n" NOR, me);  

     if ( me->query("special_skill/emperor")
          || me->query("special_skill/lonely") )
     {
         tell_object(me, HIW"你隐隐约约似乎听见女娲在你耳边说道：汝乃受神明庇护之人，\n"
                         "不必多礼了。\n\n"NOR);
         return 1;
     }

     if (! me->query("special_skill/queen") )
     {
         tell_object(me, HIR"你心中不禁哀叹，自己乃寻常之辈，并无慧根，虽在此虔心祈祷，\n"
                         "却不知道女娲是否会有所感应呢？\n\n"NOR);
         return 1;
     }

     if (  me->query("xuannv/item") &&  me->query("xuannv/tuotai")  )
     return notify_fail(HIG"你隐隐约约似乎听见女娲在你耳边说道：吾已知汝之虔诚，\n"
                        "但切勿再在此浪费光阴，快快按照玄音纱上所载之武功好\n好修行，"
                        "参悟(canwu)领会(linghui)，早日重振女纲！\n\n"NOR);      
    
     if (random(10) == 1)
     {            
         if (  ! me->query("xuannv/item") )
         {       
             message_vision(HIY "\n忽然只见女娲像一阵颤动，发出轧轧的声响，\n"
                            "$N磕头之处随即裂开一个大口子。\n$N一个立足不稳，顿时"
                            "跌了下去。\n\n"NOR, me);  
             me->set("xuannv/item", 1);

           //获得玄音纱
           fc = read_file(XUANYIN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIG "这张轻纱薄如蝉翼，却坚硬无比，"
                               "通体散发着淡淡的霞光。\n上面隐约还画着许多美女" 
                               "飞天舞剑的图案，似乎记载着一\n门极为厉害的剑法。"
                               "有缘之人参悟此纱或许能学到什么。\n"NOR 
                           HIC "玄音纱上刻着一行小字：女娲赐于九天玄女" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));          

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-xuanyin";

           if (file_size(fn + ".c") > 0)
           {
                if (xuanyin = find_object(fn)) destruct(xuanyin);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           xuanyin = load_object(fn);
           xuanyin->move(__DIR__"cave");
           me->set("can_summon/xuanyin",fn);
         
           //获得玄女剑
           fc = "";
           fc = read_file(XUANNVJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIR "这是女娲赐于九天玄女的神剑利器，"
                               "上面笼罩着一层淡淡的霞光。\n" HIW
                              "剑柄上刻着一行小字：女娲赐于九天玄女" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-xuannvjian";

           if (file_size(fn + ".c") > 0)
           {
                if (xuannvjian = find_object(fn)) destruct(xuannvjian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           xuannvjian = load_object(fn);

           xuannvjian->set("owner/" + me->query("id"), 5000000);
           xuannvjian->set("magic/imbue",50);

           xuannvjian->move(__DIR__"cave");
           me->set("can_summon/xuannvjian",fn);        
            
           me->move(__DIR__"cave");
           return 1;     
         }
 
      // 脱胎换骨,调整天赋
       if (  ! me->query("xuannv/tuotai") )
           {   
               message_vision(WHT"女娲被$N诚心感动，显现出来问道：\n“汝仍在此叩拜?"
                               "可是尚对自身天赋不满?”\n\n"NOR, me);
                            
                write(HIG"女娲赐你一次脱胎换骨的机会，可以重新调整四项天赋，\n"NOR
                      HIR"但是脱胎换骨后以前增加的先天属将全部无效，\n"
                      "实战经验及一切技能全部清除，你可想清楚了？"NOR HIY
                      "\n请回答(Y/N)\n" NOR);
		  input_to("do_yes", answer);               
           }
 
     }  
     return 1;                   
}

int do_yes(string answer)
{   
   object me;
   me = this_player();
   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	
   	me->set_temp("xuannv/tuotai/ask",1);

       write(HIG"好吧，既然你心意已决，你可以重新分配80点天赋，\n"
                "单项必须大于等于13，小于等于30,\n"
                "指令是tuotai <膂力> <悟性> <根骨> <身法>\n"NOR);
     	
   } else
   {            
   	write("好吧，改变主意的话随时回来。\n");
   }
   return 1;	
}

int do_tuotai(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();
    if	( ! me->query_temp("xuannv/tuotai/ask") ) return 0;
    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"指令格式：tuotai <膂力> <悟性> <根骨> <身法>\n"NOR);
 
    if( tmpstr<13) return notify_fail("你所选择的膂力参数不能小于13。\n");
    if( tmpint>30) return notify_fail("你所选择的悟性参数不能大于30。\n");
    if( tmpint<13) return notify_fail("你所选择的悟性参数不能小于13。\n");
    if( tmpcon>30) return notify_fail("你所选择的根骨参数不能大于30。\n");
    if( tmpcon<13) return notify_fail("你所选择的根骨参数不能小于13。\n");
    if( tmpdex>30) return notify_fail("你所选择的身法参数不能大于30。\n");
    if( tmpdex<13) return notify_fail("你所选择的身法参数不能小于13。\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>80) 
    return notify_fail("你所选择的参数总和不能大于80。\n");
    write(HIC "指定天赋为 臂力:" + tmpstr + " 悟性:" + tmpint + " 根骨:" +
          tmpcon + " 身法:" + tmpdex + "，可以吗？\n"NOR 
          HIY"请回答（Y/N）\n" NOR, me);

    me->set_temp("/xuannv/tuotai/str",tmpstr);
    me->set_temp("/xuannv/tuotai/int",tmpint);
    me->set_temp("/xuannv/tuotai/con",tmpcon);
    me->set_temp("/xuannv/tuotai/dex",tmpdex);

    input_to("do_yes2", answer);
    return 1;
}

int do_yes2(string answer)
{
   object me;
   mapping my, my_sk;
   string skills_name;

   me = this_player();
   my = me->query_entire_dbase();
   my_sk = me->query_skills();

   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	 	
      message_vision(HIY "只见一道霞光钻入了$N体内，$N顿时感到头痛欲裂，"   
                         "苦不堪言。\n"NOR, me);

        my["str"] = me->query_temp("/xuannv/tuotai/str");
        my["int"] = me->query_temp("/xuannv/tuotai/int");
        my["con"] = me->query_temp("/xuannv/tuotai/con");
        my["dex"] = me->query_temp("/xuannv/tuotai/dex");
       	me->set("combat_exp", 0);           
		me->set("max_neili",0);
		me->set("neili",0);
		me->set("max_jingli",0);
		me->set("jingli",0);
		me->set("max_qi",100);
		me->set("eff_qi",100);
		me->set("qi",100);
		me->set("max_jing",100);
		me->set("eff_jing",100);
		me->set("jing",100);
              me->set("mud_age",0);
              me->set("age", 14);
              me->set("shen",0);
              me->delete("breakup");
              me->delete("animaout");

  		foreach(skills_name in keys(my_sk))
	      {
		   me->delete_skill(skills_name);
             }
             me->delete("gift");
             me->delete_temp("xuannv");     
             me->set("xuannv/tuotai",1);
             me->unconcious();
             me->set("potential", me->query_potential_limit() );
   } else
   {
   	  write("那请重新选择天赋。\n");
   }
   return 1;		

}





