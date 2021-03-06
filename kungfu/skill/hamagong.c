// hamagong.c 蛤蟆功
// Update By Qdz

#include <ansi.h>
inherit FORCE;

mapping *action = ({
([      "action" : "$N忽而倒竖，一手撑地，身子横挺，只以一掌向$n的$l拍出",
        "dodge"  : 0,
        "force"  : 310,
        "attack" : 103,
        "parry"  : 21,
        "damage" : 58,
        "lvl"    : 0,
        "damage_type": "震伤" 
]), 
([      "action" : "$N丝毫不动声色，双腿微曲，右掌平伸，左掌运起蛤蟆功的"
                   "劲力，呼的一声推向$n",
        "dodge"  : 0,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 61,
        "lvl"    : 250,
        "damage_type": "震伤"
]), 
([      "action" : "$N闭眼逼住呼吸，过了片刻，猛跃而起，眼睛也不及睁开，双"
                   "掌便向$n的方向推了出去",
        "dodge"  : 0,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 72,
        "lvl"    : 260,
        "damage_type": "震伤"
]),
([      "action" : "$N脚步摇摇幌幌，忽然双腿一弯、一登，口中阁的一声叫喝，"
                   "手掌向$n猛然推出",
        "dodge"  : 5,
        "force"  : 410,
        "attack" : 143,
        "parry"  : 67,
        "damage" : 81,
        "lvl"    : 270,
        "damage_type": "震伤"
]), 
});

mapping *reverse_action = ({
([      "action": "忽听$N大叫三声，三个筋斗翻将出来，大吼一声，恶狠狠的朝$n扑将上来",
	"dodge": -15,
	"parry": -20,
	"force": 300,
	"damage": 60,
	"damage_type": "跌伤"
]),
([      "action":"但见$N疯势更加厉害，口吐白沫，举头朝$n猛撞",
	"parry": 15,
	"force": 360,
	"damage": 70,
	"damage_type": "瘀伤"
]),
([      "action":"$N蓦地张口，白牙一闪，已向$n$l咬落，又快又准",
	"dodge": -5,
	"force": 420,
	"damage": 80,
	"weapon": "牙齿",
	"damage_type": "咬伤"
]),
([      "action":"$N一口唾沫急吐，势挟劲风，竟将痰涎唾沫也当作了攻敌利器",
	"dodge": -45,
	"force": 480,
	"damage": 90,
	"weapon":"唾沫",
	"damage_type": "刺伤"
]),
([      "action":"$N忽然张嘴，一口唾沫往$n脸上吐去，发掌击向$n趋避的方位，同时又是一口浓痰吐将过来",
	"dodge": 30,
	"force": 540,
	"damage": 100,
	"weapon" : "浓痰",
	"damage_type": "刺伤"
]),
([      "action":"此时$N所使的招数更是希奇古怪，诡异绝伦，身子时而倒竖，时而直立，忽然一手撑地，身子横挺，一手出掌打向$n$l",
	"dodge": 10,
	"force": 600,
	"damage": 110,
	"damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{ 
	if (usage == "force" || usage == "parry" ) return 1;
	if (usage == "strike") {
		if (this_player()->query_skill("hamagong",1) < 200) {
			message_vision("$N蹲下身来，口中咕咕咕的叫了几声，要将蛤蟆功口诀用在拳脚之上，但无论如何使用不上。\n", this_player() );
			write("你的蛤蟆功火候不足，无法运用它到掌法中。\n");
			return 0;
		}
		return 1;
	}
	return 0;
}

int can_not_hubo() {return 1;}
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hamagong", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        mapping skl; 
        string *sname;
        int v, i, k=0;

       if ( me->query("gender") == "无性" && me->query("hamagong", 1) > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的蛤蟆功。\n");

        i = (int)me->query_skill("hamagong", 1);

        if ((int)me->query_skill("force", 1) < 30
         || (int)me->query_skill("force", 1)/2 < i/3 )
                return notify_fail("你的基本内功火候不足，不能学蛤蟆功。\n");

        if (this_player()->query("tianmo_jieti/times")) 
                return ::valid_learn(me);

        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );

        if(me->query_skill("hamagong", 1) > 99){

                for(v=0; v<sizeof(skl); v++) {
                        if (SKILL_D(sname[v])->check() == "force")
                        k++;  
                }
                if ( k >=3 )
                return notify_fail("你体内不同内力互相冲撞，难以领会更高深的内功。\n");
        }

        if ( me->query("class")=="bonze" )
        {
                if (me->query("gender")=="女性")
                        return notify_fail("小尼姑练蛤蟆功，不怕别人叫你秃头蛤蟆吗？\n");
                if (me->query("gender")=="男性")
                        return notify_fail("大师傅练蛤蟆功，不怕别人叫你秃头蛤蟆吗？\n");
        }

        if ( me->query("family/family_name") == "丐帮" )
                return notify_fail("老叫化的徒弟学不了蛤蟆功。\n");

        if ( me->query("family/family_name") == "武当派")
                return notify_fail("老道练蛤蟆功，不怕别人叫你牛鼻子蛤蟆吗？\n");

       return ::valid_learn(me);
}

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
	int i, level;
	string *power_msg = 
	({
		HIR"$N蹲下身来，运起蛤蟆功，双手平推，吐气扬眉，阁阁阁三声叫喊。这三推之力带有风疾雷迅的猛劲，实是非同小可"NOR,
		WHT"$N阁阁两声怒吼，蹲下身来，呼的双掌齐出，掌力未到，掌风已将地下尘土激起，一股劲风直扑$n面门，势道雄强无比"NOR,
		HIR"$N脸色阴沉，脸颊上两块肌肉微微牵动，两臂弯曲，阁的一声大叫，双手挺出，一股巨力横冲直撞的朝$n推将过来"NOR,
		WHT"$N蹲低身子，口中咕咕咕的叫了三声，双手推出，以蛤蟆功向$n猛攻。$n身周在$P掌力笼罩之下，只激得灰泥弥漫，尘土飞扬"NOR,
	});
	string *reverse_msg = 
	({
		HIM"但见$N招术奇特，怪异无伦，忽尔伸手在自己脸上猛抓一把，忽尔反足在自己臀上狠踢一脚，每一掌打将出来，中途方向必变，实不知打将何处"NOR,
		HIM"$N忽然反手拍拍拍连打自己三个耳光，大喊一声，双手据地，爬向$n，忽地翻身一滚，骤然间飞身跃起，双足向$n连环猛踢"NOR,
		HIM"突然之间，$N俯身疾攻，上盘全然不守，出招怪异无比，将蛤蟆功逆转运用，上者下之，左者右之，招数难以捉摸"NOR,
		HIM"$N全身经脉忽顺忽逆，手上招数虽然走了错道，但是错有错着，出手怪诞，竟教$n差愕难解"NOR,
	});

	level   = (int) me->query_skill("hamagong",1);

	if (me->query_skill_mapped("force") == "hamagong" ) {
		if ( !me->query_temp("hmg_dzjm") && me->query_temp("powerup") && random(me->query_skill("force")) > 250 && me->query("neili") > 1000 && me->query("jiali") > 100)
			return ([
			"action": power_msg[random(sizeof(power_msg))],
			"dodge": 20,
			"parry": 20,
			"force": 650+random(100),
			"damage": 120,
			"damage_type": random(2)?"内伤":"瘀伤"
			]);
		else if ( me->query_temp("reverse") && random(me->query_skill("force")) > 400  && random(me->query_skill("strike")) > 300 && me->query("neili") > 1000 )
			return ([
			"action": reverse_msg[random(sizeof(reverse_msg))],
			"dodge": 100,
			"parry": 100,
			"force": 630+random(100),
			"damage": 120+random(20),
			"damage_type": "瘀伤",
			]);
	}
	if ( me->query_temp("hmg_dzjm") )
		return reverse_action[random(sizeof(reverse_action))];
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if (me->query("family/master_id") != "ouyang feng"
	&& me->query_skill("hamagong", 1) > 99)
		 return notify_fail("蛤蟆功需高人指点才能继续提高。\n");
		 
	if (me->query_temp("weapon"))
		 return notify_fail("蛤蟆从不手持兵刃，所以练蛤蟆功也必须空手。\n");
		 
	if ((int)me->query("jing") < 50)
		return notify_fail("你的精气不够练蛤蟆功。\n");
		
	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够练蛤蟆功。\n");
		  me->add("neili", -30);
		  me->receive_damage("jing", 10);
	if (me->query_skill("hamagong", 1) > 100){
		me->add("neili", -40);
		  me->receive_damage("jing", 20);
	}
	if (me->query_skill("hamagong", 1) > 150){
		  me->add("neili", -20);
		  me->receive_damage("jing", 10);
	}
	if (me->query_skill("hamagong", 1) > 200){
		  me->add("neili", -10);
		  me->receive_damage("jing", 10);
	}
	return 1;
}

string exert_function_file(string func)
{
        return __DIR__"hamagong/exert/" + func;
}

string perform_action_file(string action)
{
	return __DIR__"hamagong/perform/" + action;
}
mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"用头支在地上，双脚并拢，撑向天空。",
"start_self" :HIW"你倒转身体，以头支地，双脚并拢，撑向天空，运起蛤蟆功逆转心法疗伤。\n"NOR,
"on_self" :HIM"你倒运气息，真气逆走，感觉伤势大有起色。\n"NOR,
"start_other" :HIM""+me->name()+"脸色阴沉，头下脚上倒立着，周身上下散布着一股黑气。\n"NOR,
"finish_self" :HIW"你感到全身真气通畅无阻，怪叫一声，猛得跃起。\n"NOR,
"finish_other" :me->name()+"像蛤蟆一样怪叫一声，突然跃起，黑气也随之渐渐散去。\n",
"unfinish_self" :"你正在逆转真气疗伤，突然感到真气乱窜，吓出一身冷汗，只能停了下来。\n",
"unfinish_other":me->name()+"猛然睁开双眼，缓缓站起，但脸色更加阴沉。\n",
"halt_self" :"你将逆走的真气压回丹田，双脚着地，站了起来。\n",
"halt_other" :me->name() +"将黑气吸回体内，站了起来，伤势似乎看上好了不少。\n",
        ]);
}
