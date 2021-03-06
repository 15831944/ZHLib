// 自由女神像内暗室

#include <ansi.h> 
inherit ROOM;

#define POTIAN      "/u/yuchang/special/lonely/potian.h"
#define CHIJIAN     "/u/yuchang/special/lonely/chijian.h"
#define SPECIAL     "/data/item/"

string look_wall();

string* skill = ({
        "strike",
        "parry",
        "force",        
        "sword",        
        "china-aojue",
});

void create()
{
	set("short", "暗室"); 
	set("item_desc",([
		"wall"	  :  (: look_wall :),
              "zhuan"  :  "一块突出的砖头，似乎有点古怪。不知道"
                          "(push)一会怎样。\n",
              "deng"   :  "一盏破油灯，不知还能不能点着(dian deng)。\n",	
	]));
       set("no_fight",1);
   //    set("no_sleep_room",1); 
       set("no_ride",1);       		
	setup();	
}

void init()
{		
     add_action("do_dian","dian");  
     add_action("do_canwu","canwu");  
     add_action("do_linghui","linghui"); 
     add_action("do_push","push"); 
              
}

int do_dian(string arg)
{
    object corpse, potian, chijian;
    string fn, fc, answer;     
    object me = this_player();

    if ( ! arg || arg != "deng")
       return notify_fail("你要点什么？\n");
    if ( query("light") ) 
       return notify_fail("灯已经点着了！\n");
    set("light",1);
    message_vision("$N点亮了油灯，四周总算有了点光线。不妨再仔细看看这里。\n", me);
   
    if ( me->query("special_skill/lonely") &&
        ! me->query("lonely/item") )
    {
             me->set("lonely/item", 1);
           corpse = new(__DIR__"corpse");

           //获得破天甲

           fc = read_file(POTIAN);         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIG "这张护甲的外观跟一般布衣并没多大区别，但却坚硬"
                                   "无比，\n触手生寒。\n"NOR 
                               HIC "破天甲上刻着一行小字：诸神赐予天煞孤星" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-potian";

           if (file_size(fn + ".c") > 0)
           {
                if (potian = find_object(fn)) destruct(potian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           potian = load_object(fn);
           potian->move(corpse);
           me->set("can_summon/potian",fn);
         
           //获得赤剑
           fc = "";
           fc = read_file(CHIJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIR "这是天煞孤星专用的利器，"
                               "上面笼罩着一层淡淡的血光。\n" HIW
                              "剑柄上刻着一行小字：诸神赐于天煞孤星" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" + 
                me->query("id") + "-chijian";

           if (file_size(fn + ".c") > 0)
           {
                if (chijian = find_object(fn)) destruct(chijian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           chijian = load_object(fn);

           chijian->set("owner/" + me->query("id"), 5000000);
           chijian->set("magic/imbue",50);
         
           chijian->move(corpse);
           me->set("can_summon/chijian",fn);  

          //获得脱胎换骨丸
          new(__DIR__"wan")->move(corpse);  
            
          corpse->move(this_object());

    }
    return 1;
}

int do_canwu(string arg)
{             
        object me = this_player();
        int cost;
        int i;
        
        if (! arg || arg != "wall")
                return notify_fail("你要参悟什么？\n");

        if (! query("light") )
                return notify_fail("黑嘛嘛的一片啥都看不见，惨悟个啥哟！\n");

        if (! me->query("special_skill/lonely"))
                return notify_fail("你觉得怎么都搞不懂墙壁上的记载什么意思。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("你无法在战斗中专心下来研读新知！\n");      

        cost = 50 + random(50);
        if (me->query("jing") > cost)
        {
                for (i = sizeof(skill); i > 0; i--)
                {
                        if (me->query_skill(skill[i-1], 1) < 180 &&
                            me->can_improve_skill(skill[i-1]))
                        {
                                me->improve_skill(skill[i-1], 5 + random(30));
                        }
                }
                write(sprintf("你参悟墙上所记载的密籍，似乎有点心得。\n"));
                me->receive_damage("jing", cost);
        } else
        {
                me->set("jing", 0);
                write("你现在过于疲倦，无法专心下来参悟。\n");
        }
        return 1;
}

int do_linghui( string arg )
{
    object me = this_player();

   if (! me->query("special_skill/lonely"))
       return 0;

   if (! query("light") )
       return notify_fail("黑嘛嘛的一片啥都看不见，领会个啥哟！\n");  
  
    if (me->is_busy())
          return notify_fail("你现在正忙着呢。\n");

    if (me->is_fighting())
          return notify_fail("你还是先打完架再说吧！\n");

    if ( ! arg || ( arg != "掌震中华" && arg != "剑气长江" 
         &&  arg != "中华傲诀") )
          return notify_fail("你要领会什么绝招？格式为(linghui 绝招)。\n");

    if ( arg == "掌震中华" 
        && me->query("can_perform/china-aojue/zhangzhen"))
          return notify_fail("这招你不是已经会了吗？\n");
  
    if ( arg == "剑气长江" 
        && me->query("can_perform/china-aojue/jianqi"))
          return notify_fail("这招你不是已经会了吗？\n");

    if ( arg == "中华傲诀" 
        && me->query("can_perform/china-aojue/aojue"))
          return notify_fail("这招你不是已经会了吗？\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("你的精力无法集中，无法领会绝招！\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(10) == 1 && arg == "掌震中华" )
    {
        me->add("china-aojue/zhangzhen/count", 1);

        if (me->query("china-aojue/zhangzhen/count") >= 10)
        {
            write(HIM "猛然间，你胸中豁然贯通，再无疑虑。\n" NOR);
            write(HIC "你终于通晓了绝学「掌震中华」。\n" NOR);

            me->set("can_perform/china-aojue/zhangzhen", 1);
            me->delete("china-aojue/zhangzhen/count");

            if (me->can_improve_skill("strike"))
                    me->improve_skill("strike", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "你对「掌震中华」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(10) == 1 && arg == "剑气长江" )
    {
        me->add("china-aojue/jianqi/count", 1);

        if (me->query("china-aojue/jianqi/count") >= 10)
        {
            write(HIM "猛然间，你胸中豁然贯通，再无疑虑。\n" NOR);
            write(HIC "你终于通晓了绝学「剑气长江」。\n" NOR);

            me->set("can_perform/china-aojue/jianqi", 1);
            me->delete("china-aojue/jianqi/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "你对「剑气长江」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "中华傲诀")
    {
        me->add("china-aojue/aojue/count", 1);

        if (me->query("china-aojue/aojue/count") >= 20)
        {
            write(HIM "猛然间，你胸中豁然贯通，再无疑虑。\n" NOR);
            write(HIC "你终于通晓了绝学「中华傲诀」。\n" NOR);

            me->set("can_perform/china-aojue/aojue", 1);
            me->delete("china-aojue/aojue/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("strike"))
                    me->improve_skill("strike", 1500000);
            if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
            if (me->can_improve_skill("china-aojue"))
                    me->improve_skill("china-aojue", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "你对「中华傲诀」这招有了新的认识，但是仍有许多不解之处。\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
         return notify_fail("你试图从墙上领会有关「" + arg + "」的内容，\n"
                           "但是这次没什么效果，看来得再来过！\n");

}


string look_wall()
{     
     if ( query("light") )	
     return
    WHT"※※※※※※※※※※※※※※※※※※※※※※\n"
	"※※※※　　　　　　　　　　　　　　※※※※\n"
	"※※※※　　　　　中华傲决  　　　　※※※※\n"
	"※※※※　　　　　　　　　　　　　　※※※※\n"
	"※※※※　吾生平所习武学之精华已尽  ※※※※\n"
	"※※※※　载于此处。然未曾感应天煞  ※※※※\n"
	"※※※※　之气之凡夫俗子实难领会其　※※※※\n"
	"※※※※　中真意。他日若果得有缘人  ※※※※\n"
	"※※※※　来此参悟，尽得其间真髓，  ※※※※\n"
	"※※※※　则此子必将叱咤江湖，力成  ※※※※\n"
	"※※※※　一代宗师。然天煞孤星之孤　※※※※\n"
	"※※※※　寂苦楚又几人能知哉......　※※※※\n"
	"※※※※　　　　　　　　　　　　　　※※※※\n"
	"※※※※　　　　　    华英雄　　　  ※※※※\n"
	"※※※※　　　　　   绝笔与此　　　 ※※※※\n"
	"※※※※  (指令为canwu和linghui)   ※※※※\n"
	"※※※※※※※※※※※※※※※※※※※※※※\n"NOR;
    else
      return "黑嘛嘛的一片，啥也看不到。\n";
}

string long() 
{ 
       if ( query("light"))
          return "借着混暗的灯光，你看到墙壁上似乎刻着一些古怪的文\n字，"
                 "好像是和武学有关。你忍不住想仔细看看(look wall)。\n";
       else
           return "这里一片漆黑，伸手不见五指，啥也看不见。\n"
                  "墙边隐约有盏破油灯(deng)。墙上也有一块"
                  "突出\n的砖头(zhuan)。\n";
} 

int do_push(string arg)
{
        object room, me;

        me = this_player();

        if (! arg || arg != "zhuan" )
        {
		write("你要按什么？\n");
              return 1;        
        }
        message_sort(HIY"\n$N走到墙边，用力按了一下突出的砖块。"
                     "\n" NOR, me);

        message_sort(HIY"\n突然墙壁一阵颤动，边上露出一个大洞，\n"
                     "从这里可以通向外界。"
                     "\n\n" NOR, me);
        set("exits/out", __DIR__"floor5");

        if (room = find_object(__DIR__"floor5"))
        {
        	room->set("exits/enter", __FILE__);
           	message("vision", HIY "\n墙壁忽然发出轧轧的声音，"
                        "露出一个通道。\n" NOR, room );
        }
        remove_call_out("close_andao");
        call_out("close_andao", 5);
        return 1;
}

void close_andao()
{
    	object room;
        int i;

        if (! query("exits/out")) return;
    		message("vision", HIY "\n只听乒地一声响，砖块自动"
                        "移回原处。暗道也随之消失了。\n" NOR, this_object());

    	if (room = find_object(__DIR__"floor5"))
    	{
              room->delete("exits/enter");
        	message("vision", HIY "\n只听乒地一声响，暗道"
                        "口自动严严实实地关了起来。\n" NOR, room);
    	}
    	delete("exits/out");
}







