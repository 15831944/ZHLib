inherit SKILL;

string *dodge_msg = ({
        "ֻ��$n��Хһ�����������ϱ�ֱ���������࣬�����$N��һ�С�\n",
        "$n����Ʈ���������ޱȣ��������һ�ݣ����ѱܿ���\n",
        "ֻ��$n��������ת����ͬˮ��һ�㣬ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$n�ŵ�һ���ͷ�������һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�����ڶ����㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
        "$n����Ծ���ڰ����һ������������һ�Σ��о����յرܿ���$N��һ�С�\n"

});

int valid_enable(string usage) 
{ 
        return (usage == "dodge"); 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˣ�������ϰ�����귭��\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������̫���ˣ�������ϰ�����귭��\n");

        me->receive_damage("qi", 50);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shexing-lifan/" + action;
}

