
inherit ROOM;

string* books = ({
	"/clone/book/yljing",
	"/clone/book/yljing1",
	"/clone/book/yljing2",
	"/clone/book/book-bamboo",
	"/clone/book/book-silk",
	"/clone/book/book-stone",
	"/clone/book/book-iron",
	"/clone/book/quanpu",
});

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǲ�������ǽ��һ����ܣ������˸���ȭ�ס��鼮��ǽ����һ��ľ����
��ػ��ܶ����½��ϳ�����������顢��Ϣ��
LONG );
	set("exits", ([
		"west" : __DIR__"dating",
	]));
        set("sleep_room", 1);   
	set("objects", ([
		books[random(sizeof(books))] : 1,
		books[random(sizeof(books))] : 1,
		books[random(sizeof(books))] : 1,
		books[random(sizeof(books))] : 1,
	]));
	setup();
	replace_program(ROOM);
}