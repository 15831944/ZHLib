#include <ansi.h>
#include <armor.h>

inherit "/clone/weapon/bow";

void create()
{
        set_name(HIY "���������" NOR, ({ "panlong gong", "gong", "bow" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("value", 20000);
                set("no_sell", "�ⶫ����ô����ȥ�������̵ģ�");
                set("power", 190000);   // ��������
                set("accuracy", 180);   // ׼ȷ��150%
        }
        setup();
}

