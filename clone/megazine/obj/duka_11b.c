inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>

int sy=0;
string qd="意大利";//赌的球队名
int peis=3,peig=0;

void create()
{
        set_name(HIC"赌球卡B"NOR, ({ "duqiu ka","ka", }));
        set_weight(500);
       if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long",HIY 
        "这张赌球卡上面写着:" + qd + "赢\n"
        "价值：10 cash 赔率:" + (peis-1) + "." + peig +"\n"
        "你现在可以兑换(change)支票了。\n"  NOR
        );
                set("value", 1);
                set("material", "silk");
                set("no_sell",1);
                set("no_pawn",1);
        }
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_change", "change");
	}
}

int do_change()
{
	object ob=this_object();
	object me=this_player();

	if (sy == 1)
	 {
	   message_vision(HIC "$N兑换了赌球卡。\n" NOR,me);
	   tell_object(me,HIC "你所赢的钱已经汇到了你的银行帐号上。\n" NOR);
           me->add("balance", 1000000 * peis);
           me->add("balance", 100000 * peig);

	   destruct(ob);
	   return 1;
	 }
	else if (sy == 0)
	  {
	    message_vision(HIC "$N兑换了赌球卡。\n" NOR,me);
	    tell_object(me,HIC "抱歉！你输了，你什么也没得到。\n" NOR);
	    destruct(ob);
	    return 1;
	  }
	 else if (sy ==2)
	    {
	    	tell_object(me,HIC "对不起，你没按要求换卡，因此这张作废了。\n" NOR);
	    	destruct(ob);
	    }
	 return 1;
}
