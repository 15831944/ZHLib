// crystal.c ˮ��

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(HIM "ˮ��" NOR, ({ "crystal" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
        else {
	        set("long", HIM "һ���ɫ��ˮ����\n" NOR);
                set("value", 50000);
		set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 100);
                set("armor_prop/personality", 5);
                set("wear_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "��ͷ��ժ��������\n" NOR);
	}
        setup();
}

int query_autoload() { return 1; }