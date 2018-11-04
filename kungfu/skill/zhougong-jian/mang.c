#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;
        int qi, skill, damage;
        object ob;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��âֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (userp(me) && ! me->query("can_perform/zhougong-jian/mang"))
                return notify_fail("�㻹��֪����η�����â��\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("ֻ���ý����ܷ�����â��\n");

        if ((int)me->query_skill("zhougong-jian", 1) < 100)
                return notify_fail("����ܹ���������죬�޷�ʹ����â��\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�������������죬�޷�ʹ����â��\n");

        if ((int)me->query("max_neili", 1) < 1500)
                return notify_fail("����Ŀǰ��������Ϊ���޷�ʹ����â��\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("�����������������޷�ʹ����â��\n");

        skill = me->query_skill("zhougong-jian", 1);


        lvl = (int) me->query_skill("zhougong-jian", 1) / 5 + 1;

        msg = HIW "$N" HIW "һ����Х������" + weapon->name() + HIW "��"
                  "�ջ��������ⶸȻ����������²�������â��һ�������ƿ�"
                  "��ֱ����$n��\n" NOR;

        if (random(me->query_skill("sword")) > target->query_skill("parry") / 4 )
        {
                me->add("neili", -100);
                damage = skill + me->query("jiali");

                me->add("neili", -damage/2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                       HIR "$n" HIR "һ���ҽУ������Ľ����ѻ������ţ�"
                       "�����ϴ̳�����Ѫ������Ѫ��Ȫˮ��ӿ����\n\n" NOR);

                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���\n\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIW "$N" HIW "��$n" HIW "Ӧ�Ӳ�Ͼ��һ����Ц�����л���������һ�Ǹ���"
                  "�����Ľ�â�ɽ��ⵯ����������ֱ��$n" HIW "��\n" NOR;

        if (random(me->query_skill("sword")) > target->query_skill("parry") / 2 || !living(target))
           {

                qi = (int) target->query("max_qi");
                target->receive_damage("qi", qi * lvl / 300, me);
                target->receive_wound("qi", qi * lvl / 600, me);
                me->start_busy(2 + random(3));
                me->add("neili", -300);
                msg+= HIR "ֻ�������͡�һ������������$n" HIR "�ؿڣ���"
                          "��һ����ڴ��Ѫ����$n" HIR "����һ������Ҳ�޷�"
                          "վ��\n" NOR;

                message_combatd(msg, me, target);
                return 1;
        } else
        {
                msg+= CYN "$n" CYN "ǿ��ȫ���ʹ��������һԾ���ܿ���$N" CYN "��ǿ���ɱ�š�\n" NOR;
                me->start_busy(3 + random(3));
                me->add("neili", -100);
                message_vision(msg, me, target);
                return 1;
        }

        message_combatd(msg, me, target);

        return 1;
}
