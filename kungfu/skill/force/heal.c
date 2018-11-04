// heal.c

#include <ansi.h>

mapping eff_heal = ([
	"kurong-changong"	: 5,	
	"taixuan-gong"		: 5,
	"taiji-shengong"	: 4,	
	"yijinjing"		: 4,	
	"jiuyang-shengong"	: 4,	
	"xiantian-gong"		: 4,	
	"linji-zhuang"		: 4,	
	"bahuang-gong"		: 3,
	"lengyue-shengong"	: 3,
	"shonghuo-xuanming"	: 3,
	"hunyuan-yiqi"		: 3,	
	"zixia-shengong"	: 3,
	"bibao-shengong"	: 3,
	"yunv-xinfa"		: 3,
	"xiaowuxiang"		: 3,
	"huntian-qigong"	: 3,	
	"longxiang"		: 3,
	"beiming-shengong"	: 3,	
	"zihui-xinfa"		: 3,	
	"hamagong"		: 2,	
	"huagong-dafa"		: 2,	
	"shenlong-xinfa"	: 2,
	"xixing-dafa"		: 2,	
]);

int curing(object);
int halt_curing(object);
void remove_pending(object);

int exert(object me, object target)
{
        string force;
	mapping msg;

	if (me->is_fighting())
		return notify_fail("ս�����˹����ˣ�������\n");

	if (me->is_busy())
		return notify_fail("����æ������ͷ��������˵��\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("�ȼ�����������ڹ���\n");

        if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("��������Ѫ��ӯ������Ҫ���ˡ�\n");

	if ((int)me->query_skill(force, 1) < 20)
		return notify_fail("���" + to_chinese(force) + "��Ϊ��������\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�������������\n");

	if ((int)me->query("eff_qi") < (int)me->query("max_qi") / 5)
		return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

	msg = SKILL_D(force)->curing_msg(me);

	if( !msg || undefinedp(msg["start_self"]) )
		tell_object(me, HIW"��ȫ����ɣ���������ʼ�˹����ˡ�\n"NOR);
	else	tell_object(me, msg["start_self"]);

	if( !msg || undefinedp(msg["start_other"]) )
		message("vision", me->name() +"��ϥ���£���ʼ�˹����ˡ�\n"NOR,
			environment(me), me);
	else	message("vision", msg["start_other"], environment(me), me);

	if( !msg || undefinedp(msg["apply_short"]) )
		me->set_temp("apply/short", ({ me->name() +"�����ڵ����˹����ˡ�"}));
	else	me->set_temp("apply/short", ({ msg["apply_short"] }));

	me->set_temp("pending/curing", 1);
	me->start_busy((: curing :), (: halt_curing :));

	return 1;
}

int curing(object me)
{
        int recover_points, lvl, con, eff;
	string force_skill;
	mapping msg;
        
	if( !living(me) || me->is_ghost() || !(force_skill = me->query_skill_mapped("force")) )
	{
		remove_pending(me);
		return 0;
	}

	msg = SKILL_D(force_skill)->curing_msg(me);

	if( me->query("jing") < 1)
	{
		remove_pending(me);
		me->unconcious();
		return 0;
	}
	else if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
	{
		if( !msg || undefinedp(msg["finish_self"]) )
			tell_object(me, HIY"���˹����ã��Ծ�����˳�������˾�ȥ����Ԫ�����վ��������\n"NOR);
		else	tell_object(me, msg["finish_self"]);

		if( !msg || undefinedp(msg["finish_other"]) )
			message("vision", me->name() +"�˹���ϣ�վ������������ȥ��ɫ�����������ӡ�\n"NOR,	environment(me), me);
		else	message("vision", msg["finish_other"], environment(me), me);

		remove_pending(me);
        	return 0;
	}
	else if( (int)me->query("neili") < 50 )
	{
		if( !msg || undefinedp(msg["unfinish_self"]) )
			tell_object(me, "�������˹����ˣ�������Ϣ��̷���������ݻ����ˣ�վ��������\n"NOR);
		else	tell_object(me, msg["unfinish_self"]);

		if( !msg || undefinedp(msg["unfinish_other"]) )
			message("vision", me->name() +"�˹���ϣ�����վ����������ɫ������������ࡣ\n"NOR,environment(me), me);
		else	message("vision", msg["unfinish_other"], environment(me), me);

		remove_pending(me);
		return 0;
	}

	lvl = me->query_skill("force");	// my enable force level.
	con = me->query("con");		// my original constitution.
	eff = eff_heal[force_skill];		// my force's effect on heal.
	if( !eff ) eff = 1;

	recover_points = con + lvl/5;
	recover_points += recover_points/5*eff;

        if (me->query("breakup"))
                recover_points *= 3;

	me->receive_curing("qi", recover_points);
	me->add("neili", -50);

	if( !msg || undefinedp(msg["on_self"]) )
		message_vision(WHT "$N" WHT "��ɫͨ�죬ͷ�ϰ����뵣���Ȼ�����������ڲ�ͣ��ת��\n" NOR, me);
	else
	{
		tell_object(me, msg["on_self"]);
		message("vision", msg["start_other"], environment(me), me);
	}

	return 1; 
}

int halt_curing(object me)
{
	me->receive_damage("qi",50);

	if (me->query("qi") < 5)
		me->set("qi",5);

	if (me->query("neili") > 50)
		me->add("neili", -50);
	else
		me->set("neili",0);

	tell_object(me, "��������Ϣ��Ӳ�����ؽ���Ϣѹ����ȥ������վ��������\n");
	message("vision", me->name() +"����һ���³�һ����Ѫ������վ��������\n", environment(me), me);

       	remove_pending(me); 
	me->start_busy(1+random(3));
	return 1;
}

void remove_pending(object me)
{
	me->delete_temp("pending/curing");
	me->delete_temp("apply/short");
}
