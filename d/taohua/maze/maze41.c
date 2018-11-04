// Code of ShenZhou
// Room: 
// Date: 

inherit ROOM;

#include "/d/taohua/maze/maze.h"


void create()
{
	set("short", "ʯ��");
	set("long", @LONG
����һ����ԼĪ���˶�ߵĴ�ʯ�鹹�ɵ���ʯ�󣬹�ģ�ƺ�����
��̧����ȥ�����ܾ������ص�������Ᾱ�ʯ����ȫ��������·ͨ��ʯ��
֮�⣬��֮���г�������������������������ͷ����ʯ������һ��б��
��ʯ��(shibei)�������ڸ����С�
LONG
	);

	set("exits", ([
		"east" : __DIR__"maze27",
		"south" : __DIR__"maze19",
		"west" : __DIR__"maze52",
		"north" : __DIR__"maze60",
	]));

	set("item_desc", ([
	"shibei" : "
���������ڣ�Ԫ�����޾̣����꣬����������  ��֮�ã�������������
�������ţ������������޾̣�����֮��
�����Ŷ������꣬���ף�������֮��
���������������У�����һ�ˣ�һ���У�������ѡ�
�������ģ����伲��ʹ����ϲ���޾̡�
�������壺����֮��ʮ��֮�긥��Υ��Ԫ����
�����Ͼţ�������֮���޾̣��꼪�������������ó��޼ҡ�
\n",
	]));

	set("cost", 10);
	setup();
}

void init()
{
	object me;
	me = this_player();
	
	me->add_temp("taohua/count", 41);
	check_count(me, 41);
	return;
}