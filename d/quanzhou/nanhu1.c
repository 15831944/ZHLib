// Room: /d/quanzhou/nanhu1.c
// Date: May 21, 96   Jay

inherit ROOM;

void init();
int do_out();

void create()
{
	set("short", "�����Ϻ�");
	set("long", @LONG
�������̲��������Ϻ������ϼ�ֻ�������ε������ϵ��οͺ�
��¥Ů������Ц����ˮ���û�д��Ƕɲ���ȥ�ġ�����֪��˭��
���׶���һЩľ׮��׮��Ǳ��ˮ��֮��һ����ĵط�����ʹ�ǲ���
�Ṧ��������ȥҲ����ˮ��Ư�����ӡ�
LONG );
	set("exits", ([
		"south"     : __DIR__"yanyu",
                "northwest" : __DIR__ "nanhu",
	]));
	set("outdoors", "quanzhou");
	setup();
}
