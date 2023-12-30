/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#define MODULE_NAME "lksu"
#define pr_fmt(fmt) MODULE_NAME ": " fmt

#include "lksu.h"
#include "hidden.h"
#include "hooks.h"
#include "tables.h"
#include "token.h"

#include <linux/module.h>
#include <linux/printk.h>

static __init int
lksu_init(void)
{
    int retval;

    retval = lksu_token_init();
    if (retval)
        return retval;

    retval = lksu_tables_init();
    if (retval)
        return retval;

    retval = lksu_hidden_init();
    if (retval)
        return retval;

    retval = lksu_hooks_init();
    if (retval)
        return retval;

    return 0;
}

static __exit void
lksu_exit(void)
{
    lksu_hooks_exit();
    lksu_hidden_exit();
    lksu_tables_exit();
    lksu_token_exit();
}

module_init(lksu_init);
module_exit(lksu_exit);

MODULE_AUTHOR("John Sanpe <sanpeqf@gmail.com>");
MODULE_DESCRIPTION("Linux Kernel SU");
MODULE_LICENSE("GPL v2");
