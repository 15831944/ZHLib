// qiankun-danuoyi.c Ǭ����Ų��
// by King 97.05

inherit SKILL;

#include <ansi.h>

string *parry_msg = ({
        "$Nһ�л���$n���ϣ�ȴ��$n����Ǭ����Ų�ƣ�����������������¡�\n",
        "$n����һ����$N�����Լ������ػ��������ŵ������˼�����\n",
        "$n�ֱۻ�ת����$N����������һ�ƣ�$N������ա�\n",
        "$n�����������$N����������һ����$N���Ʋ�ס��ֱ��ǰ��ȥ��\n",
        "$n���β�����$Nһ�л��£�����ʯ���󺣣�������ס�ˡ�\n",
        "$n��ǣ������$N��������������ת�˺ü���Ȧ��\n",
        "$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n",
        "$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});

string *dodge_msg = ({
        "$Nһ�л���$n���ϣ�ȴ��$n����Ǭ����Ų�ƣ�����������������¡�\n",
        "$n����һ����$N�����Լ������ػ��������ŵ������˼�����\n",
        "$n�ֱۻ�ת����$N����������һ�ƣ�$N������ա�\n",
        "$n�����������$N����������һ����$N���Ʋ�ס��ֱ��ǰ��ȥ��\n",
        "$n���β�����$Nһ�л��£�����ʯ���󺣣�������ס�ˡ�\n",
        "$n��ǣ������$N��������������ת�˺ü���Ȧ��\n",
        "$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n",
        "$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});

int can_not_hubo() {return 1;}
int valid_enable(string usage)
{
        return usage == "parry";
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int layer;

        if (me->query("gender") == "����" &&
            me->query_skill("qiankun-danuoyi", 1) >= 50)
                return notify_fail("����ͼ�����ķ�������Ų�ƣ�ȴ"
                                   "��������һ����ã�����Լ�����\n");

        if (me->query_skill("shenghuo-xuanming",1) < 0)
                {
                me->delete_skill("qiankun-danuoyi");
                return notify_fail("Ǭ����Ų�Ʊ�����ʥ����ڤ�ڹ���ϲ���������\n");
                }

        if (me->query_condition("qiankun-except"))
                return notify_fail("������������������֫�Ժ������"
                                   "����޷����������񹦡�\n");

        layer = (int)me->query_skill("qiankun-danuoyi", 1) / 50;
        if (layer > 7) layer = 7;

        if (me->query("int") < 22 + layer)
                return notify_fail("����õ�" + chinese_number(layer) +
                                   "��Ǭ����Ų��ʵ��������ޱȣ�ȫȻ�޷���⡣\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("�������̫��޷�����Ǭ����Ų�ơ�\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹����޷���ǿ����Ǭ����Ų�ơ�\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("��Ļ����мܻ�����ޣ��޷����������Ǭ����Ų�ơ�\n");

        if ((int)me->query_skill("shenghuo-xuanming", 1) < 500 &&
            (int)me->query_skill("shenghuo-xuanming",1) <= (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("���ʥ����ڤ������ޣ��޷����������Ǭ����Ų�ơ�\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("��Ļ����ڹ�������ޣ��޷����������Ǭ����Ų�ơ�\n");

        return 1;
}

mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int) me->query_skill("qiankun-danuoyi", 1) < 100)
        return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;
        dp = target->query_skill("force");
        ap = me->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -30);
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;
                result = ([ "damage": -damage,
                            "msg"   : msg ]);
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("Ǭ����Ų��ֻ��ͨ��ѧϰ���ж�Ǭ����Ų���ķ���ߡ�\n");
}

string perform_action_file(string func)
{
        return __DIR__"qiankun-danuoyi/" + func;
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        layer = lvl / 50;
        if (layer > 7) layer = 7;

        if (! layer)
        {
                tell_object(me, HIM "��Ǳ������Ǭ����Ų"
                            "���ķ�����������\n" NOR);
        } else
        if ((lvl % 50) == 0)
        {
                tell_object(me, HIM "���������˵�" + chinese_number(layer) +
                            "���Ǭ����Ų���ķ���\n" NOR);
        } else
                tell_object(me, HIM "��Ե�" + chinese_number(layer) +
                            "���Ǭ����Ų���ķ��ּ�����һ���˽⡣\n" NOR);

        if (lvl < 500 && lvl > me->query_skill("force") * 2 / 3)
        {
                if (lvl < me->query_skill("force") * 2 / 3 + 10)
                {
                        tell_object(me, HIG "�������Ϣһ�����ң�����ʱ��ʱ�ȣ����ɵô��һ����\n"
                              "����Ī�����߻���ħ����Ȼ����õ���Խ��Խ�Ǻ��䣬��Ϊ���ܡ�\n" NOR);
                        message("vision", HIG + me->name() + HIG "����ɫ�����"
                                "�̣���ò�ͣ��ֻ�ǻ���������ƺ�ʮ��ʹ�ࡣ\n" NOR,
                                environment(me), ({ me }));
                        return;
                }

                tell_object(me, HIB "���Ȼ���õ�������һ���⣬��ʱ����֫"
                      "����һ���ú����ޱȣ��̲�ס����������\n" NOR);
                message("vision", HIB + me->name() + HIB "��Ȼһ"
                        "������ɫ��Ȼ��òҰף���Ȼ������һ��������������ֹ��\n" NOR,
                        environment(me), ({ me }));
        } else
        if (lvl < 350 && (lvl * 20 + 4000) > me->query("max_neili"))
        {
                if ((lvl * 20 + 4000) < me->query("max_neili") + 200)
                {
                        tell_object(me, HIR "��������ת��һ����Ϣ��һʱ������"
                              "�����ã��������ǲ�ҪóȻ������Ų���񹦡�\n" NOR);
                        return;
                }

                tell_object(me, HIR "��������ת��һ����Ϣ����Ȼ����һ����"
                      "��Ȼת����������ʱ���н�ʹ���������˼�����Ѫ��\n" NOR);
                message("vision", HIR + me->name() + HIR "��ɫ��Ȼ"
                        "һ�䣬Ż��������Ѫ����Ŀ���ġ�\n" NOR,
                        environment(me), ({ me }));
        } else
                return;

        me->apply_condition("qiankun-except", lvl + (int)me->query_condition("qiankun-except"));
}

