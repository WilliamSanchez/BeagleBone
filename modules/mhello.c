#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int datos = 0;

MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("Modulo ejemplo Hello world");
MODULE_PARM(datos,"i");

static __int module_init(void){
  printk("Hello world, parametro %d\n",datos);
  return 0;
}

static void __exit module_exit(void){
  printk("bye world\n");
}

module_init(module_init);
module_exit(module_exit);
