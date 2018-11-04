// qingfu-shenfa.c ������
// pal 1997.05.26

inherit SKILL;

string *dodge_msg = ({
        "ֻ��$nһ�С�������֦�����ڿն������嵹�ң������$N��һ�С�\n",
        "$n˫��������һ�죬��ǰһ����һ�С�����չ������������Ʈ�������$N�Ĺ�����\n",
        "$n������������һ�ģ�һ���������ڿա����������ҵ�����Ʈ��$N��֪����η�ֻ���ջ����ơ�\n",
        "$n���˷�����һ�С�������Ӱ���ƹ�$N�Ĺ��ƣ�Ʈ��$N�����ᡣ\n",
        "$n����һЦ��һʽ��ҹ���̿ա�����������������ǡ�ñܹ�$N�Ľ�����\n",
	"$n���Ӻ�������������˳�������һ����������Ȼ��$N�������һȦ����һ��ֱ�Ƿ�����˼��\n",
	"$n�ƺ�������ҫ���򣬾���Զ�ߣ�������$N����Ȧ�ӡ�$Nʹ�����У�ȴʼ�մ򲻵�������ϡ�\n",
	"$n�ߵû�ɳ���һ·�������������ͣ�����һ����ʮ�ɵĴ��������ʱ��$n����Ӱ��ס�ˡ�\n",
	"$nһ���������������ı���������һֻ�������Ʈ��������\n",
});

int valid_enable(string usage)
{
	return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 50 )
                return notify_fail("�������̫���ˣ���������������\n");

        if( (int)me->query("neili") < 40 )
                return notify_fail("���������������������\n");

        me->receive_damage("qi", 40);
        me->add("neili", -15);
        return 1;
}
