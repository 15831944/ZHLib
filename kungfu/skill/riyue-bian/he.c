// he.c ���ϡ��־�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���±޷����ϡ��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ���ϡ��־���\n");

        if ((int)me->query_skill("riyue-bian", 1) < 135)
                return notify_fail("������±޷�������죬����ʹ�á��ϡ��־���\n");

        if (me->query("neili") < 350)
                return notify_fail("��������������޷�ʹ�á��ϡ��־���\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷����޷�ʹ�á��ϡ��־���\n");

        msg = HIY "$N" HIY "�����е�" + weapon->name() +
              HIY "һ����ʹ�����±޷����ϡ��־������������Ӱ��\n" NOR;

        ap = me->query_skill("whip");
        dp = target->query_skill("parry");
        attack_time = 5;
        if (ap / 2 + random(ap * 2) > dp || !living(target))
        {
                msg += HIC "���$p" HIC "��$P" HIC
                       "���˸����ֲ�����Ŀ�Ӳ�Ͼ��ƣ�ڱ�����\n" NOR;
                count = ap / 2;
                me->add_temp("apply/attack", count);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "���ƻֺ룬������Ȼ������Ӧ����\n" NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        me->add("neili", -attack_time * 20);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(2 + random(2));
        target->start_busy(1);
        return 1;
}

