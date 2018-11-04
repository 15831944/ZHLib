#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/huzhua-shou/juehu"))
                return notify_fail("�����ڻ�����ʹ�á���������һ�У�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
             return notify_fail("�������ֲ���ʹ�á���������\n");

        if (me->query("shen") < 10000)
                return notify_fail("��������������Զ���ʩչ��������ͻȻ�뵽�˵��������۵�һ����䣬���ò���;�����˹�����\n");

        if ((int)me->query_skill("huzhua-shou", 1) < 130)
                return notify_fail("��Ļ�צ�����ֲ�����죬����ʹ�á���������\n");

        if (me->query("neili") < 300)
                return notify_fail("��������������������ʹ�á���������\n");

        msg = HIR "$N" HIR "���һ��������Ϊצ��˫צ��������צӰ����������һ����$n" HIR
              "��Ҫ��ץȥ��\n"NOR;

        if (living(target))
                dp = target->query_skill("parry") / 2;
        else    dp = 0;

        if (random(me->query_skill("claw")) > dp)
        {
                me->start_busy(3);

                damage = me->query_skill("huzhua-shou", 1);
                damage = damage * 3 + random(damage);
                me->add("shen", -8000);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25,
                                           HIR "���$p" HIR "һ���Һ���û���м�ס$P" HIR
                                           "�����Ĺ��ƣ���ץ��Ƥ����룬��Ѫ�ɽ���\n" NOR);
                me->add("neili", -200);
        } else
        {
                me->start_busy(2);
                me->add("neili", -120);
                me->add("shen", -8000);
                msg += CYN "����$p" CYN "������$N" CYN
                       "����ͼ���㿪������ɱ�š�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

