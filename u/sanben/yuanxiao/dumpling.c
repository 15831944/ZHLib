
//元宵汤圆  (特殊force,force,dodge,parry)各加1级
//每个id最多吃两个

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "元宵汤圆" NOR, ({ "tang yuan", "yuan", "dumpling" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "瞎三笨做的汤圆圆又圆。\n" NOR);
                set("unit", "粒");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
	{
		add_action("do_eat","eat");
	}
		

int do_eat( string arg )
{	
	if (arg == "tang yuan" || arg == "yuan" || arg == "dumpling")

	{
	 string mapsk;	 
	 object me;
	
	 me = this_player();

        if (me->query("eat_dumpling") > 1 )
        {write(HIR"都吃了两个了，再吃就消化不良了！\n"NOR);return 1;}

        message_vision(HIY "$N将汤圆一口吞了，“哈喇子”顺着嘴角就流了出来，\n" +
				"还一个劲儿连说:“味道好极了哟，还有吗？再来一个!\n" NOR, me);

	 log_file("static/yuanxiao", sprintf("%s(%s) eat 元宵汤圆 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        me->add("eat_dumpling", 1);

	 me->add("combat_exp", 50000);
	 mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

		destruct(this_object());
		return 1;
	}
else {	return 0;}
}
		


       	