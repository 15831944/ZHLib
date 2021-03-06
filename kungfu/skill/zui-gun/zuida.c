// zuida.c 少林醉棍 八仙醉打
//update by cpu 2002
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int count, count1,  skill,i;
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

	
	if (! me->is_fighting(target))
	        return notify_fail("「八仙醉打」只能在战斗中使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "club")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_str() < 25)
		return notify_fail("你现在的臂力不够，目前不能使用此绝技！\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("你的内功火候不够，难以施展此项绝技！\n");

        if ((int)me->query_skill("yijinjing",1) < 150 &&
           (int)me->query_skill("jiuyang-shengong",1) < 150 &&
           (int)me->query_skill("shaolin-xinfa",1) < 150 &&
           (int)me->query_skill("hunyuan-yiqi",1) < 150)
                return notify_fail("你的少林本门内功火候不够，难以施展此项绝技！\n");	
         
	if ((int)me->query_skill("club") < 100)
		return notify_fail("你的棍法修为不够，不会使用此项绝技！\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("你的真气不足！\n");

        if ((int)me->query_condition("drunk") < 10)
                return notify_fail("你酒醉的程度不够，难以施展出少林醉棍的精髓！\n");

        skill = me->query_skill("club");

        message_vision(HIY "$N迈着奇怪的步法跌跌撞撞向$n走去，以看似毫无章法的棍法一棍接一棍地攻向$n，正是少林绝技「八仙醉打」！\n\n"NOR,me,target);
        if (skill / 2 + random(skill) > (int)target->query_skill("parry") * 2 / 3 || !living(target))
        {
                message_vision(HIR "$n" HIR "见此怪招大吃一惊，呆在当场，避无可避！\n\n"NOR,me,target);
   
	        //message_combatd(msg, me, target);
        
	
	        
	        count = (int)( (int)me->query_condition("drunk") / 5)+((int)me->query_skill("zui-gun",1)/3);
	
	        me->add_temp("apply/attack", count);

                //message_vision(HIR"$N猛然之间已经把自己的臂力提升了"+me->query_temp("apply/str",1)+HIR"点身法提升了"+me->query_temp("apply/dex",1)+HIR"点\n\n"NOR,me,target);

                message_vision(HIB"「八仙醉打」第一式——「蓝采和，提篮劝酒醉朦胧」!\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIM"「八仙醉打」第二式——「何仙姑，拦腰敬酒醉仙步」!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIC"「八仙醉打」第三式——「曹国舅，千杯不醉倒金盅」!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIW"「八仙醉打」第四式——「韩湘子，铁棍提胸醉拔萧」!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIG"「八仙醉打」第五式——「汉钟离，跌步翻身醉盘龙」!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIW"「八仙醉打」第六式——「铁拐李，踢倒金山醉玉池」!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(WHT"「八仙醉打」第七式——「张果老，醉酒抛杯倒骑驴」!\n"NOR,me,target);
         	COMBAT_D->do_attack(me, target, weapon, 1);
 
                message_vision(CYN"「八仙醉打」第八式——「吕洞宾，酒醉提壶力千钧」!\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, weapon, 1);

 	        
                me->add_temp("apply/attack", -count);

                //message_vision(HIR"$N的臂力下降了"+me->query_temp("apply/str",1)+HIR"点身法下降了"+me->query_temp("apply/dex",1)+HIR"点\n\n"NOR,me,target);

//                target->start_busy(2+random(3));
                me->add("neili", -200);
                me->start_busy(1+random(3));
                target->start_busy(1 + random(2));
        }
        else
        {
                me->add("neili", -100);
                message_vision(HIC"$n似乎看尽了$N招式的变化，将$N的进攻一一化解！\n\n"NOR,me,target);
                me->start_busy(2+random(3));
        }
        return 1;
}
