// lian.c 太极剑法「连」字诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count, acter;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("太极剑法「连」字诀只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 120)
                return notify_fail("你的太极剑法不够娴熟，不会使用「连」字诀。\n");

        if (me->query("neili") < 250)
                return notify_fail("你的真气不够，无法使用「连」字诀。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，无法使用「连」字诀。\n");

        msg = HIY "$N" HIY "使出太极剑法「连」字诀，化出一个个圆圈，把$n"
              HIY "圈在当中。\n" NOR;

        dp = (target->query_skill("force", 1) +
              target->query_skill("parry", 1) +
              target->query_skill("martial-cognize", 1)) / 3;

        if (me->query("character") == "光明磊落" || me->query("character") == "狡黠多变")
             acter = 3;
        else
             acter = 4;

        ap = (me->query_skill("taiji-shengong", 1) +
              me->query_skill("taiji-jian", 1) +
              me->query_skill("martial-cognize", 1) +
              me->query_skill("taoism", 1)) / acter;

        attack_time = 5;
        if (random(ap) > dp / 2 || !living(target))
        {
                msg += HIC "结果$p" HIC "被$P" HIC
                       "攻了个措手不及，连连后退不暇！\n" NOR;
                count = ap / 3;
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "这几剑并无破绽，不敢大意，小心应付。\n" NOR;
                count = 0;
        }
                
        me->add_temp("apply/attack", count);
        message_combatd(msg, me, target);

        if (attack_time > 10)    attack_time = 10;

        me->add("neili", -attack_time * 20);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))   break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(2 + random(3));

        return 1;
}

