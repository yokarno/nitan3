// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// /kungfu/class/xueshan/jiumozhi.c 鸠摩智

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("鸠摩智", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "大轮明王" NOR);
        set("long",@LONG
他就是大轮寺的掌门，人称大轮明王的鸠摩智。他对佛法有精深的研究。
身穿一件大红袈裟，头带僧帽。
LONG
        );
        set("title","大轮寺掌门");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);

        set("max_qi", 5800);
        set("max_jing", 2900);
        set("neili", 7100);
        set("max_neili", 7100);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2500000);

        set_skill("force", 470);
        set_skill("xiaowuxiang", 470);
        set_skill("mizong-neigong", 470);
        set_skill("dodge", 440);
        set_skill("shenkong-xing", 440);
        set_skill("parry", 470);
        set_skill("sword", 420);
        set_skill("mingwang-jian", 420);
        set_skill("lamaism", 450);
        set_skill("literate", 420);
        set_skill("strike", 470 );
        set_skill("huoyan-dao", 470);
	set_skill("cuff", 460);
	set_skill("yujiamu-quan", 460);
	set_skill("hand", 470);
	set_skill("dashou-yin", 470);
	set_skill("martial-cognize", 300);
        set_skill("longxiang-gong", 420); 

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
	map_skill("cuff", "yujiamu-quan");

        prepare_skill("strike", "huoyan-dao");
	prepare_skill("hand", "dashou-yin");

        create_family("大轮寺", 1, "掌门");
        set("class", "bonze");

        set("inquiry", ([
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "焚身" : (: ask_me :),
                "天寰神炎" : (: ask_skill :),
        ]));

        set("master_ob", 5);
	setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/huoyan-dao/fen"))
                return "绝技你已经学会了，剩下的就要靠你自己多练习了。";

        if (me->query("family/family_name") != query("family/family_name"))
                return "既然不是我们大轮寺之人，有什么好谈的。";

        if (me->query_skill("huoyan-dao", 1) < 120)
                return "你的火焰刀法修为还不够，等你练好了再说吧！";

        if (me->query("family/gongji") < 300)
                return "你为大轮寺效力不够，这招暂时还不能传你。";                

        message_vision(HIC "$n" HIC "右掌一竖，几路无形刀气袭击向$N"
                       HIC "，$N" HIC "连忙伸手格挡，不禁发现$n"
                       HIC "的内力运用可谓是奥妙无穷！\n" NOR,
                       me, this_object());
        command("simle");
        tell_object(me, HIG "你通晓了焚身的奥妙。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);        
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 90000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/huoyan-dao/fen", 1);
        me->add("family/gongji", -300);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "男性")
	{
        	command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
	}

	if ((string)ob->query("class") != "bonze")
	{
        	command("say 我佛门的清规戒律甚多。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
	}

        if ((string)ob->query("family/family_name") != "大轮寺")
	{
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非本寺弟子，还是请回吧！");
                return;
	}

        if ((int)ob->query_skill("lamaism", 1) < 150) {
                command("say 入我大轮寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("recruit " + ob->query("id"));
	ob->set("title", HIY "法王" NOR);
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if (me->query("can_perform/huoyan-dao/yan"))
                return "你又来干什么？自己下去多练。";

        if (me->query("family/family_name") != query("family/family_name"))
                return "我又不认识你，打听这个干什么？";

        if (me->query_skill("huoyan-dao", 1) < 1)
                return "你连无上火焰刀都没学，哪里来绝招？";

        if (me->query("family/gongji") < 400)
                return "你为大轮寺效力不够，这招暂时还不能传你。";

        if (me->query("shen") > -3000)
                return "你为人太过心软，这招暂时还不能传你。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不足，还学不了这一招。";

        if (me->query("max_neili") < 800)
                return "你的内力修为不足，还是修炼高点再来吧。";

        if (me->query_skill("huoyan-dao", 1) < 80)
                return "等你把火焰刀练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "对$N" HIY "点了点头，喝道：“瞧仔"
                     "细了。”话音刚落，只见$n" HIY "高举手中的刚刀，在"
                     "空中挥舞成盘，气势惊人！便在此时，那柄刚刀已携带"
                     "着震天撞击之声猛然击落。直把$N" HIY "看得目瞪口呆"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 看明白了就自己下去练吧。");
        tell_object(me, HIC "你学会了「天寰神炎」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/huoyan-dao/yan", 1);
        me->add("family/gongji", -400);

        return 1;
}
