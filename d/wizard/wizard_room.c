// Room: /d/wizard/wizard_room.c

inherit ROOM;

void create()
{
	set("short", "��ʦ��Ϣ��");
	set("long", @LONG
��������л���ʦ����Ϣ���ڣ��շ�ˢ��������ǽ���Ϲ�ͺͺ��
ʲô��û�У����ӵ����������һ���ľ�����������һ����ʦ����
��(board)�������������������һЩBUG������������
LONG );

	set("exits", ([ /* sizeof() == 1 */
	 	"down" : __DIR__"guest_room"
	]));
        set("valid_startroom", 1);
	set("no_fight", "1");
	set("no_clean_up", 0);
	setup();

	call_other("/clone/board/wiz_b", "???");
}
void init()
{
        object ob=this_player();
        if ( !wizardp(ob) && wizhood(ob) !="(immortal)" )
        {
                ob->move(__DIR__"guest_room");
                return;
        }
}

