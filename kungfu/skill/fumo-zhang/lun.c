#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/fumo-zhang/lun"))
                return notify_fail("�����ڻ�����ʹ�á�" HIR "�����" NOR "����һ�У�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��" HIR "�����" NOR "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�����������ʹ�á�" HIR "�����" NOR "����\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����ڵ������������޷�ʹ�á�" HIR "�����" NOR "����\n");

        if ((int)me->query_skill("fumo-zhang", 1) < 120)
                return notify_fail("��Ķ�ʮ��·��ħ�Ȼ������ң��޷�ʹ�á�" HIR "�����" NOR "����\n");

        if (me->query_skill_mapped("staff") != "fumo-zhang") 
                return notify_fail("��û�м�����ʮ��·��ħ�ȣ��޷�ʹ�á�" HIR "�����" NOR "����\n");

        msg = HIW "$N" HIW "һ�����ȣ�����" + weapon->name() + HIW "һ����裬"
              "��Ӱ������������Ȧ����ͬ" NOR + HIR "�����" NOR + HIW "һ�㣬��"
              "��ǵ�ϯ����$n" HIW "��\n" NOR;
        ap = me->query_skill("staff");
        if (living(target))
                 dp = target->query_skill("parry");
        else     dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$n" HIR "��ȫ�޷�����$N"
                                           HIR "���е���ʵ��ֻ����������"
                                           "��������������$P"
                                           HIR "���У���ʱŻѪ������\n" NOR);
                me->start_busy(3);
                target->start_busy(1);
        } else 
        {
                msg += CYN "$n" CYN "�����мܣ�����ֵ�ס��$P"
                       CYN "�Ĺ�����\n" NOR;
                me->add("neili", -80);
                me->start_busy(4);
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

