// wushuang.c ��Ů���� ��˫�޶�

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
void remove_effect(object me, int a_amount, int d_amount);

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("��˫�޶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("yunu-sword", 1) < 120 )
                return notify_fail("�����Ů����ʮ����������죬����ʹ�á���˫�޶ԡ���\n");

        if( (int)me->query_skill("zixia-shengong", 1) < 100 )
                return notify_fail("�����ϼ�񹦲�����죬����ʹ�á���˫�޶ԡ���\n");

        if( (int)me->query("max_neili") < 300  )
                return notify_fail("�������������\n");

        if (me->query_skill_mapped("sword") != "yunu-sword")
                return notify_fail("��û�м�����Ů����ʮ����������ʹ�á���˫�޶ԡ���\n");

        msg = HIY "$N" HIY " ˫������ " + weapon->name() + HIY "��â������һʽ����˫�޶ԡ���Ԧ�����Ҿ��׵���ǰ���!!��\n" NOR;

     if (random(me->query_skill("sword")) > target->query_skill("sword") / 3 || !living(target))
        {
                me->start_busy(2);

                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("yunu-sword", 1);
                damage = damage + random(damage);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                       HIR "����һ��," HIR "$n" HIR "���ؿں�Ȼ����һ��Ѫ��! \n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "$p" CYN "����������,���ò������������,������� \n" NOR;

        }
        message_combatd(msg, me, target);

        return 1;
}

