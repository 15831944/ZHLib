// kuang.c 狂风剑

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill, q;
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「狂风」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("huashan-xinfa", 1) < 120 )
                return notify_fail("你的华山心法不够娴熟，不会使用「狂风」。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("「狂风剑」开始时必须拿着一把剑！\n");
        if ((int)me->query("max_neili") < 600)
                return notify_fail("你的内功修为还不够，未能使出「狂风」!\n");
        if ((int)me->query("neili") < 120)
                return notify_fail("你的真气不够，无法施展狂风剑法！\n");
        if ((int)me->query_skill("kuangfeng-jian", 1) < 120)
                return notify_fail("你的狂风剑法还不到家，无法施展「狂风」！\n");
        msg = HIR "$N" HIR "大喝一声，手中的" + weapon->name() +
              HIR "犹如狂风疾电一般劈刺向" HIR "$n"
              HIY "\n\n你一声长叹:  \n" NOR;
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", 200);

        me->add("neili", -100);
        skill = (int) (me->query_skill("kuangfeng-jian",1) / 50);
        q = 5 + skill;
        for (i = 1; i < q; i++)
        {
                if (! me->is_fighting(target))
                        break;
            me->add("neili", -20);
                msg = HIC "-----接我第"+chinese_number(i)+"剑！\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -200);

        return 1;
}

