// lifeheal.c

#include <ansi.h>

mapping eff_heal = ([
	"kurong-changong"	: 3,	
	"taixuan-gong"		: 3,
	"taiji-shengong"	: 2,	
	"yijinjing"		: 2,	
	"jiuyang-shengong"	: 2,	
	"xiantian-gong"		: 2,	
	"linji-zhuang"		: 2,	
	"bahuang-gong"		: 1,
	"lengyue-shengong"	: 1,
	"shonghuo-xuanming"	: 1,
	"hunyuan-yiqi"		: 1,	
	"zixia-shengong"	: 1,
	"bibao-shengong"	: 1,
	"yunv-xinfa"		: 1,
	"xiaowuxiang"		: 1,
	"huntian-qigong"	: 1,	
	"longxiang"		: 1,
	"beiming-shengong"	: 1,	
	"zihui-xinfa"		: 1,	
	"hamagong"		: 1,	
	"huagong-dafa"		: 1,	
	"shenlong-xinfa"	: 1,
	"xixing-dafa"		: 1,	
]);

int exert(object me, object target)
{
        string force;
	int recover_points, lvl, con , eff;

        if (! target || target == me)
                return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

        if (me->is_busy())
                return notify_fail("����æ������ͷ��������˵��\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˣ�\n");

        if (target->query("not_living"))
                return notify_fail("�㲻�ܸ�" + target->name() + "���ˡ�\n");

        force = me->query_skill_mapped("force");
        if (! force)
                return notify_fail("����뼤��һ���ڹ������������ˡ�\n");

        if ((int)me->query_skill(force,1) < 50)
                return notify_fail("���" + to_chinese(force) + "�ȼ�������\n");

        if ((int)me->query("max_neili") < 300)
                return notify_fail("���������Ϊ������\n");

        if ((int)me->query("neili") < 180)
                return notify_fail("�����ڵ�����������\n");

        if (base_name(environment(target)) == "/d/city/biwu_dating")
                return notify_fail("��ô˵�������ף��ٺ٣�\n");
        if ((int)target->query("eff_qi") >= (int)target->query("max_qi"))
                return notify_fail( target->name() +
                        "����û�����ˣ�����Ҫ���˹����ƣ�\n");

        if ((int)target->query("eff_qi") < (int)target->query("max_qi") / 5)
                return notify_fail( target->name() +
                        "�Ѿ����˹��أ����ܲ�����������𵴣�\n");

        message_vision(
                HIY "$N������������" + to_chinese(force) +
                "������������$n���ģ������ؽ���������$n����....\n"
                HIW "���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ"
                "����Ѫ����ɫ������������ˡ�\n" NOR,
                me, target );

	lvl = me->query_skill("force");	// my enable force level.
	con = me->query("con");		// my original constitution.
	eff = eff_heal[force];		// my force's effect on heal.
	if( !eff ) eff = 1;

	recover_points = con + lvl/6;
	recover_points += recover_points/5*eff;

        if (target->query("breakup"))
                recover_points *= 3;

	target->receive_curing("qi", recover_points);

        me->add("neili", -150);
        return 1;
}
