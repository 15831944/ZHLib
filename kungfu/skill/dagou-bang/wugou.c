//wugou.c 打狗棒法「天下无狗」
//rama for hx

#include <ansi.h>
#include <armor.h> 
#include <combat.h> 

inherit F_DBASE;
inherit F_SSERVER;
string *wugou_msg=({
HIY"$N冷笑一声，运力于棒端，随即探身向前，向$n双腿扫去。\n"NOR,
HIW"$N一招使将完毕，招式仍然未老，内力轻吐，那棒竟然长了眼睛一般，向$n面门呼啸而至。\n"NOR,
HIW"$N一招未毕次招又至，将手中之棒舞成一圈光影向着$n当胸扎来。\n"NOR,
HIW"$N眼中杀气忽现，一改灵巧的棒招，迅雷般的直取$n眉心。\n"NOR,
HIY"$N极尽能事，闪转挪腾，手中之棒似已粘在$n身上一般，将$n笼罩在一片光影之中，实在是精妙绝伦！\n"NOR,
HIW"$N眼中一片祥和庄重，似已与手中之棒合二为一，「天下无狗」精髓尽出，刹那间$N幻作漫天棒影罩住$n，\n使出了打狗棒法不传之密！！当真是匪夷所思！\n"NOR});

int perform(object me, object target)
{
        int ap,dp,pp;
        int i,enfor;
        int num;
        string msg;
        int damage,skill;
        object obj;
        obj = me->query_temp("weapon"); 

        if( !target ) target = offensive_target(me);

        if( me->query("wugou") < 60)
                return notify_fail("你还没学会「天下无狗」。\n");
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「天下无狗」只能对战斗中的对手使用。\n");

       // if( target->is_busy() ) {
       //         return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
       // }

        if( me->query_temp("ban",1) )
                return notify_fail("你已在使用绊字诀！\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("你所用的并非混天气功，无法施展「天下无狗」！\n");

          if( me->query_skill("force") <450 )
                return notify_fail("你的混天气功火候未到，无法施展「天下无狗」。n");

        if (!(obj) || (obj->query("skill_type")!="staff"))
                return notify_fail("手中无棒,如何施展？\n");
        if ( me->query_skill("staff") < 500 )
                return notify_fail("你的打狗棒法修为不足，还不会使用「天下无狗」2！\n");
/*
        if ( me->query_skill("dagou-bang") < 200 )
                return notify_fail("你的打狗棒法修为不足，还不会使用「天下无狗」！\n");
*/


        if( me->query("max_neili") < 6000 || me->query("neili") <2000 )
                return notify_fail("你的内力修为不够，无法使用「天下无狗」！\n");
        if( me->query("max_jingli") < 600 || me->query("jingli") < 300)
                return notify_fail("你的精力不足，无法使用「天下无狗」！\n");
        if( !me->query("rank") || me->query("rank") < 9)
                return notify_fail("你在丐帮级别太低了！\n");
        message_vision(HIW"$N手中的"+obj->name()+"微微抖动，将“打狗棒法”使得变幻莫测，一顿一挑看似笨拙，却有着无穷的威力！\n",me);
        ap = COMBAT_D->skill_power(me,"staff", SKILL_USAGE_ATTACK)/500 + 1; 
        pp = COMBAT_D->skill_power(target,"parry", SKILL_USAGE_ATTACK)/1000 + 1; 
        dp = COMBAT_D->skill_power(target,"dodge", SKILL_USAGE_ATTACK)/1000 + 1; 
        num = me->query("wugou");
        if (wizardp(me) ) printf("ap = %d ,dp =%d ,pp =%d \n",ap,dp,pp);
        skill = me->query_skill("staff") + me->query_skill("huntian-qigong",1);
        if ( skill >1200 ) skill = 1200;
        if (num < 100) num = 3;
        else if (num <200) num =4;
        else if (num <500) num =5;
        else num = 6;
        enfor = (me->query("jiali") + me->query("jianu") )/2;
        for (i=0;i<num;i++)
        {
        if (i == 5) break;
        damage = skill/10 + skill*(10-i)/50 + random(enfor/2);
        damage = damage /2 + random(damage);   
        if (damage > 400) damage = 400;
        if (damage < 180) damage = 180;
        if (wizardp(me)) printf("i = %d,damage = %d\n",i,damage);
        me->add_temp("apply/damage",damage/2);
        me->add_temp("apply/attack",damage);
        msg = wugou_msg[i];
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        me->add_temp("apply/damage",-damage/2);
        me->add_temp("apply/attack",-damage);
        }
        if (num==6 && ap > random((pp+dp)/2) )
        {
            call_out("last_hit",1,me,target);
        }
        me->add("neili",-250);
        if (target->is_busy())
                target->start_busy(1);
        me->start_busy(2+random(num/2));
        return 1;
}

void last_hit(object me,object target) 
{
        object weapon;
        if (!me || 
            !target || 
            !environment(me) || 
            !environment(target) || 
            environment(me) != environment(target) ||
            !objectp(weapon = me->query_temp("weapon")) ||
            !me->is_fighting(target) ||
            !living(me)) 
		return;
        message_vision(wugou_msg[5],me,target);
        target->receive_damage("qi", 1000 + random(2000),  me);
        target->receive_wound("qi",500+random(500), me);
        COMBAT_D->report_status(target);  
}

