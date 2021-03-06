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
                return notify_fail("你要用真气为谁疗伤？\n");

        if (me->is_busy())
                return notify_fail("等你忙完了手头的事情再说！\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功疗伤！\n");

        if (target->query("not_living"))
                return notify_fail("你不能给" + target->name() + "疗伤。\n");

        force = me->query_skill_mapped("force");
        if (! force)
                return notify_fail("你必须激发一种内功才能替人疗伤。\n");

        if ((int)me->query_skill(force,1) < 50)
                return notify_fail("你的" + to_chinese(force) + "等级不够。\n");

        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力修为不够。\n");

        if ((int)me->query("neili") < 180)
                return notify_fail("你现在的真气不够。\n");

        if (base_name(environment(target)) == "/d/city/biwu_dating")
                return notify_fail("怎么说？想作弊？嘿嘿！\n");
        if ((int)target->query("eff_qi") >= (int)target->query("max_qi"))
                return notify_fail( target->name() +
                        "现在没有受伤，不需要你运功治疗！\n");

        if ((int)target->query("eff_qi") < (int)target->query("max_qi") / 5)
                return notify_fail( target->name() +
                        "已经受伤过重，经受不起你的真气震荡！\n");

        message_vision(
                HIY "$N坐了下来运起" + to_chinese(force) +
                "，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n"
                HIW "过了不久，$N额头上冒出豆大的汗珠，$n吐出一"
                "口瘀血，脸色看起来红润多了。\n" NOR,
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
