#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name( HIY"�Ͻ���"NOR, ({"zijin zhang", "zhang" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ����Ұ��������ӵ��Ͻ��ȣ���Ŀ���õĹ�â���Ի�����\n");
                set("value", 50000);   
                set("material", "gold");
                set("wield_neili", 400);
                set("wield_maxneili", 600);
                set("wield_str", 22);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(200);
        setup();
 }