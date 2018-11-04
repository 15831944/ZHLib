// longjia.c �������׵�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "�������׵�" NOR, ({ "longjia dan", "longjia", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "��ҩ�е���Ʒ�����ú󲻵�����ҽ���κ����ˣ�����\n"
                                "��ƽ��һ���������ϵĹ����������ഫ˵�˵�ɢ����\n"
                                "�������������Χ��ʮ��Բ��\n" NOR);
                set("value", 100000);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat �������׵� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;

        if (me->query("skybook/item/longjia"))
        {

        	message_vision(HIW "$N" HIW "һ������������һ���������׵���ֻ��$P"
                               HIW "����һ�������϶�ð����������\n" NOR, me);

        	me->add("combat_exp", 10000 + random(5000));
        	me->add("potential", 1000);

        	mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	me->improve_neili(50);
        	me->set("skybook/item/longjia", 1);        	

	}
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}