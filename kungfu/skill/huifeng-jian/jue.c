// Code of JHSH
// jue.c ��������
// xQin 10/99
// DEBUG by xQin 04/01
// modified by xiaojian May 22,2001

#include <ansi.h>
inherit F_SSERVER;

void remove_effect(object me,int level,int damage,int attack);

int perform(object me, object target)
{
	object weapon;
	int busytime,larger;
	int acc_damage = 0;
	int acc_attack = 0;
	int i, level, attack, damage, o_att, o_dam, o_spd;

	weapon = me->query_temp("weapon");

	if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
		weapon = me->query_temp("secondary_weapon");	

	if( !target && me->is_fighting() ) target = offensive_target(me);

	if( me->query_skill("huifeng-jian", 1) < 200 )
		return notify_fail("��Ļط����������Ϊ����������δ���򡸾�������\n");

	if( me->query_skill("force") < 300 )
		return notify_fail("����ڹ���Ϊ���δ����ʩչ��������ֻ���˼�����\n");

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
		return notify_fail("�������޽����������á�����������\n");

	if( me->query_skill_mapped("force") != "linji-zhuang" &&
            me->query_skill_mapped("force") != "emei-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-gong" &&
            me->query_skill_mapped("force") != "jiuyang-shengong" )
		return notify_fail("�����õ��ڹ��롸�𽣡��ķ���㣣�\n");

	if( (int)me->query_temp("miejue") )
                return notify_fail("���Ѿ�ʩչ������񽣡���\n");

	level = me->query_skill("sword") / 75;
	busytime = 1+level/4+random(level/3);

	if( me->query("max_neili") <= level*500 )
		return notify_fail("���������Ϊ���㣬����������ʩչ����������\n");

        if( me->query("neili") <= level*80 )
                return notify_fail("�����������������������ʩչ����������\n");

        if( me->query("jingli") <= level*60 )
                return notify_fail("��ľ������ޣ�������ʩչ����������\n");

	if( me->query_temp("perform/juejian") )
		return notify_fail("���������á��������ķ���\n");

	if(me->is_busy())
		return notify_fail("����æ����,û�취ʩչ���������ķ���\n");

	damage = me->query_skill("force"); 
	damage += me->query("jiali");
	damage /= 5;

	attack = me->query_skill("dodge");
	attack += me->query_dex()*10;
	attack /= 5;

	me->add_temp("apply/dex", level*5);
	me->add_temp("apply/damage", damage);
	me->add_temp("apply/attack", attack);
	
	me->add_temp("perform/juejian", 1);	

	for( i=0; i < (level+2)/2; i++ )
		COMBAT_D->do_attack(me, target, weapon);

	message_vision(HIY"\n�⼸�½��֣��������������䣬Ѹ�����ף�һɲ�Ǽ�$N������"+
		chinese_number((level+2)/2) +"�¿��У�������������������������\n"NOR, me);

	me->add("neili", -level*80);
	me->add("jingli", -level*20);

	me->start_call_out((:call_other, __FILE__, "remove_effect", me, level*5, damage, attack :),level * 5);
	return 1;
}


void remove_effect(object me,int level,int damage,int attack)
{
	if (!me) return;
	me->add_temp("apply/dex", -level);
	me->add_temp("apply/damage", -damage);
	me->add_temp("apply/attack", -attack);
       	me->delete_temp("perform/juejian");
}
