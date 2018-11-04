#include <ansi.h>
#include <combat.h> 
         
inherit F_SSERVER; 
         
int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 
        int ap, dp; 
        int bs;
        int damage; 
        
        if (! target) target = offensive_target(me); 
        
        if (! target || ! me->is_fighting(target)) 
                return notify_fail("�����޾���ָ��ֻ����ս���жԶ���ʹ�á�\n"); 
         
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("�������ֲ���ʹ�á����޾���ָ����\n"); 

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ�����޾���ָ����\n");

        if (me->query_skill("force") < 250) 
                return notify_fail("����ڹ�����Ϊ����������ʹ�á����޾���ָ����\n"); 
        
        if (me->query_skill("xiuluo-zhi", 1) < 150) 
                return notify_fail("�������ָ��Ϊ������Ŀǰ����ʹ�á����޾���ָ����\n"); 
         
        if (me->query("neili") < 500) 
                return notify_fail("��������������޷�ʹ�á����޾���ָ����\n"); 
         
        if (me->query_skill_mapped("finger") != "xiuluo-zhi") 
                return notify_fail("��û�м�������ָ������ʹ�á����޾���ָ����\n"); 
         
        msg = HIB "$N��Ȼ��¶�׹⣬���α���쳣Ʈ�죬��$n" HIB
                  "���������߸���ͣ��$n" HIB "����ãʱ��$N" HIB
                  "ͻȻ��������\n��Ϣ��һָ������\n" NOR; 
         
        ap = me->query_skill("finger") + me->query_skill("force"); 
        dp = target->query_skill("dodge") + target->query_skill("parry"); 
         
        if (ap / 2 + random(ap) > dp || !living(target))
        { 
                damage = ap + random(ap / 2); 
                bs = 1 + random(3);
                me->add("neili", -350); 
                me->start_busy(bs);
         
                msg += HIR "ֻ��$n" HIR "һ���ҽУ��Ա�����Ҫ����λ��ֻ������ǰһ�ڣ��ƺ��Կ�������Χ��һ�У�����ҡҡ��׹��\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100); 
        } else 
        { 
                me->add("neili", -150); 
                me->start_busy(3); 
                msg += CYN "����$n" CYN "������$N" CYN "����ͼ������" 
                       CYN "���Ʈ�����ɣ��������һ������һ����\n"NOR; 
        } 
                message_combatd(msg, me, target); 
         
                return 1; 
}

