// shuang.c 国士无双
// Created by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "国士无双" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者城府极深，善于隐藏自己的特性，\n"
                           "让人揣摩不透。此天性者无论修炼何种武\n"
                           "功，均不考虑武功中关于天性的限制。\n");
}


