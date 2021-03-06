// wushuang.c 玉女剑法 无双无对

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
                return notify_fail("无双无对只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("yunu-sword", 1) < 120 )
                return notify_fail("你的玉女金针十三剑不够娴熟，不会使用「无双无对」。\n");

        if( (int)me->query_skill("zixia-shengong", 1) < 100 )
                return notify_fail("你的紫霞神功不够娴熟，不会使用「无双无对」。\n");

        if( (int)me->query("max_neili") < 300  )
                return notify_fail("你的内力不够。\n");

        if (me->query_skill_mapped("sword") != "yunu-sword")
                return notify_fail("你没有激发玉女金针十三剑，不能使用「无双无对」。\n");

        msg = HIY "$N" HIY " 双手握起 " + weapon->name() + HIY "剑芒暴长，一式「无双无对」，驭剑猛烈绝伦地往前冲刺!!。\n" NOR;

     if (random(me->query_skill("sword")) > target->query_skill("sword") / 3 || !living(target))
        {
                me->start_busy(2);

                damage = (int)me->query_skill("sword", 1) +
                         (int)me->query_skill("yunu-sword", 1);
                damage = damage + random(damage);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                       HIR "剑光一闪," HIR "$n" HIR "的胸口赫然留下一道血痕! \n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "$p" CYN "见剑招凶险,不得不向后连退数步,险象横生 \n" NOR;

        }
        message_combatd(msg, me, target);

        return 1;
}

