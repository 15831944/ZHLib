// guanyin.c

inherit ITEM;

void create()
{
	set_name("��ӡ", ({ "guan yin", "yin" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "���ǹ�Ա��ӡ�¡�\n");
		set("value", 0);
		set("material", "ivory");
	}
	setup();
} 
