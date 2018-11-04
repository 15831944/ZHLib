inherit ROOM;
inherit "/clone/newitem/newitems.c";
inherit "/clone/newitem/newitemname.c";
#include <ansi.h>
string* file=({"/clone/newitem/newweapon/sword.c",	"/clone/newitem/newweapon/blade.c",
		"/clone/newitem/newweapon/stick.c",
		"/clone/newitem/newweapon/whip.c",
		"/clone/newitem/newweapon/hammer.c",
		"/clone/newitem/newweapon/staff.c",
                "/clone/newitem/newweapon/axe.c"});
mixed* name=({
({YEL"��ͭ","bronz",50,3500,2000,50,3,0,3,200,100,20,500,500,1}),
({HIC"����","steel",75,2500,5000,60,4,0,3,500,120,21,600,600,2}),
({HIB"����","iron",100,3000,15000,75,5,1,3,1000,150,22,800,800,3}),
({HIY"�ڽ�","gold",150,4000,25000,95,6,1,4,4000,200,23,1000,1000,4}),
({HIG"����","jade",200,2000,50000,120,7,2,4,10000,280,24,1500,1500,5}),
({HIR+BLK"����","xianling",250,2000,100000,140,8,2,5,25000,350,24,2000,2000,6}),
({HIW"����","datang",250,2000,200000,160,9,3,5,40000,450,24,2500,2500,7})
		});
string *file2=({
"/clone/newitem/newarmor/armor.c",
"/clone/newitem/newarmor/boots.c",
"/clone/newitem/newarmor/cloth.c",
"/clone/newitem/newarmor/finger.c",
"/clone/newitem/newarmor/hands.c",
"/clone/newitem/newarmor/head.c",
"/clone/newitem/newarmor/neck.c",
"/clone/newitem/newarmor/shield.c",
"/clone/newitem/newarmor/surcoat.c",
"/clone/newitem/newarmor/waist.c",
"/clone/newitem/newarmor/wrists.c"});
mixed *name2=({
({HIG"����","mammoth","60/110",4000,30000,"20/45","15/10/20","5/0/3","5/0/3","5/0/3","5/0/3","",2,1000,5}),
({HIR+BLK"�ڽ�","gold","20/50",2500,5000,"15/30","15/5/15","40/5/15","40/5/15","40/5/15","40/5/15","10/5",1,100,2}),
({CYN"����","crocodile","50/100",3000,10000,"15/35","15/8/15","5/0/2","5/0/2","5/0/2","5/0/2","",2,200,3}),
({HIM"����","jade","30/60",2500,20000,"20/40","15/8/20","40/10/15","40/8/15","40/8/15","40/8/15","10/6",2,500,4}),
({HIG"����","mammoth","60/110",4000,30000,"20/45","15/10/20","5/0/3","5/0/3","5/0/3","5/0/3","",2,1000,5}),
({YEL"����","amber","40/80",2000,40000,"25/50","15/10/25","40/8/20","40/8/20","40/8/20","40/8/20","10/7",2,2000,6}),
({MAG"����","kylin","80/120",2500,60000,"25/55","15/10/25","5/0/3","5/0/3","5/0/3","5/0/3","",3,4000,7}),
({HIM"���","emerald","50/80",2000,80000,"30/60","15/10/30","40/8/16","40/8/16","40/8/16","40/8/16","10/8",3,6000,8}),
({HIC"����","dragon","100/150",2500,100000,"30/65","15/10/30","5/1/3","5/1/3","5/1/3","5/1/3","",3,10000,9}),
({HIY"ˮ��","crystal","60/100",1500,120000,"35/70","15/10/35","40/10/22","40/10/22","40/10/22","40/10/22","10/9",3,15000,10}),
({HIR"ս��","mars","120/170",3000,140000,"35/75","15/10/35","5/1/4","5/1/4","5/1/4","5/1/4","",4,20000,11}),
({HIB"���","spirit","80/120",1000,160000,"40/80","15/15/35","40/10/25","40/10/25","40/10/25","40/10/25","10/10",4,25000,12}),
({HIW"�޵�","sunshine","150/250",2000,180000,"40/85","15/15/40","5/2/4","5/2/4","5/2/4","5/2/4","",5,30000,13}),
({HIR+BLK"����","dark","100/150",1000,200000,"45/90","15/15/40","40/10/30","40/10/30","40/10/30","40/10/30","10/11",5,35000,14})
});
mapping tianfu1=([
               "str":"���",
              "int":"����",
               "per":"��ò",
             "kar":"��Ե",
               ]);

mapping tianfu2=([
              "con":"����",
               "dex":"��",
               "per":"��ò",
             "kar":"��Ե",
            ]);
void create ()
{
  set("short",HIY"�׸�"NOR);
  set ("long","�׸ס�����Ҫ��װ��,���忴(words)\n");
set("exits", ([ "kz" : "/d/city/kezhan","xzg": "/u/workroom",]));        
//set("no_time", 1);set("no_magic", 1);        
set("item_desc",(["words" : "nweapon <����1> <����2> ��������������,����1Ϊ�������࣬ȡֵ0-10,����2
Ϊԭ�ϣ�ȡֵ0-6��\n\n narmor <����1> <����2> �����·��ߣ�����1Ϊ�������࣬ȡֵ0-10,����2Ϊԭ�ϣ�ȡֵ
0-13�������������ԣ��Ҿ����д���£�newitemname������ģ�û����ѡ�۵ġ��м��һЩ����������max_level
��Ҳû��skills,����Ϊ1000�ˣ������ĺ�get_armor(),get_weapon()����һ������Ӱ����ԣ��Ǻǡ��� \n ",
]));
set("valid_startroom", 1);setup();
}
void init ()
{
 add_action ("do_nweapon", "nweapon");
add_action ("do_narmor", "narmor");
}
int do_nweapon(string arg)
{
object me,weapon;
int i,j,l,value,max_level=1000;
string att;
me=this_player();
if(!arg || sscanf(arg, "%d %d", i,l)!=2)
 return notify_fail("��ʽ���ԣ���look words!\n");
if(i>9)
return notify_fail("�����б��11�֣����С��11��\n");
if(l>6)
return notify_fail("ԭ���б��7�֣����С��7��\n");
weapon=new(file[i]);

weapon->set("changed",1);
weapon->set("unbreak",1);
weapon->set_name(name[l][0]+weapon->query("name")+NOR,({name[l][1]+" "+weapon->query("id"),weapon->query("id")}));
weapon->set("durability/max",name[l][2]+random(name[l][2]));
 weapon->set("durability/now",random(name[l][2]));
weapon->set_weight((name[l][3]+weapon->query_weight())/2);
switch(l)
{ case 0: att="������ͭ�Ƴɵġ�\n";break;
  case 1: att="���ɰ��������ɵġ�\n";break;
case 2: att="����ǧ�꺮�����ɵġ�\n";break;
case 3: att="���������ڽ����ɵġ�\n";break;
  case 4: att="�����Ϲ��������ɵġ�\n";break;
case 5: att="���ɴ�˵�е�����֮ʯ���ɵġ�\n";break;
case 6: att="���ɴ�˵�еĴ�������̫��֮ʯ���ɵġ�\n";break;
}
weapon->set("long",HIG+weapon->query("long")+att+NOR);
 weapon->set("material", name[l][1]);
weapon->set("grade", name[l][14]);
weapon->set("weapon_prop/damage",name[l][5]+name[l][5]*random(20)/100);//������
         weapon->set("weapon_prop/luck",random(name[l][7]+1));//����ֵ�������еĴ���
          weapon->set("sockets/max",random(name[l][8]));//���ű�ʯ��
          weapon->set("sockets/now",0);
j=random(5);
 switch(j)
        {
                 case  0: att="cold_attack";break;
                case  1:att="fire_attack";break;
                 case  2:att="lightning_attack";break;
              case  3:att="poison_attack";break;
                 case  4:att="wind_attack";break;
                 default:att="";
         }
if (att!="") //ħ������
          {                       
                max_level=name[l][6]-random(3);//��ߵȼ�
                  if (max_level<1) max_level=1;
                 weapon->set((att+"/max_level"),max_level);
                 weapon->set("weapon_prop"+"/"+att,1);//��ǰ�ȼ�
               weapon->set((att+"/exp"),0);//����ֵ
        }
value=name[l][4];
         value+=weapon->query("durability/max")*50;
         value+=weapon->query("durability/now")*25;
         value+=weapon->query("weapon_prop/luck")*20000;
         value+=weapon->query("sockets/max")*2500;
         value+=weapon->query("cold/max_level")*2500;
        value+=weapon->query("fire/max_level")*2500;
        value+=weapon->query("lightning/max_level")*2500;
         value+=weapon->query("poison/max_level")*2500;
        value+=weapon->query("wind/max_level")*2500;
        weapon->set("value", value*(i+1));
weapon->set("weapon_wiel/exp",name[l][9]);
          weapon->set("weapon_wiel/skill",name[l][10]);
               if(random(2))
             weapon->set("weapon_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
              else 
                weapon->set("weapon_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));

         weapon->set("weapon_wiel/max_qi",name[l][12]);
        weapon->set("weapon_wiel/max_jing",name[l][13]);
 weapon->set("bind_type",3);
 weapon->set("bind_id",getuid(me));
setname_weapon(weapon);
message_vision("$N����ǽ������....���������....,���һ��һ��װ�������ڵ���!\n", me);
if (wizardp(this_player()))
tell_object(this_player(),HIM+"���ͣ�"+weapon->query("skill_type")+"     ��ʼ�ȼ���"+weapon->query("grade")+"\n"NOR);
       weapon->move(environment(me));

  return 1;
}
int do_narmor(string arg) {
object armor;
object me;
int i,j,l,value,a1,a2,a3;
string att;
me=this_player();
if(!wizardp(me))
return notify_fail("�����ף�������ʦ�\n");
if(!arg || sscanf(arg, "%d %d", i,l)!=2)
 return notify_fail("��ʽ���ԣ���look words!\n");
if(i>10)
return notify_fail("�����б��11�֣����С��11��\n");
if(l>13)
return notify_fail("ԭ���б��14�֣����С��14��\n");
armor=new(file2[i]);
armor->set("changed",1);	
armor->set("unbreak",1);
armor->set_name(name2[l][0]+armor->query("name")+NOR,({name2[l][1]+" "+armor->query("id"),armor->query("id")}));
sscanf (name2[l][2], "%d/%d", a1, a2) ;
		
armor->set("durability/max",a1+random(a2-a1));
armor->set("durability/now",random(a2));	
armor->set_weight((name2[l][3]+armor->query_weight())/2);        	
armor->set("long",armor->query("name"));        	
armor->set("material", name2[l][1]);
armor->set("grade", name2[l][14]);
sscanf (name2[l][5], "%d/%d", a1, a2) ;
armor->set("armor_prop/armor",a1+random(a2-a1));       	
//armor->set("armor_prop/luck",random(name2[l][7]+1));
if (sscanf (name2[l][6], "%d/%d/%d", a1, a2,a3)==3) {
if (random(200)<=a1) armor->set("armor_prop/cold_defence",a2+random(a3-a2));
if (random(200)<=a1) armor->set("armor_prop/fire_defence",a2+random(a3-a2));//��ϵ����
if (random(200)<=a1) armor->set("armor_prop/lightning_defence",a2+random(a3-a2));//��ϵ����
if (random(200)<=a1) armor->set("armor_prop/poison_defence",a2+random(a3-a2));//��ϵ����
if (random(200)<=a1) armor->set("armor_prop/wind_defence",a2+random(a3-a2));//��ϵ����
        	}
switch(random(3))
{
case 0 : armor->set("armor_prop/cold_defence",5+random(5));
        			armor->set("armor_prop/fire_defence",5+random(5));
        			armor->set("armor_prop/lightning_defence",5+random(5));
        			armor->set("armor_prop/poison_defence",5+random(5));
                                armor->set("armor_prop/wind_defence",5+random(5));
break;
case 1:armor->set("armor_prop/cold_defence",5+random(10));armor->set("armor_prop/fire_defence",5+random(10));
armor->set("armor_prop/lightning_defence",5+random(10));
        			armor->set("armor_prop/poison_defence",5+random(10));
                                armor->set("armor_prop/wind_defence",5+random(10));
        			break;	
        		case 2 :
        			armor->set("armor_prop/cold_defence",5+random(15));
        			armor->set("armor_prop/fire_defence",5+random(15));
        			armor->set("armor_prop/lightning_defence",5+random(15));
        			armor->set("armor_prop/poison_defence",5+random(15));
                                armor->set("armor_prop/wind_defence",5+random(15));

break;
        	}
if (sscanf (name2[l][11], "%d/%d", a1, a2)==2)
if (random(1)<=a1) armor->set("armor_prop/chance",random(a2));//ħ��װ�������       	
        	armor->set("sockets/max",random(name2[l][12]));//���ű�ʯ��
        	
 armor->set("bind_type",3);
 armor->set("bind_id",getuid(me));
armor->set("sockets/now",0);
value=name2[l][4];
value+=armor->query("durability/max")*50;
value+=armor->query("durability/now")*25;
value+=armor->query("sockets/max")*2000;
value+=armor->query("armor_prop/armor")*100;
value+=armor->query("armor_prop/cold_defence")*100;
value+=armor->query("armor_prop/fire_defence")*100;
value+=armor->query("armor_prop/lightning_defence")*100;	value+=armor->query("armor_prop/poison_defence")*100;
        	value+=armor->query("armor_prop/magic_defence")*100;        	
        	value+=armor->query("armor_prop/chance")*500;
armor->set("value", value);
armor->set("armor_wiel/exp",name2[l][13]);
if(random(2))
armor->set("armor_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
else 
armor->set("armor_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));
setname_armor(armor);
message_vision("$N����ǽ������....���������....,���һ��һ��װ�������ڵ���!\n", me);
if (wizardp(this_player()))
tell_object(this_player(),HIM+"���ͣ�"+armor->query("armor_type")+"     ��ʼ�ȼ���"+armor->query("grade")+"\n"NOR);
armor->move(environment(me));
return 1;}
