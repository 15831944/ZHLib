#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC"����"NOR+HIY"��ũ��"NOR, ({"qinglong dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_sell", "�������������뿪�㡣\n");
                set("no_put", "�����������ܷ����Ƕ���\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_steal", "�������������뿪�Ƕ���\n");
                set("no_beg", "�������������뿪�Ƕ���\n");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if (time() - me->query_temp("last_eat/dan(S)") < 600)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(S)", time());

        message_vision(HIC
"    $N����һ��������ũ����ֻ��ȫ�������������, ����ԴԴ���ϵ�ӿ�뵤��, ˵\n"
"������������á���ʱ�е���̨�������һ��ƽ��, ������ѧ����ѧ֪ʶһһӿ����\n"
"ͷ, ����̨�����ڹ�ͨ��$N�е��ľ����Ǳ������һ���Ľ�չ��\n"NOR,me);
        me->set("jingli",me->query("max_jingli"));
        me->set("neili",me->query("max_neili"));
        me->add("combat_exp", 350);
        me->add("potential", 350);

        if (me->query("potential") > me->query_potential_limit()) 
        me->set("potential", me->query_potential_limit()); 

        me->start_busy(2);
        destruct(this_object());
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}

