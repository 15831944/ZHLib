#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/liuyue-jian/liu"))
                return notify_fail("�����ڻ�����ʹ�á����¡���һ�У�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����¡�ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 120)
                return notify_fail("����ڹ�����Ϊ������ʹ���������¡���һ�У�\n");

        if (me->query_skill("liuyue-jian", 1) < 120)
                return notify_fail("�����Ӱ���½�����Ϊ������ʹ���������¡���һ�У�\n");

        if (me->query("neili") < 250)
                return notify_fail("�������������ʹ���������¡���һ�У�\n");

        msg = HIY "$N" HIY "һ����Х���������䣬����" + weapon->name() + HIY
                  "���Ữ��������һ���ޱ�Ѥ���Ľ�â��ңָ$n" HIY "��ȥ��\n" NOR;
        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = ap / 2 + random(ap);
                me->add("neili", -150);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$n" HIR "ֻ����Ŀ�ɿڴ���һ����������$N" HIR
                                           "����Ľ��д��У���Ѫ�ɽ���\n" NOR);
        } else
        {
                me->add("neili", -60);
                me->start_busy(3);
                msg += CYN "����$p" CYN "�������ң�������������񵲿���$P"
                       CYN "�Ľ��С�\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}

