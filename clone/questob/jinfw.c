// jinfw.c

inherit ITEM;

void create()
{
	set_name("����", ({ "jin fanwu", "fanwu" }));
	set_weight(1600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("no_sell", "��...����ʲô�������ҿɲ���Ҫ��\n");
		set("long", "�ƽ����ķ��룬����֮�������滹���ż����֡�\n");
		set("value", 0);
		set("material", "gold");
	}
	setup();
}