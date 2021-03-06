// combat.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int count;

	if (!ultrap(me)) return notify_fail("你不是大宗师，未能转化实战经验为攻击力！\n");
        if (!arg || !(sscanf(arg,"%d",count) == 1)) count = 100;
        if (count < 100) return notify_fail("你必须激发至少100点的实战经验。\n");       
        if (count > (int)me->query("combat_exp")/10) return notify_fail("你最多能激发全部实战经验的十分之一。\n");

        if (me->query_temp("on_combat"))
                return notify_fail("你现在正处于激发实战经验中，没有必要再激发一次。\n");

        message_vision(HIR "$N" HIR "突然全身骨骼一阵爆响，两目登时精光"
                       "四射，一招一式更显沉着干练。\n" NOR, me);

        me->add("combat_exp",-count);
        count = me->query_skill("force") / 5;
        me->set_temp("combat",count);
        me->add_temp("apply/attack", count);
        me->set_temp("on_combat",1);
	me->set_temp("combating",300+random(300));
	me->apply_condition("combat",1);

	return 1;
}

int help (object me)
{
        write(@HELP
指令格式: combat [点数]
 
这个指令让你将积累的实战经验部分转化为攻击力，这样在一段时间之内可
以充分的提升你的攻击能力。最少需要消耗100点实战经验， 如果没有指定
消耗的点数，默认为100点； 玩家一次最多可以将全部实战经验的十分之一
转化为攻击力。只有大宗师有这种能力。

HELP
        );
        return 1;
}
