#include <ansi.h>

#include <weapon.h>

inherit WHIP;

void create()
{
        set_name(WHT "��˿��" NOR,({ "rousi suo", "suo", "rousi" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 2000);
                set("long", HIW "һ��ǳ������ϸ˿�������˿��֯������������֮һ��\n" NOR );
                set("wield_msg", HIW "$N" HIW "�ó�һ��$n" HIW "������̯�����������С�\n" NOR );
                set("unwield_msg", HIW "$N" HIW "��$n" HIW "�ջسɾ��Ż����䡣\n" NOR );
        }
        init_whip(30);
        setup();
}
