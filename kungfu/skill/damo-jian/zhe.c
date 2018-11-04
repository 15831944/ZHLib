// shang.c ����Ԫ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/damo-jian/zhe"))
                return notify_fail("�㲻��ʹ�á���Ԫ������\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����Ԫ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ����Ԫ������\n");

        if ((int)me->query_skill("damo-jian", 1) < 200)
                return notify_fail("��Ĵ�Ħ����������죬����ʹ�á���Ԫ������\n");

        if (me->query("neili") < 300)
                return notify_fail("�����������������޷�ʹ�á���Ԫ������\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("��û�м�����Ħ�������޷�ʹ�á���Ԫ������\n");

        msg = HIM "$N" HIM "��" + weapon->name() + "����һ��һ���⻪�Խ�����������"
              "�������ı���$n" HIM "�ĵ��\n" NOR;

        me->add("neili", -200);
        ap = me->query_skill("sword") + me->query_skill("force");

        if (living(target))
                 dp = target->query("force") * 2;
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "���õ����Ȼһ�ȣ��漴����������������̫�\n" NOR;
                damage = ap / 20 + random(ap / 20);
                target->receive_damage("jing", damage, me);
                target->receive_wound("jing", damage / 2, me);
                target->receive_damage("qi", damage * 2, me);
                target->receive_wound("qi", damage, me);
                target->affect_by("damo_zheyuan",
                               ([ "level" : ap / 4 + random(ap / 4),
                                  "id"    : me->query("id"),
                                  "duration" : ap / 90 + random(ap / 90) ]));
                me->start_busy(2);
                target->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "�������ʹ��$P" CYN
                       "��һ��û�����κ����á�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

