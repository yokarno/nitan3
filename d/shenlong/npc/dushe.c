// dushe

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("毒蛇", ({ "dushe" }) );
	set("long", "一支昂首吐信的毒蛇正虎视眈眈地盯著你。\n");

	set("race", "蛇类");
	set("age", 3);
	set("attitude", "peaceful");

	set("max_ging", 80);
	set("max_qi", 80);

	set("str", 10);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"   : 80,
                "remain"  : 20,
                "maximum" : 20,
                "perhit"  : 10,
                "supply"  : 1,
        ]));

	set_temp("apply/attack", 10);
	set_temp("apply/damage", 10);
	set_temp("apply/armor", 10);

	set("combat_exp", 8000);
	setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="dushe") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N左手按住毒蛇的头，右手轻抚其七寸，口中念念有词，片刻间将蛇化为一根蛇杖。\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}
